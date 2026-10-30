#include "include/api/schedule.h"
#include <string.h>
#include "low_level_platform/api/low_level_platform.h"
#include "include/AircraftController/SpeedReference.h"
#include "_speedreference.h"
// ***** Start of method declarations.
// ***** End of method declarations.
#include "include/api/reaction_macros.h"
void _speedreferencereaction_function_0(void* instance_args) {
    _speedreference_self_t* self = (_speedreference_self_t*)instance_args; SUPPRESS_UNUSED_WARNING(self);
    
    #line 19 "/workspaces/RTS_Practica_4/AircraftController.lf"
    // Cuando el tiempo lógico llega a 2 segundos, cambiamos el estado interno
    self->current_ref = 110.0;
    printf("[SpeedReference] Evento: Cambio de referencia a 110.0 m/s\n");
#line 17 "/workspaces/RTS_Practica_4/src-gen/AircraftController/_speedreference.c"
}
#include "include/api/reaction_macros_undef.h"
#include "include/api/reaction_macros.h"
void _speedreferencereaction_function_1(void* instance_args) {
    _speedreference_self_t* self = (_speedreference_self_t*)instance_args; SUPPRESS_UNUSED_WARNING(self);
    _speedreference_v_ref_t* v_ref = &self->_lf_v_ref;
    #line 26 "/workspaces/RTS_Practica_4/AircraftController.lf"
    // Publica la referencia vigente (100.0 al inicio, 110.0 después de los 2s)
    lf_set(v_ref, self->current_ref);
#line 27 "/workspaces/RTS_Practica_4/src-gen/AircraftController/_speedreference.c"
}
#include "include/api/reaction_macros_undef.h"
_speedreference_self_t* new__speedreference() {
    _speedreference_self_t* self = (_speedreference_self_t*)lf_new_reactor(sizeof(_speedreference_self_t));
    self->_lf__reaction_0.number = 0;
    self->_lf__reaction_0.function = _speedreferencereaction_function_0;
    self->_lf__reaction_0.self = self;
    self->_lf__reaction_0.deadline_violation_handler = NULL;
    self->_lf__reaction_0.STP_handler = NULL;
    self->_lf__reaction_0.name = "?";
    self->_lf__reaction_0.mode = NULL;
    self->_lf__reaction_1.number = 1;
    self->_lf__reaction_1.function = _speedreferencereaction_function_1;
    self->_lf__reaction_1.self = self;
    self->_lf__reaction_1.deadline_violation_handler = NULL;
    self->_lf__reaction_1.STP_handler = NULL;
    self->_lf__reaction_1.name = "?";
    self->_lf__reaction_1.mode = NULL;
    self->_lf__ref_timer.last_tag = NEVER_TAG;
    #ifdef FEDERATED_DECENTRALIZED
    self->_lf__ref_timer.intended_tag = (tag_t) { .time = NEVER, .microstep = 0u};
    #endif // FEDERATED_DECENTRALIZED
    self->_lf__ref_timer_reactions[0] = &self->_lf__reaction_1;
    self->_lf__ref_timer.reactions = &self->_lf__ref_timer_reactions[0];
    self->_lf__ref_timer.number_of_reactions = 1;
    #ifdef FEDERATED
    self->_lf__ref_timer.physical_time_of_arrival = NEVER;
    #endif // FEDERATED
    self->_lf__ref_timer.is_timer = true;
    #ifdef FEDERATED_DECENTRALIZED
    self->_lf__ref_timer.intended_tag = (tag_t) { .time = NEVER, .microstep = 0u};
    #endif // FEDERATED_DECENTRALIZED
    self->_lf__step_event.last_tag = NEVER_TAG;
    #ifdef FEDERATED_DECENTRALIZED
    self->_lf__step_event.intended_tag = (tag_t) { .time = NEVER, .microstep = 0u};
    #endif // FEDERATED_DECENTRALIZED
    self->_lf__step_event_reactions[0] = &self->_lf__reaction_0;
    self->_lf__step_event.reactions = &self->_lf__step_event_reactions[0];
    self->_lf__step_event.number_of_reactions = 1;
    #ifdef FEDERATED
    self->_lf__step_event.physical_time_of_arrival = NEVER;
    #endif // FEDERATED
    self->_lf__step_event.is_timer = true;
    #ifdef FEDERATED_DECENTRALIZED
    self->_lf__step_event.intended_tag = (tag_t) { .time = NEVER, .microstep = 0u};
    #endif // FEDERATED_DECENTRALIZED
    return self;
}
