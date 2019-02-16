#include <stdio.h>
#include <time.h>
#include <wiringPi.h>
#include <unistd.h>
#include "ifttt.h"

void alarm_off(void);
void alarm_arming(void);
void alarm_armed(void);
void alarm_triggered(void);
void alarm_sounding(void);

int main(int argc, char *argv[]){
wiringPiSetup ();
pinMode(0, INPUT);    /*IR tester*/
pinMode(1, OUTPUT);   /*LED1*/
pinMode(2, OUTPUT);   /*LED2*/
pinMode(3, INPUT);    /*switch*/
pullUpDnControl(3, PUD_UP);
pinMode(4, OUTPUT);    /*buzzer*/

    alarm_off();
    return 0;
}

void alarm_off(void){
    digitalWrite (1, HIGH);
    digitalWrite (2, LOW);
    digitalWrite (4, LOW);    /*buzzer silent*/
    sleep(1);
    while(1){
    if(digitalRead(3)==0){
         alarm_arming();
    }
    }
}

void alarm_arming(void){
    time_t second1 = time(NULL);
    time_t second2 = time(NULL);
    while(difftime(time(NULL),second1)<10){
        second2 = time(NULL);
        while(difftime(time(NULL),second2)<1);
        digitalWrite (1, LOW);
        second2 = time(NULL);
        while(difftime(time(NULL),second2)<1);       
        digitalWrite (1, HIGH);
        }
    digitalWrite (1, LOW);
    digitalWrite (2, HIGH);
    alarm_armed();
}

void alarm_armed(void){

    while(1){
    if(digitalRead(3)==0){
        alarm_off();
    }
    if(digitalRead(0)==1){
        alarm_triggered();
    }
    }

}

void alarm_triggered(void){
    time_t second3 = time(NULL);
    time_t second4 = time(NULL);
    digitalWrite (1,LOW);
    digitalWrite (2,LOW);
    while(difftime(time(NULL),second3)<10){
        second4 = time(NULL);
        while(difftime(time(NULL),second4)<2){
            if(digitalRead(3)==0)
            alarm_off();
        }
        digitalWrite (1,HIGH);
        digitalWrite (2,HIGH);
        second4 = time(NULL);
        while(difftime(time(NULL),second4)<0.1){
            if(digitalRead(3)==0)
            alarm_off();
        }
        digitalWrite (1,LOW);
        digitalWrite (2,LOW);
    }
    alarm_sounding();
}

void alarm_sounding(void){
    ifttt("https://maker.ifttt.com/trigger/alarm_triggered/with/key/XgUKMIYlggF6VnWUxPG55", "my1", "my 2", "my 33333");
    time_t second = time(NULL);
    digitalWrite (4, HIGH);
    digitalWrite (1, HIGH);
    digitalWrite (2, HIGH);
    while(1){
        second = time(NULL);
        while(difftime(time(NULL),second)<2){
            if(digitalRead(3)==0){
                alarm_off();
            }
        }
        digitalWrite (1, LOW);
        digitalWrite (2, LOW);
        second = time(NULL);
        while(difftime(time(NULL),second)<2){
            if(digitalRead(3)==0){
                alarm_off();
            }
        }
        digitalWrite (1, HIGH);
        digitalWrite (2, HIGH);
    }
}
