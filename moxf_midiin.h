//
//  moxf_midiin.h
//  max-external
//
//  Created by James Hook on 01/03/2018.
//

#ifndef moxf_midiin_h
#define moxf_midiin_h


#include "ext.h"                            // standard Max include, always required
#include "ext_obex.h"                        // required for new style Max object
#include "midi/midi_typedefs.h"

#define ALL_CHANNELS -1

typedef struct _moxf_midiin
{
    t_object    ob;
    void*       midi_sysex_in;
    void*       midi_editor_in;
    void*       moxf_setting_outlet;
    long        channel_number;
    midi_callback_t callback;
    
} t_moxf_midiin;

BEGIN_USING_C_LINKAGE

void *moxf_midiin_new(t_symbol *s, long argc, t_atom *argv);
void moxf_midiin_free(t_moxf_midiin *x);
void moxf_midiin_emitvalue( t_moxf_midiin* , midichannel_t chn, t_symbol *msg, midiword_t val );
t_class* moxf_midiin_build_class();

END_USING_C_LINKAGE

#endif /* moxf_midiin_h */
