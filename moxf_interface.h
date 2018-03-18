//
//  moxf_interface.h
//  moxf
//
//  Created by James Hook on 01/03/2018.
//

#ifndef moxf_interface_h
#define moxf_interface_h

#include <stdio.h>

#define LOG_FILE  "/Users/jameshook/max.log"
#define DEBUGF(  msg )    { \
FILE* logfile = fopen( LOG_FILE , "a" ); \
fprintf( logfile , "[%s:%d] %s\n" , __FILE__ , __LINE__ ,  msg ); \
fclose( logfile ); \
}

#define NULL_INTERFACE 0x0
#define MOXF_EDITOR_PORT "Yamaha MOXF6/MOXF8 Port4"
#define MOXF_SYSEX_BULK_PORT "Yamaha MOXF6/MOXF8 Port1"
#define SYSEX_START 0xf0
#define MANUFACTURER 0x43
#define MODEL_HI 0x7f
#define MODEL_LO 0x1c
#define ADDR_HI 0x00
#define ADDR_MID 0x00
#define ADDR_LO 0x00
#define VAL_HI 0x00
#define VAL_LO 0x00
#define SYSEX_END 0xf7
#define LO_BYTE(x) ( x &  0x00ff )
#define HI_BYTE(x) ( ( x & 0xff00 ) >> 8 )
#define ALL_CHANNELS -1
#define VALUE_OFFSET 9
#define CHANNEL_OFFSET 7
#define HIGH_OFFSET 6
#define LOW_OFFSET 8
#define TWO_BYTE_VAL_LEN 11
#define ONE_BYTE_VAL_LEN 10


#include "midi/midi_typedefs.h"

#ifdef __cplusplus
extern "C" {
#endif

    void* open_input_editor_interface(  void* userData);
    void* open_input_midi_interface(  void* userData);
    void* close_input_interface( void* intf);
    void* open_output_editor_interface();
    void* open_output_midi_interface();
    void* close_output_interface( void* intf);
    void register_callback( midi_callback_t fn );
    void register_debug_callback( debug_callback_t fn );
    void send_midi_setting(midibyte_t chn , midibyte_t hi , midibyte_t lo , midibyte_t sz ,midiword_t val );
    long external_to_internal_midichannel( long external );
    long internal_to_external_midichannel( long internal );
    

#ifdef __cplusplus
}
#endif

#endif /* moxf_interface_h */
