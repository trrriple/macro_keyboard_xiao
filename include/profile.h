#ifndef PROFILE_H
#define PROFILE_H
/************************************************
 * Includes 
 * *********************************************/
#include <stdint.h>
#include <stdbool.h>
#include "hardware.h"
#include "Adafruit_TinyUSB.h" /* Brings in hid.h */



/************************************************
 * Defines 
 * *********************************************/

#define NUM_PROFILES     3
#define MAX_BUTTON_FUNCS 10
#define MAX_MSG_LEN      24

/* These keys will quick switch to the specified profile when pressed and 
   go back when released */
#define KEY_PROFILE1_TEMP 0xFFF
#define KEY_PROFILE2_TEMP 0xFFE
#define KEY_PROFILE3_TEMP 0XFFD

#define FUNC_NOT_IN_REPORT 256

#define HID_CONSUMER_CONTROL_FLAG 0xF000

#define HID_PLAY_PAUSE           (0x00CD | HID_CONSUMER_CONTROL_FLAG)
#define HID_SCAN_NEXT            (0x00B5 | HID_CONSUMER_CONTROL_FLAG)
#define HID_SCAN_PREVIOUS        (0x00B6 | HID_CONSUMER_CONTROL_FLAG)
#define HID_STOP                 (0x00B7 | HID_CONSUMER_CONTROL_FLAG)
#define HID_VOLUME               (0x00E0 | HID_CONSUMER_CONTROL_FLAG)
#define HID_MUTE                 (0x00E2 | HID_CONSUMER_CONTROL_FLAG)
#define HID_BASS                 (0x00E3 | HID_CONSUMER_CONTROL_FLAG)
#define HID_TREBLE               (0x00E4 | HID_CONSUMER_CONTROL_FLAG)
#define HID_BASS_BOOST           (0x00E5 | HID_CONSUMER_CONTROL_FLAG)
#define HID_VOLUME_INCREMENT     (0x00E9 | HID_CONSUMER_CONTROL_FLAG)
#define HID_VOLUME_DECREMENT     (0x00EA | HID_CONSUMER_CONTROL_FLAG)
#define HID_BASS_INCREMENT       (0x0152 | HID_CONSUMER_CONTROL_FLAG)
#define HID_BASS_DECREMENT       (0x0153 | HID_CONSUMER_CONTROL_FLAG)
#define HID_TREBLE_INCREMENT     (0x0154 | HID_CONSUMER_CONTROL_FLAG)
#define HID_TREBLE_DECREMENT     (0x0155 | HID_CONSUMER_CONTROL_FLAG)
#define HID_MEDIA_FASTFOWARD     (0x00B3 | HID_CONSUMER_CONTROL_FLAG)
#define HID_MEDIA_REWIND         (0x00B4 | HID_CONSUMER_CONTROL_FLAG)

/************************************************
 * Typedefs 
 * *********************************************/

typedef struct
{
    /* config variables */
    char msg[MAX_MSG_LEN];           /* OLED message when pressed */
    uint16_t func[MAX_BUTTON_FUNCS]; /* what keystrokes to send when pressed */
    bool turbo;                      /* while key is held, key will act like being spammed */
    /* state variable */
    bool funcFired;                 /* if press action has fired */
    int  inReportIdx;                 /* > NKRO_N if this function is not in report */
    int  keysInReport;                 /* How many keys this fella has in the report */

} button_func_t;


extern button_func_t g_buttonFuncMap1[NUM_BUTTONS];
extern button_func_t g_encoderFuncMap1[NUM_ENCODERS * 2];
 

extern button_func_t g_buttonFuncMap2[NUM_BUTTONS];
extern button_func_t g_encoderFuncMap2[NUM_ENCODERS * 2];
 
 
extern button_func_t g_buttonFuncMap3[NUM_BUTTONS];
extern button_func_t g_encoderFuncMap3[NUM_ENCODERS * 2];
 


#endif /*PROFILE_H */