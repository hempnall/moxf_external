/**
	@file
	moxf - a Max UI for Yamaha MOXF Keyboards
	james hook

	@ingroup	moxf
*/



#include "ext.h"                            // standard Max include, always required
#include "ext_obex.h"                       // required for new style Max object
#include "moxf_midiin.h"
#include "moxf_midiout.h"
#include "data/moxf_midi_data.h"


extern void* moxf_midiin_class;
extern void* moxf_midiout_class;

void ext_main(void *r)
{
    DEBUGF( "start" )
    
	t_class *c_midi_in;
    t_class *c_midi_out;
    
    populate_symbol_arrays();
    
    c_midi_in = moxf_midiin_build_class();   
	class_register(CLASS_BOX, c_midi_in);
	moxf_midiin_class = c_midi_in;
    
    c_midi_out = moxf_midiout_build_class();
    class_register(CLASS_BOX, c_midi_out);
    moxf_midiout_class = c_midi_out;
}




