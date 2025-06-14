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

### FreeRTOS

### Quantum Leaps

### Nextion
