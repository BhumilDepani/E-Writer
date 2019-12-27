#include "string.h"
static void GetASCIICode(unsigned char *pBuffer, unsigned char ASCII);

static char AsciiLib[1][16] = {
		{0x00,0x00,0x00,0x3c,0x66,0x66,0x66,0x66,0x3e,0x0c,0x18,0x38,0x00,0x00,0x00,0x00}
};

static void GetASCIICode(unsigned char *pBuffer, unsigned char ASCII)
{
	memcpy(pBuffer, AsciiLib[0], 16);
}
