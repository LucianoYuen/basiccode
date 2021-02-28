/*!
 * @file Adafruit_MCP23017.cpp
 *
 * @mainpage Adafruit MCP23017 Library
 *
 * @section intro_sec Introduction
 *
 * This is a library for the MCP23017 i2c port expander
 *
 * These displays use I2C to communicate, 2 pins are required to
 * interface
 * Adafruit invests time and resources providing this open source code,
 * please support Adafruit and open-source hardware by purchasing
 * products from Adafruit!
 *
 * @section author Author
 *
 * Written by Limor Fried/Ladyada for Adafruit Industries.
 *
 * @section license License
 *
 * BSD license, all text above must be included in any redistribution
 */

#ifdef __AVR
#include <avr/pgmspace.h>
#elif defined(ESP8266)
#include <pgmspace.h>
#endif
#include "Adafruit_MCP23017.h"

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

// minihelper to keep Arduino backward compatibility
static inline void wiresend(uint8_t x, TwoWire *theWire) {
#if ARDUINO >= 100
  theWire->write((uint8_t)x);
#else
  theWire->send(x);
#endif
}

static inline uint8_t wirerecv(TwoWire *theWire) {
#if ARDUINO >= 100
  return theWire->read();
#else
  return theWire->receive();
#endif
}

/**
 * Bit number associated to a give Pin
 */
uint8_t Adafruit_MCP23017::bitForPin(uint8_t pin) { return pin % 8; }

/**
 * STM32 Bit number associated to a give Pin
 */
uint8_t bitForPin(uint8_t pin) 
{ 
  return pin % 8; 
}

/**
 * Register address, port dependent, for a given PIN
 */
uint8_t Adafruit_MCP23017::regForPin(uint8_t pin, uint8_t portAaddr,
                                     uint8_t portBaddr) {
  return (pin < 8) ? portAaddr : portBaddr;
}

/**
 * STM32 Register address, port dependent, for a given PIN
 */
uint8_t regForPin(uint8_t pin, uint8_t portAaddr, uint8_t portBaddr) 
{
  return (pin < 8) ? portAaddr : portBaddr ;
}

/**
 * Reads a given register
 */
uint8_t Adafruit_MCP23017::readRegister(uint8_t addr) {
  // read the current GPINTEN
  _wire->beginTransmission(MCP23017_ADDRESS | i2caddr);
  wiresend(addr, _wire);
  _wire->endTransmission();
  _wire->requestFrom(MCP23017_ADDRESS | i2caddr, 1);
  return wirerecv(_wire);
}

/**
 * STM32 Reads a given register
 */
uint8_t readRegister(uint8_t addr)
{
	uint8_t wirerecv;

	uint8_t TXbuffer[1];

	TXbuffer[0] = addr;

	uint8_t RXbuffer[1];

ret = HAL_I2C_Master_Transmit(&hi2c1, MCP23017_ADDRESS, TXbuffer, 1, HAL_MAX_DELAY);
if ( ret != HAL_OK ) {
	  HAL_GPIO_WritePin(GPIOA, LED1_Pin, GPIO_PIN_SET);
	  HAL_Delay(100);
}

else	{
  // Read 2 bytes from the temperature register
  ret = HAL_I2C_Master_Receive(&hi2c1, MCP23017_ADDRESS, RXbuffer, 1, HAL_MAX_DELAY);
  if ( ret != HAL_OK ) {
  	HAL_GPIO_WritePin(GPIOA, LED2_Pin, GPIO_PIN_SET);
  	HAL_Delay(100);
  } else {

  	//TEST_OK_Signal();

  	wirerecv = RXbuffer[0];
  	}
}
return wirerecv;
}

/**
 * Writes a given register
 */
void Adafruit_MCP23017::writeRegister(uint8_t regAddr, uint8_t regValue) {
  // Write the register
  _wire->beginTransmission(MCP23017_ADDRESS | i2caddr);
  wiresend(regAddr, _wire);
  wiresend(regValue, _wire);
  _wire->endTransmission();
}

/**
 * STM32Writes a given register
 */
