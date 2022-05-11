/* 
Laboration 2 
tänk på att alla pwn pins delar frekvens/klocka.

Kvar att göra:
-joiystick
-externt batteri
-hur ska main se ut?

*/
#include "mbed.h"

//sätt rätt PWN pins i labben
PwmOut red(p23);
PwmOut blue(p25);
PwmOut green(p24);
PwmOut servo(p);
AnalogIn PM(p20);

//deklarerar våra functioner
void fast();
void slow();
void interval();
void off();


int main() {
    
    int up = 1;
    int down = 0;
    int right = 0;
    int left = 0;
    
    off();
    while (1) {
        // möjligtis sätt ett case beroende på hur joystick input ser ut
        if(up==1){
            fast();
        }
        if(down==1){
            slow();
        }
        if(right==1){
            off();
        }
        if(left==1){
            interval();
        }
        
    }
}

void off(){  //funktion för stänga av allt
    red = 0;
    blue = 0;
    green = 0;
    servo = 0;
}

void fast(){ //funktion för att köra vindrutetorkaren snabbt och blinkar med röd lampa
    servo.period_ms(20); //kolla upp om 20ms var standard
    red = 0.5;
    float i;
    for (i=900; i<2100; i++){ //du vill den rör upp sig från 0-180 (900-2100 µs) vilken pulsbredd är det utav 20ms
        servo.pulsewidth_us(i);
        wait_ms(2); //justerar farten
    }
    for (i=2100; i>900; i--){ //du vill den rör sig ner från 180-0 (900-2100 µs) vilken pulsbredd är det utav 20ms
        servo.pulsewidth_us(i);
        wait_ms(2);  //justerar farten
    }
    
}

void slow(){ //funktion för att köra vindrutetorkaren långsamt och blinkar med blå lampa
    servo.period_ms(20); 
    blue = 0.5;
    float i;
    for (i=900; i<2100; i++){ //du vill den rör upp sig från 0-180 (900-2100 µs) vilken pulsbredd är det utav 20ms
        servo.pulsewidth_us(i);
        wait(0.1); //justerar farten
    }
    for (i=2100; i>900; i--){ //du vill den rör sig ner från 180-0 (900-2100 µs) vilken pulsbredd är det utav 20ms
        servo.pulsewidth_us(i);
        wait(0.1);  //justerar farten
    }
    
}

void interval(){  //grön lampa styrd av potentiometer efter 5 blink en torkning

    float value = PM; //lista ut hur du får blink intervall mellan 300ms-1000ms, Detta ger (för 5 st blinkningar) torkarintervall från 1,5 till 5 sekunder
    // du behöver också räkna blink innan torkaren kommer härnäst
    float interval = value * 700 + 300;  //blink intervall mellan 300ms-1000ms
    green = 0.5;
    green.period_ms(interval);
    float waiting = intervall * 5;
    wait_ms(waiting);
    green = 0;
    //sätter in green till ett mräknat värde ifrån variabeln value
    //skapa ett if statement utifrån pulsbredden så vi vet när 5 blinkningar har skett
    float i;
    servo.period_ms(20);
    for (i=900; i<2100; i++){ //du vill den rör upp sig från 0-180 (900-2100 µs) vilken pulsbredd är det utav 20ms
        servo.pulsewidth_us(i);
        wait_ms(2); //justerar farten
    }
    for (i=2100; i>900; i--){ //du vill den rör sig ner från 180-0 (900-2100 µs) vilken pulsbredd är det utav 20ms
        servo.pulsewidth_us(i);
        wait_ms(2);  //justerar farten
    }
}