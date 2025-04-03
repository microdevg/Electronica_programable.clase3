#define LED_BOARD     13
#define PIN_TEST      12
#define BUTTON        3

int state = 0;
unsigned long counter1 = 0;
unsigned long counter2 = 0;
bool flag_serial = false;
bool lastButtonState = LOW;  // Estado anterior del botón

void setup() {
    pinMode(PIN_TEST , OUTPUT);
    pinMode(LED_BOARD, OUTPUT);
    pinMode(BUTTON    , INPUT_PULLUP);
    Serial.begin(9600);
}

void loop() {
    bool currentButtonState = digitalRead(BUTTON      );

    if (lastButtonState == LOW && currentButtonState == HIGH) {  // Detección de flanco de subida 
        counter1 = micros();  // Capturar tiempo de presionado
        state = 1;
    }

    if (lastButtonState == HIGH && currentButtonState == LOW) {  // Detección de flanco de bajada 
        counter2 = (micros() - counter1) ;  // Calcular el tiempo transcurrido en microsegundos
        state = 0;
        flag_serial = true;
    }

    lastButtonState = currentButtonState;  // Actualizar estado del botón

    digitalWrite(LED_BOARD, state);  // Actualizar LED según el estado

    if (flag_serial) {
        Serial.print("Counter: ");
        Serial.print(counter2);
        Serial.println(" microseg");
        flag_serial = false;
    }
}
