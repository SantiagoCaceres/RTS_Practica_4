#ifndef _AIRDATASENSOR_H
#define _AIRDATASENSOR_H
#include "include/core/reactor.h"

typedef struct {
    token_type_t type;
    lf_token_t* token;
    size_t length;
    bool is_present;
    lf_port_internal_t _base;
    double value;
    #ifdef FEDERATED
    #ifdef FEDERATED_DECENTRALIZED
    tag_t intended_tag;
    #endif
    interval_t physical_time_of_arrival;
    #endif
} _airdatasensor_v_in_t;
typedef struct {
    token_type_t type;
    lf_token_t* token;
    size_t length;
    bool is_present;
    lf_port_internal_t _base;
    double value;
    #ifdef FEDERATED
    #ifdef FEDERATED_DECENTRALIZED
    tag_t intended_tag;
    #endif
    interval_t physical_time_of_arrival;
    #endif
} _airdatasensor_perturbation_input_t;
typedef struct {
    token_type_t type;
    lf_token_t* token;
    size_t length;
    bool is_present;
    lf_port_internal_t _base;
    double value;
    #ifdef FEDERATED
    #ifdef FEDERATED_DECENTRALIZED
    tag_t intended_tag;
    #endif
    interval_t physical_time_of_arrival;
    #endif
} _airdatasensor_v_med_t;
typedef struct {
    struct self_base_t base;
#line 50 "/workspaces/RTS_Practica_4/src-gen/AircraftController/_airdatasensor.h"
    #line 33 "/workspaces/RTS_Practica_4/AircraftController.lf"
    double current_disturbance;
    #line 34 "/workspaces/RTS_Practica_4/AircraftController.lf"
    double current_speed;
#line 55 "/workspaces/RTS_Practica_4/src-gen/AircraftController/_airdatasensor.h"
    _airdatasensor_v_in_t* _lf_v_in;
    // width of -2 indicates that it is not a multiport.
    int _lf_v_in_width;
    // Default input (in case it does not get connected)
    _airdatasensor_v_in_t _lf_default__v_in;
    _airdatasensor_perturbation_input_t* _lf_perturbation_input;
    // width of -2 indicates that it is not a multiport.
    int _lf_perturbation_input_width;
    // Default input (in case it does not get connected)
    _airdatasensor_perturbation_input_t _lf_default__perturbation_input;
    _airdatasensor_v_med_t _lf_v_med;
    int _lf_v_med_width;
    reaction_t _lf__reaction_0;
    reaction_t _lf__reaction_1;
    trigger_t _lf__sensor_timer;
    reaction_t* _lf__sensor_timer_reactions[1];
    trigger_t _lf__v_in;
    reaction_t* _lf__v_in_reactions[1];
    #ifdef FEDERATED
    
    #endif // FEDERATED
    trigger_t _lf__perturbation_input;
    reaction_t* _lf__perturbation_input_reactions[1];
    #ifdef FEDERATED
    
    #endif // FEDERATED
} _airdatasensor_self_t;
_airdatasensor_self_t* new__airdatasensor();
#endif // _AIRDATASENSOR_H