void writeRegister(uint8_t regAddr, uint8_t regValue)
{
	uint8_t TXbuffer[2];

	TXbuffer[0] = regAddr;
	TXbuffer[1] = regValue;

ret = HAL_I2C_Master_Transmit(&hi2c1, MCP23017_ADDRESS, TXbuffer, 2, HAL_MAX_DELAY);
if ( ret != HAL_OK ) {
	  HAL_GPIO_WritePin(GPIOA, LED1_Pin, GPIO_PIN_SET);
	  HAL_Delay(100);
    }
}

/**
 * Helper to update a single bit of an A/B register.
 * - Reads the current register value
 * - Writes the new register value
 */
void Adafruit_MCP23017::updateRegisterBit(uint8_t pin, uint8_t pValue,
                                          uint8_t portAaddr,
                                          uint8_t portBaddr) {
  uint8_t regValue;
  uint8_t regAddr = regForPin(pin, portAaddr, portBaddr);
  uint8_t bit = bitForPin(pin);
  regValue = readRegister(regAddr);

  // set the value for the particular bit
  bitWrite(regValue, bit, pValue);

  writeRegister(regAddr, regValue);
}

/**STM32
 * Helper to update a single bit of an A/B register.
 * - Reads the current register value
 * - Writes the new register value
 */
void updateRegisterBit(uint8_t pin, uint8_t pValue, uint8_t portAaddr, uint8_t portBaddr)
{
  uint8_t regValue;
  uint8_t New_regValue;
  uint8_t regAddr = regForPin(pin, portAaddr, portBaddr);
  uint8_t bit = bitForPin(pin);

  regValue = readRegister(regAddr);

  New_regValue = bitWrite(regValue, bit, pValue);

  writeRegister(regAddr, New_regValue);
}

////////////////////////////////////////////////////////////////////////////////

/*!
 * Initializes the MCP23017 given its HW selected address, see datasheet for
 * Address selection.
 * @param addr Selected address
 * @param theWire the I2C object to use, defaults to &Wire
 */
void Adafruit_MCP23017::begin(uint8_t addr, TwoWire *theWire) {
  if (addr > 7) {
    addr = 7;
  }
  i2caddr = addr;
  _wire = theWire;

  _wire->begin();

  // set defaults!
  // all inputs on port A and B
  writeRegister(MCP23017_IODIRA, 0xff);
  writeRegister(MCP23017_IODIRB, 0xff);

  // Turn off interrupt triggers
  writeRegister(MCP23017_GPINTENA, 0x00);
  writeRegister(MCP23017_GPINTENB, 0x00);

  // Turn off pull up resistors
  writeRegister(MCP23017_GPPUA, 0x00);
  writeRegister(MCP23017_GPPUB, 0x00);
}

/*!STM32
 * Initializes the MCP23017 given its HW selected address, see datasheet for
 * Address selection.
 * @param addr Selected address
 * @param theWire the I2C object to use, defaults to &Wire
 */
void MCP23017_Init() 
{
  // set defaults!
  // all inputs on port A and B
  writeRegister(MCP23017_IODIRA, 0xff);
  writeRegister(MCP23017_IODIRB, 0xff);

  // Turn off interrupt triggers
  writeRegister(MCP23017_GPINTENA, 0x00);
  writeRegister(MCP23017_GPINTENB, 0x00);

  // Turn off pull up resistors
  writeRegister(MCP23017_GPPUA, 0x00);
  writeRegister(MCP23017_GPPUB, 0x00);
}

/**
 * Initializes the default MCP23017, with 000 for the configurable part of the
 * address
 * @param theWire the I2C object to use, defaults to &Wire
 */
void Adafruit_MCP23017::begin(TwoWire *theWire) { begin(0, theWire); }

/**
 * Sets the pin mode to either INPUT or OUTPUT
 * @param p Pin to set
 * @param d Mode to set the pin
 */
void Adafruit_MCP23017::pinMode(uint8_t p, uint8_t d) {
  updateRegisterBit(p, (d == INPUT), MCP23017_IODIRA, MCP23017_IODIRB);
}

/**STM32
 * Sets the pin mode to either INPUT or OUTPUT
 * @param p Pin to set
 * @param d Mode to set the pin
 */
void pinMode(uint8_t p, uint8_t d)
{
  updateRegisterBit(p, (d == 0), MCP23017_IODIRA, MCP23017_IODIRB);
}

