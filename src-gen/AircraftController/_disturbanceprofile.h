#ifndef _DISTURBANCEPROFILE_H
#define _DISTURBANCEPROFILE_H
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
} _disturbanceprofile_dv_t;
typedef struct {
    struct self_base_t base;
#line 22 "/workspaces/RTS_Practica_4/src-gen/AircraftController/_disturbanceprofile.h"
#line 23 "/workspaces/RTS_Practica_4/src-gen/AircraftController/_disturbanceprofile.h"
    _disturbanceprofile_dv_t _lf_dv;
    int _lf_dv_width;
    reaction_t _lf__reaction_0;
    reaction_t _lf__reaction_1;
    trigger_t _lf__disturbance_start;
    reaction_t* _lf__disturbance_start_reactions[1];
    trigger_t _lf__disturbance_end;
    reaction_t* _lf__disturbance_end_reactions[1];
} _disturbanceprofile_self_t;
_disturbanceprofile_self_t* new__disturbanceprofile();
#endif // _DISTURBANCEPROFILE_H
