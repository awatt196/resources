// Sound Level (from MAX9814) sensor resource implementation

#ifndef SOUND_LEVEL_H
#define SOUND_LEVEL_H

#include "nsdl_support.h"

int create_sound_level_resource(sn_nsdl_resource_info_s *resource_ptr);
void sound_level_report();
#endif  // SOUND_LEVEL
