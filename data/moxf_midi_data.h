//
//  moxf_midi_data.h
//  moxf
//
//  Created by James Hook on 03/03/2018.
//

#ifndef moxf_midi_data_h
#define moxf_midi_data_h

#include "ext.h"                            // standard Max include, always required
#include "ext_obex.h"
#include "../midi/midi_typedefs.h"

typedef struct _moxf_message
{
    uint16_t offset;
    const char* name;
    t_symbol* symbol;
    uint8_t size;
    void* translate_fn;
} moxf_message;

#define PART_PARAMETER_NAME_COUNT 0x3d
#define ARP_PARAMETER_NAME_COUNT 0x46
#define MAX_LO_ARRAY_DIMENSION 0xff

void populate_symbol_array(  moxf_message* msg_array  ,  moxf_message* output      );
void populate_symbol_arrays();
t_symbol* translate_symbol( midibyte_t hi , midibyte_t low);
moxf_message* get_message_for_symbol( midibyte_t hi,t_symbol* sym );

#endif /* moxf_midi_data_h */
