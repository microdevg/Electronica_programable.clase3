#define LED_BOARD     13
#define PIN_TEST      12
#define BUTTON_IRQ    3

volatile int state = 0;      // Use volatile for variables modified in ISR
volatile unsigned long counter1 = 0;
volatile unsigned long counter2 = 0;
volatile bool flag_serial = false;  // Flag to print time in loop

void setup() {
    pinMode(PIN_TEST , OUTPUT);
    pinMode(LED_BOARD, OUTPUT);
    pinMode(BUTTON_IRQ, INPUT_PULLUP);
    Serial.begin(9600);
    attachInterrupt(digitalPinToInterrupt(BUTTON_IRQ), blink, RISING);
}
int value = 0;
int test_value = 0;
void loop() {

    // Print elapsed time after button release
    if (flag_serial) {
        Serial.print("Counter: ");
        Serial.print(counter2);
        Serial.println(" useg");
        flag_serial = false;  // Reset flag
    }
}

void blink() {

    noInterrupts(); 
    if (state == 0) {  
        counter1 = micros();  // Capture time when button is pressed
        state = 1;  
    attachInterrupt(digitalPinToInterrupt(BUTTON_IRQ), blink, FALLING);
    } 
    else {  
        counter2 = (micros() - counter1) ;  // Calculate elapsed time
        state = 0;  
        flag_serial = true;  // Set flag to print time in loop
        attachInterrupt(digitalPinToInterrupt(BUTTON_IRQ), blink, RISING);
    }
      interrupts();
     digitalWrite(LED_BOARD, state);
}


