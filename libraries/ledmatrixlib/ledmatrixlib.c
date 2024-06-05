#include <avr/io.h>
#include <util/delay.h>
#include <stddef.h>

// set pins for top LED matrix
#define DATA_PIN_ROW_1 PD6
#define PUSH_PIN_ROW_1 PD7
#define DATA_PIN_COLUMN_1 PD4
#define PUSH_PIN_COLUMN_1 PD5

// set pins for bottom LED matrix
#define DATA_PIN_ROW_2 PB0
#define PUSH_PIN_ROW_2 PB1
#define DATA_PIN_COLUMN_2 PB2
#define PUSH_PIN_COLUMN_2 PB3

// set pin for the shared update clock signal
#define CLOCK PD2

// initialize all the pins for the library
void initMatrix()
{
  DDRD |= (1 << DATA_PIN_COLUMN_1);
  DDRD |= (1 << DATA_PIN_ROW_1);
  DDRD |= (1 << PUSH_PIN_COLUMN_1);
  DDRD |= (1 << PUSH_PIN_ROW_1);

  DDRB |= (1 << DATA_PIN_COLUMN_2);
  DDRB |= (1 << DATA_PIN_ROW_2);
  DDRB |= (1 << PUSH_PIN_COLUMN_2);
  DDRB |= (1 << PUSH_PIN_ROW_2);

  DDRD |= (1 << CLOCK);

  PORTD &= ~(1 << PUSH_PIN_COLUMN_1);
  PORTD &= ~(1 << PUSH_PIN_ROW_1);
  PORTB &= ~(1 << PUSH_PIN_COLUMN_2);
  PORTB &= ~(1 << PUSH_PIN_ROW_2);
}

// turn on all LEDs on the top half of the "screen"
void lightUpWholeTopMatrix()
{
  // light down the clocks
  PORTD &= ~(1 << CLOCK);

  PORTD &= ~(1 << PUSH_PIN_COLUMN_1);
  PORTD &= ~(1 << PUSH_PIN_ROW_1);

  PORTD &= ~(1 << DATA_PIN_COLUMN_1);
  PORTD |= (1 << DATA_PIN_ROW_1);

  for (int i = 0; i < 8; i++)
  {
    // push LOW bits for columns, and HIGH bits for rows
    PORTD |= (1 << PUSH_PIN_COLUMN_1);
    PORTD |= (1 << PUSH_PIN_ROW_1);

    PORTD &= ~(1 << PUSH_PIN_COLUMN_1);
    PORTD &= ~(1 << PUSH_PIN_ROW_1);
  }
  // update the output
  PORTD |= (1 << CLOCK);
}

// turn off all LEDs on the top half of the "screen"
void lightDownWholeTopMatrix()
{
  // light down the clocks
  PORTD &= ~(1 << CLOCK);

  PORTD &= ~(1 << PUSH_PIN_COLUMN_1);
  PORTD &= ~(1 << PUSH_PIN_ROW_1);

  PORTD |= (1 << DATA_PIN_COLUMN_1);
  PORTD &= ~(1 << DATA_PIN_ROW_1);

  for (int i = 0; i < 8; i++)
  {
    // push LOW bits for columns, and HIGH bits for rows
    PORTD |= (1 << PUSH_PIN_COLUMN_1);
    PORTD |= (1 << PUSH_PIN_ROW_1);

    PORTD &= ~(1 << PUSH_PIN_COLUMN_1);
    PORTD &= ~(1 << PUSH_PIN_ROW_1);
  }
  // update the output
  PORTD |= (1 << CLOCK);
}

// turn on all LEDs on the bottom half of the "screen"
void lightUpWholeBottomMatrix()
{
  // light down the clocks
  PORTD &= ~(1 << CLOCK);

  PORTB &= ~(1 << PUSH_PIN_COLUMN_2);
  PORTB &= ~(1 << PUSH_PIN_ROW_2);

  PORTB &= ~(1 << DATA_PIN_COLUMN_2);
  PORTB |= (1 << DATA_PIN_ROW_2);

  for (int i = 0; i < 8; i++)
  {
    // push LOW bits for columns, and HIGH bits for rows
    PORTB |= (1 << PUSH_PIN_COLUMN_2);
    PORTB |= (1 << PUSH_PIN_ROW_2);

    PORTB &= ~(1 << PUSH_PIN_COLUMN_2);
    PORTB &= ~(1 << PUSH_PIN_ROW_2);
  }
  // update the output
  PORTD |= (1 << CLOCK);
}