/**
 * Reads all 16 pins (port A and B) into a single 16 bits variable.
 * @return Returns the 16 bit variable representing all 16 pins
 */
uint16_t Adafruit_MCP23017::readGPIOAB() {
  uint16_t ba = 0;
  uint8_t a;

  // read the current GPIO output latches
  _wire->beginTransmission(MCP23017_ADDRESS | i2caddr);
  wiresend(MCP23017_GPIOA, _wire);
  _wire->endTransmission();

  _wire->requestFrom(MCP23017_ADDRESS | i2caddr, 2);
  a = wirerecv(_wire);
  ba = wirerecv(_wire);
  ba <<= 8;
  ba |= a;

  return ba;
}

/**STM32
 * Reads all 16 pins (port A and B) into a single 16 bits variable.
 * @return Returns the 16 bit variable representing all 16 pins
 */
uint16_t readGPIOAB()
{
	uint16_t ba = 0;

    uint8_t a;

	uint8_t TXbuffer[1];

	TXbuffer[0] = MCP23017_GPIOA;

	uint8_t RXbuffer[2];

ret = HAL_I2C_Master_Transmit(&hi2c1, MCP23017_ADDRESS, TXbuffer, 1, HAL_MAX_DELAY);
if ( ret != HAL_OK ) {
	  HAL_GPIO_WritePin(GPIOA, LED1_Pin, GPIO_PIN_SET);
	  HAL_Delay(100);
}

else	{
  // Read 2 bytes from the temperature register
  ret = HAL_I2C_Master_Receive(&hi2c1, MCP23017_ADDRESS, RXbuffer, 2, HAL_MAX_DELAY);
  if ( ret != HAL_OK ) {
  	HAL_GPIO_WritePin(GPIOA, LED2_Pin, GPIO_PIN_SET);
  	HAL_Delay(100);
  } else {

  	//TEST_OK_Signal();

  	a = RXbuffer[0];
    ba = RXbuffer[1];
    ba <<= 8;
    ba |= a;
  	}
}
return ba;
}

/**
 * Read a single port, A or B, and return its current 8 bit value.
 * @param b Decided what gpio to use. Should be 0 for GPIOA, and 1 for GPIOB.
 * @return Returns the b bit value of the port
 */
uint8_t Adafruit_MCP23017::readGPIO(uint8_t b) {

  // read the current GPIO output latches
  _wire->beginTransmission(MCP23017_ADDRESS | i2caddr);
  if (b == 0)
    wiresend(MCP23017_GPIOA, _wire);
  else {
    wiresend(MCP23017_GPIOB, _wire);
  }
  _wire->endTransmission();

  _wire->requestFrom(MCP23017_ADDRESS | i2caddr, 1);
  return wirerecv(_wire);
}

/**STM32
 * Read a single port, A or B, and return its current 8 bit value.
 * @param b Decided what gpio to use. Should be 0 for GPIOA, and 1 for GPIOB.
 * @return Returns the b bit value of the port
 */
uint8_t readGPIO(uint8_t b)
{
  uint8_t TXbuffer[1];

  if (b == 0)
    TXbuffer[0] = MCP23017_GPIOA;
  else {
    TXbuffer[0] = MCP23017_GPIOB;
  }
	uint8_t RXbuffer[1];

    uint8_t data;

ret = HAL_I2C_Master_Transmit(&hi2c1, MCP23017_ADDRESS, TXbuffer, 1, HAL_MAX_DELAY);
if ( ret != HAL_OK ) {
	  HAL_GPIO_WritePin(GPIOA, LED1_Pin, GPIO_PIN_SET);
	  HAL_Delay(100);
}

else	{
  // Read 2 bytes from the temperature register
  ret = HAL_I2C_Master_Receive(&hi2c1, MCP23017_ADDRESS, RXbuffer, 1, HAL_MAX_DELAY);
  if ( ret != HAL_OK ) {
  	HAL_GPIO_WritePin(GPIOA, LED2_Pin, GPIO_PIN_SET);
  	HAL_Delay(100);
  } else {

  	data = RXbuffer[0];

  	}
}
return data;
}

/**
 * Writes all the pins in one go. This method is very useful if you are
 * implementing a multiplexed matrix and want to get a decent refresh rate.
 */
