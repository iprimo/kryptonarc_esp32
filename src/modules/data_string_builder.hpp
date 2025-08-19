#ifndef DATA_STRING_BUILDER_HPP
#define DATA_STRING_BUILDER_HPP

#include "iostream"
#include "string.h"
#include "modules/system_structs.hpp"

// extern SOFTWARE_GLOBAL_PARAMETERS_VAR software_parameters_variables;
// extern SOFTWARE_GLOBAL_PARAMETERS_FIXED software_parameters_fixed;
// extern DEVICE_GLOBAL_HARDWARE_PARAMETERS_FIXED constrcut_mcu_id_fixed;
// extern E2PROM_STORED_DATA_FIXED e2prom_variables;
// extern BROADCAST_GLOBAL_VAR broadcast_global_variables;

void append_bluetooth_session_sequence( char* processingString ) {


      //////////////////////////////////////////      
      // Session Management
      strcat(processingString, "sM_");

      //////////////////////////////////////////      
      // Request session Sequence
      int randomNumber = random(0, 2147483640);
      software_parameters_variables.data_transfer_sequence_ble = randomNumber ;
      char charArray[5];  // Assuming a 4-digit integer plus the null terminator
      sprintf(charArray, "%d", software_parameters_variables.data_transfer_sequence_ble);


      strcat(processingString, "bLESSEQ_");  // BLE Session Sequest
      strcat(processingString, charArray );
      strcat(processingString, "_bLESSEQ");


      //////////////////////////////////////////      
      // time stamp
      strcat(processingString, "tS_");  // BLE Session Sequest
      strcat(processingString, software_parameters_variables.incoming_data_time_stamp );
      strcat(processingString, "_tS");

      //////////////////////////////////////////      
      // Session Management
      strcat(processingString, "_sM");
}

void append_status_information( char* processingString ) {

      //////////////////////////////////////////      
      // Hardware Status
      strcat(processingString, "sI_");

      //////////////////////////////////////////      
      // currnet lock state
      strcat(processingString, "cSLC_");
      strcat(processingString, e2prom_variables.current_shackle_lock_configuration );
      strcat(processingString, "_cSLC");


      //////////////////////////////////////////      
      // temperture
      strcat(processingString, "tmp_");
      strcat(processingString, "0.0" );
      strcat(processingString, "_tmp");


      //////////////////////////////////////////      
      // Hardware Info starter and ender char
      strcat(processingString, "_sI");

}

void append_config_information( char* processingString ) {

      //////////////////////////////////////////      
      // Hardware Info starter and ender char
      strcat(processingString, "cI_");

      //////////////////////////////////////////      
      // tX: Tenant XigCode
      strcat(processingString, "tXC_");
      strcat(processingString, e2prom_variables.tenant_xc );
      strcat(processingString, "_tXC");

      //////////////////////////////////////////      
      // DX: Device XigCode
      strcat(processingString, "dXC_");
      strcat(processingString, e2prom_variables.device_xc );
      strcat(processingString, "_dXC");



      //////////////////////////////////////////      
      // Hardware Info starter and ender char
      strcat(processingString, "_cI");

}

void append_secret_config_information( char* processingString ) {

      // hashKey_Internal
      strcat(processingString, "scHK_");
      strcat(processingString, "00000_abc123abc1" );
      strcat(processingString, "_scHK");
      // encryptionKey_Internal
      strcat(processingString, "scEnI_");
      strcat(processingString, "00001_abc123abc1" );
      strcat(processingString, "_scEnI");
      // keySmithKeyOnline_Internal
      strcat(processingString, "scKSO_");
      strcat(processingString, "00002_abc123abc1" );
      strcat(processingString, "_scKSO");
      // lastResortKeyOffline_Internal
      strcat(processingString, "scLRKO_");
      strcat(processingString, "00003_abc123abc1" );
      strcat(processingString, "_scLRKO");

      // hashKey02_Internal
      strcat(processingString, "scHK02_");
      strcat(processingString, "00004_abc123abc1" );
      strcat(processingString, "_scHK02");
      // encryptionKey02_Internal
      strcat(processingString, "scEnI02_");
      strcat(processingString, "00005_abc123abc1" );
      strcat(processingString, "_scEnI02");
      // keySmithKeyOnline02_Internal
      strcat(processingString, "scKSO02_");
      strcat(processingString, "00006_abc123abc1" );
      strcat(processingString, "_scKSO02");
      // lastResortKeyOffline02_Internal
      strcat(processingString, "scLRKO02_");
      strcat(processingString, "00007_abc123abc1" );
      strcat(processingString, "_scLRKO02");

}