// turn off all LEDs on the bottom half of the "screen"
void lightDownWholeBottomMatrix()
{
  // light down the clocks
  PORTD &= ~(1 << CLOCK);

  PORTB &= ~(1 << PUSH_PIN_COLUMN_2);
  PORTB &= ~(1 << PUSH_PIN_ROW_2);

  PORTB |= (1 << DATA_PIN_COLUMN_2);
  PORTB &= ~(1 << DATA_PIN_ROW_2);

  for (int i = 0; i < 8; i++)
  {
    // push LOW bits for columns, and HIGH bits for rows
    PORTB |= (1 << PUSH_PIN_COLUMN_2);
    PORTB |= (1 << PUSH_PIN_ROW_2);

    PORTB &= ~(1 << PUSH_PIN_COLUMN_2);
    PORTB &= ~(1 << PUSH_PIN_ROW_2);
  }
  // update the output
  PORTD |= (1 << CLOCK);
}

// turn on all LEDs
void lightUpWholeMatrix()
{
  lightUpWholeBottomMatrix();
  lightUpWholeTopMatrix();
}

// turn off all LEDs
void lightDownWholeMatrix()
{
  lightDownWholeTopMatrix();
  lightDownWholeBottomMatrix();
}

// enable a specific row on the top matrix by setting its bit to HIGH and the other bits to LOW
void setRowOnTopMatrix(int row)
{
  if (row < 1 || row > 8)
    return;
  row = row - 1;

  // light down the clocks
  PORTD &= ~_BV(CLOCK);

  PORTD &= ~_BV(PUSH_PIN_ROW_1);

  for (int i = 0; i < 8; i++)
  {
    if (row == i)
    {
      PORTD |= _BV(DATA_PIN_ROW_1);
    }
    else
      PORTD &= ~_BV(DATA_PIN_ROW_1);
    PORTD |= _BV(PUSH_PIN_ROW_1);
    PORTD &= ~_BV(PUSH_PIN_ROW_1);
  }
  PORTD |= _BV(CLOCK);
}

// enable a specific column on the top matrix by setting its bit to to LOW and the other bits to HIGH
void setColumnOnTopMatrix(int col)
{
  if (col < 1 || col > 8)
    return;
  col = col - 1;

  // light down the clocks
  PORTD &= ~_BV(CLOCK);

  PORTD &= ~_BV(PUSH_PIN_COLUMN_1);

  PORTD |= _BV(DATA_PIN_COLUMN_1);

  for (int i = 0; i < 8; i++)
  {
    if (col == i)
    {
      PORTD &= ~_BV(DATA_PIN_COLUMN_1);
    }
    else
      PORTD |= _BV(DATA_PIN_COLUMN_1);
    PORTD |= _BV(PUSH_PIN_COLUMN_1);
    PORTD &= ~_BV(PUSH_PIN_COLUMN_1);
  }
  PORTD |= _BV(CLOCK);
}

// enable multiple columns at once on the top matrix by setting their bits to LOW and the other bits to HIGH
void setMultipleColumnsOnTopMatrix(uint8_t cols)
{
  // light down the clocks
  PORTD &= ~_BV(CLOCK);

  PORTD &= ~_BV(PUSH_PIN_COLUMN_1);

  PORTD |= _BV(DATA_PIN_COLUMN_1);

  for (int i = 0; i < 8; i++)
  {
    if (cols & (1 << i))
    {
      PORTD &= ~_BV(DATA_PIN_COLUMN_1);
    }
    else
      PORTD |= _BV(DATA_PIN_COLUMN_1);
    PORTD |= _BV(PUSH_PIN_COLUMN_1);
    PORTD &= ~_BV(PUSH_PIN_COLUMN_1);
  }
  PORTD |= _BV(CLOCK);
}

