/**
	@file
	dummy - a dummy object
	jeremy bernstein - jeremy@bootsquad.com

	@ingroup	examples
*/



#include "ext.h"                            // standard Max include, always required
#include "ext_obex.h"                        // required for new style Max object
#include "moxf_midiin.h"

extern void* moxf_midiin_class;

void ext_main(void *r)
{
	t_class *c_midi_in;
    c_midi_in = moxf_midiin_build_class();   
	class_register(CLASS_BOX, c_midi_in);
	moxf_midiin_class = c_midi_in;
}




