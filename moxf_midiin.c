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

void* object_callback_table[16];
t_object* midi_inchn_attr;

void initialise_object_callback_table()
{
    BEGIN_CRITICAL_SECTION(0)
    int i;
    for (i=0;i<16;++i) object_callback_table[i] = NULL;
    END_CRITICAL_SECTION(0)
}

bool add_object_to_callback_table( long chn , void* obj)
{

    if (chn >= 16 || chn < 0) return false;
    if (object_callback_table[chn] != NULL) return false;

    BEGIN_CRITICAL_SECTION( 0 )
    object_callback_table[chn] = obj;
    END_CRITICAL_SECTION( 0 )
    
    return true;
}

void remove_object_from_table( long chn )
{
    if (chn >= 16 || chn < 0) return false;
    BEGIN_CRITICAL_SECTION( 0 )
    object_callback_table[chn] = NULL;
    END_CRITICAL_SECTION( 0 )
}

void master_midi_sysex_cb(midibyte_t high, midibyte_t mid , midibyte_t low , midiword_t val  )
{

    if (mid >= 16) return;
    void* userdata = object_callback_table[mid];
    if (userdata == NULL) return;
    
    BEGIN_CRITICAL_SECTION(0)
    t_symbol* msg = translate_symbol( high , low );
    if (msg == null_str)  return;
    moxf_midiin_emitvalue(userdata,mid,msg,val);
    END_CRITICAL_SECTION(0)
}

void moxf_midiin_free(t_moxf_midiin *x)
{
    remove_object_from_table(x->midi_channel);
}

t_max_err midiin_midi_chn_attr_set( t_moxf_midiin* obj , void* attr , long ac , t_atom* atom_v )
{
    if ( ! ac ||  !atom_v ) return MAX_ERR_GENERIC;
    long val = external_to_internal_midichannel( atom_getlong(atom_v)) ;
    remove_object_from_table( obj->midi_channel );
    obj->midi_channel = val;
    add_object_to_callback_table(val, obj);
}

void *moxf_midiin_new(t_symbol *s, long argc, t_atom *argv)
{
    t_moxf_midiin *x = NULL;
    
    
    if ((x = (t_moxf_midiin *)object_alloc(moxf_midiin_class))) {
        x->midi_channel = ALL_CHANNELS;
        x->midi_sysex_in = open_input_midi_interface(x);
        x->midi_editor_in = open_input_editor_interface(x);
        x->moxf_setting_outlet = outlet_new(x, NULL);
        object_addattr(x,midi_inchn_attr);
    }
    return (x);
}

t_class* moxf_midiin_build_class()  {
    register_debug_callback(post);
    initialise_object_callback_table();
    register_callback(master_midi_sysex_cb);
    
    null_str = gensym("");
    t_class* class = class_new("moxf.midiin"  MAX_OBJ_NAME_SUFFIX , (method)moxf_midiin_new, (method)moxf_midiin_free, (long)sizeof(t_moxf_midiin),
              0L /* leave NULL!! */, A_GIMME, 0);
    midi_inchn_attr  = attribute_new( "midi_channel" , gensym("long") ,ATTR_FLAGS_NONE , NULL, midiin_midi_chn_attr_set );
    class_addmethod(class, (method) moxf_midiin_emitvalue, "emitvalue", A_LONG,A_SYM,A_LONG,0);
    
    return class;
}



void moxf_midiin_emitvalue( t_moxf_midiin* x, midichannel_t chn, t_symbol *msg, midiword_t val )
{
    if ( x->midi_channel != ALL_CHANNELS && chn != x->midi_channel) return;
    t_atom output[2];
    atom_setlong( &output[0] , internal_to_external_midichannel(chn) );
    atom_setlong( &output[1] , val);
    outlet_anything( x->moxf_setting_outlet , msg, 2, output);
}
