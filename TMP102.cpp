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
  * int main() {
  *     float temp_C=temp.ReadTemperature();
  * }
  * @endcode
  */

/** Includes
 */
#include "TMP102.h"

TMP102::TMP102(PinName sda, PinName scl)
{
    /* in the constructor, we create the mbed API objects using 'new' */
    i2c_ = new I2C(sda,scl);
}
/** Initialises
 */
int TMP102::init()
{
    i2c_->frequency(400000); // set bus speed to 400 kHz

    int ack;  // used to store acknowledgement bit
    char config_data[2];  // array for data
    char reg = CONFIG_REG;  // register address

    /**Read current status of configuration register */

    ack = i2c_->write(TMP102_W_ADD,&reg,1);  // send the slave write address and the configuration register address
    if (ack)
    {
        return -255;
    }
       
    ack = i2c_->read(TMP102_R_ADD,config_data,2);  // read default 2 bytes from configuration register and store in array
    if (ack)
    {
        return -255;
    }

    /**Configure the register */

    /* set conversion rate to 1 Hz - CR1 and CR2 are in the second data byte */
    config_data[1] |= (1 << 6);    // set bit 6
    config_data[1] &= ~(1 << 7);    // clear bit 7

    /**Send the configured register value to the slave config register
     */ 

    /* create data packet */
    char data_packet[3] = {reg,config_data[0],config_data[1]};

    ack = i2c_->write(TMP102_W_ADD,data_packet,3);  // send the data packet to the slave write address
    if (ack)
    {
        return -255;
    }
    return 0;
}
/**Read temperature */
float TMP102::ReadTemperature()
{
    int ack=init();
    if (ack)
    {
        return -255;
    }
   
    char data[2];  // array for data
    char reg = TEMP_REG;  // temperature register address

    ack = i2c_->write(TMP102_W_ADD,&reg,1);  // send temperature register address
    if (ack)
    {
        return -255;
    }
        
    ack = i2c_->read(TMP102_R_ADD,data,2);  // read 2 bytes from temperature register and store in array
    if (ack)
    {
        return -255;
    }
    int temperature = (data[0] << 4) | (data[1] >> 4);

    return temperature*0.0625F;
}

