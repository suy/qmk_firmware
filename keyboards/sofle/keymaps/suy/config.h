#pragma once

/* The way how "handedness" is decided (which half is which),
see https://docs.qmk.fm/#/feature_split_keyboard?id=setting-handedness
for more options.
*/

#define DYNAMIC_TAPPING_TERM_INCREMENT 10 // How much the DT_UP key increases TAPPING_TERM

#undef TAPPING_TERM
#define TAPPING_TERM 260

#define ONESHOT_TAP_TOGGLE 5  /* Tapping this number of times holds the key until tapped once again. */
#define ONESHOT_TIMEOUT 4000  /* Time (in ms) before the one shot key is released */

#define TAPPING_TOGGLE 3

#define MK_COMBINED // Mouse mode. Accelerated by default, constant when ACLx gets held.

#define ENCODER_DIRECTION_FLIP
#ifdef ENCODER_RESOLUTION
#undef ENCODER_RESOLUTION
#endif
#define ENCODER_RESOLUTION 4
