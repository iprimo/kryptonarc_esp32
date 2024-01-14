#include "iostream"
#include "string.h"
#include "modules/system_structs.hpp"

extern SOFTWARE_GLOBAL_PARAMETERS_VAR software_parameters_variables;
extern SOFTWARE_GLOBAL_PARAMETERS_FIXED software_parameters_fixed;
extern DEVICE_GLOBAL_HARDWARE_PARAMETERS_FIXED constrcut_MCU_ID_fixed;
extern E2PROM_STORED_DATA_FIXED e2prom_variables;
extern BROADCAST_GLOBAL_VAR broadcast_global_variables;

#ifndef APPEND_BLE_SESSION_SEQUENCE_HPP
#define APPEND_BLE_SESSION_SEQUENCE_HPP
void append_bluetooth_session_sequence( char* processingString ) {


      //////////////////////////////////////////      
      // Session Management
      strcat(processingString, "|SM");

      //////////////////////////////////////////      
      // Request session Sequence
      int randomNumber = random(1000, 9998);
      software_parameters_variables.data_transfer_sequence_ble = randomNumber ;
      char charArray[5];  // Assuming a 4-digit integer plus the null terminator
      sprintf(charArray, "%d", software_parameters_variables.data_transfer_sequence_ble);


      strcat(processingString, "BLESEQ_");  // BLE Session Sequest
      strcat(processingString, charArray );
      strcat(processingString, "_BLESSEQ");


      //////////////////////////////////////////      
      // Session Management
      strcat(processingString, "SM|");
}
#endif

#ifndef APPEND_CONFIG_INFORMATION_HPP
#define APPEND_CONFIG_INFORMATION_HPP
void append_config_information( char* processingString ) {

      //////////////////////////////////////////      
      // Hardware Info starter and ender char
      strcat(processingString, "|cI");

      //////////////////////////////////////////      
      // TX: Tenant XigCode
      strcat(processingString, "TX_");
      strcat(processingString, e2prom_variables.tenant_xc );
      strcat(processingString, "_TX");

      //////////////////////////////////////////      
      // DX: Device XigCode
      strcat(processingString, "DX_");
      strcat(processingString, e2prom_variables.device_xc );
      strcat(processingString, "_DX");

      //////////////////////////////////////////      
      // Hardware Info starter and ender char
      strcat(processingString, "cI|");

}
#endif

#ifndef APPEND_FIRMWARE_INFORMATION_HPP
#define APPEND_FIRMWARE_INFORMATION_HPP
void append_firmware_information( char* processingString ) {

      //////////////////////////////////////////      
      // Hardware Info starter and ender char
      strcat(processingString, "|fI");

      //////////////////////////////////////////      
      // HWCM: Hardware ChipModel
      strcat(processingString, "FIV_");
      strcat(processingString, software_parameters_fixed.FIRMWARE_VERSION );
      strcat(processingString, "_FIV");


      //////////////////////////////////////////      
      // Hardware Info starter and ender char
      strcat(processingString, "fI|");

}
#endif

#ifndef APPEND_HARDWARE_INFORMATION_HPP
#define APPEND_HARDWARE_INFORMATION_HPP
void append_hardware_information( char* processingString ) {

      //////////////////////////////////////////      
      // Hardware Info starter and ender char
      strcat(processingString, "|hI");

      //////////////////////////////////////////
      // HU : Hardware UUID
      strcat(processingString, "HU_");
      strcat(processingString, e2prom_variables.hardware_uuid );
      strcat(processingString, "_HU");

      //////////////////////////////////////////      
      // PS: Product Series XigCode
      strcat(processingString, "PS_");
      strcat(processingString, software_parameters_fixed.PRODUCT_SERIES );
      strcat(processingString, "_PS");

      //////////////////////////////////////////      
      // PM: Product Model XigCode
      strcat(processingString, "PM_");
      strcat(processingString, software_parameters_fixed.PRODUCT_MODEL );
      strcat(processingString, "_PM");

      //////////////////////////////////////////      
      // MX: Manufacturer XigCode
      strcat(processingString, "MX_");
      strcat(processingString, e2prom_variables.manufacturer_xc );
      strcat(processingString, "_MX");

      //////////////////////////////////////////      
      // VX: Vender XigCode
      strcat(processingString, "VX_");
      strcat(processingString, e2prom_variables.vender_xc );
      strcat(processingString, "_VX");

      //////////////////////////////////////////
      // BM: Board Model
      strcat(processingString, "BM_");
      strcat(processingString, e2prom_variables.board_model );
      strcat(processingString, "_BM");

      //////////////////////////////////////////      
      // HWCM: Hardware ChipModel
      strcat(processingString, "HWCM_");
      strcat(processingString, constrcut_MCU_ID_fixed.cChipModel );
      strcat(processingString, "_HWCM");

      //////////////////////////////////////////      
      // HWCR: Hardware ChipRevision
      strcat(processingString, "HWCR_");
      strcat(processingString, constrcut_MCU_ID_fixed.cChipRevision );
      strcat(processingString, "_HWCR");

      //////////////////////////////////////////      
      // HWCC: Hardware ChipCores
      strcat(processingString, "HWCC_");
      strcat(processingString, constrcut_MCU_ID_fixed.cChipCores );
      strcat(processingString, "_HWCC");

      //////////////////////////////////////////      
      // HWCI: Hardware ChipId
      strcat(processingString, "HWCI_");
      strcat(processingString, constrcut_MCU_ID_fixed.cChipId );
      strcat(processingString, "_HWCI");

      //////////////////////////////////////////      
      // HWAP: Hardware baseMacChrSOFTAP
      strcat(processingString, "HWAP_");
      strcat(processingString, constrcut_MCU_ID_fixed.baseMacChrSOFTAP );
      strcat(processingString, "_HWAP");

      //////////////////////////////////////////      
      // HWBT: Hardware baseMacChrBT
      strcat(processingString, "HWBT_");
      strcat(processingString, constrcut_MCU_ID_fixed.baseMacChrBT );
      strcat(processingString, "_HWBT");

      //////////////////////////////////////////      
      // HWETH: Hardware baseMacChrETH
      strcat(processingString, "HWETH_");
      strcat(processingString, constrcut_MCU_ID_fixed.baseMacChrETH );
      strcat(processingString, "_HWETH");

      //////////////////////////////////////////      
      // HWWIFI: Hardware baseMacChrWiFi
      strcat(processingString, "HWWIFI_");
      strcat(processingString, constrcut_MCU_ID_fixed.baseMacChrWiFi );
      strcat(processingString, "_HWWIFI");

      //////////////////////////////////////////      
      // Hardware Info starter and ender char
      strcat(processingString, "hI|");

}
#endif


