#ifndef _aircraftdynamics_H
#define _aircraftdynamics_H
#ifndef _AIRCRAFTDYNAMICS_H // necessary for arduino-cli, which automatically includes headers that are not used

#ifdef __cplusplus
extern "C" {
#endif
#include "../include/api/schedule.h"
#include "../include/core/reactor.h"
#ifdef __cplusplus
}
#endif
typedef struct aircraftdynamics_self_t{
    self_base_t base; // This field is only to be used by the runtime, not the user.
    double Ts;
    double a_T;
    double a_D;
    double v;
    int end[0]; // placeholder; MSVC does not compile empty structs
} aircraftdynamics_self_t;
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
} aircraftdynamics_u_T_t;
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
} aircraftdynamics_v_out_t;
#endif
#endif
