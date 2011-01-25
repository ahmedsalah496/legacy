#include <stdint.h>
#include <assert.h>

#include "../compat/pgmspace.h"
#include "bitmapscroller.h"
#include "amphibian.h"


static uint8_t amphibian_getChunk(unsigned char const nBitPlane,
                                  unsigned char const nChunkX,
                                  unsigned char const nChunkY,
                                  unsigned int const nFrame)
{
	assert(nChunkX < 6);
	assert(nChunkY < 38);

	static uint8_t aBitmap [2][38][6] PROGMEM =
		{{{0x00, 0x00, 0x24, 0x00, 0x00, 0x00}, // bit plane 0
		  {0x00, 0x20, 0x3C, 0x00, 0x00, 0x00},
		  {0x07, 0x30, 0x47, 0x00, 0x00, 0x00},
		  {0x03, 0x00, 0xC3, 0x00, 0x00, 0x00},
		  {0x04, 0xD9, 0xA7, 0x00, 0x00, 0x00},
		  {0x02, 0xEB, 0x7C, 0x00, 0x00, 0x00},
		  {0x03, 0x3F, 0xBA, 0x00, 0x00, 0x00},
		  {0x00, 0xFF, 0xEF, 0x00, 0x00, 0x00},
		  {0x01, 0xFC, 0x3C, 0x80, 0x00, 0x00},
		  {0x02, 0xFC, 0x00, 0x00, 0x00, 0x00},
		  {0x01, 0xFC, 0x03, 0x00, 0x00, 0x00},
		  {0x05, 0xF8, 0x01, 0x40, 0x00, 0x00},
		  {0x00, 0x70, 0x01, 0x80, 0x00, 0x00},
		  {0x00, 0x00, 0x01, 0xE0, 0x00, 0x00},
		  {0x00, 0x00, 0x00, 0x80, 0x00, 0x00},
		  {0x00, 0x00, 0x00, 0x18, 0x00, 0x00},
		  {0x10, 0x7F, 0xC0, 0x18, 0x80, 0x00},
		  {0x03, 0xFF, 0xFC, 0x38, 0x00, 0x00},
		  {0x03, 0xFF, 0xFC, 0x3E, 0x00, 0x20},
		  {0x00, 0xFF, 0xFC, 0x7F, 0x00, 0xFC},
		  {0x00, 0xFF, 0xFC, 0xDE, 0x93, 0xFE},
		  {0x00, 0x7F, 0xFE, 0x8E, 0x57, 0xFF},
		  {0x22, 0xFF, 0xFD, 0x86, 0x0F, 0xFF},
		  {0x00, 0xFF, 0xFA, 0xC2, 0x7F, 0xFE},
		  {0x00, 0x5F, 0xF5, 0xC0, 0x7F, 0xFC},
		  {0x20, 0x78, 0x4B, 0xC8, 0x3F, 0xF8},
		  {0x00, 0xF0, 0x2F, 0xDC, 0x3F, 0xF0},
		  {0x10, 0xFF, 0xDF, 0x8E, 0x1F, 0xE0},
		  {0x08, 0xFF, 0xEF, 0x9E, 0x17, 0xC0},
		  {0x28, 0xFF, 0xFF, 0x83, 0x87, 0x00},
		  {0x80, 0xFF, 0xFF, 0x81, 0x87, 0xF0},
		  {0x70, 0x7F, 0xFF, 0x80, 0x1F, 0x8C},
		  {0x08, 0x1C, 0x1F, 0x01, 0xCF, 0x84},
		  {0x02, 0x54, 0x00, 0x02, 0x10, 0xC0},
		  {0x03, 0x40, 0x04, 0x08, 0x00, 0x30},
		  {0x00, 0x00, 0x1E, 0x40, 0x00, 0x08},
		  {0x02, 0x08, 0x16, 0x00, 0x00, 0x00},
		  {0x00, 0x00, 0x4C, 0x00, 0x00, 0x00}},

		 {{0x00, 0x00, 0x18, 0x00, 0x00, 0x00}, // bit plane 1
		  {0x01, 0xC0, 0x7E, 0x00, 0x00, 0x00},
		  {0x03, 0xE0, 0xFE, 0x00, 0x00, 0x00},
		  {0x06, 0x30, 0x82, 0x00, 0x00, 0x00},
		  {0x06, 0x10, 0xDA, 0x00, 0x00, 0x00},
		  {0x07, 0xF0, 0xFE, 0x00, 0x00, 0x00},
		  {0x07, 0xC0, 0x7C, 0x00, 0x00, 0x00},
		  {0x03, 0x00, 0x10, 0x00, 0x00, 0x00},
		  {0x00, 0x03, 0xC3, 0x00, 0x00, 0x00},
		  {0x01, 0x03, 0xFF, 0x80, 0x00, 0x00},
		  {0x02, 0x03, 0xFC, 0x80, 0x00, 0x00},
		  {0x02, 0x07, 0xFE, 0x80, 0x00, 0x00},
		  {0x07, 0x8F, 0xFE, 0x40, 0x00, 0x00},
		  {0x0F, 0xFF, 0xFE, 0x00, 0x00, 0x00},
		  {0x1F, 0xFF, 0xFF, 0x60, 0x00, 0x00},
		  {0x3F, 0xFF, 0xFF, 0xE0, 0x00, 0x00},
		  {0x0F, 0xFF, 0xFF, 0xE7, 0x00, 0x00},
		  {0x03, 0xFF, 0xFF, 0xC7, 0x80, 0x00},
		  {0x01, 0xFF, 0xFF, 0xC1, 0xC0, 0x00},
		  {0x01, 0xFF, 0xFF, 0x80, 0xE0, 0x00},
		  {0x00, 0xFF, 0xFF, 0x21, 0x60, 0x00},
		  {0x00, 0xFF, 0xFF, 0x71, 0xA0, 0x00},
		  {0x1C, 0x7F, 0xFE, 0xF9, 0xF0, 0x00},
		  {0x3F, 0x7F, 0xFD, 0xFD, 0x80, 0x00},
		  {0x3F, 0xBF, 0xFA, 0xFF, 0x80, 0x00},
		  {0x1F, 0xC7, 0xB7, 0xF7, 0xC0, 0x00},
		  {0x1F, 0xFF, 0xFF, 0xE3, 0xC0, 0x00},
		  {0x0F, 0xFF, 0xEF, 0xF1, 0xE0, 0x00},
		  {0x07, 0xFF, 0xFF, 0xE1, 0xE8, 0x00},
		  {0x17, 0xFF, 0xFF, 0xFC, 0x78, 0x00},
		  {0x7F, 0xFF, 0xFF, 0xFE, 0x78, 0x00},
		  {0x0F, 0xFF, 0xFF, 0xFF, 0xE0, 0x00},
		  {0x07, 0xFF, 0xFF, 0xFE, 0x00, 0x00},
		  {0x01, 0x88, 0x1F, 0xFC, 0x00, 0x00},
		  {0x00, 0x20, 0x03, 0xF0, 0x00, 0x00},
		  {0x02, 0x18, 0x01, 0x80, 0x00, 0x00},
		  {0x00, 0x00, 0x60, 0x00, 0x00, 0x00},
		  {0x00, 0x00, 0x80, 0x00, 0x00, 0x00}}};

	static uint8_t aEye[2][16][3] PROGMEM =
		{{{0x07, 0xF0, 0x67},    // frame 1 (bit plane 0)
		  {0x03, 0xC0, 0xC3},
		  {0x04, 0x19, 0xA7},
		  {0x03, 0xEB, 0x7C},
		  {0x07, 0xF0, 0x5F},    // frame 2
		  {0x03, 0xE0, 0xC3},
		  {0x04, 0x19, 0xA7},
		  {0x03, 0xEB, 0x7C},
		  {0x07, 0xF0, 0x27},    // frame 3
		  {0x00, 0x00, 0xC3},
		  {0x07, 0xD9, 0xDF},
		  {0x03, 0xEB, 0x7C},
		  {0x07, 0xF0, 0x27},    // frame 4
		  {0x00, 0xC0, 0xC3},
		  {0x07, 0x19, 0xE7},
		  {0x03, 0x2B, 0x7C}},

		 {{0x03, 0xE0, 0xC6},    // frame 1 (bit plane 1)
		  {0x06, 0x30, 0x82},
		  {0x06, 0x10, 0xDA},
		  {0x07, 0xF0, 0xFE},
		  {0x03, 0xE0, 0xE6},    // frame 2
		  {0x07, 0xF0, 0x82},
		  {0x06, 0x10, 0xDA},
		  {0x07, 0xF0, 0xFE},
		  {0x03, 0xE0, 0xDA},    // frame 3
		  {0x06, 0x10, 0x82},
		  {0x06, 0x30, 0xE6},
		  {0x07, 0xF0, 0xFE},
		  {0x03, 0xE0, 0xDA},    // frame 4
		  {0x06, 0x10, 0x82},
		  {0x06, 0x30, 0xC6},
		  {0x07, 0xF0, 0xFE}}};


	if ((nChunkX <= 2) && (nChunkY >= 2) && (nChunkY <= 5)
			&& (((nFrame >> 1) % 8) != 0))
	{
		uint8_t nOffset;
		switch ((nFrame >> 1) % 8)
		{
		case 1:
		case 7:
			nOffset = 0;
			break;
		case 2:
		case 6:
			nOffset = 4;
			break;
		case 3:
		case 5:
			nOffset = 8;
			break;
		case 4:
		default:
			nOffset = 12;
			break;
		}

		return pgm_read_byte(&aEye[nBitPlane][nChunkY-2+nOffset][nChunkX]);
	}
	else
	{
		return pgm_read_byte(&aBitmap[nBitPlane][nChunkY][nChunkX]);
	}
}


void amphibian()
{
	bitmap_scroll(48, 38, 2, 400, 75, amphibian_getChunk);
}
