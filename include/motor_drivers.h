#include <avr/io.h>
#include <stdint.h>
#include <stdbool.h>


void motor_setup(void){
    //Configure motor pins to output
    DDRB |= _BV(PB3);
    DDRD |= _BV(PD3) | _BV(PD5) | _BV(PD6);

    //Configure timers and 0 and 2 to fast pwm (mode 3)
    TCCR0A |= _BV(WGM01) | _BV(WGM00);
    TCCR2A |= _BV(WGM21) | _BV(WGM20);

    //Set timers to clear on compare set on bottom
    TCCR0A |= _BV(COM0A1) | _BV(COM0B1);
    TCCR2A |= _BV(COM2A1) | _BV(COM2B1);

    //No prescalar
    TCCR0B |= _BV(CS00);
    TCCR2B |= _BV(CS20);
}

void motor_move_left(int16_t speed){
    if(speed>255){speed=255;}
    if(speed<-255){speed=-255;}
    if(speed<0){speed = -1 * speed + 0x0100;}
    OCR0A = speed * (speed<0x0100);
    OCR0B = speed * (speed>=0x0100);
}

void motor_move_right(int16_t speed){
    if(speed>255){speed=255;}
    if(speed<-255){speed=-255;}
    if(speed<0){speed = -1 * speed + 0x0100;}
    OCR2A = speed * (speed<0x0100);
    OCR2B = speed * (speed>=0x0100);
}

void motor_move_tank(int16_t left_speed, int16_t right_speed){
    motor_move_left(left_speed);
    motor_move_right(right_speed);
}