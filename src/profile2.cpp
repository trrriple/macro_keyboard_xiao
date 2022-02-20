#include "profile.h"
#include "hardware.h"



button_func_t g_buttonFuncMap2[NUM_BUTTONS] =
{
        {   /* 0, 0 */
            "N/A",
            {0, 0, 0, 0, 0, 0, 0, 0, 0 ,0},
            true,
            false,
            false,
            FUNC_NOT_IN_REPORT,
            0,
        },
        {   /* 0, 1 */
            "N/A",
            {0, 0, 0, 0, 0, 0, 0, 0, 0 ,0},
            true,
            false,
            false,
            FUNC_NOT_IN_REPORT,
            0,
        },
        {   /* 0, 2 */
            "N/A",
            {0, 0, 0, 0, 0, 0, 0, 0, 0 ,0},
            true,
            false,
            false,
            FUNC_NOT_IN_REPORT,
            0,
        },
        {   /* 0, 3 */
            "N/A",
            {0, 0, 0, 0, 0, 0, 0, 0, 0 ,0},
            true,
            false,
            false,
            FUNC_NOT_IN_REPORT,
            0,
        },
        {   /* 0, 4 */
            "N/A",
            {0, 0, 0, 0, 0, 0, 0, 0, 0 ,0},
            true,
            false,
            false,
            FUNC_NOT_IN_REPORT,
            0,
        },
        {   /* 1, 0 */
            "N/A",
            {0, 0, 0, 0, 0, 0, 0, 0, 0 ,0},
            true,
            false,
            false,
            FUNC_NOT_IN_REPORT,
            0,
        },
        {   /* 1, 1 */
            "N/A",
            {0, 0, 0, 0, 0, 0, 0, 0, 0 ,0},
            true,
            false,
            false,
            FUNC_NOT_IN_REPORT,
            0,
        },
        {   /* 1, 2 */
            "N/A",
            {0, 0, 0, 0, 0, 0, 0, 0, 0 ,0},
            true,
            false,
            false,
            FUNC_NOT_IN_REPORT,
            0,
        },
        {   /* 1, 3 */
            "N/A",
            {0, 0, 0, 0, 0, 0, 0, 0, 0 ,0},
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
            "P1 Quick Swap",
            {KEY_PROFILE1_TEMP, 0, 0, 0, 0, 0, 0, 0, 0 ,0},
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
button_func_t g_encoderFuncMap2[NUM_ENCODERS * 2] =
{
        {
            "Redo",
            {HID_KEY_CONTROL_LEFT, HID_KEY_Y, 0, 0, 0, 0, 0, 0, 0 ,0},
            true,
            false, /* not implemented for encoders */
            false, /* not implemented for encoders */
            FUNC_NOT_IN_REPORT,
            0,
        },
        {
            "Undo",
            {HID_KEY_CONTROL_LEFT, HID_KEY_Z, 0, 0, 0, 0, 0, 0, 0 ,0},
            true,
            false,  /* not implemented for encoders */
            false, /* not implemented for encoders */
            FUNC_NOT_IN_REPORT,
            0,
        },
};

