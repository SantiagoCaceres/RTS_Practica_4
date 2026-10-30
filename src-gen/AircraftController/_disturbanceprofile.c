#include "include/api/schedule.h"
#include <string.h>
#include "low_level_platform/api/low_level_platform.h"
#include "include/AircraftController/DisturbanceProfile.h"
#include "_disturbanceprofile.h"
// ***** Start of method declarations.
// ***** End of method declarations.
#include "include/api/reaction_macros.h"
void _disturbanceprofilereaction_function_0(void* instance_args) {
    _disturbanceprofile_self_t* self = (_disturbanceprofile_self_t*)instance_args; SUPPRESS_UNUSED_WARNING(self);
    _disturbanceprofile_dv_t* dv = &self->_lf_dv;
    #line 177 "/workspaces/RTS_Practica_4/AircraftController.lf"
    lf_set(dv, -5.0);
#line 15 "/workspaces/RTS_Practica_4/src-gen/AircraftController/_disturbanceprofile.c"
}
#include "include/api/reaction_macros_undef.h"
#include "include/api/reaction_macros.h"
void _disturbanceprofilereaction_function_1(void* instance_args) {
    _disturbanceprofile_self_t* self = (_disturbanceprofile_self_t*)instance_args; SUPPRESS_UNUSED_WARNING(self);
    _disturbanceprofile_dv_t* dv = &self->_lf_dv;
    #line 181 "/workspaces/RTS_Practica_4/AircraftController.lf"
    lf_set(dv, 0.0);
#line 24 "/workspaces/RTS_Practica_4/src-gen/AircraftController/_disturbanceprofile.c"
}
#include "include/api/reaction_macros_undef.h"
_disturbanceprofile_self_t* new__disturbanceprofile() {
    _disturbanceprofile_self_t* self = (_disturbanceprofile_self_t*)lf_new_reactor(sizeof(_disturbanceprofile_self_t));
    self->_lf__reaction_0.number = 0;
    self->_lf__reaction_0.function = _disturbanceprofilereaction_function_0;
    self->_lf__reaction_0.self = self;
    self->_lf__reaction_0.deadline_violation_handler = NULL;
    self->_lf__reaction_0.STP_handler = NULL;
    self->_lf__reaction_0.name = "?";
    self->_lf__reaction_0.mode = NULL;
    self->_lf__reaction_1.number = 1;
    self->_lf__reaction_1.function = _disturbanceprofilereaction_function_1;
    self->_lf__reaction_1.self = self;
    self->_lf__reaction_1.deadline_violation_handler = NULL;
    self->_lf__reaction_1.STP_handler = NULL;
    self->_lf__reaction_1.name = "?";
    self->_lf__reaction_1.mode = NULL;
    self->_lf__disturbance_start.last_tag = NEVER_TAG;
    #ifdef FEDERATED_DECENTRALIZED
    self->_lf__disturbance_start.intended_tag = (tag_t) { .time = NEVER, .microstep = 0u};
    #endif // FEDERATED_DECENTRALIZED
    self->_lf__disturbance_start_reactions[0] = &self->_lf__reaction_0;
    self->_lf__disturbance_start.reactions = &self->_lf__disturbance_start_reactions[0];
    self->_lf__disturbance_start.number_of_reactions = 1;
    #ifdef FEDERATED
    self->_lf__disturbance_start.physical_time_of_arrival = NEVER;
    #endif // FEDERATED
    self->_lf__disturbance_start.is_timer = true;
    #ifdef FEDERATED_DECENTRALIZED
    self->_lf__disturbance_start.intended_tag = (tag_t) { .time = NEVER, .microstep = 0u};
    #endif // FEDERATED_DECENTRALIZED
    self->_lf__disturbance_end.last_tag = NEVER_TAG;
    #ifdef FEDERATED_DECENTRALIZED
    self->_lf__disturbance_end.intended_tag = (tag_t) { .time = NEVER, .microstep = 0u};
    #endif // FEDERATED_DECENTRALIZED
    self->_lf__disturbance_end_reactions[0] = &self->_lf__reaction_1;
    self->_lf__disturbance_end.reactions = &self->_lf__disturbance_end_reactions[0];
    self->_lf__disturbance_end.number_of_reactions = 1;
    #ifdef FEDERATED
    self->_lf__disturbance_end.physical_time_of_arrival = NEVER;
    #endif // FEDERATED
    self->_lf__disturbance_end.is_timer = true;
    #ifdef FEDERATED_DECENTRALIZED
    self->_lf__disturbance_end.intended_tag = (tag_t) { .time = NEVER, .microstep = 0u};
    #endif // FEDERATED_DECENTRALIZED
    return self;
}
