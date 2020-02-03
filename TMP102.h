/**
  * @file    TMP102.cpp
  * @version 0.1.0
  * @author  (c) Craig A. Evans, University of Leeds, Jan 2016, modified by Adam Mitcell
  * @brief   TMP102 driver module. Measures temperature for the radiator sensor node v1.0.0. Designed by Think Engineer.
  * 
  * Example: 
  * code
  * #include "TMP102.h"
  *
  * TMP102 temp(SDA,SCL); 
  * 
  * void setup(){
  *    temp.init();
  * }
  * int main() {
  *     float temp_C=temp.get_temperature();
  * }
  * @endcode
  */

/** Header Guard
 */
#ifndef TMP102_H
#define TMP102_H

#include "mbed.h"

/** The next thing in a library is usually any required defines
 *  addresses for ADD0 connected to GND
 */
#define TMP102_ADD      0x48
#define TMP102_R_ADD    0x91
#define TMP102_W_ADD    0x90

/** Register addresses
 */
#define TEMP_REG    0x00
#define CONFIG_REG  0x01
#define TLOW_REG   0x02
#define THIGH_REG    0x03

/** Class TMP102
 */
class TMP102
{
    // we define the methods that are 'public' i.e. able to be used by the user
public:
    
    /** Constructor to create the object */
    TMP102(PinName sda, PinName scl);
    
    /* Reads temperature from the sensor */
    float ReadTemperature();
private:
    /* we will also create an initialisation method*/
    int init();
    
private:
    // class data member names often have a trailing underscore to make them easily identifiable
    I2C* i2c_;
};

// end of the header guard
#endif