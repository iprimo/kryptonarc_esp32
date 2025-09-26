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





////////////////////////////////////////////////////////////////
// 0x0000|pi_....._pi|pl _....._pl|global_hash

    // APIs: hardwareCheckInCentral - publicAPI_hardwareProxied
    // ---------------------- Device originated ----------------------
    // ++-----------+-------------------------++-----------+-------------------------+
    // ||   Code    | Code Description        ||   Code    | Code Description        |
    // ++-----------+-------------------------++-----------+-------------------------+
    // ||  0x0001   |                         ||  0x0102   |                         |
    // ++-----------+-------------------------++-----------+-------------------------+
    // ||    0x0    | Device originated       ||    0x0    | Device originated       |
    // ++-----------+-------------------------++-----------+-------------------------+
    // ||     0     | Global hash             ||     1     | Device hash01           |
    // ++-----------+-------------------------++-----------+-------------------------+
    // ||     0     | No Ecncryption          ||     0     | No ecncryption          |
    // ++-----------+-------------------------++-----------+-------------------------+
    // ||     1     | From blank device                                              |   
    // ||     2     | Configured device                                              |   
    // ++-----------+-------------------------++-----------+-------------------------+
    
    // ---------------------- Cloud originated ----------------------
    // ++-------------------------------------++-------------------------------------++---------------------------------------------++---------------------------------------------+
    // ||   Code    | Code Description        ||   Code    | Code Description        ||   Code            | Code Description        ||   Code            | Code Description        |
    // ++-------------------------------------++-------------------------------------++---------------------------------------------++---------------------------------------------+
    // ||   0x1001  |                         ||   0x1102  |                         ||   v1 -1 -1 -1 -9 -0 00 00 00 00  (0x1119)   ||   (0x1109)                                  |
    // ++-----------+-------------------------++-----------+-------------------------++-------------------+-------------------------++-------------------+-------------------------+
    // ||    0x1    |     Cloud originated    ||    0x1    |     Cloud originated    ||    01             |     Cloud originated    ||    1              |     Cloud originated    |
    // ++-----------+-------------------------++-----------+-------------------------++-------------------+-------------------------++-------------------+-------------------------+
    // ||     0     | Global hash             ||     1     | Device hash01           ||    01             | Device hash01           ||    1              | Device hash01           |
    // ++-----------+-------------------------++-----------+-------------------------++-------------------+-------------------------++-------------------+-------------------------+
    // ||     0     | No ecncryption          ||     0     | No ecncryption          ||    01             | Device Encryp Code 01   ||    0              | No ecncryption          |
    // ++-----------+-------------------------++-----------+-------------------------+
    // ||     3     | Reboot                                                         |
    // ||     4     | Unlock > Wipe tenant > Reboot                                  |
    // ||     5     | Lock (Keep tenant)                                             |
    // ||     6     | Unlock (Keep tenant)                                           |
    // ||     7     | OS Upgrade - 2 lastest (default)                               |
    // ||     8     | OS Upgrade - Custom details                                    |
    // ||     9     | Hardware Instruction                                           |
    // ||           |                                                                |
    // ++-----------+-------------------------++-----------+--------------------------

    // -------------------- Smart App Originated --------------------
    // +----------+-----------+-------------------------------------+
    // |          |    0x2    |     Smart App Originated            |
    // +          +-----------+-------------------------------------+
    // |  0x2001  |     0     | No hash                             |
    // +          +-----------+-------------------------------------+
    // |          |     0     | No ecncryption                      | 
    // +          +-----------+-------------------------------------+
    // |          |     1     |     GetStatus                       |
    // |          |     2     |     Reboot                          |
    // |          |     3     |     Update OS                       |
    // +----------+-----------+-------------------------------------+
    // |          |           |                                     |
    // +----------+-----------+-------------------------------------+
////////////////////////////////////////////////////////////////



struct DataStringCodeOptions {
      int versionCode = 1;
      int randomStuff1 = 1;
      int randomStuff2 = 1;
      std::string hwConfigState = "";
      std::string traffOrigin = "";
      std::string md5Hashing = "";
      std::string encryption = "";
};

