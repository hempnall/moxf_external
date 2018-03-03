//
//  moxf_interface.h
//  moxf
//
//  Created by James Hook on 01/03/2018.
//

#ifndef moxf_interface_h
#define moxf_interface_h

#define NULL_INTERFACE 0x0
#define MOXF_EDITOR_PORT "Yamaha MOXF6/MOXF8 Port4"
#define MOXF_SYSEX_BULK_PORT "Yamaha MOXF6/MOXF8 Port1"

#include "midi/midi_typedefs.h"

#ifdef __cplusplus
extern "C" {
#endif

   
    void* open_input_editor_interface(  void* userData);
    void* open_input_midi_interface(  void* userData);
    void* close_input_interface( void* intf);
    void* open_output_interface( void* intf , char* name , void* userData);
    void* close_output_interface( void* intf);
    

    
    void register_callback( midi_callback_t fn );
    void register_debug_callback( debug_callback_t fn );

#ifdef __cplusplus
}
#endif

#endif /* moxf_interface_h */
