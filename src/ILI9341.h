#ifndef ILI9341
#define ILI9341
#include "stm32f4xx.h"

//#define TFT_data_out_port_low                                                            PORTC
//#define TFT_data_out_port_high                                                           PORTA
#define Sixteen_Port                     GPIOB
#define Signal_Port                      GPIOD
//#define TFT_data_in_port_low                                                             PINC
//#define TFT_data_in_port_high                                                            PINA

//#define TFT_port_config_low                                                              DDRC
//#define TFT_port_config_high                                                             DDRA

#define TFT_RS_Pin                        GPIO_Pin_0   //This pin is connected to RS pin of LCD
#define TFT_WR_Pin                        GPIO_Pin_1   //This pin is connected to CS pin of LCD
#define TFT_RD_Pin                        GPIO_Pin_2   //This pin is connected to WR pin of LCD
#define TFT_CS_Pin                        GPIO_Pin_3   //This pin is connected to RD pin of LCD
#define TFT_RST_Pin						  GPIO_Pin_4   //This pin is connected to REST pin of LCD

//TFT_RD_pin pull up 3.3V

//#define TFT_RST_pin_dir                                                                  DDG0_bit
//#define TFT_CS_pin_dir                                                                   DDG1_bit
//#define TFT_WR_pin_dir                                                                   DDG2_bit
//#define TFT_RS_pin_dir                                                                   DDD7_bit

#define White                                                   0xFFFF
#define Black                                                   0x0000
#define Grey                                                    0xF7DE
#define Grey2                                                   0x8430
#define Light_Grey                                              0xC618
#define Dark_Grey                                               0x8410
#define Purple                                                  0xF81F
#define Grey_Blue                                               0x5458
#define Blue                                                    0x001F
#define Dark_Blue                                               0x01CF
#define Light_Blue                                              0x051F
#define Light_Blue_2                                            0x7D7C
#define Red                                                     0xF800
#define Green                                                   0x07E0
#define Cyan                                                    0x7FFF
#define Yellow                                                  0xFFE0
#define Orange                                                  0xFC08
#define Magenta                                                 0xF81F

#define TRUE           											1
#define FALSE                                                   0

#define YES                                                     1
#define NO                                                      0

#define ON                                                      1
#define OFF                                                     0

#define HIGH                                                    1
#define LOW                                                     0

#define DAT                                                     1
#define CMD                                                     0

#define SQUARE                                                  0
#define ROUND                                                   1

#define ILI9341_NOP                                             0x0000
#define ILI9341_RESET                                           0x0001
#define ILI9341_READ_DISPLAY_IDENTIFICATION_INFORMATION         0x0004
#define ILI9341_READ_DISPLAY_STATUS                             0x0009
#define ILI9341_READ_DISPLAY_POWER_MODE                         0x000A
#define ILI9341_READ_DISPLAY_MADCTL                             0x000B
#define ILI9341_READ_DISPLAY_PIXEL_FORMAT                       0x000C
#define ILI9341_READ_DISPLAY_IMAGE_FORMAT                       0x000D
#define ILI9341_READ_DISPLAY_SIGNAL_MODE                        0x000E
#define ILI9341_READ_DISPLAY_SELF_DIAGNOSTIC_RESULT             0x000F
#define ILI9341_ENTER_SLEEP_MODE                                0x0010
#define ILI9341_SLEEP_OUT                                       0x0011
#define ILI9341_PARTIAL_MODE_ON                                 0x0012
#define ILI9341_NORMAL_DISPLAY_MODE_ON                          0x0013
#define ILI9341_DISPLAY_INVERSION_OFF                           0x0020
#define ILI9341_DISPLAY_INVERSION_ON                            0x0021
#define ILI9341_GAMMA                                           0x0026
#define ILI9341_DISPLAY_OFF                                     0x0028
#define ILI9341_DISPLAY_ON                                      0x0029
#define ILI9341_COLUMN_ADDR                                     0x002A
#define ILI9341_PAGE_ADDR                                       0x002B
#define ILI9341_GRAM                                            0x002C
#define ILI9341_COLOR_SET                                       0x002D
#define ILI9341_MEMORY_READ                                     0x002E
#define ILI9341_PARTIAL_AREA                                    0x0030
#define ILI9341_VERTICAL_SCROLLING_DEFINITION                   0x0033
#define ILI9341_TEARING_EFFECT_LINE_OFF                         0x0034
#define ILI9341_TEARING_EFFECT_LINE_ON                          0x0035
#define ILI9341_MAC                                             0x0036
#define ILI9341_VERTICAL_SCROLLING_START_ADDRESS                0x0037
#define ILI9341_IDLE_MODE_OFF                                   0x0038
#define ILI9341_IDLE_MODE_ON                                    0x0039
#define ILI9341_PIXEL_FORMAT                                    0x003A
#define ILI9341_WMC                                             0x003C
#define ILI9341_RMC                                             0x003E
#define ILI9341_SET_TEAR_SCANLINE                               0x0044
#define ILI9341_WDB                                             0x0051
#define ILI9341_READ_DISPLAY_BRIGHTNESS                         0x0052
#define ILI9341_WCD                                             0x0053
#define ILI9341_READ_CTRL_DISPLAY                               0x0054
#define ILI9341_WCABC                                           0x0055
#define ILI9341_RCABC                                           0x0056
#define ILI9341_WCABCMB                                         0x005E
#define ILI9341_RCABCMB                                         0x005F
#define ILI9341_RGB_INTERFACE                                   0x00B0
#define ILI9341_FRC                                             0x00B1//problem
#define ILI9341_FRAME_CTRL_NM                                   0x00B2//problem
#define ILI9341_FRAME_CTRL_IM                                   0x00B3//problem
#define ILI9341_FRAME_CTRL_PM                                   0x00B4//problem
#define ILI9341_BPC                                             0x00B5
#define ILI9341_DFC                                             0x00B6
#define ILI9341_ENTRY_MODE_SET                                  0x00B7
#define ILI9341_BACKLIGHT_CONTROL_1                             0x00B8
#define ILI9341_BACKLIGHT_CONTROL_2                             0x00B9
#define ILI9341_BACKLIGHT_CONTROL_3                             0x00BA
#define ILI9341_BACKLIGHT_CONTROL_4                             0x00BB
#define ILI9341_BACKLIGHT_CONTROL_5                             0x00BC
#define ILI9341_BACKLIGHT_CONTROL_6                             0x00BD
#define ILI9341_BACKLIGHT_CONTROL_7                             0x00BE
#define ILI9341_BACKLIGHT_CONTROL_8                             0x00BF
#define ILI9341_POWER1                                          0x00C0
#define ILI9341_POWER2                                          0x00C1
#define ILI9341_VCOM1                                           0x00C5
#define ILI9341_VCOM2                                           0x00C7
#define ILI9341_POWERA                                          0x00CB
#define ILI9341_POWERB                                          0x00CF
#define ILI9341_READ_ID1                                        0x00DA
#define ILI9341_READ_ID2                                        0x00DB
#define ILI9341_READ_ID3                                        0x00DC
#define ILI9341_PGAMMA                                          0x00E0
#define ILI9341_NGAMMA                                          0x00E1
#define ILI9341_DTCA                                            0x00E8
#define ILI9341_DTCB                                            0x00EA
#define ILI9341_POWER_SEQ                                       0x00ED
#define ILI9341_3GAMMA_EN                                       0x00F2
#define ILI9341_INTERFACE                                       0x00F6
#define ILI9341_PRC                                             0x00F7