void append_data_string_code(char* processingString, const DataStringCodeOptions& opts) {

      if (  opts.versionCode == 1 && opts.hwConfigState == "unregisteredDevice" && opts.md5Hashing == "global" && 
            opts.encryption == "none" ) {
        // ---------------------- Device originated ----------------------
        // ++-----------+-------------------------++
        // ||   Code    | Code Description        ||
        // ++-----------+-------------------------++
        // ||  0x0001   |                         ||
        // ++-----------+-------------------------++
        // ||    0x0    | Device originated       ||
        // ++-----------+-------------------------++
        // ||     0     | Global hash             ||
        // ++-----------+-------------------------++
        // ||     0     | No Ecncryption          ||
        // ++-----------+-------------------------++
        // ||     1     | From blank device    
        // ||     2     | Configured device    
        // ++-----------+-------------------------++

        std::string info = std::string("") + 
            "ver:" + "1" + "::" + 
            "code:" + "0x0001" + "::" + 
            "hwConfigState:" + opts.hwConfigState + "::" +
            "md5Hashing:" + opts.md5Hashing + "::" +
            "encryption:" + opts.encryption +  "::" +"_v1";
        strcat(processingString, info.c_str());

    } else if (  opts.versionCode == 1 && opts.traffOrigin == "hwDevice" && opts.md5Hashing == "hwDevice" &&
            opts.encryption == "none" && opts.hwConfigState == "registeredDevice" ) {

        // ---------------------- Device originated ----------------------
        // ++-----------+-------------------------+
        // ||   Code    | Code Description        |
        // ++-----------+-------------------------+
        // ||  0x0102   |                         |
        // ++-----------+-------------------------+
        // ||    0x0    | Device originated       |
        // ++-----------+-------------------------+
        // ||     1     | Device hash01           |
        // ++-----------+-------------------------+
        // ||     0     | No ecncryption          |
        // ++-----------+-------------------------+
        // ||     2     | Configured device       |   
        // ++-----------+-------------------------+

        std::string info = std::string("") + 
            "ver:" + "1" + "::" + 
            "code:" + "0x0102" + "::" + 
            "traffOrigin:" + opts.traffOrigin + "::" +
            "md5Hashing:" + opts.md5Hashing + "::" +
            "encryption:" + opts.encryption + "::" +
            "hwConfigState:" + opts.hwConfigState + "_v1";
        strcat(processingString, info.c_str());
      }
}




void append_bluetooth_session_sequence( char* processingString ) {


      //////////////////////////////////////////      
      // Request session Sequence
      int randomNumber = random(0, 2147483640);
      software_parameters_variables.data_transfer_sequence_ble = randomNumber ;
      char charArray[5];  // Assuming a 4-digit integer plus the null terminator
      sprintf(charArray, "%d", software_parameters_variables.data_transfer_sequence_ble);


      strcat(processingString, "BLESessionSeq:");  // BLE Session Sequest
      strcat(processingString, charArray );
      strcat(processingString, "::");


      //////////////////////////////////////////      
      // time stamp
      strcat(processingString, "timeStamp:");  // BLE Session Sequest
      strcat(processingString, software_parameters_variables.incoming_data_time_stamp );
      strcat(processingString, "::");

}

void append_status_information( char* processingString ) {
      strcat(processingString, "shackleCurrentState:"); // cSLC_ : shackleCurrentState
      strcat(processingString, e2prom_variables.current_shackle_lock_configuration );
      strcat(processingString, "::"); // cSLC_ : shackleCurrentState

}

void append_config_information( char* processingString ) {

      //////////////////////////////////////////      
      // tX: Tenant XigCode
      strcat(processingString, "tenantXC:"); // _tXC
      strcat(processingString, e2prom_variables.tenant_xc );
      strcat(processingString, "::"); // _tXC

      //////////////////////////////////////////      
      // DX: Device XigCode
      strcat(processingString, "deviceXC:");   // "dXC_"
      strcat(processingString, e2prom_variables.device_xc );
      strcat(processingString, "::");

}

void append_secret_config_information( char* processingString ) {

      // hashKey_Internal
      strcat(processingString, "hashKeyInternal:");      // scHK - hashKey_Internal
      strcat(processingString, "00000_abc123abc1" );
      strcat(processingString, "::");
      // encryptionKey_Internal
      strcat(processingString, "encryptionKeyInternal:"); // scEnI
      strcat(processingString, "00001_abc123abc1" );
      strcat(processingString, "::");
      // keySmithKeyOnline_Internal
      strcat(processingString, "keySmithKeyOnline02Internal:"); // scKSO
      strcat(processingString, "00002_abc123abc1" );
      strcat(processingString, "::");
      // lastResortKeyOffline_Internal
      strcat(processingString, "lastResortKeyOfflineInternal:"); // scLRKO_
      strcat(processingString, "00003_abc123abc1" );
      strcat(processingString, "::");

      // hashKey02_Internal
      strcat(processingString, "hashKeyInternal02:"); // scHK 
      strcat(processingString, "00004_abc123abc1" );
      strcat(processingString, "::");
      // encryptionKey02_Internal
      strcat(processingString, "encryptionKeyInternal02:");
      strcat(processingString, "00005_abc123abc1" );
      strcat(processingString, "::");
      // keySmithKeyOnline02_Internal
      strcat(processingString, "keySmithKeyOnline02Internal02:");
      strcat(processingString, "00006_abc123abc1" );
      strcat(processingString, "::");
      // lastResortKeyOffline02_Internal
      strcat(processingString, "lastResortKeyOfflineInternal02:");
      strcat(processingString, "00007_abc123abc1" );
      strcat(processingString, "::");

}

void append_firmware_information( char* processingString ) {
      // HWCM: Hardware ChipModel
      strcat(processingString, "firmwareVersion:");
      strcat(processingString, software_parameters_fixed.FIRMWARE_VERSION );
      strcat(processingString, "::");
}

