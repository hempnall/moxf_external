//
//  midi_message.cpp
//  rtmidi_test
//
//  Created by James Hook on 28/02/2018.
//  Copyright © 2018 James Hook. All rights reserved.
//


#include "midi_message.h"
#include <cassert>
#include <algorithm>

midibyte_t sysex_header[] { 0xF0, 0x43, 0x00, 0x7F, 0x1C };
midibyte_t sysex_footer[] { 0xF7 };
#define SYSEX_DATA_OFFSET 0x0b

bool assert_sysex_header_and_footer(   const midimessage_t& msg )
{
    
    if ( !std::equal(msg.begin(), msg.begin() + 5, sysex_header ) ) return false;
    return sysex_footer[0] == *msg.rbegin();
}

uint16_t get_midi_value( const midimessage_t& msg ,  size_t offset , size_t midi_offset = 0 )
{
    size_t actual_offset = offset + midi_offset;
    assert( msg.size() > actual_offset);
    midibyte_t high_order = msg[actual_offset];
    midibyte_t low_order = msg[actual_offset+1];
    return (high_order << 8) + low_order;
}

midibyte_t get_midi_byte( const midimessage_t& msg ,  size_t offset  , size_t midi_offset = 0 )
{
    
    size_t actual_offset = offset + midi_offset;
    assert( msg.size() >= actual_offset);
    midibyte_t low_order = msg[actual_offset];
    return  low_order;
}




size_t get_sysex_size( const midimessage_t& msg )
{
    if (msg.size() < 10) return 0;
    return get_midi_value(msg, 5);
}



double get_message_with_sleep(RtMidiIn& in , uint8_t sleep_time, size_t sz , midimessage_t *msg  )
{
    bool done = false;
    
    while (!done) {
        double stamp = in.getMessage( msg );
        int nBytes = msg->size();
        if (0 < nBytes) {
            //std::cout << "received " << nBytes << " bytes (expected " << sz  << ")\n";
            assert(  sz == nBytes || ( sz + 1  == nBytes ));
            //dump_midi_message(*msg);
            return stamp;
        }
        SLEEP(sleep_time);
    }
    return 0;
}

void parse_bulk_dump(RtMidiIn& in ,  partfilter_t filt , part_callback_fn part_callback, arp_callback_fn  arp_callback  )
{
    bool return_all_channels = ( filt == 0 );
    partfilter_t selected_channel = filt - 1;
    
    if (!is_port_open( in )) return;
    in.ignoreTypes(false);
    
    bool done = false;
    double stamp;
    int nBytes ,i ;
    midimessage_t message;

    std::cout << "waiting for first message..";
    stamp = get_message_with_sleep(in,10, 13, &message);
    
    // process bulk header
    
    // common::common
    stamp = get_message_with_sleep(in, 10, 93, &message);
    
    // common::reverb
    stamp = get_message_with_sleep(in, 10, 51, &message);

    // common::chorus
    stamp = get_message_with_sleep(in, 10, 53, &message);
    
    // common::insertion_a
    stamp = get_message_with_sleep(in, 10, 49, &message);
    
    // common::insertion_b
    stamp = get_message_with_sleep(in, 10, 49, &message);
    
    // common::master_eq
    stamp = get_message_with_sleep(in, 10, 33, &message);
    
    // common::master_effect
    stamp = get_message_with_sleep(in, 10, 51, &message);
    
    // common::arp common
    stamp = get_message_with_sleep(in, 10, 27, &message);
    
    for (midi_channel_t pp = 0 ; pp < 16 ; ++pp ) {
        stamp = get_message_with_sleep(in, 10, 75, &message);
        part_callback_fn cb = ( return_all_channels || pp == selected_channel ) ? part_callback : nullptr;
        if (return_all_channels || pp == selected_channel) {
            parse_part_message(message, pp + 1, cb);
        }
    }
    
    for (midi_channel_t pp = 0 ; pp < 16 ; ++pp ) {
        stamp = get_message_with_sleep(in, 10, 85, &message);
        arp_callback_fn cb = ( return_all_channels || pp == selected_channel ) ? arp_callback : nullptr;
        if (return_all_channels || pp == selected_channel) {
            parse_arp_message(message, pp + 1 , cb);
        }
    }
    
    // audio part
    stamp = get_message_with_sleep(in, 10, 21, &message);
    
    // bulk footer
    stamp = get_message_with_sleep(in, 10, 13, &message);
}


void parse_arp_message( const midimessage_t& msg ,midi_channel_t chn , arp_callback_fn fn)
{
    if (fn == nullptr) return;
    assert_sysex_header_and_footer(msg);
    size_t sz = get_sysex_size(msg);
    assert( sz == 0x4c);
    
    arp_information_38_00 info;
    info.arp_switch = get_midi_byte(msg,SYSEX_DATA_OFFSET, 0);
    info.arp_midi_out_switch = get_midi_byte(msg,SYSEX_DATA_OFFSET ,1);
    info.arp_transmit_channel = get_midi_byte(msg, SYSEX_DATA_OFFSET,2);
    
    
    fn( chn , &info);
    
}


void parse_part_message( const midimessage_t& msg ,midi_channel_t chn , part_callback_fn fn)
{
    if (fn == nullptr) return;

    assert_sysex_header_and_footer(msg);
    size_t sz = get_sysex_size(msg);
    assert( sz == 0x42);
    part_information_36_00 info;
    info.volume = get_midi_byte(msg,SYSEX_DATA_OFFSET, 0x0e);
    info.pan = get_midi_byte(msg, SYSEX_DATA_OFFSET,0x0f);
    info.detune = get_midi_value(msg,SYSEX_DATA_OFFSET, 0x10);
    info.bank_select_msb = get_midi_byte(msg,SYSEX_DATA_OFFSET, 0x01);
    info.bank_select_lsb = get_midi_byte(msg,SYSEX_DATA_OFFSET, 0x02);
    info.program_number = get_midi_byte(msg,SYSEX_DATA_OFFSET, 0x03);
    info.receive_channel = get_midi_byte(msg,SYSEX_DATA_OFFSET, 0x04);
    
    fn(chn,&info);
}



std::ostream& operator << ( std::ostream& ostr , const part_information_36_00& part_info)
{
    ostr << "[part_info {";
    ostr << "volume: " << (int) part_info.volume;
    ostr << ",pan: " << (int)part_info.pan;
    ostr << ",detune: " << (int)part_info.detune;
    ostr << ",bank_select_msb: " << (int)part_info.bank_select_msb;
    ostr << ",bank_select_lsb: " << (int)part_info.bank_select_lsb;
    ostr << ",program_number: " << (int)part_info.program_number;
    ostr << ",receive_channel: " << (int)part_info.receive_channel;
    ostr << "}]";
    return ostr;
}

std::ostream& operator << ( std::ostream& ostr , const arp_information_38_00& arp_info)
{
    ostr << "[arp_info {";
    ostr << "arp_switch: " << (int)arp_info.arp_switch;
    ostr << ",arp_midi_out_switch: " << (int)arp_info.arp_midi_out_switch;
    ostr << ",arp_transmit_channel: " << (int)arp_info.arp_transmit_channel;
    ostr << "}]";
    return ostr;
}