void Adafruit_MCP23017::writeGPIOAB(uint16_t ba) {
  _wire->beginTransmission(MCP23017_ADDRESS | i2caddr);
  wiresend(MCP23017_GPIOA, _wire);
  wiresend(ba & 0xFF, _wire);
  wiresend(ba >> 8, _wire);
  _wire->endTransmission();
}

/**STM32
 * Writes all the pins in one go. This method is very useful if you are
 * implementing a multiplexed matrix and want to get a decent refresh rate.
 */
void Adafruit_MCP23017::writeGPIOAB(uint16_t ba) {
  _wire->beginTransmission(MCP23017_ADDRESS | i2caddr);
  wiresend(MCP23017_GPIOA, _wire);
  wiresend(ba & 0xFF, _wire);
  wiresend(ba >> 8, _wire);
  _wire->endTransmission();
}

void writeGPIOAB(uint16_t ba)
{
	uint8_t TXbuffer[3];

	TXbuffer[0] = MCP23017_GPIOA;
	TXbuffer[1] = ba & 0xFF;
    TXbuffer[2] = ba >> 8;

ret = HAL_I2C_Master_Transmit(&hi2c1, MCP23017_ADDRESS, TXbuffer, 3, HAL_MAX_DELAY);
if ( ret != HAL_OK ) {
	  HAL_GPIO_WritePin(GPIOA, LED1_Pin, GPIO_PIN_SET);
	  HAL_Delay(100);
    }
}

/*!
 * @brief Writes to a pin on the MCP23017
 * @param pin Pin to write to
 * @param d What to write to the pin
 */
void Adafruit_MCP23017::digitalWrite(uint8_t pin, uint8_t d) { //(0, HIGH);
  uint8_t gpio;
  uint8_t bit = bitForPin(pin);

  // read the current GPIO output latches
  uint8_t regAddr = regForPin(pin, MCP23017_OLATA, MCP23017_OLATB);
  gpio = readRegister(regAddr);

  // set the pin and direction
  bitWrite(gpio, bit, d);

  // write the new GPIO
  regAddr = regForPin(pin, MCP23017_GPIOA, MCP23017_GPIOB);
  writeRegister(regAddr, gpio);
}

/*!STM32
 * @brief Writes to a pin on the MCP23017
 * @param pin Pin to write to
 * @param d What to write to the pin
 */
void digitalWrite(uint8_t pin, uint8_t d) 
{
  uint8_t gpio;
  uint8_t bit = bitForPin(pin);

  uint8_t regAddr = regForPin(pin, MCP23017_OLATA, MCP23017_OLATB);
  gpio = readRegister(regAddr);

  bitWrite(gpio, bit, d);

  regAddr = regForPin(pin, MCP23017_GPIOA, MCP23017_GPIOB);
  writeRegister(regAddr, gpio);
}

/*!
 * @brief Enables the pull-up resistor on the specified pin
 * @param p Pin to set
 * @param d Value to set the pin
 */
void Adafruit_MCP23017::pullUp(uint8_t p, uint8_t d) {
  updateRegisterBit(p, d, MCP23017_GPPUA, MCP23017_GPPUB);
}

/*!STM32
 * @brief Enables the pull-up resistor on the specified pin
 * @param p Pin to set
 * @param d Value to set the pin
 */
void pullUp(uint8_t p, uint8_t d) 
{
  updateRegisterBit(p, d, MCP23017_GPPUA, MCP23017_GPPUB);
}

/*!
 * @brief Reads the specified pin
 * @param pin Pin to read
 * @return Value of the pin
 */
uint8_t Adafruit_MCP23017::digitalRead(uint8_t pin) {
  uint8_t bit = bitForPin(pin);
  uint8_t regAddr = regForPin(pin, MCP23017_GPIOA, MCP23017_GPIOB);
  return (readRegister(regAddr) >> bit) & 0x1;
}

/*!STM32
 * @brief Reads the specified pin
 * @param pin Pin to read
 * @return Value of the pin
 */
