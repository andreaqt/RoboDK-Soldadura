#  ESP32-RoboDK-IoT-Integration


[![C++](https://img.shields.io/badge/C++-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)](https://isocpp.org/)
[![Arduino](https://img.shields.io/badge/Arduino-00979D?style=for-the-badge&logo=Arduino&logoColor=white)](https://www.arduino.cc/)
[![Python](https://img.shields.io/badge/Python-3776AB?style=for-the-badge&logo=python&logoColor=white)](https://www.python.org/)
[![MQTT](https://img.shields.io/badge/MQTT-6600CC?style=for-the-badge&logo=mqtt&logoColor=white)](https://mqtt.org/)

> Un sistema de control industrial bidireccional que conecta un nodo físico en tiempo real (ESP32) con una celda de manufactura y simulación en RoboDK, utilizando MQTT como broker central.


## 📌 Descripción del Proyecto

Este proyecto es una solución IoT para entornos industriales. Permite la comunicación bidireccional entre el mundo físico y el virtual de la siguiente manera:
1. **Entrada Física a Virtual:** Al interactuar con el hardware (pulsar un botón en la ESP32), el sistema envía un payload a través de MQTT que es interpretado por RoboDK para realizar acciones en la simulación.
2. **Virtual a Salida Física:** El entorno virtual puede enviar comandos por MQTT para gobernar actuadores físicos (como encender LEDs de estado) conectados a la ESP32.



## 📂 Arquitectura del Sistema

*Aquí puedes añadir el diagrama o esquema de la arquitectura de comunicación. (Ver sección de adjuntar imágenes abajo).*



## ⚙️ Estructura del Código

El proyecto está dividido en dos grandes bloques:

### 1. 🌐 Nodo IoT Físico (ESP32)

Demuestra cómo se gestiona el hardware utilizando detección de flancos para evitar rebotes y no saturar la red.

```cpp
// Lógica de control del botón y detección de flancos (w_loop.ino)
const int BUTTON_PIN = 17; 
const int LED_PIN = 6; // LED rojo

static int lastButtonState = HIGH; 
static int ledState = LOW;

void on_loop() {
  int currentButtonState = digitalRead(BUTTON_PIN);
  
  // Detección de flanco de bajada (de suelto a pulsado)
  if (lastButtonState == HIGH && currentButtonState == LOW) {
    
    // Invertimos el estado del LED local
    ledState = !ledState;
    digitalWrite(LED_PIN, ledState);
    
    // Enviamos el mensaje al broker MQTT correspondiente
    if (ledState == HIGH) {
      // enviarMensajePorTopic("giirob/pr2/devices/andreaxd", "on");
      Serial.println("-> Mensaje MQTT Enviado: on");
    } else {
      // enviarMensajePorTopic("giirob/pr2/devices/andreaxd", "off");
      Serial.println("-> Mensaje MQTT Enviado: off");
    }
  }
  
  lastButtonState = currentButtonState;
  delay(50); // Debounce
}
```

### 2. 🤖 Control de Simulación (Python / RoboDK)

El script `RobotController.py` gestiona la recepción de mensajes mediante hilos (threads) para no bloquear la interfaz ni la conexión MQTT:

```python
# Manejador de eventos en RoboDK (RobotController.py)
import threading
import Leds_conf as leds

station_commands_topic = "giirob/pr2/station/demo/commands"
station_status_topic = "giirob/pr2/station/demo/status"

def handle_message(mqttc, topic, payload, init_all, simulacion):
    msg = payload.strip()
    
    if topic == station_commands_topic: 
        if msg == "1":
            # Ejecutamos la secuencia de semáforo en un hilo para no bloquear el broker
            hilo_leds = threading.Thread(target=leds.secuencia_semaforo, args=(mqttc, station_status_topic))
            hilo_leds.start() 

def move_robot(position):
    robot = RDK.Item("myRobotUR", ITEM_TYPE_ROBOT)
    target = RDK.Item(position).setAsCartesianTarget()
    if robot.Valid() and target.Valid():
        robot.MoveJ(target)
```

---

## 🚀 Cómo poner en marcha el proyecto

1. **Requisitos previos:**
   * Tener instalado el IDE de Arduino y RoboDK.
   * Instalar las librerías `PubSubClient`, `ArduinoJson` y `paho-mqtt` (en Python).
2. **Configuración del Hardware:**
   * Modifica `Config.h` insertando tus credenciales de red de forma segura (sin exponer contraseñas).
   * Conecta el ESP32 y sube el código.
3. **Ejecución de la simulación:**
   * Inicia tu estación en RoboDK.
   * Ejecuta `MqttListener.py` para sincronizar las señales virtuales y físicas.

---

### 🛡️ Buenas Prácticas y Autores
* **Desarrollado bajo principios de modularidad** y encapsulamiento.
* **Seguridad:** Credenciales protegidas mediante variables de entorno o archivos de cabecera locales.

---

<br>