// enable a specific row on the bottom matrix by setting its bit to HIGH and the other bits to LOW
void setRowOnBottomMatrix(int row)
{
  if (row < 1 || row > 8)
    return;
  row = row - 1;

  // light down the clocks
  PORTD &= ~_BV(CLOCK);

  PORTB &= ~_BV(PUSH_PIN_ROW_2);

  for (int i = 0; i < 8; i++)
  {
    if (row == i)
    {
      PORTB |= _BV(DATA_PIN_ROW_2);
    }
    else
      PORTB &= ~_BV(DATA_PIN_ROW_2);
    PORTB |= _BV(PUSH_PIN_ROW_2);
    PORTB &= ~_BV(PUSH_PIN_ROW_2);
  }
  PORTD |= _BV(CLOCK);
}

// enable a specific column on the bottom matrix by setting its bit to to LOW and the other bits to HIGH
void setColumnOnBottomMatrix(int col)
{
  if (col < 1 || col > 8)
    return;
  col = col - 1;

  // light down the clocks
  PORTD &= ~_BV(CLOCK);

  PORTB &= ~_BV(PUSH_PIN_COLUMN_2);

  PORTB |= _BV(DATA_PIN_COLUMN_2);

  for (int i = 0; i < 8; i++)
  {
    if (col == i)
    {
      PORTB &= ~_BV(DATA_PIN_COLUMN_2);
    }
    else
      PORTB |= _BV(DATA_PIN_COLUMN_2);
    PORTB |= _BV(PUSH_PIN_COLUMN_2);
    PORTB &= ~_BV(PUSH_PIN_COLUMN_2);
  }
  PORTD |= _BV(CLOCK);
}

// enable multiple columns at once on the top matrix by setting their bits to LOW and the other bits to HIGH
void setMultipleColumnsOnBottomMatrix(uint8_t cols)
{
  // light down the clocks
  PORTD &= ~_BV(CLOCK);

  PORTB &= ~_BV(PUSH_PIN_COLUMN_2);

  PORTB |= _BV(DATA_PIN_COLUMN_2);

  for (int i = 0; i < 8; i++)
  {
    if (cols & (1 << i))
    {
      PORTB &= ~_BV(DATA_PIN_COLUMN_2);
    }
    else
      PORTB |= _BV(DATA_PIN_COLUMN_2);
    PORTB |= _BV(PUSH_PIN_COLUMN_2);
    PORTB &= ~_BV(PUSH_PIN_COLUMN_2);
  }
  PORTD |= _BV(CLOCK);
}

// enable ONE specific row and ONE or MORE columns at once. The method picks automatically between the top and bottom matrix
void displayRow(int row, uint8_t columns)
{
  if (row > 8)
  {
    setMultipleColumnsOnBottomMatrix(columns);
    setRowOnBottomMatrix(row - 8);
    _delay_us(500);
    lightDownWholeBottomMatrix();
  }
  else
  {
    setMultipleColumnsOnTopMatrix(columns);
    setRowOnTopMatrix(row);
    _delay_us(500);
    lightDownWholeTopMatrix();
  }
}

void testDisplay()
{
  initMatrix();

  _delay_ms(500);
  while (1)
  {

    for (int i = 1; i <= 16; i++)
    {
      if (i == 1)
      {
        setMultipleColumnsOnBottomMatrix(0b00000000);
      }
      if (i == 9)
      {
        setMultipleColumnsOnTopMatrix(0b00000000);
      }

      for (int x = 0; x < 8; x++)
      {
        uint8_t cols;
        if (i % 2)
        {
          cols = _BV(x);
        }
        else
        {
          cols = _BV(7 - x);
        }
        displayRow(i, cols);
        _delay_ms(50);
      }
    }
  }
}



void displayScreenArray(uint8_t *screenArray, int width, int height)
{
  for (int row = 0; row < height; row++)
  {
    uint8_t cols = 0b00000000;
    for (int col = 0; col < width; col++)
    {
      if (screenArray[row * width + col])
      {
        cols |= (1 << (width - col - 1));
      }
    }
    displayRow(row + 1, cols);
  }
}