#include "system_structs.hpp"

const char* find_values_between_substringsV4(char* str, const char* substringA1, const char* substringA2 ) {
    char* p1 = strstr(str, substringA1);
    if (!p1) return "N_A__" ;

    p1 += strlen(substringA1);
    char* p2 = strstr(p1, substringA2);
    if (!p2) return "N_A__" ;
    
    *p2 = 0;
    return p1 ;
}



char convertStringToChar(String str) {
    int str_len = str.length() + 1;
    char char_array[str_len];
    str.toCharArray(char_array, str_len);
    return char_array[0];
}


