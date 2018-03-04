//
//  midi_typedefs.h
//  moxf
//
//  Created by James Hook on 03/03/2018.
//

#ifndef midi_typedefs_h
#define midi_typedefs_h

#ifndef MAX_OBJ_NAME_SUFFIX
#define MAX_OBJ_NAME_SUFFIX ""
#endif

#include <inttypes.h>

typedef unsigned int midiportindex_t;
typedef unsigned char midibyte_t;
typedef uint16_t midiword_t;
typedef long midichannel_t;

typedef void (*midi_callback_t)(midibyte_t high, midibyte_t mid , midibyte_t low, midiword_t val , void* userData );
typedef void (*debug_callback_t)(char*,...);

#endif /* midi_typedefs_h */
