#include "delay.h"

void delay(void){
    int volatile counter = 0;
    while(counter < 100000){
        counter++;
    }
}