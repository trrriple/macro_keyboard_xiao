#include "profile.h"
#include "hardware.h"



button_func_t g_buttonFuncMap2[NUM_BUTTONS] =
{
        {
            "Play/Pause",
            {'a', 'b', 'c', 'd', 'e', 0, 0, 0, 0 ,0},
            false,
            false,
            FUNC_NOT_IN_REPORT,
            0,
        },
        {
            "Prev",
            {HID_PLAY_PAUSE, 0, 0, 0, 0, 0, 0, 0, 0 ,0},
            false,
            false,
            FUNC_NOT_IN_REPORT,
            0,
        },
        {
            "Next",
            {HID_SCAN_NEXT, 0, 0, 0, 0, 0, 0, 0, 0 ,0},
            false,
            false,
            FUNC_NOT_IN_REPORT,
            0,
        },
        {
            "Stop",
            {HID_STOP, 0, 0, 0, 0, 0, 0, 0, 0 ,0},
            false,
            false,
            FUNC_NOT_IN_REPORT,
            0,
        },
        {
            "N/A",
            {0, 0, 0, 0, 0, 0, 0, 0, 0 ,0},
            false,
            false,
            FUNC_NOT_IN_REPORT,
            0,
        },
        {
            "N/A",
            {0, 0, 0, 0, 0, 0, 0, 0, 0 ,0},
            false,
            false,
            FUNC_NOT_IN_REPORT,
            0,
        },
        {
            "N/A",
            {0, 0, 0, 0, 0, 0, 0, 0, 0 ,0},
            false,
            false,
            FUNC_NOT_IN_REPORT,
            0,
        },
        {
            "N/A",
            {0, 0, 0, 0, 0, 0, 0, 0, 0 ,0},
            false,
            false,
            FUNC_NOT_IN_REPORT,
            0,
        },
        {
            "N/A",
            {0, 0, 0, 0, 0, 0, 0, 0, 0 ,0},
            false,
            false,
            FUNC_NOT_IN_REPORT,
            0,
        },
        {
            "N/A",
            {0, 0, 0, 0, 0, 0, 0, 0, 0 ,0},
            false,
            false,
            FUNC_NOT_IN_REPORT,
            0,
        },
        {
            "N/A",
            {0, 0, 0, 0, 0, 0, 0, 0, 0 ,0},
            false,
            false,
            FUNC_NOT_IN_REPORT,
            0,
        },
        {
            "N/A",
            {0, 0, 0, 0, 0, 0, 0, 0, 0 ,0},
            false,
            false,
            FUNC_NOT_IN_REPORT,
            0,
        },
        {
            "N/A",
            {0, 0, 0, 0, 0, 0, 0, 0, 0 ,0},
            false,
            false,
            FUNC_NOT_IN_REPORT,
            0,
        },
        {
            "N/A",
            {0, 0, 0, 0, 0, 0, 0, 0, 0 ,0},
            false,
            false,
            FUNC_NOT_IN_REPORT,
            0,
        },
        {
            "N/A",
            {0, 0, 0, 0, 0, 0, 0, 0, 0 ,0},
            false,
            false,
            FUNC_NOT_IN_REPORT,
            0,
        },
        {
            "N/A",
            {0, 0, 0, 0, 0, 0, 0, 0, 0 ,0},
            false,
            false,
            FUNC_NOT_IN_REPORT,
            0,
        },

};

                                    /* both directions per encoder */
button_func_t g_encoderFuncMap2[NUM_ENCODERS * 2] =
{
        {
            "V+",
            {HID_VOLUME_INCREMENT, 0, 0, 0, 0, 0, 0, 0, 0 ,0},
            false, /* not implemented for encoders */
            false, /* not implemented for encoders */
            FUNC_NOT_IN_REPORT,
            0,
        },
        {
            "V-",
            {HID_VOLUME_DECREMENT, 0, 0, 0, 0, 0, 0, 0, 0 ,0},
            false,  /* not implemented for encoders */
            false, /* not implemented for encoders */
            FUNC_NOT_IN_REPORT,
            0,
        },
};

