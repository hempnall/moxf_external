//
//  moxf_message_parser.cpp
//  max-external
//
//  Created by James Hook on 03/03/2018.
//

#include "moxf_message_parser.hpp"
#include <cstring>


midibyte_t sysex_editor_header[] { 0xF0, 0x43, 0x10, 0x7F, 0x1C };
midibyte_t sysex_sysex_header[] { 0xF0, 0x43, 0x00, 0x7F, 0x1C };
midibyte_t sysex_footer[] { 0xF7 };


void parse_moxf_editor_message(midimessage_t* msg , midi_callback_t cb , void* userdata )
{
    if (msg->size() != 10 && msg->size() != 11) return;
    int n = memcmp( sysex_editor_header , &(*msg)[0] ,5  );
    if ( n != 0 ) return;
    
    midibyte_t final_byte = * msg->rbegin();
    if (final_byte != sysex_footer[0]) return;

    midiword_t val;
    midibyte_t hi = (*msg)[6];
    midibyte_t mid = (*msg)[7];
    midibyte_t lo = (*msg)[8];

    if ((*msg)[5] == 0x01) {
        val = (*msg)[9];
    } else if ((*msg)[5] == 0x02 ) {
        val = ((*msg)[9] << 8) + (*msg)[10];
    } else {
        return;
    }

    
    cb(hi,mid,lo,val,userdata)  ;

    
}
