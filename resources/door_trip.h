// Door trip (from SHARPPIR) sensor resource implementation

#ifndef DOOR_TRIP_H
#define DOOR_TRIP_H

#include "nsdl_support.h"

int create_door_trip_resource(sn_nsdl_resource_info_s *resource_ptr);
void door_trip_report();
#endif  // DOOR_TRIP