#define PORTRAIT_1                                              1
#define PORTRAIT_2                                              2
#define LANDSCAPE_1                                             3
#define LANDSCAPE_2                                             4

#define X_MAX                                                   240
#define Y_MAX                                                   320

#define pixels                                                  (X_MAX * Y_MAX)

//unsigned int X_MAX = X_MAX;
//unsigned int MAX_Y = Y_MAX;


void TFT_init();                                                //To initialize LCD
void TFT_GPIO_init();											//To initialize GPIO pins as input or output
void TFT_reset();												//To reset the LCD
void TFT_write_bus(uint16_t value);							//To write in Output Data Register
void TFT_write(uint16_t value, uint8_t mode);			// To select whether it is data of command
void TFT_write_REG_DATA(uint16_t reg, uint16_t data_value);
//void TFT_on_off(unsigned char mode);
void TFT_set_rotation(unsigned char value);
void TFT_set_display_window(uint16_t x_pos1, uint16_t y_pos1, uint16_t x_pos2, uint16_t y_pos2);
void TFT_fill(uint16_t colour);
void TFT_fill_area(signed int x1, signed int y1, signed int x2, signed int y2, unsigned int colour);
unsigned int TFT_BGR2RGB(unsigned int colour);
unsigned int RGB565_converter(unsigned char r, unsigned char g, unsigned char b);
void swap(signed int *a, signed int *b);
void Draw_Pixel(unsigned int x_pos, unsigned int y_pos, unsigned int colour);
void Draw_Point(unsigned int x_pos, unsigned int y_pos, unsigned char pen_width, unsigned int colour);
void Draw_Line(signed int x1, signed int y1, signed int x2, signed int y2, unsigned int colour);
void Draw_V_Line(signed int x1, signed int y1, signed int y2, unsigned colour);
void Draw_H_Line(signed int x1, signed int x2, signed int y1, unsigned colour);
void Draw_Triangle(signed int x1, signed int y1, signed int x2, signed int y2, signed int x3, signed int y3, unsigned char fill, unsigned int colour);
void Draw_Rectangle(signed int x1, signed int y1, signed int x2, signed int y2, unsigned char fill, unsigned char type, unsigned int colour, unsigned int back_colour);
void Draw_H_Bar(signed int x1, signed int x2, signed int y1, signed int bar_width, signed int bar_value, unsigned int border_colour, unsigned int bar_colour, unsigned int back_colour, unsigned char border);
void Draw_V_Bar(signed int x1, signed int y1, signed int y2, signed int bar_width, signed int bar_value, unsigned int border_colour, unsigned int bar_colour, unsigned int back_colour, unsigned char border);
void Draw_Circle(signed int xc, signed int yc, signed int radius, unsigned char fill, unsigned int colour);
void Draw_Font_Pixel(unsigned int x_pos, unsigned int y_pos, unsigned int colour, unsigned char pixel_size);
void print_char(unsigned int x_pos, unsigned int y_pos, unsigned char font_size, unsigned int colour, unsigned int back_colour, unsigned char ch);
void print_str(unsigned int x_pos, unsigned int y_pos, unsigned char font_size, unsigned int colour, unsigned int back_colour, unsigned char *ch);
void print_C(unsigned int x_pos, unsigned int y_pos, unsigned char font_size, unsigned int colour, unsigned int back_colour, signed int value);
void print_I(unsigned int x_pos, unsigned int y_pos, unsigned char font_size, unsigned int colour, unsigned int back_colour, signed int value);
void print_D(unsigned int x_pos, unsigned int y_pos, unsigned char font_size, unsigned int colour, unsigned int back_colour, unsigned int value, unsigned char points);
void print_F(unsigned int x_pos, unsigned int y_pos, unsigned char font_size, unsigned int colour, unsigned int back_colour, float value, unsigned char points);
void Draw_BMP(signed int x_pos1, signed int y_pos1, signed int x_pos2, signed int y_pos2, const unsigned int *bitmap);

#endif
