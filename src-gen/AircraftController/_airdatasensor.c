#include "include/api/schedule.h"
#include <string.h>
#include "low_level_platform/api/low_level_platform.h"
#include "include/AircraftController/AirDataSensor.h"
#include "_airdatasensor.h"
// ***** Start of method declarations.
// ***** End of method declarations.
#include "include/api/reaction_macros.h"
void _airdatasensorreaction_function_0(void* instance_args) {
    _airdatasensor_self_t* self = (_airdatasensor_self_t*)instance_args; SUPPRESS_UNUSED_WARNING(self);
    _airdatasensor_perturbation_input_t* perturbation_input = self->_lf_perturbation_input;
    int perturbation_input_width = self->_lf_perturbation_input_width; SUPPRESS_UNUSED_WARNING(perturbation_input_width);
    #line 46 "/workspaces/RTS_Practica_4/AircraftController.lf"
    // Cuando llega un evento, actualiza el estado interno
    self->current_disturbance = perturbation_input->value;
#line 17 "/workspaces/RTS_Practica_4/src-gen/AircraftController/_airdatasensor.c"
}
#include "include/api/reaction_macros_undef.h"
#include "include/api/reaction_macros.h"
void _airdatasensorreaction_function_1(void* instance_args) {
    _airdatasensor_self_t* self = (_airdatasensor_self_t*)instance_args; SUPPRESS_UNUSED_WARNING(self);
    _airdatasensor_v_in_t* v_in = self->_lf_v_in;
    int v_in_width = self->_lf_v_in_width; SUPPRESS_UNUSED_WARNING(v_in_width);
    _airdatasensor_v_med_t* v_med = &self->_lf_v_med;
    #line 52 "/workspaces/RTS_Practica_4/AircraftController.lf"
    // Actualizar la muestra si llegó un dato nuevo de la planta
    if (v_in->is_present) {
        self->current_speed = v_in->value;
    }
    
    // Aplicar el modelo: v_med[k] = v[k] + d_v[k]
    double measured_speed = self->current_speed + self->current_disturbance;
    
    // Publicar la última muestra disponible en cada período del sensor
    lf_set(v_med, measured_speed);
#line 37 "/workspaces/RTS_Practica_4/src-gen/AircraftController/_airdatasensor.c"
}
#include "include/api/reaction_macros_undef.h"
_airdatasensor_self_t* new__airdatasensor() {
    _airdatasensor_self_t* self = (_airdatasensor_self_t*)lf_new_reactor(sizeof(_airdatasensor_self_t));
    // Set input by default to an always absent default input.
    self->_lf_v_in = &self->_lf_default__v_in;
    // Set the default source reactor pointer
    self->_lf_default__v_in._base.source_reactor = (self_base_t*)self;
    // Set input by default to an always absent default input.
    self->_lf_perturbation_input = &self->_lf_default__perturbation_input;
    // Set the default source reactor pointer
    self->_lf_default__perturbation_input._base.source_reactor = (self_base_t*)self;
    self->_lf__reaction_0.number = 0;
    self->_lf__reaction_0.function = _airdatasensorreaction_function_0;
    self->_lf__reaction_0.self = self;
    self->_lf__reaction_0.deadline_violation_handler = NULL;
    self->_lf__reaction_0.STP_handler = NULL;
    self->_lf__reaction_0.name = "?";
    self->_lf__reaction_0.mode = NULL;
    self->_lf__reaction_1.number = 1;
    self->_lf__reaction_1.function = _airdatasensorreaction_function_1;
    self->_lf__reaction_1.self = self;
    self->_lf__reaction_1.deadline_violation_handler = NULL;
    self->_lf__reaction_1.STP_handler = NULL;
    self->_lf__reaction_1.name = "?";
    self->_lf__reaction_1.mode = NULL;
    self->_lf__sensor_timer.last_tag = NEVER_TAG;
    #ifdef FEDERATED_DECENTRALIZED
    self->_lf__sensor_timer.intended_tag = (tag_t) { .time = NEVER, .microstep = 0u};
    #endif // FEDERATED_DECENTRALIZED
    self->_lf__sensor_timer_reactions[0] = &self->_lf__reaction_1;
    self->_lf__sensor_timer.reactions = &self->_lf__sensor_timer_reactions[0];
    self->_lf__sensor_timer.number_of_reactions = 1;
    #ifdef FEDERATED
    self->_lf__sensor_timer.physical_time_of_arrival = NEVER;
    #endif // FEDERATED
    self->_lf__sensor_timer.is_timer = true;
    #ifdef FEDERATED_DECENTRALIZED
    self->_lf__sensor_timer.intended_tag = (tag_t) { .time = NEVER, .microstep = 0u};
    #endif // FEDERATED_DECENTRALIZED
    self->_lf__v_in.last_tag = NEVER_TAG;
    #ifdef FEDERATED_DECENTRALIZED
    self->_lf__v_in.intended_tag = (tag_t) { .time = NEVER, .microstep = 0u};
    #endif // FEDERATED_DECENTRALIZED
    self->_lf__v_in_reactions[0] = &self->_lf__reaction_1;
    self->_lf__v_in.reactions = &self->_lf__v_in_reactions[0];
    self->_lf__v_in.number_of_reactions = 1;
    #ifdef FEDERATED
    self->_lf__v_in.physical_time_of_arrival = NEVER;
    #endif // FEDERATED
    self->_lf__v_in.tmplt.type.element_size = sizeof(double);
    self->_lf__perturbation_input.last_tag = NEVER_TAG;
    #ifdef FEDERATED_DECENTRALIZED
    self->_lf__perturbation_input.intended_tag = (tag_t) { .time = NEVER, .microstep = 0u};
    #endif // FEDERATED_DECENTRALIZED
    self->_lf__perturbation_input_reactions[0] = &self->_lf__reaction_0;
    self->_lf__perturbation_input.reactions = &self->_lf__perturbation_input_reactions[0];
    self->_lf__perturbation_input.number_of_reactions = 1;
    #ifdef FEDERATED
    self->_lf__perturbation_input.physical_time_of_arrival = NEVER;
    #endif // FEDERATED
    self->_lf__perturbation_input.tmplt.type.element_size = sizeof(double);
    return self;
}
