# Conexiones del TFT LCD Touchscreen con ESP32

A continuación se detallan las conexiones entre el TFT LCD touchscreen y el ESP32:

| **TFT LCD**        | **ESP32 GPIO** |
|:-------------------|:---------------|
| **T_IRQ**          | GPIO 36        |
| **T_OUT**          | GPIO 39        |
| **T_DIN**          | GPIO 32        |
| **T_CS**           | GPIO 33        |
| **T_CLT_CLK**      | GPIO 25        |
| **SDO (MISO)**     | GPIO 12        |
| **LED**            | GPIO 21        |
| **SCK**            | GPIO 14        |
| **SDI (MOSI)**     | GPIO 13        |
| **D/C**            | GPIO 2         |
| **RESET**          | GPIO 5         |
| **CS**             | GPIO 15        |
| **GND**            | GND            |
| **VCC**            | 5V (or 3.3V)   |

> **Nota:** Asegúrate de conectar cada pin del TFT LCD al GPIO correspondiente en el ESP32 según la tabla para asegurar un funcionamiento correcto.

# Conexiones de la Termocupla con ESP32

A continuación se detallan las conexiones entre la termocupla y el ESP32:

| **Termocupla** | **ESP32 GPIO** |
|:---------------|:---------------|
| **DO**         | GPIO 4         |
| **CS**         | GPIO 18        |
| **CLK**        | GPIO 22        |

> **Nota:** Verifica que las conexiones estén firmemente establecidas para obtener lecturas precisas de la termocupla.
