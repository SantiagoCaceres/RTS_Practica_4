#include "include/api/schedule.h"
#include <string.h>
#include "low_level_platform/api/low_level_platform.h"
#include "include/AircraftController/AircraftController.h"
#include "_aircraftcontroller_main.h"
// ***** Start of method declarations.
// ***** End of method declarations.
_aircraftcontroller_main_main_self_t* new__aircraftcontroller_main() {
    _aircraftcontroller_main_main_self_t* self = (_aircraftcontroller_main_main_self_t*)lf_new_reactor(sizeof(_aircraftcontroller_main_main_self_t));

    return self;
}
