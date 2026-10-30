#include "include/api/schedule.h"
#include <string.h>
#include "low_level_platform/api/low_level_platform.h"
#include "include/AircraftController/AircraftDynamics.h"
#include "_aircraftdynamics.h"
// ***** Start of method declarations.
// ***** End of method declarations.
#include "include/api/reaction_macros.h"
void _aircraftdynamicsreaction_function_0(void* instance_args) {
    _aircraftdynamics_self_t* self = (_aircraftdynamics_self_t*)instance_args; SUPPRESS_UNUSED_WARNING(self);
    _aircraftdynamics_u_T_t* u_T = self->_lf_u_T;
    int u_T_width = self->_lf_u_T_width; SUPPRESS_UNUSED_WARNING(u_T_width);
    _aircraftdynamics_v_out_t* v_out = &self->_lf_v_out;
    #line 127 "/workspaces/RTS_Practica_4/AircraftController.lf"
    // 1. Leer el comando de empuje. 
    // Si no ha llegado ninguno, asumimos 0 (o el último estado, según el diseño)
    double current_u = 0.0;
    if (u_T->is_present) {
        current_u = u_T->value;
    }
    
    // 2. Aplicar la ecuación en diferencias: v[k+1] = v[k] + Ts(a_T * u_T[k] - a_D * v[k])
    self->v = self->v + self->Ts * (self->a_T * current_u - self->a_D * self->v);
    
    // 3. Publicar la velocidad simulada actualizada
    lf_set(v_out, self->v);
#line 28 "/workspaces/RTS_Practica_4/src-gen/AircraftController/_aircraftdynamics.c"
}
#include "include/api/reaction_macros_undef.h"
_aircraftdynamics_self_t* new__aircraftdynamics() {
    _aircraftdynamics_self_t* self = (_aircraftdynamics_self_t*)lf_new_reactor(sizeof(_aircraftdynamics_self_t));
    // Set input by default to an always absent default input.
    self->_lf_u_T = &self->_lf_default__u_T;
    // Set the default source reactor pointer
    self->_lf_default__u_T._base.source_reactor = (self_base_t*)self;
    self->_lf__reaction_0.number = 0;
    self->_lf__reaction_0.function = _aircraftdynamicsreaction_function_0;
    self->_lf__reaction_0.self = self;
    self->_lf__reaction_0.deadline_violation_handler = NULL;
    self->_lf__reaction_0.STP_handler = NULL;
    self->_lf__reaction_0.name = "?";
    self->_lf__reaction_0.mode = NULL;
    self->_lf__update_timer.last_tag = NEVER_TAG;
    #ifdef FEDERATED_DECENTRALIZED
    self->_lf__update_timer.intended_tag = (tag_t) { .time = NEVER, .microstep = 0u};
    #endif // FEDERATED_DECENTRALIZED
    self->_lf__update_timer_reactions[0] = &self->_lf__reaction_0;
    self->_lf__update_timer.reactions = &self->_lf__update_timer_reactions[0];
    self->_lf__update_timer.number_of_reactions = 1;
    #ifdef FEDERATED
    self->_lf__update_timer.physical_time_of_arrival = NEVER;
    #endif // FEDERATED
    self->_lf__update_timer.is_timer = true;
    #ifdef FEDERATED_DECENTRALIZED
    self->_lf__update_timer.intended_tag = (tag_t) { .time = NEVER, .microstep = 0u};
    #endif // FEDERATED_DECENTRALIZED
    self->_lf__u_T.last_tag = NEVER_TAG;
    #ifdef FEDERATED_DECENTRALIZED
    self->_lf__u_T.intended_tag = (tag_t) { .time = NEVER, .microstep = 0u};
    #endif // FEDERATED_DECENTRALIZED
    self->_lf__u_T.tmplt.type.element_size = sizeof(double);
    return self;
}
