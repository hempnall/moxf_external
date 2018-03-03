//
//  midi_message.h
//  rtmidi_test
//
//  Created by James Hook on 28/02/2018.
//  Copyright © 2018 James Hook. All rights reserved.
//

#ifndef midi_message_h
#define midi_message_h

#include <vector>
#include <inttypes.h>
#include "moxf_types.h"
#include "rtmidi_utils.hpp"


typedef uint8_t partfilter_t; // 0 = all, otherwise 1,2,3, ..16 for just that part;

void parse_bulk_dump( RtMidiIn& in ,  partfilter_t filt , part_callback_fn , arp_callback_fn   );
void parse_part_message( const midimessage_t& msg , midi_channel_t chn ,  part_callback_fn = nullptr);
void parse_arp_message( const midimessage_t& msg ,midi_channel_t chn ,arp_callback_fn = nullptr);
double get_message_with_sleep( RtMidiIn& in ,uint8_t sleep_time, size_t sz , midimessage_t *msg  );

std::ostream& operator << ( std::ostream& ostr , const part_information_36_00& part_info);
std::ostream& operator << ( std::ostream& ostr , const arp_information_38_00& arp_info);

#endif /* midi_message_h */
