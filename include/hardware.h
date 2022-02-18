#ifndef HARDWARE_H
#define HARDWARE_H
/************************************************
 * Includes 
 * *********************************************/
#include <Arduino.h>
#include <stdint.h>

/************************************************
 * Defines 
 * *********************************************/
/* These pins are on the xiao */
#define ENCODER_1_CLK_PIN 9
#define ENCODER_1_DAT_PIN 10

#define MCP_RESET_CTRL_PIN 2

/* These pins are on the MCP23017 */
#define BUTTON_01_PIN     0
#define BUTTON_02_PIN     1
#define BUTTON_03_PIN     2
#define BUTTON_04_PIN     3
#define BUTTON_05_PIN     4
#define BUTTON_06_PIN     5
#define BUTTON_07_PIN     6
#define BUTTON_08_PIN     7
#define BUTTON_09_PIN     8
#define BUTTON_10_PIN     9
#define BUTTON_11_PIN     10
#define BUTTON_12_PIN     11
#define BUTTON_13_PIN     12
#define BUTTON_14_PIN     13
#define BUTTON_15_PIN     14

#define ENCODER_1_BUT_PIN 15



#define NUM_BUTTONS       16
#define NUM_ENCODERS      1

#define OLED_RESET           -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define OLED_SCREEN_ADDRESS  0x3C
#define OLED_SCREEN_WIDTH    128 // OLED display width, in pixels
#define OLED_SCREEN_HEIGHT   64 // OLED display height, in pixels

/************************************************
 * Typedefs 
 * *********************************************/

typedef struct
{
    int button;            /* what pin is this button on */
    int actState;          /* active HIGH or LOW */
    uint32_t tDebounce_ms; /* time required to change state once pressed */
    uint32_t tPressed_ms;  /* time button was last pressed */
    uint32_t tReleased_ms; /* time button was last released */
    int prevState;         /* state of the button when it was last checked */

} button_hw_t;

/************************************************
 * External variables
 * *********************************************/
extern button_hw_t G_BUTTON_HW_MAP[NUM_BUTTONS];

#endif /* HARDWARE_H */