//
//  moxf_midiin.c
//  max-external
//
//  Created by James Hook on 01/03/2018.
//

#include "moxf_midiin.h"

#define END_MSG { 0,0,0,0}


typedef struct _moxf_message
{
    uint16_t offset;
    const char* name;
    uint8_t size;
    void* translate_fn;
} moxf_message;

moxf_message part_msg_defs[] = {
    { 0x01 , "bank_select_msb" , 1, 0 },
    { 0x02 , "bank_select_lsb" , 1 , 0 },
    { 0x03 , "progtam_number"  , 1 , 0 },
    { 0x04 , "receive_channel" , 1 , 0 },
    { 0x0e , "volume" , 1 , 0 },
    { 0x0f , "pan" , 1 ,0  },
    END_MSG
};
moxf_message arp_msg_defs[] = {
    END_MSG
};

#define PART_PARAMETER_NAME_COUNT 0x3d
#define ARP_PARAMETER_NAME_COUNT 0x46
#define MAX_LO_ARRAY_DIMENSION 0xff
t_symbol* part_msg_symbol[ MAX_LO_ARRAY_DIMENSION ];
t_symbol* arp_msg_symbol[ MAX_LO_ARRAY_DIMENSION ];
t_symbol* null_str;

void *moxf_midiin_class;

void populate_symbol_array(  moxf_message* msg_array ,  t_symbol** output     )
{
    int idx;
    moxf_message* start = msg_array;
    
    for (idx = 0 ;  idx < MAX_LO_ARRAY_DIMENSION ; idx++)
    {
        output[idx] = null_str;
    }
    
    while (start->size != 0 ) {
        post("setting symbol %d=%s", start->offset , start->name);
        output[ start->offset ] = gensym( start->name );
        start++;
    }
}



void master_midi_sysex_cb(midibyte_t high, midibyte_t mid , midibyte_t low , midiword_t val , void* userdata )
{
    switch (high) {
        case 0x37:
        {
            post("main callback %d %d %d %d" , high , mid , low , val);
            t_symbol* msg = part_msg_symbol[low];
            if (userdata == NULL) return;
            if (msg == null_str)  return;

            moxf_midiin_emitvalue(userdata,mid,msg,val);
            break;
        }
        case 0x38:
            return;
            break;
        default:
            return;
            break;
    }
}

void moxf_midiin_free(t_moxf_midiin *x)
{
    ;
}

void *moxf_midiin_new(t_symbol *s, long argc, t_atom *argv)
{
    t_moxf_midiin *x = NULL;
    
    if ((x = (t_moxf_midiin *)object_alloc(moxf_midiin_class))) {
        x->moxf_setting_outlet = intout( (t_moxf_midiin*)  x );
        x->midi_sysex_in = open_input_midi_interface(x);
        x->midi_editor_in = open_input_editor_interface(x);
        x->moxf_setting_outlet = outlet_new(x, NULL);
        register_callback(master_midi_sysex_cb);
    }
    return (x);
}

t_class* moxf_midiin_build_class()  {
    
    register_debug_callback(post);
    
    null_str = gensym("");
    t_class* class = class_new("moxf" MAX_OBJ_NAME_SUFFIX , (method)moxf_midiin_new, (method)moxf_midiin_free, (long)sizeof(t_moxf_midiin),
              0L /* leave NULL!! */, A_GIMME, 0);
    
    populate_symbol_array(part_msg_defs, part_msg_symbol);
    populate_symbol_array(arp_msg_defs, arp_msg_symbol);
    
    class_addmethod(class, (method) moxf_midiin_emitvalue, "emitvalue", A_LONG,A_SYM,A_LONG,0);
    return class;
}



void moxf_midiin_emitvalue( t_moxf_midiin* x, midichannel_t chn, t_symbol *msg, midiword_t val )
{
    t_atom output[2];
    atom_setlong( &output[0] , chn);
    atom_setlong( &output[1] , val);
    outlet_anything( x->moxf_setting_outlet , msg, 2, output);
}
