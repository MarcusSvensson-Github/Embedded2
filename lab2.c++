/* 
Laboration 2 
tänk på att alla pwn pins delar frekvens/klocka.

Kvar att göra:
-joiystick
-externt batteri
-hur ska main se ut?

*/
#include "mbed.h"

//alla pin är nog 
PwmOut red(p23);
PwmOut blue(p25);
PwmOut green(p24);
PwmOut servo(p21);
AnalogIn PM(p19);

DigitalIn Left(p12);
DigitalIn Down(p13);
DigitalIn Right(p15);
DigitalIn Up(p16);
//BusIn joy(p15,p12,p13,p16);

/*
JOYSTICK:
Down:p12
Left:p13
Centre:p14
Up:p15
Right:p16  */

//deklarerar våra functioner
void fast();
void slow();
void interval();
void off();


int main() {
bool fastF;
bool slowF;
bool intervalF;
    
    off();
    while (1) {
        // möjligtis sätt ett case beroende på hur joystick input ser ut
        if(Up==1){
            slowF = false;
            intervalF = false;
            fastF = true;
            while(fastF){
                fast();
                if(Down == 1 || Right == 1 || Left == 1){
                    break;
                    }
                }
            off();
        }
        if(Down==1){
            slowF = true;
            intervalF = false;
            fastF = false;
            while(slowF){
                slow();
                if(Up == 1 || Right == 1 || Left == 1){
                    break;
                    }
                }
            off();
        }
        if(Right==1){
            slowF = false;
            intervalF = false;
            fastF = false;
            off();
        }
        if(Left==1){
            slowF = false;
            intervalF = true;
            fastF = false;
            while(intervalF){
                interval();
                if(Down == 1 || Right == 1 || Up == 1){
                    break;
                    }
                }
            off();
        }
        
    }
}



void off(){  //funktion för stänga av allt
    red = 1;
    blue = 1;
    green = 1;
    servo.period_ms(20);
    servo.pulsewidth_us(900);
    
}

void fast(){ //funktion för att köra vindrutetorkaren snabbt och blinkar med röd lampa
    servo.period_ms(20); //kolla upp om 20ms var standard
    red = 1 - 0.2;
    float i;
    for (i=900; i<2100; i++){ //du vill den rör upp sig från 0-180 (900-2100 µs) vilken pulsbredd är det utav 20ms
        servo.pulsewidth_us(i);
        wait_ms(1); //justerar farten
        if(Down == 1 || Right == 1 || Left == 1){
                    return;
                    }
    }
    for (i=2100; i>900; i--){ //du vill den rör sig ner från 180-0 (900-2100 µs) vilken pulsbredd är det utav 20ms
        servo.pulsewidth_us(i);
        wait_ms(1);  //justerar farten
        if(Down == 1 || Right == 1 || Left == 1){
                    return;
                    }
    }
}

void slow(){ //funktion för att köra vindrutetorkaren långsamt och blinkar med blå lampa
    servo.period_ms(20); 
    blue = 1 - 0.2;
    float i;
    for (i=900; i<2100; i++){ //du vill den rör upp sig från 0-180 (900-2100 µs) vilken pulsbredd är det utav 20ms
        servo.pulsewidth_us(i);
        wait_ms(2); //justerar farten
        if(Up == 1 || Right == 1 || Left == 1){
                    return;
                    }
    }
    for (i=2100; i>900; i--){ //du vill den rör sig ner från 180-0 (900-2100 µs) vilken pulsbredd är det utav 20ms
        servo.pulsewidth_us(i);
        wait_ms(2);  //justerar farten
        if(Up == 1 || Right == 1 || Left == 1){
                    return;
                    }
    }
}

void interval(){  //grön lampa styrd av potentiometer efter 5 blink en torkning

    float value = PM; //lista ut hur du får blink intervall mellan 300ms-1000ms, Detta ger (för 5 st blinkningar) torkarintervall från 1,5 till 5 sekunder
    // du behöver också räkna blink innan torkaren kommer härnäst. du vill samtidigt inte göra att pulsebredden tar ifrån de tiden

    float interval = value * 700 + 300;  //blink intervall mellan 300ms-1000ms
    for(int e= 0; e<5; e++){
        green = 0;
        wait_ms(100);
        green = 1;
        wait_ms(interval-100);
        if(Down == 1 || Right == 1 || Up == 1){
                    return;
                    }
        }
    //green.pulsewidth_ms(interval/2); // kommer lysa hälften av intervallen
    /* red = 1;
    blue = 1;
    green.period_ms(interval * 1.5); //vi lägger nu på den halva tiden till perioden som vi stal för att den skulle lysa under
    float waiting = interval * 1.5 * 5; //vi väntar 5X perioden + pulsbredden innan vi sätter på bladet
    wait_ms(waiting); */
    
    green = 1; //stänger av lampa
    
    float i;
    servo.period_ms(20); // korrigera rätt perioden för servon
    for (i=900; i<2100; i++){ //du vill den rör upp sig från 0-180 (900-2100 µs) vilken pulsbredd är det utav 20ms
        servo.pulsewidth_us(i);
        wait_ms(2); //justerar farten
        if(Down == 1 || Right == 1 || Up == 1){
                    return;
                    }
    }
    for (i=2100; i>900; i--){ //du vill den rör sig ner från 180-0 (900-2100 µs) vilken pulsbredd är det utav 20ms
        servo.pulsewidth_us(i);
        wait_ms(2);  //justerar farten
        if(Down == 1 || Right == 1 || Up == 1){
                    return;
                    }
    }
}