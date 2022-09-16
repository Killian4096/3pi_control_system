#include <avr/io.h>
#include <motor_drivers.h>

int main(void){
    motor_move_tank(255,255);
    while(1);
}