#ifndef __LF_GENDELAY_70AA8AA2_H
#define __LF_GENDELAY_70AA8AA2_H
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
} __lf_gendelay_70aa8aa2_inp_t;
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
} __lf_gendelay_70aa8aa2_out_t;
typedef struct {
    token_type_t type;
    lf_token_t* token;
    size_t length;
    bool is_present;
    lf_action_internal_t _base;
    self_base_t* parent;
    bool has_value;
    int source_id;
    double value;
    #ifdef FEDERATED
    #ifdef FEDERATED_DECENTRALIZED
    tag_t intended_tag;
    #endif
    interval_t physical_time_of_arrival;
    #endif
} __lf_gendelay_70aa8aa2_act_t;
typedef struct {
    struct self_base_t base;
    interval_t delay;
#line 54 "/workspaces/RTS_Practica_4/src-gen/AircraftController/__lf_gendelay_70aa8aa2.h"
#line 55 "/workspaces/RTS_Practica_4/src-gen/AircraftController/__lf_gendelay_70aa8aa2.h"
    __lf_gendelay_70aa8aa2_act_t _lf_act;
    __lf_gendelay_70aa8aa2_inp_t* _lf_inp;
    // width of -2 indicates that it is not a multiport.
    int _lf_inp_width;
    // Default input (in case it does not get connected)
    __lf_gendelay_70aa8aa2_inp_t _lf_default__inp;
    __lf_gendelay_70aa8aa2_out_t _lf_out;
    int _lf_out_width;
    reaction_t _lf__reaction_0;
    reaction_t _lf__reaction_1;
    trigger_t _lf__act;
    reaction_t* _lf__act_reactions[1];
    trigger_t _lf__inp;
    reaction_t* _lf__inp_reactions[1];
    #ifdef FEDERATED
    
    #endif // FEDERATED
} __lf_gendelay_70aa8aa2_self_t;
__lf_gendelay_70aa8aa2_self_t* new___lf_gendelay_70aa8aa2();
#endif // __LF_GENDELAY_70AA8AA2_H
