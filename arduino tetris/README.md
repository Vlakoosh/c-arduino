# The Arduino Tetris LED Matrix Project

## Short Description
This is an overly overengineered version of Tetris built with 2 breadboards, 2 8x8 LED matrixes, 4 shift registers, 6 buttons, a buzzer, and a LOT of wires

## Parts
- [Arduino R3](https://www.google.com)
- [2x Full Size Breadboards](https://www.google.com)
- [2x 8x8 LED matrix (pure 16 pin with no extra pcb or chip)](https://www.google.com)
- [4x 74HC595 shift register](https://www.google.com)
- [6x button/switch](https://www.google.com)
- [jumper wires (male to male only)](https://www.google.com)
- [arduino prototype breadboard shield](https://www.google.com)
- [16x 10k Ohm resistor](https://www.google.com)
- [Piezo buzzer](https://www.google.com)

## Requirements
|Requirement|Solution|
|---|---|
|Control of at least 1 LED (D1 - D4)|controlling a 8x16 grid of LEDs|
|Detection of a button press on at least one of the buttons (S1 - S3)|Using 6 different buttons (4 directional, A, B)|
|Use of the buzzer|using buzzer for various beeps and boops in the game.|
|Use of the buzzer with various notes, OR dimming the LEDs|Using the buzzer to make sound effects for completing a row and for losing a game|
|Control of the 8-segment display (use of the KdG libraries is allowed)|Not using an 8-segment display, but a 128 (8x16) segment display|
|Use of the ADC|Using ADC to pick random Tetris pieces|
|Your own, self-written library/libraries for all generic functions of the expansion shield / the arduino (don’t include any application-specific code in the libraries)|Using my own button and buzzer library. Also, I wrote a custom 8x16 LED matrix library that I use a lot in the project|
|Use of pointers and dynamic memory allocation|TETROMINOS struct holding all tetris pieces is dynamically allocated using malloc|
|Parameter “by value” and “by reference”|Passing arrays as "reference" in methods and passing most int values as "value" in functions|
|Use of interrupts|Using timer and button interrupts for game logic|
|Use of timers|Using timers to update game screen and tetris pieces around every half a second|
|Use of the serial communication with the connected computer (use of the KdG libraries is allowed)|After the game is over, arduino prints score to the console|
|Use of arrays|Using an array to represent a game field|
|Use of structs|Using custom TETROMINO and TETROMINOS structs|
|Use of macros|Using macros for pins of clock, data-in pins, buttons, buzzer, and shift register push pins |
