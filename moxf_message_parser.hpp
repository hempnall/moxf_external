//
//  moxf_message_parser.hpp
//  max-external
//
//  Created by James Hook on 03/03/2018.
//

#ifndef moxf_message_parser_hpp
#define moxf_message_parser_hpp

#include <stdio.h>
#include "midi/rtmidi_utils.hpp"

void parse_moxf_editor_message( midimessage_t* msg , midi_callback_t cb );

#endif /* moxf_message_parser_hpp */
