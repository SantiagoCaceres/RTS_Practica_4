#ifndef _FLIGHTMONITOR_H
#define _FLIGHTMONITOR_H
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
} _flightmonitor_v_ref_t;
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
} _flightmonitor_v_med_t;
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
} _flightmonitor_u_T_t;
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
} _flightmonitor_v_actual_t;
typedef struct {
    struct self_base_t base;
#line 64 "/workspaces/RTS_Practica_4/src-gen/AircraftController/_flightmonitor.h"
#line 65 "/workspaces/RTS_Practica_4/src-gen/AircraftController/_flightmonitor.h"
    _flightmonitor_v_ref_t* _lf_v_ref;
    // width of -2 indicates that it is not a multiport.
    int _lf_v_ref_width;
    // Default input (in case it does not get connected)
    _flightmonitor_v_ref_t _lf_default__v_ref;
    _flightmonitor_v_med_t* _lf_v_med;
    // width of -2 indicates that it is not a multiport.
    int _lf_v_med_width;
    // Default input (in case it does not get connected)
    _flightmonitor_v_med_t _lf_default__v_med;
    _flightmonitor_u_T_t* _lf_u_T;
    // width of -2 indicates that it is not a multiport.
    int _lf_u_T_width;
    // Default input (in case it does not get connected)
    _flightmonitor_u_T_t _lf_default__u_T;
    _flightmonitor_v_actual_t* _lf_v_actual;
    // width of -2 indicates that it is not a multiport.
    int _lf_v_actual_width;
    // Default input (in case it does not get connected)
    _flightmonitor_v_actual_t _lf_default__v_actual;
    reaction_t _lf__reaction_0;
    trigger_t _lf__monitor_timer;
    reaction_t* _lf__monitor_timer_reactions[1];
    trigger_t _lf__v_ref;
    #ifdef FEDERATED
    
    #endif // FEDERATED
    trigger_t _lf__v_med;
    #ifdef FEDERATED
    
    #endif // FEDERATED
    trigger_t _lf__u_T;
    #ifdef FEDERATED
    
    #endif // FEDERATED
    trigger_t _lf__v_actual;
    #ifdef FEDERATED
    
    #endif // FEDERATED
} _flightmonitor_self_t;
_flightmonitor_self_t* new__flightmonitor();
#endif // _FLIGHTMONITOR_H
