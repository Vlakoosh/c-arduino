#include <util/delay.h>
#include <avr/io.h>

#define SSD1306_I2C_ADDRESS 0x3C
#define SSD1306_COMMAND_MODE 0x00
#define SSD1306_DATA_MODE 0x40

#define SDA_PIN 4 // Pin A4
#define SCL_PIN 5 // Pin A5

// Function to initialize I2C hardware
void i2c_init() {
  // Initialize I2C 

    // Set SDA and SCL pins as outputs
    DDRC |= (1 << SDA_PIN) | (1 << SCL_PIN);
    // Enable pull-up resistors for SDA and SCL pins
    PORTC |= (1 << SDA_PIN) | (1 << SCL_PIN);
    // this is just like enabling a button pin as input

}


void i2c_start() {
    // Start condition: SDA from high to low while SCL is high
    PORTC |= (1 << SDA_PIN);
    _delay_us(2);
    PORTC &= ~(1 << SDA_PIN);
    _delay_us(2);
}

void i2c_stop() {
    // Stop condition: SDA from low to high while SCL is high
    PORTC &= ~(1 << SDA_PIN);
    _delay_us(2);
    PORTC |= (1 << SDA_PIN);
    _delay_us(2);
}

void i2c_write_bit(uint8_t bit) {
    // Write a single bit to the SDA pin
    if (bit) {
        PORTC |= (1 << SDA_PIN);
    } else {
        PORTC &= ~(1 << SDA_PIN);
    }
    // Generate clock pulse
    PORTC |= (1 << SCL_PIN);
    _delay_us(2);
    PORTC &= ~(1 << SCL_PIN);
    _delay_us(2);
}



void i2c_write_byte(uint8_t byte) {
    // Write a byte to the I2C bus
    for (int i = 7; i >= 0; i--) {
        i2c_write_bit((byte >> i) & 1);
    }
    // Receive ACK bit
    i2c_write_bit(0); // Dummy bit, we're not reading ACK
}

// Function to send a command to the SSD1306 / transmit a byte over I2C
void sendCommand(uint8_t command) {
  // Start I2C communication with SSD1306
  i2c_start();                                  // start data transfer
  i2c_write_byte(SSD1306_I2C_ADDRESS << 1);     // Slave address + Write bit
  i2c_write_byte(SSD1306_COMMAND_MODE);         // Command mode
  i2c_write_byte(command);                      // Send command byte
  i2c_start();                                  // finish command
  // End I2C communication
}

// Function to set a pixel at a specific location with a specific color
void setPixel(uint8_t x, uint8_t y, uint8_t color) {
  // Set column address
  sendCommand(0x21);          // (select start/end columns with next 2 commands)
  sendCommand(x);             // (select the start column)
  sendCommand(x);             // (select the end column)
  // Set page address
  sendCommand(0x22);          // (select start/end rows with next 2 commands)
  sendCommand(y/8);           // (select the start row)
  sendCommand(y/8);           // (select the end row)
  // Set data mode
  i2c_write_byte(SSD1306_I2C_ADDRESS << 1);     // Slave address + Write bit
  i2c_write_byte(SSD1306_DATA_MODE);            // Data mode, idk
  // Set pixel data
  uint8_t pixelMask = 1 << (y % 8);
  if (color == 0) {
    // Clear the pixel
    i2c_write_byte(0x00);
  } else {
    // Set the pixel
    i2c_write_byte(pixelMask);
  }
  // End I2C communication
}

int main() {
  // Initialize I2C hardware
  i2c_init();

  // Set a pixel at position (10, 20) with color white (1)
  setPixel(10, 20, 0);

  // Main loop
  while (1) {
    //code here

    //todo
  }

  return 0;
}
