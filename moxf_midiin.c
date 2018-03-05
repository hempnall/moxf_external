//
//  moxf_midiin.c
//  max-external
//
//  Created by James Hook on 01/03/2018.
//

#include "moxf_midiin.h"
#include "moxf_interface.h"
#include "data/moxf_midi_data.h"

void *moxf_midiin_class;
extern t_symbol* null_str;
extern t_symbol** part_msg_symbol;

void master_midi_sysex_cb(midibyte_t high, midibyte_t mid , midibyte_t low , midiword_t val , void* userdata )
{
    if (userdata == NULL) return;
    t_symbol* msg = translate_symbol( high , low );
    if (msg == null_str)  return;
    moxf_midiin_emitvalue(userdata,mid,msg,val);
}

void moxf_midiin_free(t_moxf_midiin *x)
{
    ;
}

void *moxf_midiin_new(t_symbol *s, long argc, t_atom *argv)
{
    t_moxf_midiin *x = NULL;
    
    if ((x = (t_moxf_midiin *)object_alloc(moxf_midiin_class))) {
        x->midi_sysex_in = open_input_midi_interface(x);
        x->midi_editor_in = open_input_editor_interface(x);
        x->moxf_setting_outlet = outlet_new(x, NULL);
        x->channel_number = ALL_CHANNELS;
        if (argc >= 1) x->channel_number = atom_getlong( &argv[0]);
        register_callback(master_midi_sysex_cb);
    }
    return (x);
}

t_class* moxf_midiin_build_class()  {
    register_debug_callback(post);
    
    null_str = gensym("");
    t_class* class = class_new("moxf.midiin." MAX_OBJ_NAME_SUFFIX , (method)moxf_midiin_new, (method)moxf_midiin_free, (long)sizeof(t_moxf_midiin),
              0L /* leave NULL!! */, A_GIMME, 0);
    class_addmethod(class, (method) moxf_midiin_emitvalue, "emitvalue", A_LONG,A_SYM,A_LONG,0);
    return class;
}



void moxf_midiin_emitvalue( t_moxf_midiin* x, midichannel_t chn, t_symbol *msg, midiword_t val )
{
    if ( x->channel_number != ALL_CHANNELS && chn != x->channel_number) return;
    t_atom output[2];
    atom_setlong( &output[0] , chn);
    atom_setlong( &output[1] , val);
    outlet_anything( x->moxf_setting_outlet , msg, 2, output);
}
