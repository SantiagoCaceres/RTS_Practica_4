#ifndef _AIRCRAFTDYNAMICS_H
#define _AIRCRAFTDYNAMICS_H
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
} _aircraftdynamics_u_T_t;
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
} _aircraftdynamics_v_out_t;
typedef struct {
    struct self_base_t base;
#line 36 "/workspaces/RTS_Practica_4/src-gen/AircraftController/_aircraftdynamics.h"
    #line 111 "/workspaces/RTS_Practica_4/AircraftController.lf"
    double Ts;
    #line 112 "/workspaces/RTS_Practica_4/AircraftController.lf"
    double a_T;
    #line 113 "/workspaces/RTS_Practica_4/AircraftController.lf"
    double a_D;
    #line 116 "/workspaces/RTS_Practica_4/AircraftController.lf"
    double v;
#line 45 "/workspaces/RTS_Practica_4/src-gen/AircraftController/_aircraftdynamics.h"
    _aircraftdynamics_u_T_t* _lf_u_T;
    // width of -2 indicates that it is not a multiport.
    int _lf_u_T_width;
    // Default input (in case it does not get connected)
    _aircraftdynamics_u_T_t _lf_default__u_T;
    _aircraftdynamics_v_out_t _lf_v_out;
    int _lf_v_out_width;
    reaction_t _lf__reaction_0;
    trigger_t _lf__update_timer;
    reaction_t* _lf__update_timer_reactions[1];
    trigger_t _lf__u_T;
    #ifdef FEDERATED
    
    #endif // FEDERATED
} _aircraftdynamics_self_t;
_aircraftdynamics_self_t* new__aircraftdynamics();
#endif // _AIRCRAFTDYNAMICS_H
