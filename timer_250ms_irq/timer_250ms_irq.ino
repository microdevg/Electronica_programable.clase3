#include <TimerOne.h>
const int led = 13;  
volatile int ledState = LOW;    // El LED empieza apagado

void setup(void)
   {
       pinMode(led, OUTPUT);
       Timer1.initialize(250);         // Dispara cada 250 ms
       Timer1.attachInterrupt(ISR_Blink); // Activa la interrupcion y la asocia a ISR_Blink
       Serial.begin(9600);
   }
   void loop(void)
   {
       Serial.print("Haciendo nada");
       delay(1000);
   }
void ISR_Blink()
   {   
       ledState = !ledState ;
       digitalWrite(led, ledState);  
   }