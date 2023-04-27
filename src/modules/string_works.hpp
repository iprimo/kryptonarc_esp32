#include "system_structs.cpp"

const char* find_values_between_substringsV4(char* str, const char* substringA1, const char* substringA2 ) {
    char* p1 = strstr(str, substringA1);
    if (!p1) return "N_A__" ;

    p1 += strlen(substringA1);
    char* p2 = strstr(p1, substringA2);
    if (!p2) return "N_A__" ;
    
    *p2 = 0;
    return p1 ;
}



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
