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
#define ENCODER_1_DAT_PIN 8
#define HEARTBEAT_LED_PIN           13
#define STATUS1_LED_PIN             12
#define STATUS2_LED_PIN             11

#define MCP_RESET_CTRL_PIN 2

/* These pins are on the MCP23017 */ /* R, C */
#define BUTTON_01_PIN     13        /* 0, 0 */
#define BUTTON_02_PIN     14        /* 0, 1 */
#define BUTTON_03_PIN     15        /* 0, 2 */
#define BUTTON_04_PIN     5         /* 0, 3 */
#define BUTTON_05_PIN     6         /* 0, 4 */
#define BUTTON_06_PIN     12        /* 1, 0 */
#define BUTTON_07_PIN     11        /* 1, 1 */
#define BUTTON_08_PIN     10        /* 1, 2 */
#define BUTTON_09_PIN     3         /* 1, 3 */
#define BUTTON_10_PIN     4         /* 1, 4 */
#define BUTTON_11_PIN     9         /* 2, 0 */
#define BUTTON_12_PIN     8         /* 2, 1 */
#define BUTTON_13_PIN     0         /* 2, 2 */
#define BUTTON_14_PIN     1         /* 2, 3 */
#define BUTTON_15_PIN     2         /* 2, 4 */

#define ENCODER_1_BUT_PIN 7



#define NUM_BUTTONS       16
#define NUM_ENCODERS      1

#define OLED_RESET           -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define OLED_SCREEN_ADDRESS  0x3C
#define OLED_SCREEN_WIDTH    128 // OLED display width, in pixels
#define OLED_SCREEN_HEIGHT   64 // OLED display height, in pixels
#define OLED_MAX_ON_TIME_MS  5000 /* How how to let OLED stay on for */

#define LED_BLINK_ON_MS      2
#define LED_BLINK_OFF_MS     50

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