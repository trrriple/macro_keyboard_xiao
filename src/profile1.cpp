#include "profile.h"
#include "hardware.h"



button_func_t g_buttonFuncMap1[NUM_BUTTONS] =
{
        {   /* 0, 0 */
            "Play/Pause",
            {HID_PLAY_PAUSE, 0, 0, 0, 0, 0, 0, 0, 0 ,0},
            true,
            false,
            false,
            FUNC_NOT_IN_REPORT,
            0,
        },
        {   /* 0, 1 */
            "Prev",
            {HID_SCAN_PREVIOUS, 0, 0, 0, 0, 0, 0, 0, 0 ,0},
            true,
            false,
            false,
            FUNC_NOT_IN_REPORT,
            0,
        },
        {   /* 0, 2 */
            "Next",
            {HID_SCAN_NEXT, 0, 0, 0, 0, 0, 0, 0, 0 ,0},
            true,
            false,
            false,
            FUNC_NOT_IN_REPORT,
            0,
        },
        {   /* 0, 3 */
            "Stop",
            {HID_STOP, 0, 0, 0, 0, 0, 0, 0, 0 ,0},
            true,
            false,
            false,
            FUNC_NOT_IN_REPORT,
            0,
        },
        {   /* 0, 4 */
            "N/A",
            {0, 0 , 0, 0, 0, 0, 0, 0, 0 ,0},
            false,
            false,
            false,
            FUNC_NOT_IN_REPORT,
            0,
        },
        {   /* 1, 0 */
            "Window <-",
            {HID_KEY_GUI_LEFT, HID_ARROW_LEFT, 0, 0, 0, 0, 0, 0, 0 ,0},
            true,
            false,
            false,
            FUNC_NOT_IN_REPORT,
            0,
        },
        {   /* 1, 1 */
            "Window ->",
            {HID_KEY_GUI_LEFT, HID_ARROW_RIGHT, 0, 0, 0, 0, 0, 0, 0 ,0},
            true,
            false,
            false,
            FUNC_NOT_IN_REPORT,
            0,
        },
        {   /* 1, 2 */
            "Window ^",
            {HID_KEY_GUI_LEFT, HID_ARROW_UP, 0, 0, 0, 0, 0, 0, 0 ,0},
            true,
            false,
            false,
            FUNC_NOT_IN_REPORT,
            0,
        },
        {   /* 1, 3 */
            "Window v",
            {HID_KEY_GUI_LEFT, HID_ARROW_DOWN, 0, 0, 0, 0, 0, 0, 0 ,0},
            true,
            false,
            false,
            FUNC_NOT_IN_REPORT,
            0,
        },
        {   /* 1, 4 */
            "N/A",
            {0, 0, 0, 0, 0, 0, 0, 0, 0 ,0},
            true,
            false,
            false,
            FUNC_NOT_IN_REPORT,
            0,
        },
        {   /* 2, 0 */
            "N/A",
            {0, 0, 0, 0, 0, 0, 0, 0, 0 ,0},
            true,
            false,
            false,
            FUNC_NOT_IN_REPORT,
            0,
        },
        {   /* 2, 1 */
            "N/A",
            {0, 0, 0, 0, 0, 0, 0, 0, 0 ,0},
            true,
            false,
            false,
            FUNC_NOT_IN_REPORT,
            0,
        },
        {   /* 2, 2 */
            "N/A",
            {0, 0, 0, 0, 0, 0, 0, 0, 0 ,0},
            true,
            false,
            false,
            FUNC_NOT_IN_REPORT,
            0,
        },
        {   /* 2, 3 */
            "N/A",
            {0, 0, 0, 0, 0, 0, 0, 0, 0 ,0},
            true,
            false,
            false,
            FUNC_NOT_IN_REPORT,
            0,
        },
        {   /* 2, 4 */
            "P2 Quick Swap",
            {KEY_PROFILE2_TEMP, 0, 0, 0, 0, 0, 0, 0, 0 ,0},
            false,
            false,
            false,
            FUNC_NOT_IN_REPORT,
            0,
        },
        {   /* Encoder Button */
            "N/A, Hold: Profile Chng",
            {0, 0, 0, 0, 0, 0, 0, 0, 0 ,0},
            true,
            false,
            false,
            FUNC_NOT_IN_REPORT,
            0,
        },

};

                                    /* both directions per encoder */
button_func_t g_encoderFuncMap1[NUM_ENCODERS * 2] =
{
        {
            "V+",
            {HID_VOLUME_INCREMENT, 0, 0, 0, 0, 0, 0, 0, 0 ,0},
            true,
            false, /* not implemented for encoders */
            false, /* not implemented for encoders */
            FUNC_NOT_IN_REPORT,
            0,
        },
        {
            "V-",
            {HID_VOLUME_DECREMENT, 0, 0, 0, 0, 0, 0, 0, 0 ,0},
            true,
            false,  /* not implemented for encoders */
            false, /* not implemented for encoders */
            FUNC_NOT_IN_REPORT,
            0,
        },
};

