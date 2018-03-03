//
//  rtmidi_utils.hpp
//  rtmidi_test
//
//  Created by James Hook on 28/02/2018.
//  Copyright © 2018 James Hook. All rights reserved.
//

#ifndef rtmidi_utils_hpp
#define rtmidi_utils_hpp

#include <iostream>
#include <signal.h>
#include <unistd.h>
#include <vector>
#include <rtmidi/RtMidi.h>
#include "midi_typedefs.h"

typedef std::vector<midibyte_t> midimessage_t;

#define SLEEP( x ) {  usleep( 10 * x  );  }

void displayMidiIns( RtMidiIn& in );
void displayMidiOuts( RtMidiOut& out );

template< typename T >
bool is_port_available(  T& midiport, const std::string& port_name )
{
    for ( midiportindex_t idx = 0 ; idx < midiport.getPortCount() ;++idx ) {
        std::string name = midiport.getPortName( idx );
        if ( port_name == name ) return true;
    }
    return false;
}

template< typename T >
midiportindex_t get_port_index(  T& midiport, const std::string& port_name )
{
    for ( midiportindex_t idx = 0 ; idx < midiport.getPortCount() ;++idx ) {
        std::string name = midiport.getPortName( idx );
        if ( port_name == name ) return idx;
    }
    return 99999;
}

template<typename T>
bool is_port_open( T& port )
{
    return port.isPortOpen(); // not much point in having this :-( just here for completeness
}

void dump_midi_message( const midimessage_t& msg );

#endif /* rtmidi_utils_hpp */
