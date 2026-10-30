#ifndef _SPEEDREFERENCE_H
#define _SPEEDREFERENCE_H
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
} _speedreference_v_ref_t;
typedef struct {
    struct self_base_t base;
#line 22 "/workspaces/RTS_Practica_4/src-gen/AircraftController/_speedreference.h"
    #line 6 "/workspaces/RTS_Practica_4/AircraftController.lf"
    double current_ref;
#line 25 "/workspaces/RTS_Practica_4/src-gen/AircraftController/_speedreference.h"
    _speedreference_v_ref_t _lf_v_ref;
    int _lf_v_ref_width;
    reaction_t _lf__reaction_0;
    reaction_t _lf__reaction_1;
    trigger_t _lf__ref_timer;
    reaction_t* _lf__ref_timer_reactions[1];
    trigger_t _lf__step_event;
    reaction_t* _lf__step_event_reactions[1];
} _speedreference_self_t;
_speedreference_self_t* new__speedreference();
#endif // _SPEEDREFERENCE_H
