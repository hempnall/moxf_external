//
//  moxf_interface.cpp
//  max-external
//
//  Created by James Hook on 01/03/2018.
//

#include "moxf_interface.h"
#include "moxf_message_parser.hpp"

RtMidiIn editorInterface_in;
RtMidiIn midiInterface_in;
RtMidiOut editorInterface_out;
RtMidiOut midiInterface_out;

#include <string>
#include <iostream>

midi_callback_t  g_master_midi_callback = NULL;
debug_callback_t g_debug_fn = NULL;

void debug( const std::string& fmt, const std::string& arg1 = "" , long arg2 = 0)
{
    if (g_debug_fn == NULL) return;
    std::string msg = std::string("[moxf_interface] ") + fmt + " [%s,%d]";
    g_debug_fn( (char*) msg.c_str() , arg1.c_str() , arg2 );
}


void midiin_callback_editor_fn(
    double deltatime ,
    midimessage_t* msg ,
    void* userdata)
{
    if (NULL == g_master_midi_callback) return;
    parse_moxf_editor_message(msg, g_master_midi_callback, userdata);
}

void midiin_callback_sysex_fn(
   double deltatime ,
   midimessage_t* msg ,
   void* userdata)
{
    if (NULL == g_master_midi_callback) return;
    g_master_midi_callback( 0x37 , 3 , 0x0f , 8 , userdata);
}

void register_callback( midi_callback_t fn )
{
    g_master_midi_callback = fn;
}

void register_debug_callback( debug_callback_t fn )
{
    g_debug_fn = fn;
}

template<typename T>
void open_midi_port(  T& port , const std::string& port_name )
{
    if (! is_port_available(port,port_name) ) {
        return;
    }
    midiportindex_t idx = get_port_index(port,port_name);
    port.openPort(idx);
}

void* open_input_editor_interface(   void* userData)
{
    editorInterface_in.cancelCallback();
    editorInterface_in.setCallback(midiin_callback_editor_fn,userData);
    
    if (!editorInterface_in.isPortOpen()) {
        open_midi_port(  editorInterface_in , MOXF_EDITOR_PORT );
        editorInterface_in.ignoreTypes(false);
    }
    return editorInterface_in.isPortOpen() ? &editorInterface_in : NULL_INTERFACE;
}

void* open_input_midi_interface(  void* userData)
{
    midiInterface_in.cancelCallback();
    midiInterface_in.setCallback(midiin_callback_sysex_fn,userData);
    
    if (!midiInterface_in.isPortOpen()) {
        open_midi_port(  midiInterface_in , MOXF_SYSEX_BULK_PORT );
        midiInterface_in.ignoreTypes(false);
    }
    return midiInterface_in.isPortOpen() ? &midiInterface_in : NULL_INTERFACE;
}


void* close_input_interface( void* intf)
{
    RtMidiIn* input = static_cast<RtMidiIn*>( intf );
    input->closePort();
    return intf;
}


void* open_output_editor_interface()
{
    if (!editorInterface_out.isPortOpen()) {
        open_midi_port( editorInterface_out , MOXF_EDITOR_PORT );
    }
    return editorInterface_out.isPortOpen() ? &editorInterface_out : NULL_INTERFACE;
}

void* open_output_midi_interface()
{
    if (!midiInterface_out.isPortOpen()) {
        open_midi_port( midiInterface_out , MOXF_SYSEX_BULK_PORT );
    }
    return midiInterface_out.isPortOpen() ? &midiInterface_out : NULL_INTERFACE;
}


void* close_output_interface( void* intf)
{
    RtMidiOut* output = static_cast<RtMidiOut*>( intf );
    output->closePort();
    return intf;
}

void send_midi_setting(
    midibyte_t chn ,
    midibyte_t hi ,
    midibyte_t lo ,
    midibyte_t sz ,
    midiword_t val
    )
{
    if (chn > 0xf) return;
    midibyte_t device_id = 0x10;

    if (sz == 2) {
        if (val > 0xffff) return;
        midimessage_t two_byte_editor_value {SYSEX_START , MANUFACTURER , device_id ,MODEL_HI , MODEL_LO ,0,ADDR_HI , ADDR_MID, ADDR_LO, VAL_HI ,VAL_LO, SYSEX_END };
        two_byte_editor_value[HIGH_OFFSET] = hi;
        two_byte_editor_value[CHANNEL_OFFSET] = chn;
        two_byte_editor_value[LOW_OFFSET] = lo;
        two_byte_editor_value[VALUE_OFFSET] = HI_BYTE( val );
        two_byte_editor_value[VALUE_OFFSET+1] = LO_BYTE( val );
        editorInterface_out.sendMessage(&two_byte_editor_value);
        
    } else if (sz == 1 ) {
        if (val > 0xff) return;
        midimessage_t one_byte_editor_value {SYSEX_START , MANUFACTURER , device_id ,MODEL_HI , MODEL_LO ,0,ADDR_HI , ADDR_MID, ADDR_LO,VAL_LO, SYSEX_END };
        one_byte_editor_value[HIGH_OFFSET] = hi;
        one_byte_editor_value[CHANNEL_OFFSET] = chn;
        one_byte_editor_value[LOW_OFFSET] = lo;
        one_byte_editor_value[VALUE_OFFSET] = LO_BYTE( val );
        editorInterface_out.sendMessage(&one_byte_editor_value);
        
    } else {
        return;
    }
}


