#include <Arduino.h>

typedef struct {
    String first_name;
    String last_name;
    long age;
} person;

String getMacAddress();

long addx(int a, int b);