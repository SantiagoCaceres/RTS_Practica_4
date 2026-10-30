#ifndef _SPEEDCONTROLLER_H
#define _SPEEDCONTROLLER_H
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
} _speedcontroller_v_med_t;
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
} _speedcontroller_v_ref_in_t;
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
} _speedcontroller_u_T_t;
typedef struct {
    struct self_base_t base;
#line 50 "/workspaces/RTS_Practica_4/src-gen/AircraftController/_speedcontroller.h"
    #line 67 "/workspaces/RTS_Practica_4/AircraftController.lf"
    double Kp;
    #line 68 "/workspaces/RTS_Practica_4/AircraftController.lf"
    double current_vref;
#line 55 "/workspaces/RTS_Practica_4/src-gen/AircraftController/_speedcontroller.h"
    _speedcontroller_v_med_t* _lf_v_med;
    // width of -2 indicates that it is not a multiport.
    int _lf_v_med_width;
    // Default input (in case it does not get connected)
    _speedcontroller_v_med_t _lf_default__v_med;
    _speedcontroller_v_ref_in_t* _lf_v_ref_in;
    // width of -2 indicates that it is not a multiport.
    int _lf_v_ref_in_width;
    // Default input (in case it does not get connected)
    _speedcontroller_v_ref_in_t _lf_default__v_ref_in;
    _speedcontroller_u_T_t _lf_u_T;
    int _lf_u_T_width;
    reaction_t _lf__reaction_0;
    reaction_t _lf__reaction_1;
    trigger_t _lf__controller_timer;
    reaction_t* _lf__controller_timer_reactions[1];
    trigger_t _lf__v_med;
    #ifdef FEDERATED
    
    #endif // FEDERATED
    trigger_t _lf__v_ref_in;
    reaction_t* _lf__v_ref_in_reactions[1];
    #ifdef FEDERATED
    
    #endif // FEDERATED
} _speedcontroller_self_t;
_speedcontroller_self_t* new__speedcontroller();
#endif // _SPEEDCONTROLLER_H