uint8_t digitalRead(uint8_t pin)
{
  uint8_t i;
  uint8_t x; 
  uint8_t bit = bitForPin(pin);
  uint8_t regAddr = regForPin(pin, MCP23017_GPIOA, MCP23017_GPIOB);

  i = readRegister(regAddr);

  x = (i >> bit) & 0x1;

  return x;
}

/**
 * Configures the interrupt system. both port A and B are assigned the same
 * configuration.
 * @param mirroring Mirroring will OR both INTA and INTB pins.
 * @param openDrain Opendrain will set the INT pin to value or open drain.
 * @param polarity polarity will set LOW or HIGH on interrupt.
 * Default values after Power On Reset are: (false, false, LOW)
 * If you are connecting the INTA/B pin to arduino 2/3, you should configure the
 * interupt handling as FALLING with the default configuration.
 */
void Adafruit_MCP23017::setupInterrupts(uint8_t mirroring, uint8_t openDrain,
                                        uint8_t polarity) {
  // configure the port A
  uint8_t ioconfValue = readRegister(MCP23017_IOCONA);
  bitWrite(ioconfValue, 6, mirroring);
  bitWrite(ioconfValue, 2, openDrain);
  bitWrite(ioconfValue, 1, polarity);
  writeRegister(MCP23017_IOCONA, ioconfValue);

  // Configure the port B
  ioconfValue = readRegister(MCP23017_IOCONB);
  bitWrite(ioconfValue, 6, mirroring);
  bitWrite(ioconfValue, 2, openDrain);
  bitWrite(ioconfValue, 1, polarity);
  writeRegister(MCP23017_IOCONB, ioconfValue);
}

/**STM32
 * Configures the interrupt system. both port A and B are assigned the same
 * configuration.
 * @param mirroring Mirroring will OR both INTA and INTB pins.
 * @param openDrain Opendrain will set the INT pin to value or open drain.
 * @param polarity polarity will set LOW or HIGH on interrupt.
 * Default values after Power On Reset are: (false, false, LOW)
 * If you are connecting the INTA/B pin to arduino 2/3, you should configure the
 * interupt handling as FALLING with the default configuration.
 */
void setupInterrupts(uint8_t mirroring, uint8_t openDrain, uint8_t polarity)
{
  // configure the port A
  uint8_t ioconfValue = readRegister(MCP23017_IOCONA);
  uint8_t ioconfValue_1 = bitWrite(ioconfValue, 6, mirroring);
  uint8_t ioconfValue_2 = bitWrite(ioconfValue_1, 2, openDrain);
  uint8_t ioconfValue_3 = bitWrite(ioconfValue_2, 1, polarity);
  writeRegister(MCP23017_IOCONA, ioconfValue_3);
  // Configure the port B
  ioconfValue = readRegister(MCP23017_IOCONB);
  ioconfValue_1 = bitWrite(ioconfValue, 6, mirroring);
  ioconfValue_2 = bitWrite(ioconfValue_1, 2, openDrain);
  ioconfValue_3 = bitWrite(ioconfValue_2, 1, polarity);
  writeRegister(MCP23017_IOCONB, ioconfValue_3);
}
/**
 * Set's up a pin for interrupt. uses arduino MODEs: CHANGE, FALLING, RISING.
 *
 * Note that the interrupt condition finishes when you read the information
 * about the port / value that caused the interrupt or you read the port itself.
 * Check the datasheet can be confusing.
 * @param pin Pin to set
 * @param mode Mode to set the pin
 *
 */
void Adafruit_MCP23017::setupInterruptPin(uint8_t pin, uint8_t mode) {

  // set the pin interrupt control (0 means change, 1 means compare against
  // given value);
  updateRegisterBit(pin, (mode != CHANGE), MCP23017_INTCONA, MCP23017_INTCONB);
  // if the mode is not CHANGE, we need to set up a default value, different
  // value triggers interrupt

  // In a RISING interrupt the default value is 0, interrupt is triggered when
  // the pin goes to 1. In a FALLING interrupt the default value is 1, interrupt
  // is triggered when pin goes to 0.
  updateRegisterBit(pin, (mode == FALLING), MCP23017_DEFVALA, MCP23017_DEFVALB);

  // enable the pin for interrupt
  updateRegisterBit(pin, HIGH, MCP23017_GPINTENA, MCP23017_GPINTENB);
}

