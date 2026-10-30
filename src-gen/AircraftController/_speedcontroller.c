#include "include/api/schedule.h"
#include <string.h>
#include "low_level_platform/api/low_level_platform.h"
#include "include/AircraftController/SpeedController.h"
#include "_speedcontroller.h"
// ***** Start of method declarations.
// ***** End of method declarations.
#include "include/api/reaction_macros.h"
void _speedcontrollerreaction_function_0(void* instance_args) {
    _speedcontroller_self_t* self = (_speedcontroller_self_t*)instance_args; SUPPRESS_UNUSED_WARNING(self);
    _speedcontroller_v_ref_in_t* v_ref_in = self->_lf_v_ref_in;
    int v_ref_in_width = self->_lf_v_ref_in_width; SUPPRESS_UNUSED_WARNING(v_ref_in_width);
    #line 80 "/workspaces/RTS_Practica_4/AircraftController.lf"
    // Cuando llegue un evento de cambio de referencia, lo guardamos en el estado interno
    self->current_vref = v_ref_in->value;
#line 17 "/workspaces/RTS_Practica_4/src-gen/AircraftController/_speedcontroller.c"
}
#include "include/api/reaction_macros_undef.h"
#include "include/api/reaction_macros.h"
void _speedcontrollerreaction_function_1(void* instance_args) {
    _speedcontroller_self_t* self = (_speedcontroller_self_t*)instance_args; SUPPRESS_UNUSED_WARNING(self);
    _speedcontroller_v_med_t* v_med = self->_lf_v_med;
    int v_med_width = self->_lf_v_med_width; SUPPRESS_UNUSED_WARNING(v_med_width);
    _speedcontroller_u_T_t* u_T = &self->_lf_u_T;
    #line 86 "/workspaces/RTS_Practica_4/AircraftController.lf"
    // 1. Obtener la velocidad medida (si está presente)
    double current_vmed = 0.0;
    if (v_med->is_present) {
        current_vmed = v_med->value;
    }
    
    // 2. Calcular el error de velocidad
    double error_v = self->current_vref - current_vmed;
    
    // 3. Control Proporcional y Saturación sat(x, 0, 1)
    double control_signal = self->Kp * error_v;
    
    if (control_signal > 1.0) {
        control_signal = 1.0;
    } else if (control_signal < 0.0) {
        control_signal = 0.0;
    }
    
    // 4. Publicar el comando de empuje normalizado
    lf_set(u_T, control_signal);
#line 47 "/workspaces/RTS_Practica_4/src-gen/AircraftController/_speedcontroller.c"
}
#include "include/api/reaction_macros_undef.h"
_speedcontroller_self_t* new__speedcontroller() {
    _speedcontroller_self_t* self = (_speedcontroller_self_t*)lf_new_reactor(sizeof(_speedcontroller_self_t));
    // Set input by default to an always absent default input.
    self->_lf_v_med = &self->_lf_default__v_med;
    // Set the default source reactor pointer
    self->_lf_default__v_med._base.source_reactor = (self_base_t*)self;
    // Set input by default to an always absent default input.
    self->_lf_v_ref_in = &self->_lf_default__v_ref_in;
    // Set the default source reactor pointer
    self->_lf_default__v_ref_in._base.source_reactor = (self_base_t*)self;
    self->_lf__reaction_0.number = 0;
    self->_lf__reaction_0.function = _speedcontrollerreaction_function_0;
    self->_lf__reaction_0.self = self;
    self->_lf__reaction_0.deadline_violation_handler = NULL;
    self->_lf__reaction_0.STP_handler = NULL;
    self->_lf__reaction_0.name = "?";
    self->_lf__reaction_0.mode = NULL;
    self->_lf__reaction_1.number = 1;
    self->_lf__reaction_1.function = _speedcontrollerreaction_function_1;
    self->_lf__reaction_1.self = self;
    self->_lf__reaction_1.deadline_violation_handler = NULL;
    self->_lf__reaction_1.STP_handler = NULL;
    self->_lf__reaction_1.name = "?";
    self->_lf__reaction_1.mode = NULL;
    self->_lf__controller_timer.last_tag = NEVER_TAG;
    #ifdef FEDERATED_DECENTRALIZED
    self->_lf__controller_timer.intended_tag = (tag_t) { .time = NEVER, .microstep = 0u};
    #endif // FEDERATED_DECENTRALIZED
    self->_lf__controller_timer_reactions[0] = &self->_lf__reaction_1;
    self->_lf__controller_timer.reactions = &self->_lf__controller_timer_reactions[0];
    self->_lf__controller_timer.number_of_reactions = 1;
    #ifdef FEDERATED
    self->_lf__controller_timer.physical_time_of_arrival = NEVER;
    #endif // FEDERATED
    self->_lf__controller_timer.is_timer = true;
    #ifdef FEDERATED_DECENTRALIZED
    self->_lf__controller_timer.intended_tag = (tag_t) { .time = NEVER, .microstep = 0u};
    #endif // FEDERATED_DECENTRALIZED
    self->_lf__v_med.last_tag = NEVER_TAG;
    #ifdef FEDERATED_DECENTRALIZED
    self->_lf__v_med.intended_tag = (tag_t) { .time = NEVER, .microstep = 0u};
    #endif // FEDERATED_DECENTRALIZED
    self->_lf__v_med.tmplt.type.element_size = sizeof(double);
    self->_lf__v_ref_in.last_tag = NEVER_TAG;
    #ifdef FEDERATED_DECENTRALIZED
    self->_lf__v_ref_in.intended_tag = (tag_t) { .time = NEVER, .microstep = 0u};
    #endif // FEDERATED_DECENTRALIZED
    self->_lf__v_ref_in_reactions[0] = &self->_lf__reaction_0;
    self->_lf__v_ref_in.reactions = &self->_lf__v_ref_in_reactions[0];
    self->_lf__v_ref_in.number_of_reactions = 1;
    #ifdef FEDERATED
    self->_lf__v_ref_in.physical_time_of_arrival = NEVER;
    #endif // FEDERATED
    self->_lf__v_ref_in.tmplt.type.element_size = sizeof(double);
    return self;
}
