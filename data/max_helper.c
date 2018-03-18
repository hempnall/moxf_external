//
//  max_helper.c
//  max-external
//
//  Created by James Hook on 17/03/2018.
//

#include "max_helper.h"



void add_midi_channel_attr_to_object( void* object , method attr_setter )
{
    t_symbol* long_attr = gensym("long");
    t_object* midichn_attr  = attribute_new( "midi_channel" , long_attr ,ATTR_FLAGS_NONE , NULL, attr_setter );
    if ( NULL == midichn_attr) {
        object_error_obtrusive(object, "unable to create midichannel attribute");
    } else {
        t_max_err err = object_addattr( object , midichn_attr );
        if ( err != MAX_ERR_NONE ) {
            object_error_obtrusive(object, "unable to attach midichannel attribute to object");
        }
    }
}