void append_hardware_information( char* processingString ) {

      //////////////////////////////////////////
      // HU : Hardware UUID
      strcat(processingString, "hwUUID:"); // hU_
      strcat(processingString, e2prom_variables.hardware_uuid );
      strcat(processingString, "::");

      //////////////////////////////////////////      
      // PS: Product Series XigCode
      strcat(processingString, "productSeries:");   // pS_
      strcat(processingString, software_parameters_fixed.PRODUCT_SERIES );
      strcat(processingString, "::");

      //////////////////////////////////////////      
      // PM: Product Model XigCode
      strcat(processingString, "productModel:");   // pM_
      strcat(processingString, software_parameters_fixed.PRODUCT_MODEL );
      strcat(processingString, "::");

      //////////////////////////////////////////      
      // MX: Manufacturer XigCode
      strcat(processingString, "manufacturerXC:"); //mX_
      strcat(processingString, e2prom_variables.manufacturer_xc );
      strcat(processingString, "::");

      //////////////////////////////////////////      
      // VX: Vender XigCode
      strcat(processingString, "venderXC:");    // vX_
      strcat(processingString, e2prom_variables.vender_xc );
      strcat(processingString, "::");

      //////////////////////////////////////////
      // BM: Board Model
      strcat(processingString, "boardModel:");  // bM_
      strcat(processingString, e2prom_variables.board_model );
      strcat(processingString, "::");

      //////////////////////////////////////////      
      // HWCM: Hardware ChipModel
      strcat(processingString, "cChipModel:");  // hWCM_
      strcat(processingString, constrcut_mcu_id_fixed.cChipModel );
      strcat(processingString, "::");

      //////////////////////////////////////////      
      // HWCR: Hardware ChipRevision
      strcat(processingString, "cChipRevision:");     // hWCR
      strcat(processingString, constrcut_mcu_id_fixed.cChipRevision );
      strcat(processingString, "::");

      //////////////////////////////////////////      
      // HWCC: Hardware ChipCores
      strcat(processingString, "cChipCores:");    // hWCC
      strcat(processingString, constrcut_mcu_id_fixed.cChipCores );
      strcat(processingString, "::");

      //////////////////////////////////////////      
      // HWCI: Hardware ChipId
      strcat(processingString, "cChipId:");      // hWCI_
      strcat(processingString, constrcut_mcu_id_fixed.cChipId );
      strcat(processingString, "::");

      //////////////////////////////////////////      
      // HWAP: Hardware baseMacChrSOFTAP
      strcat(processingString, "baseMacChrSOFTAP:");      // hWAP_
      strcat(processingString, constrcut_mcu_id_fixed.baseMacChrSOFTAP );
      strcat(processingString, "::");

      //////////////////////////////////////////      
      // HWBT: Hardware baseMacChrBT
      strcat(processingString, "baseMacChrBT:");        // hWBT_
      strcat(processingString, constrcut_mcu_id_fixed.baseMacChrBT );
      strcat(processingString, "::");

      //////////////////////////////////////////      
      // HWETH: Hardware baseMacChrETH
      strcat(processingString, "baseMacChrETH:");             // hWETH_
      strcat(processingString, constrcut_mcu_id_fixed.baseMacChrETH );
      strcat(processingString, "::");

      //////////////////////////////////////////      
      // HWWIFI: Hardware baseMacChrWiFi
      strcat(processingString, "baseMacChrWiFi:");          // hWWIFI_
      strcat(processingString, constrcut_mcu_id_fixed.baseMacChrWiFi );
      strcat(processingString, "::");

}



// Returns status information as a std::string
// Use case example
// // append_status_information( sendStr56 );
// // Prepend status information
// std::string combined = device_shackle_state() + sendStr56;
// strcpy(sendStr56, combined.c_str());-
// Serial.print("sendStr56:22766666222 ");
inline std::string device_shackle_state() {
    std::string s;
    s += "curShackleConf:";
    s += e2prom_variables.current_shackle_lock_configuration;
    s += "::";
    return s;
}

// Returns config information as a std::string
inline std::string device_tenant_xigcode() {
    std::string s;
    s += "tenantXC:";
    s += e2prom_variables.tenant_xc;
    s += "::";
    s += "deviceXC:";
    s += e2prom_variables.device_xc;
    s += "::";
    return s;
}

// Returns firmware information as a std::string
inline std::string device_firmware_information() {
      std::string s;
      s += "firmwareVersion:";
      s += software_parameters_fixed.FIRMWARE_VERSION;
      s += "::";
      return s;
}

// Returns bluetooth session sequence as a std::string
inline std::string device_bluetooth_session_sequence() {

      // Generate random session sequence and update global variable
      int randomNumber = random(0, 2147483640);
      software_parameters_variables.data_transfer_sequence_ble = randomNumber;
      char charArray[16];
      sprintf(charArray, "%d", software_parameters_variables.data_transfer_sequence_ble);
      std::string s;
      s += "BLESessionSeq:";
      s += charArray;
      s += "::";
      s += "timeStamp:";
      s += software_parameters_variables.incoming_data_time_stamp;
      s += "::";
    return s;
}


#endif