void append_firmware_information( char* processingString ) {

      //////////////////////////////////////////      
      // Hardware Info starter and ender char
      strcat(processingString, "fI_");

      //////////////////////////////////////////      
      // HWCM: Hardware ChipModel
      strcat(processingString, "fIV_");
      strcat(processingString, software_parameters_fixed.FIRMWARE_VERSION );
      strcat(processingString, "_fIV");


      //////////////////////////////////////////      
      // Hardware Info starter and ender char
      strcat(processingString, "_fI");

}

void append_hardware_information( char* processingString ) {

      //////////////////////////////////////////      
      // Hardware Info starter and ender char
      strcat(processingString, "hI_");

      //////////////////////////////////////////
      // HU : Hardware UUID
      strcat(processingString, "hU_");
      strcat(processingString, e2prom_variables.hardware_uuid );
      strcat(processingString, "_hU");

      //////////////////////////////////////////      
      // PS: Product Series XigCode
      strcat(processingString, "pS_");
      strcat(processingString, software_parameters_fixed.PRODUCT_SERIES );
      strcat(processingString, "_pS");

      //////////////////////////////////////////      
      // PM: Product Model XigCode
      strcat(processingString, "pM_");
      strcat(processingString, software_parameters_fixed.PRODUCT_MODEL );
      strcat(processingString, "_pM");

      //////////////////////////////////////////      
      // MX: Manufacturer XigCode
      strcat(processingString, "mX_");
      strcat(processingString, e2prom_variables.manufacturer_xc );
      strcat(processingString, "_mX");

      //////////////////////////////////////////      
      // VX: Vender XigCode
      strcat(processingString, "vX_");
      strcat(processingString, e2prom_variables.vender_xc );
      strcat(processingString, "_vX");

      //////////////////////////////////////////
      // BM: Board Model
      strcat(processingString, "bM_");
      strcat(processingString, e2prom_variables.board_model );
      strcat(processingString, "_bM");

      //////////////////////////////////////////      
      // HWCM: Hardware ChipModel
      strcat(processingString, "hWCM_");
      strcat(processingString, constrcut_mcu_id_fixed.cChipModel );
      strcat(processingString, "_hWCM");

      //////////////////////////////////////////      
      // HWCR: Hardware ChipRevision
      strcat(processingString, "hWCR_");
      strcat(processingString, constrcut_mcu_id_fixed.cChipRevision );
      strcat(processingString, "_hWCR");

      //////////////////////////////////////////      
      // HWCC: Hardware ChipCores
      strcat(processingString, "hWCC_");
      strcat(processingString, constrcut_mcu_id_fixed.cChipCores );
      strcat(processingString, "_hWCC");

      //////////////////////////////////////////      
      // HWCI: Hardware ChipId
      strcat(processingString, "hWCI_");
      strcat(processingString, constrcut_mcu_id_fixed.cChipId );
      strcat(processingString, "_hWCI");

      //////////////////////////////////////////      
      // HWAP: Hardware baseMacChrSOFTAP
      strcat(processingString, "hWAP_");
      strcat(processingString, constrcut_mcu_id_fixed.baseMacChrSOFTAP );
      strcat(processingString, "_hWAP");

      //////////////////////////////////////////      
      // HWBT: Hardware baseMacChrBT
      strcat(processingString, "hWBT_");
      strcat(processingString, constrcut_mcu_id_fixed.baseMacChrBT );
      strcat(processingString, "_hWBT");

      //////////////////////////////////////////      
      // HWETH: Hardware baseMacChrETH
      strcat(processingString, "hWETH_");
      strcat(processingString, constrcut_mcu_id_fixed.baseMacChrETH );
      strcat(processingString, "_hWETH");

      //////////////////////////////////////////      
      // HWWIFI: Hardware baseMacChrWiFi
      strcat(processingString, "hWWIFI_");
      strcat(processingString, constrcut_mcu_id_fixed.baseMacChrWiFi );
      strcat(processingString, "hWETH_");

      //////////////////////////////////////////      
      // Hardware Info starter and ender char
      strcat(processingString, "_hI");

}
#endif

