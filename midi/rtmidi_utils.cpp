//
//  rtmidi_utils.cpp
//  rtmidi_test
//
//  Created by James Hook on 28/02/2018.
//  Copyright © 2018 James Hook. All rights reserved.
//

#include "rtmidi_utils.hpp"


void displayMidiIns( RtMidiIn& in )
{
    std::cout << "MidiIns\n";
    std::cout << "=======\n";
    unsigned int midi_in_count = in.getPortCount();
    std::cout << "count: " << midi_in_count << std::endl;
    for (midiportindex_t idx = 0 ; idx < midi_in_count ; ++idx) {
        std::cout << "[" << idx << "] " << in.getPortName(idx) << std::endl;
    }
}

void displayMidiOuts( RtMidiOut& out )
{
    std::cout << "MidiOuts\n";
    std::cout << "========\n";
    unsigned int midi_out_count = out.getPortCount();
    std::cout << "count: " << midi_out_count << std::endl;
    for (midiportindex_t idx = 0 ; idx < midi_out_count ; ++idx) {
        std::cout << "[" << idx << "] " << out.getPortName(idx) << std::endl;
    }
}

void dump_midi_message( const midimessage_t& msg )
{
    std::cout << "=== msg ===\n";
    int nBytes = msg.size();
    for ( int i=0; i<nBytes; i++ )
        std::cout << "Byte " << i << " = " << (int)msg[i] << ", ";
    std::cout << "=========\n";
}



