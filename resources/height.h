// Height (from Maxbotix) sensor resource implementation

#ifndef HEIGHT_H
#define HEIGHT_H

#include "nsdl_support.h"

int create_height_resource(sn_nsdl_resource_info_s *resource_ptr);
void height_report();
#endif  // HEIGHT
