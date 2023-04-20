// #include "global_variables.hpp"
#include "system_structs.cpp"

extern BROADCAST_GLOBAL_VAR broadcast_global_variables;

String find_values_between_substringsV3(char* str, const char* substringA1, const char* substringA2 ) {
    char* p1 = strstr(str, substringA1);
    // if (!p1) return strdup("") ;
    if (!p1) return "N_A__" ;

    p1 += strlen(substringA1);
    char* p2 = strstr(p1, substringA2);
    if (!p2) return strdup("") ;
    if (!p2) return "N_A__" ;
    
    *p2 = 0;
    return p1 ;
}




// void find_values_between_substringsV3(String str, const char* substringA1, const char* substringA2 ) {
//     char* p1 = strstr(str.c_str(), substringA1);
//     if (!p1) return;
//     p1 += strlen(substringA1);
//     char* p2 = strstr(p1, substringA2);
//     if (!p2) return;
//     // char* p3 = strstr(p2, substringB1);
//     // if (!p3) return;
//     // p3 += strlen(substringB1);
//     // char* p4 = strstr(p3, substringB2);
//     // if (!p4) return;
//     *p2 = 0;
//     // *p4 = 0;
//     // outputA = strdup(p1);
//     // valueB = strdup(p3);

//     broadcast_global_variables.outputA = strdup(p1);
// }
