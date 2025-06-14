# AWG RP2040

## Introducción
> El proyecto consiste en el diseño e implementación de un Generador de Funciones Arbitrarias (AWG) utilizando una Raspberry Pi Pico. El objetvio es generar cualquier señal periódica (actualmente cargadas senoidal, triangular y cuadrada). Respecto al hardware posee el microcontrolador RP2040 y permite ajustar el tipo de señal, frecuencia, amplitud y offset, con un rango de salida de hasta 10 Vpp, offset de hasta +- 5 Vp y una frecuencia máxima de 1.5 MHz, con resolución de 1 Hz. Para la conversión digital a analógica se emplea una red R-2R controlada por los periféricos PIO y 2 DMAs encadenados, perimitiendo un flujo continuo de datos a alta velocidad.

> Respecto al sotfware está desarrollado mediante el sistema operativo en tiempo real FreeRTOS junto con el framework Quantum Leaps (QP), el cual utiliza una arquitectura basada en máquinas de estado finitas (donde su fuerte en este proyecto consiste en el menú para la configuración como se verá en una imagen mas adelante) y objetos activos. Esto permite una gran modularidad y escalabilidad del proyecto. Además se tiene una pantalla Nextion de 2.4' que permite mostrar las configuraciones antes mecionadas al usuario.

## RPI Pi Pico

![Diagrama de conexionado del Bus Can con sus Nodos](https://github.com/Agustin586/AWG-RP2040/blob/main/img/pico2w-pinout.svg)

> Pinout de la placa de desarrollo RPI Pi Pico

## Hardware

![Placa de Desarrollo](https://github.com/Agustin586/AWG-RP2040/blob/main/img/AWG_Placa.jpeg)

> Exposición del proyecto

## PCB

La Placa fue diseñada en el software de Altium Designer 2021. Dicho proyecto puede ser descargado en la carpeta correspondiente.

## Sotfware 

Como se comentó al comienzo el programa fue realizado con el sistema operativo en tiempo real FreeRTOS junto con Quantum Leaps, el cual nos permite generar máquinas de estado. Para la lógica en el programa se realizó una estructura en capas, como se puede ver a continuación.

![Diagrama en capas](https://github.com/Agustin586/AWG-RP2040/blob/main/img/Diagrama%20en%20capas.png)

> Diagrama en capas

En este diagrama podemos ver la división en capas del proyecto. En lo más alto tenemos el framework de Quantum Leaps, que al tener las máquinas de estados se encuentran lo más cerca posible del usuario (respecto al sotfware). Esa etapa se comunica con el display junto con el archivo AWG. Este último controla el objeto de tipo señal que se encarga de guardar toda la información necesaria para que el dispositivo genere la señal requerida por el usuario, a decir frecuencia, amplitud, offset, buffer de datos (muy importante ya que es donde se carga cada punto a muestrear), etc. Para lograr esto, el objeto señal contiene información de cada objeto generado por las capas inferiores, como puede verse a continuación:

```c
// Objeto tipo generador de funciones
typedef struct
{
    dacR2R_t EtapaDac;
    amplificacion_t EtapaAmp;
    offset_t EtapaOffset;
    periferico_t DatosPerifericos;
} awg;

// Generamos el objeto señal
awg Gen_Funcion;
```
> Si tuvieramos la posibilidad de generar (quizás con más pines disponibles) otro canal, simplementa bastaría con declarar otro objeto de tipo awg. Deberíamos tener presente que al tener mas de un canal el ancho de banda disminuiría por lo que no podríamos lograr una frecuencia como la específicada al comienzo. Cabe destacar que la frecuencia de la señal senoidal puede llevarse hasta 4 MHz, logrando una buena respuesta. Sin embargo se dejó por software la limitación de 1.5 MHz para todas las señales.

### FreeRTOS

Con el objetivo de distribuir distintas acciones en particular, se realizaron diferentes tareas. En la siguiente tabla puede verse una descripción mas detallada de cada tarea.

| Tarea | Descripción | Tipo de procesamiento |
|:-----|:-------------|:----------------------|
|Encoder| Se encarga de detectar una notificación de interrupción cuando el encoder se mueve hacia un lado en particular. Junto con esto activa una variable para detectar el lado al que fue girado el encoder (izquierda o derecha). | Interrupción |
|Pulsadores| Cada cierto tiempo se ejecuta dicha tarea con el fin de detectar por polling el estado de los pulsadores. | Continua |
|QP Máquina de estado| Se ejecuta la máquina de estado como una tarea de tipo estática. | Aperiódica. Solo cuando sucede un evento o cambia de estado |


### Quantum Leaps

![Máquina de Estados](https://github.com/Agustin586/AWG-RP2040/blob/main/img/SM_of_Awg.png)

> Máquina de estados para la configuración de los parámetros.

### Nextion

## Ensayos
