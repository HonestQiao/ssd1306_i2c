#include <stdio.h>
#include <string.h>

#include "ssd1306_i2c.h"
#include "oled_fonts_cn.h"

extern int cursor_y;
extern int cursor_x;

void ssd1306_setCursor(uint8_t x, uint8_t y)
{
	cursor_x = x;
	cursor_y = y;
}

void ssd1306_drawRegion(uint8_t x, uint8_t y, uint8_t w, uint8_t h, const uint8_t *data, uint32_t size, uint32_t stride)
{
	if (x + w > SSD1306_LCDWIDTH || y + h > SSD1306_LCDHEIGHT || w * h == 0)
	{
		fprintf(stderr, "%dx%d @ %d,%d out of range or invalid!\r\n", w, h, x, y);
		return;
	}

	w = (w <= SSD1306_LCDWIDTH ? w : SSD1306_LCDWIDTH);
	h = (h <= SSD1306_LCDHEIGHT ? h : SSD1306_LCDHEIGHT);
	stride = (stride == 0 ? w : stride);

	uint8_t rows = size * 8 / stride;
	for (uint8_t i = 0; i < rows; i++)
	{
		uint32_t base = i * stride / 8;
		for (uint8_t j = 0; j < w; j++)
		{
			uint32_t idx = base + (j / 8);
			uint8_t byte = idx < size ? data[idx] : 0;
			uint8_t bit = byte & (0x80 >> (j % 8));
			ssd1306_drawPixel(x + j, y + i, bit ? WHITE : BLACK);
		}
	}
}

void ssd1306_drawChinese(uint8_t x, uint8_t y, char *str)
{
	const uint32_t W = 16, H = 16, S = 16;

	for (uint32_t i = 0, end=strlen(str); i < end; i += FONT_CN_CHAR_WIDTH)
	{
		for (uint32_t n = 0; n < FONT_CN_CHAR_NUM; n++)
		{
			if (strncmp(str+i, font_cn_chars+n*FONT_CN_CHAR_WIDTH, FONT_CN_CHAR_WIDTH)==0)
			{
				// 字符匹配成功，获取字体数据
				ssd1306_drawRegion(x + i / FONT_CN_CHAR_WIDTH * W, y, W, H, font_cn_16x16 + n * FONT_CN_CHAR_BIT_NUM, FONT_CN_CHAR_BIT_NUM, S);
				break;
			}
		}
	}
}