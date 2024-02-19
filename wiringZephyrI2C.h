#ifndef SSD1306_WIRING_PI_I2C_H_
#define SSD1306_WIRING_PI_I2C_H_

int wiringPiI2CSetup(unsigned int i2caddr) {
    return 1;
}
void wiringPiI2CWriteReg8(int i2cd, unsigned int control, unsigned int c) {
    return;
}
#endif				/* SSD1306_WIRING_PI_I2C_H_ */