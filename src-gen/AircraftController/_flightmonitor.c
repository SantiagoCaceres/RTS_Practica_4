#include "include/api/schedule.h"
#include <string.h>
#include "low_level_platform/api/low_level_platform.h"
#include "include/AircraftController/FlightMonitor.h"
#include "_flightmonitor.h"
// ***** Start of method declarations.
// ***** End of method declarations.
#include "include/api/reaction_macros.h"
void _flightmonitorreaction_function_0(void* instance_args) {
    _flightmonitor_self_t* self = (_flightmonitor_self_t*)instance_args; SUPPRESS_UNUSED_WARNING(self);
    _flightmonitor_v_ref_t* v_ref = self->_lf_v_ref;
    int v_ref_width = self->_lf_v_ref_width; SUPPRESS_UNUSED_WARNING(v_ref_width);
    _flightmonitor_v_med_t* v_med = self->_lf_v_med;
    int v_med_width = self->_lf_v_med_width; SUPPRESS_UNUSED_WARNING(v_med_width);
    _flightmonitor_u_T_t* u_T = self->_lf_u_T;
    int u_T_width = self->_lf_u_T_width; SUPPRESS_UNUSED_WARNING(u_T_width);
    _flightmonitor_v_actual_t* v_actual = self->_lf_v_actual;
    int v_actual_width = self->_lf_v_actual_width; SUPPRESS_UNUSED_WARNING(v_actual_width);
    #line 153 "/workspaces/RTS_Practica_4/AircraftController.lf"
    // 1. Obtener los tiempos lógico y físico en nanosegundos y convertirlos a milisegundos
    instant_t logical_time = lf_time_logical() / 1000000;
    instant_t physical_time = lf_time_physical() / 1000000;
    
    // 2. Extraer los datos (si están presentes en este ciclo)
    double ref = v_ref->is_present ? v_ref->value : 0.0;
    double med = v_med->is_present ? v_med->value : 0.0;
    double cmd = u_T->is_present ? u_T->value : 0.0;
    double real = v_actual->is_present ? v_actual->value : 0.0;
    
    // 3. Imprimir el registro para tu análisis y gráficas posteriores
    printf("[FlightMonitor] Tag Logica: %lld ms | Tiempo Fisico: %lld ms | ",
           (long long)logical_time, (long long)physical_time);
    printf("v_ref: %.1f | v_med: %.2f | v_real: %.2f | u_T: %.3f\n", ref, med, real, cmd);
#line 35 "/workspaces/RTS_Practica_4/src-gen/AircraftController/_flightmonitor.c"
}
#include "include/api/reaction_macros_undef.h"
_flightmonitor_self_t* new__flightmonitor() {
    _flightmonitor_self_t* self = (_flightmonitor_self_t*)lf_new_reactor(sizeof(_flightmonitor_self_t));
    // Set input by default to an always absent default input.
    self->_lf_v_ref = &self->_lf_default__v_ref;
    // Set the default source reactor pointer
    self->_lf_default__v_ref._base.source_reactor = (self_base_t*)self;
    // Set input by default to an always absent default input.
    self->_lf_v_med = &self->_lf_default__v_med;
    // Set the default source reactor pointer
    self->_lf_default__v_med._base.source_reactor = (self_base_t*)self;
    // Set input by default to an always absent default input.
    self->_lf_u_T = &self->_lf_default__u_T;
    // Set the default source reactor pointer
    self->_lf_default__u_T._base.source_reactor = (self_base_t*)self;
    // Set input by default to an always absent default input.
    self->_lf_v_actual = &self->_lf_default__v_actual;
    // Set the default source reactor pointer
    self->_lf_default__v_actual._base.source_reactor = (self_base_t*)self;
    self->_lf__reaction_0.number = 0;
    self->_lf__reaction_0.function = _flightmonitorreaction_function_0;
    self->_lf__reaction_0.self = self;
    self->_lf__reaction_0.deadline_violation_handler = NULL;
    self->_lf__reaction_0.STP_handler = NULL;
    self->_lf__reaction_0.name = "?";
    self->_lf__reaction_0.mode = NULL;
    self->_lf__monitor_timer.last_tag = NEVER_TAG;
    #ifdef FEDERATED_DECENTRALIZED
    self->_lf__monitor_timer.intended_tag = (tag_t) { .time = NEVER, .microstep = 0u};
    #endif // FEDERATED_DECENTRALIZED
    self->_lf__monitor_timer_reactions[0] = &self->_lf__reaction_0;
    self->_lf__monitor_timer.reactions = &self->_lf__monitor_timer_reactions[0];
    self->_lf__monitor_timer.number_of_reactions = 1;
    #ifdef FEDERATED
    self->_lf__monitor_timer.physical_time_of_arrival = NEVER;
    #endif // FEDERATED
    self->_lf__monitor_timer.is_timer = true;
    #ifdef FEDERATED_DECENTRALIZED
    self->_lf__monitor_timer.intended_tag = (tag_t) { .time = NEVER, .microstep = 0u};
    #endif // FEDERATED_DECENTRALIZED
    self->_lf__v_ref.last_tag = NEVER_TAG;
    #ifdef FEDERATED_DECENTRALIZED
    self->_lf__v_ref.intended_tag = (tag_t) { .time = NEVER, .microstep = 0u};
    #endif // FEDERATED_DECENTRALIZED
    self->_lf__v_ref.tmplt.type.element_size = sizeof(double);
    self->_lf__v_med.last_tag = NEVER_TAG;
    #ifdef FEDERATED_DECENTRALIZED
    self->_lf__v_med.intended_tag = (tag_t) { .time = NEVER, .microstep = 0u};
    #endif // FEDERATED_DECENTRALIZED
    self->_lf__v_med.tmplt.type.element_size = sizeof(double);
    self->_lf__u_T.last_tag = NEVER_TAG;
    #ifdef FEDERATED_DECENTRALIZED
    self->_lf__u_T.intended_tag = (tag_t) { .time = NEVER, .microstep = 0u};
    #endif // FEDERATED_DECENTRALIZED
    self->_lf__u_T.tmplt.type.element_size = sizeof(double);
    self->_lf__v_actual.last_tag = NEVER_TAG;
    #ifdef FEDERATED_DECENTRALIZED
    self->_lf__v_actual.intended_tag = (tag_t) { .time = NEVER, .microstep = 0u};
    #endif // FEDERATED_DECENTRALIZED
    self->_lf__v_actual.tmplt.type.element_size = sizeof(double);
    return self;
}
