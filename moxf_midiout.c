//
//  moxf_midiout.c
//  max-external
//
//  Created by James Hook on 03/03/2018.
//

#include "moxf_midiout.h"
#include "data/moxf_midi_data.h"

#define DEBUG post( "[%s:%d] moxf_midiout_recvvalue_sym", __FILE__ , __LINE__);
void *moxf_midiout_class;

void *moxf_midiout_new(t_symbol *s, long argc, t_atom *argv)
{
    t_moxf_midiout *x = NULL;
    
    if ((x = (t_moxf_midiout *)object_alloc(moxf_midiout_class))) {
        x->midi_editor_out = open_output_editor_interface();
    }
    return (x);
}

void moxf_midiout_free(t_moxf_midiout *x)
{
    
}

void moxf_midiout_recvvalue_sym( t_moxf_midiout* x, long mid,t_symbol *msg,long val )
{
    moxf_message* msg_spec = get_message_for_symbol(  msg  );
    if (msg_spec == NULL) return;
    moxf_midiout_recvvalue(x, msg_spec->high_add, mid, msg_spec->offset, msg_spec->size, val);
}

void moxf_midiout_recvvalue_byte( t_moxf_midiout* x, long hi, long mid,long lo, long val )
{
    long msg_sz = get_message_size(hi, lo);
    if (msg_sz == 0 || msg_sz > 2) return;
    moxf_midiout_recvvalue(x, hi, mid, lo, msg_sz, val);
}

void moxf_midiout_recvvalue( t_moxf_midiout* x, long hi, long mid,long lo, long sz, long val )
{
    if (hi < 0 || hi > 0xff) return;
    if (mid < 0 || mid > 0xff) return;
    if (lo < 0 || lo > 0xff) return;
    if (sz < 0 || sz > 2) return;
    if (val < 0 || val > 0xfff) return;
    send_midi_setting(mid, hi, lo, sz, val);
}


t_class* moxf_midiout_build_class()
{
    register_debug_callback(post);
    
    t_class* class = class_new("moxf.midiout." MAX_OBJ_NAME_SUFFIX , (method)moxf_midiout_new, (method)moxf_midiout_free, (long)sizeof(t_moxf_midiout),
                               0L /* leave NULL!! */, A_GIMME, 0);
    
    class_addmethod(class, (method) moxf_midiout_recvvalue_sym, "recvsym",    A_LONG,A_SYM, A_LONG,0);
    class_addmethod(class, (method) moxf_midiout_recvvalue_byte, "recvvalue", A_LONG,A_LONG,A_LONG,A_LONG,0);
    class_addmethod(class, (method) moxf_midiout_recvvalue, "recv", A_LONG,A_LONG,A_LONG,A_LONG,A_LONG,0);
    return class;
}
