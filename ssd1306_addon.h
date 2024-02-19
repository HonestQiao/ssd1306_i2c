#ifndef SSD1306_ADDON_H_
#define SSD1306_ADDON_H_

#include <stdio.h>
#include "ssd1306_i2c.h"

void ssd1306_setCursor(uint8_t x, uint8_t y);
void ssd1306_drawRegion(uint8_t x, uint8_t y, uint8_t w, uint8_t h, const uint8_t *data, uint32_t size, uint32_t stride);
void ssd1306_drawChinese(uint8_t x, uint8_t y, char *str);

#endif