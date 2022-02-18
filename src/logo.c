// Filename: logo128x64.png
// Filesize: 3927 Bytes

// Size bitmap: 1024 bytes

#include <avr/pgmspace.h> 
#include <stdint.h>

#define LOGO_WIDTH 128
#define LOGO_HEIGHT 64

// 'image', 128x64px
const unsigned char logo [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x03, 0xff, 0xe0, 0x00, 0x3f, 0xff, 0x00, 0x00, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x01, 0xff, 0xff, 0x00, 0x0f, 0xff, 0xf8, 0x00, 0x7f, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0xfe, 0x1f, 0xc0, 0x0f, 0xe1, 0xfe, 0x00, 0x7f, 0x8f, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0xfe, 0x0f, 0xf0, 0x0f, 0xe0, 0x7f, 0x00, 0x3f, 0x03, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0xfc, 0x07, 0xf8, 0x07, 0xe0, 0x7f, 0x80, 0x3f, 0x01, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0xfc, 0x03, 0xf8, 0x07, 0xe0, 0x3f, 0xc0, 0x3f, 0x00, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0xfc, 0x03, 0xfc, 0x07, 0xc0, 0x3f, 0xc0, 0x3f, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0xfc, 0x03, 0xfc, 0x07, 0xc0, 0x1f, 0xe0, 0x3f, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0xfc, 0x03, 0xfc, 0x07, 0xc0, 0x1f, 0xc0, 0x3e, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0xf8, 0x03, 0xfc, 0x07, 0xc0, 0x1f, 0xc0, 0x3e, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0xf8, 0x03, 0xf8, 0x07, 0xc0, 0x1f, 0xc0, 0x3e, 0x00, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0xf8, 0x03, 0xf8, 0x07, 0xc0, 0x3f, 0x80, 0x3e, 0x00, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0xf8, 0x03, 0xf0, 0x0f, 0xc0, 0x3f, 0x00, 0x3e, 0x00, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0xf8, 0x07, 0xe0, 0x0f, 0x80, 0x3e, 0x00, 0x3e, 0x01, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0xf8, 0x0f, 0x80, 0x0f, 0x80, 0x7c, 0x00, 0x3e, 0x03, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0xf8, 0x1f, 0x00, 0x0f, 0x80, 0xf0, 0x00, 0x3e, 0x07, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0xf8, 0x7e, 0x00, 0x0f, 0x87, 0xf0, 0x00, 0x3e, 0x1f, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0xf9, 0xff, 0x00, 0x0f, 0x8f, 0xf0, 0x00, 0x3e, 0x7f, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0xf8, 0xff, 0x00, 0x0f, 0x8f, 0xf8, 0x00, 0x7e, 0x3f, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x01, 0xf8, 0x7f, 0x80, 0x0f, 0x87, 0xf8, 0x00, 0x7c, 0x3f, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x01, 0xf8, 0x7f, 0xc0, 0x0f, 0x83, 0xfc, 0x00, 0x7c, 0x1f, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x01, 0xf8, 0x3f, 0xe0, 0x0f, 0x81, 0xfe, 0x00, 0x7e, 0x0f, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x01, 0xf8, 0x1f, 0xe0, 0x0f, 0x80, 0xff, 0x00, 0x7e, 0x07, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x01, 0xf8, 0x0f, 0xf0, 0x0f, 0x80, 0x7f, 0x80, 0x7e, 0x03, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x01, 0xf8, 0x07, 0xf8, 0x1f, 0x80, 0x3f, 0xc0, 0x7e, 0x01, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x01, 0xf8, 0x03, 0xfc, 0x1f, 0x80, 0x1f, 0xe0, 0x7e, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x01, 0xf8, 0x01, 0xfe, 0x1f, 0xc0, 0x0f, 0xf0, 0xfe, 0x00, 0x7f, 0x80, 0x00, 0x00, 0x00, 0x00, 
	0x03, 0xf8, 0x00, 0xff, 0x1f, 0xc0, 0x07, 0xf8, 0xfe, 0x00, 0x3f, 0xc0, 0x00, 0x00, 0x00, 0x00, 
	0x03, 0xf8, 0x00, 0x7f, 0x9f, 0xc0, 0x03, 0xf8, 0xfe, 0x00, 0x1f, 0xe0, 0x00, 0x00, 0x00, 0x00, 
	0x03, 0xfc, 0x00, 0x3f, 0xff, 0xc0, 0x01, 0xfc, 0xff, 0x00, 0x0f, 0xf0, 0x00, 0x00, 0x00, 0x00, 
	0x07, 0xfe, 0x00, 0x1f, 0xff, 0xe0, 0x00, 0xff, 0xff, 0x00, 0x07, 0xf8, 0x00, 0x00, 0x00, 0x00, 
	0x07, 0xfe, 0x00, 0x0f, 0xff, 0xf0, 0x00, 0xff, 0xff, 0x80, 0x07, 0xfc, 0x00, 0x00, 0x00, 0x00, 
	0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x00, 
	0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 
	0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x7f, 0x00, 0x00, 0x07, 0xf8, 0x00, 0x00, 0x1f, 0xc0, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x3f, 0x80, 0x00, 0x01, 0xfc, 0x00, 0x00, 0x0f, 0xe0, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x1f, 0xc0, 0x00, 0x00, 0xfe, 0x00, 0x00, 0x07, 0xf0, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x07, 0xf0, 0x00, 0x00, 0x7f, 0x00, 0x00, 0x01, 0xfc, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x03, 0xf8, 0x00, 0x00, 0x1f, 0xc0, 0x00, 0x00, 0xfe, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0x00, 0x00, 0x07, 0xe0, 0x00, 0x00, 0x3f, 0x80, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x80, 0x00, 0x03, 0xf8, 0x00, 0x00, 0x0f, 0xe0, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xe0, 0x00, 0x00, 0x7e, 0x00, 0x00, 0x03, 0xf0, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xf8, 0x00, 0x00, 0x1f, 0xc0, 0x00, 0x00, 0x7e, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xf8, 0x00, 0x03, 0xff, 0x80, 0x00, 0x0f, 0xfe, 0x00, 
	0x00, 0x00, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 
	0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 
	0x00, 0x00, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