/**STM32
 * Set's up a pin for interrupt. uses arduino MODEs: CHANGE, FALLING, RISING.
 *
 * Note that the interrupt condition finishes when you read the information
 * about the port / value that caused the interrupt or you read the port itself.
 * Check the datasheet can be confusing.
 * @param pin Pin to set
 * @param mode Mode to set the pin
 *
 */
void setupInterruptPin(uint8_t pin, uint8_t mode)
{
  // set the pin interrupt control (0 means change, 1 means compare against
  // given value);
  updateRegisterBit(pin, (mode != CHANGE), MCP23017_INTCONA, MCP23017_INTCONB);
  // if the mode is not CHANGE, we need to set up a default value, different
  // value triggers interrupt

  // In a RISING interrupt the default value is 0, interrupt is triggered when
  // the pin goes to 1. In a FALLING interrupt the default value is 1, interrupt
  // is triggered when pin goes to 0.
  updateRegisterBit(pin, (mode == FALLING), MCP23017_DEFVALA, MCP23017_DEFVALB);

  // enable the pin for interrupt
  updateRegisterBit(pin, HIGH, MCP23017_GPINTENA, MCP23017_GPINTENB);
}

/**
 * Disable a pin for interrupt.
 *
 * @param pin Pin to set
 *
 */
void Adafruit_MCP23017::disableInterruptPin(uint8_t pin) {
  // disable the pin for interrupt
  updateRegisterBit(pin, LOW, MCP23017_GPINTENA, MCP23017_GPINTENB);
}

/**STM32
 * Disable a pin for interrupt.
 *
 * @param pin Pin to set
 *
 */
void Adafruit_MCP23017::disableInterruptPin(uint8_t pin)
{
  // disable the pin for interrupt
  updateRegisterBit(pin, LOW, MCP23017_GPINTENA, MCP23017_GPINTENB);
}

/*!
 * @brief Gets the last interrupt pin
 * @return Returns the last interrupt pin
 */
uint8_t Adafruit_MCP23017::getLastInterruptPin() {
  uint8_t intf;

  // try port A
  intf = readRegister(MCP23017_INTFA);
  for (int i = 0; i < 8; i++)
    if (bitRead(intf, i))
      return i;

  // try port B
  intf = readRegister(MCP23017_INTFB);
  for (int i = 0; i < 8; i++)
    if (bitRead(intf, i))
      return i + 8;

  return MCP23017_INT_ERR;
}

/*!
 * @brief Gets the last interrupt pin
 * @return Returns the last interrupt pin
 */
uint8_t getLastInterruptPin() {
  uint8_t intf;
  // try port A
  intf = readRegister(MCP23017_INTFA);
  for (int i = 0; i < 8; i++)
    if (bitRead(intf, i))
    {
        return i;
    }

  // try port B
  intf = readRegister(MCP23017_INTFB);
  for (int i = 0; i < 8; i++)
    if (bitRead(intf, i))
    {
        return i + 8;
    }
  return MCP23017_INT_ERR;
}

/*!
 * @brief Gets the value of the last interrupt pin
 * @return Returns the value of the last interrupt pin
 */
uint8_t Adafruit_MCP23017::getLastInterruptPinValue() {
  uint8_t intPin = getLastInterruptPin();
  if (intPin != MCP23017_INT_ERR) {
    uint8_t intcapreg = regForPin(intPin, MCP23017_INTCAPA, MCP23017_INTCAPB);
    uint8_t bit = bitForPin(intPin);
    return (readRegister(intcapreg) >> bit) & (0x01);
  }

  return MCP23017_INT_ERR;
}

/*!STM32
 * @brief Gets the value of the last interrupt pin
 * @return Returns the value of the last interrupt pin
 */
uint8_t Adafruit_MCP23017::getLastInterruptPinValue() {
  uint8_t intPin = getLastInterruptPin();
  if (intPin != MCP23017_INT_ERR) {
    uint8_t intcapreg = regForPin(intPin, MCP23017_INTCAPA, MCP23017_INTCAPB);
    uint8_t bit = bitForPin(intPin);
    uint8_t a = readRegister(intcapreg);
    uint8_t i = (a >> bit) & (0x01);
    return i;
  }

  return MCP23017_INT_ERR;
}
