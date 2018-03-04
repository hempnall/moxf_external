//
//  moxf_midi_data.c
//  max-external
//
//  Created by James Hook on 03/03/2018.
//

#include "moxf_midi_data.h"

moxf_message part_msg_symbol[ MAX_LO_ARRAY_DIMENSION ];
moxf_message arp_msg_symbol[ MAX_LO_ARRAY_DIMENSION ];
t_symbol* null_str;

#define END_MSG { 0,0,0,0}

moxf_message part_msg_defs[] = {
    { 0x01 , "bank_select_msb" ,0, 1, 0 },
    { 0x02 , "bank_select_lsb",0 , 1 , 0 },
    { 0x03 , "program_number" ,0 , 1 , 0 },
    { 0x04 , "receive_channel",0 , 1 , 0 },
    { 0x0e , "volume" ,0, 1 , 0 },
    { 0x0f , "pan" , 0,1 ,0  },
    END_MSG
};

moxf_message arp_msg_defs[] = {
    END_MSG
};


void populate_symbol_array(  moxf_message* msg_array ,  moxf_message* output     )
{
    int idx;
    moxf_message* start = msg_array;
    moxf_message null_msg = { 0,"",null_str,0,0 };

    for (idx = 0 ;  idx < MAX_LO_ARRAY_DIMENSION ; idx++)
    {
        output[idx] = null_msg;
    }
    
    while (start->size != 0 ) {
        start->symbol = gensym(start->name);
        output[ start->offset ] = *start;
        start++;
    }
}

void populate_symbol_arrays()
{
    populate_symbol_array(part_msg_defs, part_msg_symbol);
    populate_symbol_array(arp_msg_defs, arp_msg_symbol);
}

t_symbol* translate_symbol( midibyte_t hi , midibyte_t low)
{
    switch (hi)
    {
        case 0x37:
            return part_msg_symbol[low].symbol;
            break;
        case 0x38:
            return null_str;
            break;
        default:
            return null_str;
    }
}

moxf_message* get_message_for_symbol( midibyte_t hi,t_symbol* sym )
{
    moxf_message* moxf_msg;
    
    switch (hi)
    {
        case 0x37:
            moxf_msg = part_msg_defs;
            break;
        case 0x38:
            moxf_msg = arp_msg_defs;
            break;
        default:
            return NULL;
    }
    while (moxf_msg->size != 0 ) {
        if (moxf_msg->symbol == sym) return moxf_msg;
        moxf_msg++;
    }
    return NULL;
}
