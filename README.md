# Integración de ESP32, MQTT y RoboDK

Proyecto práctico que conecta hardware físico con un entorno de simulación industrial en RoboDK mediante un broker MQTT. 

El sistema permite una comunicación bidireccional:
* **Físico a Virtual:** Al pulsar un botón en la ESP32, se envía un comando a través de MQTT para actualizar el estado en RoboDK.
* **Virtual a Físico:** El entorno de simulación puede enviar señales para activar LEDs de estado en el circuito físico.

---

## Archivos en el repositorio

### 🐍 Control en Python (RoboDK)
* **`MqttListener.py`**: Conecta con el broker MQTT y escucha los comandos entrantes.
* **`RobotController.py`**: Gestiona las acciones en RoboDK al recibir un mensaje (ejecuta secuencias en segundo plano).
* **`Leds_conf.py`**: Controla la visibilidad de los LEDs (rojo, verde, amarillo) en el entorno 3D.
* **`Movimientos.py`**: Define las trayectorias y movimientos del robot.
* **`Main_para_probar_semaforos.py`**: Script de prueba para la secuencia de los semáforos.

### 🔌 Código de Arduino / ESP32
* **`mqtt_a_ard.ino`**: Archivo principal del microcontrolador.
* **`w_loop.ino`**: Contiene la lógica para la lectura del botón y detección de flancos (*edge detection*).
* **`g_comunicaciones.ino`**: Callback para procesar los mensajes MQTT recibidos.
* **`s_setup.ino`**: Configuración inicial de los pines.

*(Nota: El archivo `Config.h` se ha omitido para proteger los datos personales y de la red de la universidad).*

---

## Imágenes del proyecto

### Circuito físico y hardware
![Circuito Físico](img/image_fdaae1.jpg)

### Entorno de simulación
![Simulación en RoboDK](img/image_fdab16.jpg)

---

## Puesta en marcha

1. **Crea una carpeta llamada `img`** en la raíz de este repositorio y guarda ahí las fotos.
2. **Configura tus credenciales:** Añade tu propio archivo `Config.h` en el IDE de Arduino con tus datos de WiFi y MQTT (sin subirlo a GitHub).
3. **Ejecución:** Sube los archivos `.ino` a la ESP32 y ejecuta los scripts de Python en RoboDK para conectar la celda.
