#include "Arduino.h"
#include "system_structs.cpp"
#include "pitches.hpp"

// System wide variables
extern SYSTEM_GLOBAL_VAR system_global_variables;


/*
 * Maintainer: Ben-BJD ( https://github.com/Ben-BJD )
 * Thanks to ShiftBit ( https://www.reddit.com/user/ShiftBit ) for optimisation advice!
 */

const int DOT_BLNK_LEN = 500;//Length of a dot is one unit
const int DASH_BLNK_LEN = 1500;//Length of a dash is three units

//Here the first 1 is a start flag and the reaminder of the byte indicates the sequence.
//For example A's sequence is 01 or dot-dash. 
//The preceeding zeroes are shifted out until the start flag is found which is also discarded.
const byte morse_table[] PROGMEM = {
  'A', 0B00000101,
  'B', 0B00011000,
  'C', 0B00011010,
  'D', 0B00001100,
  'E', 0B00000010,
  'F', 0B00010010,
  'G', 0B00001110,
  'H', 0B00010000,
  'I', 0B00000100,
  'J', 0B00010111,
  'K', 0B00001101,
  'L', 0B00010100,
  'M', 0B00000111,
  'N', 0B00000110,
  'O', 0B00001111,
  'P', 0B00010110,
  'Q', 0B00011101,
  'R', 0B00001010,
  'S', 0B00001000,
  'T', 0B00000011,
  'U', 0B00001001,
  'V', 0B00010001,
  'W', 0B00001011,
  'X', 0B00011001,
  'Y', 0B00011011,
  'Z', 0B00011100,

  '0', 0B00111111,
  '1', 0B00101111,
  '2', 0B00100111,
  '3', 0B00100011,
  '4', 0B00100001,
  '5', 0B00100000,
  '6', 0B00110000,
  '7', 0B00111000,
  '8', 0B00111100,
  '9', 0B00111110,

  '#', 0B11000101,  // /BK - Break in conversation
  '+', 0B00101010,  // /AR - Message separator, start new message / telegram
  ',', 0B01110011,
  '-', 0B01100001,
  '.', 0B01010101,
  '/', 0B00110010,
  '=', 0B00110001, // BT - Start of new section / new paragraph
  '?', 0B01001100, // Please say again
  '^', 0B01000101,  // /SK - End of contact / End of work

  0xff  // end-of-table marker
};

const char* message;
char currSignal = '\0';
int currMsgIdx = 0;
uint8_t ledPin = system_global_variables.ledRed ;

void blinkDelay(int duration)
{
  digitalWrite(ledPin, HIGH);   // turn the LED on (HIGH is the voltage level)
  tone(system_global_variables.buzzerPassive, 800);
  delay(duration);// wait for the set duration
  digitalWrite(ledPin, LOW);    // turn the LED off by making the voltage LOW
  tone(system_global_variables.buzzerPassive, 0);
}

void sendDot()
{
  blinkDelay(DOT_BLNK_LEN);
}

void sendDash()
{
  blinkDelay(DASH_BLNK_LEN);
}

void sendMorseChar(byte letter)
{
  byte bp = 0;
  byte ditordah = 0;
  bool first = false;
  unsigned int j = 0;
  unsigned int ele_len = DOT_BLNK_LEN;
  
  switch (letter)
  {
    case ' ':
      delay(ele_len * 7);//there is a seven unit delay between words
      break;

    case 8:
    case 127:
      break;

    default:
    // while bp is not our end of table flag
      while (bp != 0xff)
      {
        // we should be pointing as an alpha/digit/puncutation character in our table
        bp = pgm_read_byte_near(morse_table + j);

        // have we reached the end of our table ?
        if (bp != 0xff)
        {
          // is the chacater we're pointing to in the Morse table the same as the
          // character we want to send ?
          if (bp == letter)
          {
            // yes - so bump our pointer to the Morse code chacter bit pattern for
            // the chacater we want to send
            j++;

            // now get the bit pattern into bp
            bp = pgm_read_byte_near(morse_table + j);

            // start processing the bit pattern. ie: A = 00000101 = DOT DASH
            for (int i = 0; i < 8; i++)
            {
              // get the high bit of the pattern into our ditordah variable 
              /*
                  ie: 
                       00000101
                  AND  10000000 
                    =  00000000
               */
              ditordah = (bp & 128);

              // have we found our start flag yet ?
              if (first == false)
              {
                // if no, is it our start flag
                if (ditordah != 0)
                {
                  // yes - set our flag
                  first = true;
                }

                // now shift the bit pattern one bit to the left and continue
                bp = (bp << 1); //ie: 00000101 becomes 00001010

                /*
                  Continuing with the example A this will be shifted here until we reach
                  10100000
                  Then the first flag will be set. And the sequence 01 will be used below for the remainder of the loop
                 
                 */
                
                continue;
              }

              // if we've seen our start flag then send the dash or dot based on the bit
              if (ditordah != 0)
              {
                sendDash();
              }
              else
              {
                sendDot();
              }

              //we have a one unit delay between parts of the letter
              delay(ele_len);
  
              // now shift the bit pattern one bit to the left and continue
              
              bp = (bp << 1);//continue shifting bits in the sequence until complete
            }

            // there is a three element delay between chacaters.  the sendDash() or
            // sendDot() functions already add a one element delay so we delay
            // two more element times.
            delay(ele_len * 2);
            return;
          }
        }

        j++;
        j++;
      }

      break;
  }
}

// // the setup function runs once when you press reset or power the board
// void setup() 
// {
//    // initialize digital pin 13 as an output. (Same pin used in Blink)
//   pinMode(ledPin, OUTPUT);

//   message = "WAR, GREED, CRUELTY AND DOMINATION ARE THE ROOT CAUSE OF ALL SUFFERING.";
// }

// // the loop function runs over and over again forever
// //It will move from each letter in the 'message' variable 
// void loop() 
// { 
//   if( currSignal == '\0' )
//   {
//     currMsgIdx = 0;
//   }
//   else
//   {
//     currMsgIdx++;

//     if(message[currMsgIdx] == '\0')
//     {
//       currMsgIdx = 0;
//     }
//   }
  
//   sendMorseChar( message[currMsgIdx] );
//   currSignal = message[currMsgIdx];
  
// }


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void morse_code_data_transfer(const char* String_send_as_morse_code) {
    message = "WAR, GREED, CRUELTY AND DOMINATION ARE THE ROOT CAUSE OF ALL SUFFERING.";

    while(true){
            if( currSignal == '\0' ) {
                currMsgIdx = 0;
            } else {
                currMsgIdx++;
                if(message[currMsgIdx] == '\0')
                {
                currMsgIdx = 0;
                }
            }
            
            sendMorseChar( message[currMsgIdx] );
            currSignal = message[currMsgIdx];
            Serial.print("currMsgIdx:   "); Serial.println(currMsgIdx);
    
    }
    
}





