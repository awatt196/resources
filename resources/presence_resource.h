// Motion (from PIR) sensor resource implementation

#ifndef MOTION_H
#define MOTION_H

#include "nsdl_support.h"

int create_presence_resource(sn_nsdl_resource_info_s *resource_ptr);
void presence_report();
#endif  // MOTION
