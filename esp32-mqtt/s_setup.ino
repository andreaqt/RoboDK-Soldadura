void on_setup() {

    // initialize digital pin LED_BUILTIN as an output.
    pinMode(LED_RED, OUTPUT);
    pinMode(LED_YELLOW, OUTPUT);
    pinMode(LED_GREEN, OUTPUT);

    // initialize el boton
    pinMode(botonPin, INPUT_PULLUP);

    setInternalLed(0);

    String hello_msg = String("Hola Mundo! Desde dispositivo ") + deviceID;

    enviarMensajePorTopic(NEW_TOPIC, hello_msg);

}
