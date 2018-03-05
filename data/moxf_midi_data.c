//
//  moxf_midi_data.c
//  max-external
//
//  Created by James Hook on 03/03/2018.
//

#include "moxf_midi_data.h"

#define HIGH_ADDRESS_SIZE 0x80
#define LOW_ADDRESS_SIZE 0xff

moxf_message* msg_symbols[HIGH_ADDRESS_SIZE];
moxf_message part_defs[LOW_ADDRESS_SIZE];
moxf_message arp_defs[LOW_ADDRESS_SIZE];

t_symbol* null_str;

#define END_MSG { 0,0,0,0,0,0}

moxf_message msg_defs[] = {
    { 0x37 , 0x01 , "bank_select_msb" ,0, 1, 0 },
    { 0x37 , 0x02 , "bank_select_lsb",0 , 1 , 0 },
    { 0x37 , 0x03 , "program_number" ,0 , 1 , 0 },
    { 0x37 , 0x04 , "receive_channel",0 , 1 , 0 },
    { 0x37 , 0x0e , "volume" ,0, 1 , 0 },
    { 0x37 , 0x0f , "pan" , 0,1 ,0  },
    END_MSG
};

void initialize_symbol_array( moxf_message* arr , size_t sz )
{
    moxf_message null_msg = { 0, 0,"",null_str,0,0 };
    int i;
    for (int i =0 ; i < 0xff ;++i) {
        arr[i] = null_msg;
    }
}

bool is_end_message( moxf_message* msg )
{
    return ( msg->high_add==0 && msg->offset == 0 && msg->name == 0 && msg->symbol == 0 && msg->translate_fn == 0);
}

void populate_symbol_arrays()
{
    null_str = gensym("");
    int idx;
    for (idx = 0 ; idx < sizeof(msg_symbols); ++idx) {
        msg_symbols[idx] = NULL;
    }
    
    initialize_symbol_array(part_defs, LOW_ADDRESS_SIZE);
    initialize_symbol_array(arp_defs, LOW_ADDRESS_SIZE);
    msg_symbols[0x37] = part_defs;
    msg_symbols[0x38] = arp_defs;
    
    moxf_message* start = msg_defs;
    while (! is_end_message(start)) {
        start->symbol = gensym(start->name);
        msg_symbols[ start->high_add ][ start->offset ] = *start;
        start++;
    }
}

t_symbol* translate_symbol( midibyte_t hi , midibyte_t low)
{
    moxf_message* m = msg_symbols[hi];
    if (m==NULL) return null_str;
    return msg_symbols[hi][low].symbol;
}

moxf_message* get_message_for_symbol( t_symbol* sym )
{
    moxf_message* start = msg_defs;
    while (! is_end_message(start)) {
        if (start->symbol == sym) return start;
        start++;
    }
    return NULL;
}

long get_message_size( midibyte_t hi, midibyte_t lo )
{
    if (hi >= HIGH_ADDRESS_SIZE ) return 0;
    return msg_symbols[hi][lo].size;
}
