#ifndef WRITE_SHACKLE_STATUS_HPP
#define WRITE_SHACKLE_STATUS_HPP

#include "iostream"
#include "string.h"
#include "modules/system_structs.hpp"
#include "modules/e2prom_works.hpp"
#include "modules/servo.hpp"

extern SOFTWARE_GLOBAL_PARAMETERS_VAR software_parameters_variables;
extern SOFTWARE_GLOBAL_PARAMETERS_FIXED software_parameters_fixed;
extern DEVICE_GLOBAL_HARDWARE_PARAMETERS_FIXED constrcut_MCU_ID_fixed;
extern E2PROM_STORED_DATA_FIXED e2prom_variables;
extern BROADCAST_GLOBAL_VAR broadcast_global_variables;

// char* read_shackle_lock_status( ) {
//       char current_shackle_lock_configuration[] = e2promReadWorks( "current_shackle_lock_configuration" ) ;
//       strcpy( e2prom_variables.current_shackle_lock_configuration, current_shackle_lock_configuration );
//       return current_shackle_lock_configuration;
// }

bool write_shackle_lock_status( const char* new_status) {

      if ( strcmp( new_status, "lock" ) == 0 ) {
            e2promWriteWorks("current_shackle_lock_configuration", "lock" );
            strcpy( e2prom_variables.current_shackle_lock_configuration, "lock" );
            servoWorksDrive( software_parameters_fixed.SHACKLE_LOCK_DEGREE );       // servo action 

      } else if ( strcmp( new_status, "unlock" ) == 0 ) {
            e2promWriteWorks("current_shackle_lock_configuration", "unlock" );
            strcpy( e2prom_variables.current_shackle_lock_configuration, "unlock" );
            servoWorksDrive( software_parameters_fixed.SHACKLE_UNLOCK_DEGREE );     // servo action 
      } else {
            return false;      
      }      
      return true;
}
#endif
