// Helpful example
// https://www.dfrobot.com/blog-1001.html


// Original source - Example of Arduino IDE AES128_Example
#include "string.h"
#include "Crypto.h"
#include "AES.h"




#ifndef AES_ENCRYPTION_HPP
#define AES_ENCRYPTION_HPP

void aesEncryption(char* clearMessage, char* encryptionKey, char* encryptedData ) {

  //key[16] cotain 16 byte key(128 bit) for encryption
  // byte key[16]={0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F};
  byte key[16];
  memcpy(key, encryptionKey, sizeof(encryptionKey)) ;

  
  byte clearMessageInByte[1024];
  // Convert char array to byte array
  memcpy(clearMessageInByte, clearMessage, sizeof(clearMessage)) ;


  //cypher[16] stores the encrypted text
  byte cypher[1024];

  //creating an object of AES128 class
  AES128 aes128;

  aes128.setKey(key,16);// Setting Key for AES
   
  aes128.encryptBlock(cypher,clearMessageInByte);//cypher->output block and clearMessageInByte->input block
    

char resultArray[sizeof(cypher) * 2 + 1];  // Allocate space for digits and null terminator
int resultIndex = 0;


Serial.print(" --------------------------  " );
        Serial.print(" sizeof(cypher) >>>  " );
        Serial.println( sizeof(cypher) );
    Serial.print(" --------------------------  " );

for (int i = 0; i < sizeof(cypher); i++) {
    char str[3];
    sprintf(str, "%02x", (int)cypher[i]);

    // Append str to the resultArray
    strncpy(resultArray + resultIndex, str, 2);  // Copy 2 characters from str
    resultIndex += 2;  // Move the index for the next append
}

    
  // Convert byte array back to char array
  memcpy(encryptedData, cypher, sizeof( cypher ));

}

#endif


#ifndef AES_DECRYPTION_HPP
#define AES_DECRYPTION_HPP

void aesDecryption(char* encryptedData, char* encryptionKey, char* receivedMessage ) {

  //key[16] cotain 16 byte key(128 bit) for encryption
  byte key[16]={0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F};
  // //clearMessageInByte[1024] contain the text we need to encrypt
  // byte clearMessageInByte[1024]={0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,0x88, 0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF};


  char message[128] = "UrMessageHere";
  //     Serial.print("message:  ");
  //     Serial.println(message);
  
  byte clearMessageInByte[1024];
  // Convert char array to byte array
  memcpy(clearMessageInByte, message, sizeof(message)) ;



  //     Serial.print("clearMessageInByte:  ");
  //     Serial.println(clearMessageInByte[0]);





  //cypher[16] stores the encrypted text
  byte cypher[16];
  //decryptedtext[16] stores decrypted text after decryption
  byte decryptedtext[16];
  //creating an object of AES128 class
  AES128 aes128;







  aes128.setKey(key,16);// Setting Key for AES
  
  //     Serial.print("Before Encryption:");
  for(int i=0; i<sizeof(clearMessageInByte); i++){
    //     Serial.write(clearMessageInByte[i]);
   }
   
  aes128.encryptBlock(cypher,clearMessageInByte);//cypher->output block and clearMessageInByte->input block
  //     Serial.println();
  //     Serial.print("After Encryption:");
  for(int j=0;j<sizeof(cypher);j++){
      //     Serial.write(cypher[j]);
    }
    
   aes128.decryptBlock(decryptedtext,cypher);
   
  //     Serial.println();
  //     Serial.print("After Dencryption:");
  for(int i=0; i<sizeof(decryptedtext); i++){
    //     Serial.write(decryptedtext[i]);
   }

   
  //     Serial.print("decryptedtext:  ");
  //     Serial.println(decryptedtext[0]);

    // Convert byte array back to char array
    memcpy(receivedMessage, decryptedtext, sizeof( decryptedtext ));
   
  //     Serial.print("receivedMessage >>>>> :  ");
  //     Serial.println( receivedMessage );

}

#endif





#ifndef AES_ENCRYPTION_DECRYPTION_HPP
#define AES_ENCRYPTION_DECRYPTION_HPP
void aes_Encryption_Decryption( char* receivedMessage) {

  //key[16] cotain 16 byte key(128 bit) for encryption
  byte key[16]={0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F};
  // //clearMessageInByte[1024] contain the text we need to encrypt
  // byte clearMessageInByte[1024]={0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,0x88, 0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF};


  char message[128] = "UrMessageHere";
  //     Serial.print("message:  ");
  //     Serial.println(message);
  
  byte clearMessageInByte[1024];
  // Convert char array to byte array
  memcpy(clearMessageInByte, message, sizeof(message)) ;



  //     Serial.print("clearMessageInByte:  ");
  //     Serial.println(clearMessageInByte[0]);





  //cypher[16] stores the encrypted text
  byte cypher[16];
  //decryptedtext[16] stores decrypted text after decryption
  byte decryptedtext[16];
  //creating an object of AES128 class
  AES128 aes128;







  aes128.setKey(key,16);// Setting Key for AES
  
  //     Serial.print("Before Encryption:");
  for(int i=0; i<sizeof(clearMessageInByte); i++){
    //     Serial.write(clearMessageInByte[i]);
   }
   
  aes128.encryptBlock(cypher,clearMessageInByte);//cypher->output block and clearMessageInByte->input block
  //     Serial.println();
  //     Serial.print("After Encryption:");
  for(int j=0;j<sizeof(cypher);j++){
      //     Serial.write(cypher[j]);
    }
    
   aes128.decryptBlock(decryptedtext,cypher);
   
  //     Serial.println();
  //     Serial.print("After Dencryption:");
  for(int i=0; i<sizeof(decryptedtext); i++){
    //     Serial.write(decryptedtext[i]);
   }

   
  //     Serial.print("decryptedtext:  ");
  //     Serial.println(decryptedtext[0]);

    // Convert byte array back to char array
    memcpy(receivedMessage, decryptedtext, sizeof( decryptedtext ));
   
  //     Serial.print("receivedMessage >>>>> :  ");
  //     Serial.println( receivedMessage );

}
#endif // MD5_HPP