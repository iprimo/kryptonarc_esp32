#include "Arduino.h"

void loggingService(const char *cMessage, const char *cFuncId, const char *cFuncName, const char *cTenant, const char *cProfile ) {
   
    // Log to Console

    Serial.print("'cMessage': '");
    Serial.print(cMessage);
    Serial.print("', ");

    Serial.print("'cFuncId': '");
    Serial.print(cFuncId);
    Serial.print("', ");

    Serial.print("'cFuncName': '");
    Serial.print(cFuncName);
    Serial.print("', ");

    Serial.print("'cTenant': '");
    Serial.print(cTenant);
    Serial.print("', ");

    Serial.print("'cProfile': '");
    Serial.print(cProfile);
    Serial.print("', ");

    Serial.println();


    //////

    // char *combined_variables;
    // int formattedStrResult = asprintf(&combined_variables, " 'cMessage': '%s', 'cFuncId': '%s', 'cFuncName': '%s','cTenant': '%s', 'cProfile': '%s'   "  , cMessage, cFuncId, cFuncName, cTenant, cProfile );

    // if(formattedStrResult > 0){
    //     // do what you want for formatted string: combined_variables
    //     Serial.println(combined_variables);
    //     free(combined_variables);
    // } else {
    //     Serial.println( "NA" );
    // }

 
}
