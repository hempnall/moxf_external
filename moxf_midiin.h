//
//  moxf_midiin.h
//  max-external
//
//  Created by James Hook on 01/03/2018.
//

#ifndef moxf_midiin_h
#define moxf_midiin_h


#ifndef MAX_OBJ_NAME_SUFFIX
#define MAX_OBJ_NAME_SUFFIX ""
#endif

#include "ext.h"                            // standard Max include, always required
#include "ext_obex.h"                        // required for new style Max object
#include "moxf_interface.h"

typedef struct _moxf_midiin
{
    t_object    ob;
    void*       midi_sysex_in;
    void*       midi_editor_in;
    void*       moxf_setting_outlet;
    long        channel_number;
    midi_callback_t callback;
    
} t_moxf_midiin;

void *moxf_midiin_new(t_symbol *s, long argc, t_atom *argv);
void moxf_midiin_free(t_moxf_midiin *x);
void moxf_midiin_emitvalue( t_moxf_midiin* , midichannel_t chn, t_symbol *msg, midiword_t val );
t_class* moxf_midiin_build_class();


#endif /* moxf_midiin_h */