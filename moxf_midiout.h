//
//  moxf_midiout.h
//  max-external
//
//  Created by James Hook on 03/03/2018.
//

#ifndef moxf_midiout_h
#define moxf_midiout_h

#include <stdio.h>

#include "ext.h"                            // standard Max include, always required
#include "ext_obex.h"                        // required for new style Max object
#include "moxf_interface.h"

typedef struct _moxf_midiout
{
    t_object    ob;
    void*       midi_editor_out;
    t_object*   midi_channel_attr;
    long        midi_channel;
} t_moxf_midiout;

BEGIN_USING_C_LINKAGE

void *moxf_midiout_new(t_symbol *s, long argc, t_atom *argv);
void moxf_midiout_free(t_moxf_midiout *x);
void moxf_midiout_recvvalue_chnval( t_moxf_midiout* , t_symbol *msg,long val );
void moxf_midiout_recvvalue_sym( t_moxf_midiout* ,  long mid,t_symbol *msg,long val );
void moxf_midiout_recvvalue_byte( t_moxf_midiout* , long hi, long mid,long lo, long val );
void moxf_midiout_recvvalue( t_moxf_midiout* , long hi, long mid,long lo, long sz, long val );
t_class* moxf_midiout_build_class();
t_max_err midiout_midi_chn_attr_set( t_moxf_midiout* obj , void* attr , long ac , t_atom* atom_v );

END_USING_C_LINKAGE

#endif /* moxf_midiout_h */
