#ifndef GLOBAL_TIMER_HPP
#define GLOBAL_TIMER_HPP

#include "iostream"
#include "string.h"
#include "modules/system_structs.hpp"
#include "modules/e2prom_works.hpp"
#include "modules/servo.hpp"

// extern SOFTWARE_GLOBAL_PARAMETERS_VAR software_parameters_variables;
// extern SOFTWARE_GLOBAL_PARAMETERS_FIXED software_parameters_fixed;
// extern DEVICE_GLOBAL_HARDWARE_PARAMETERS_FIXED constrcut_mcu_id_fixed;
// extern E2PROM_STORED_DATA_FIXED e2prom_variables;
// extern BROADCAST_GLOBAL_VAR broadcast_global_variables;

void timer_global_initiation() {}

void timer_global_startup() {}

void timer_global_action( ) {
    software_parameters_variables.global_current_millis = millis();
}
#endif
