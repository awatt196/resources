//accelerometer sensor resource implementation

#ifndef ACCELEROMETER_H
#define ACCELEROMETER_H

#include "nsdl_support.h"

int create_accelerometer_resource(sn_nsdl_resource_info_s *resource_ptr);
void accelerometer_report();
#endif  // ACCELEROMETER