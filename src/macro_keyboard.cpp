/* STM 32 Blue Pill Keyboard.
 *
 * 
 */

/************************************************
 * Includes 
 * *********************************************/
#include <Arduino.h>
#include <Adafruit_TinyUSB.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_MCP23X17.h>
#include <Adafruit_GFX.h>
#include <RotaryEncoder.h>

#include "logo.c"
#include "hardware.h"
#include "profile.h"


#define DO_ENCODERS 1
#define DO_KEYBOARD 1 

/************************************************
 * Defines
 * *********************************************/
#define PROFILE_CHANGE_BUTTON 15  /* last key in map = encoder button */
#define PROFILE_CHANGE_DWELL 1000 /* how long to hold button */

/************************************************
 * Globals
 * *********************************************/
static uint8_t const gc_ascii2Keycode[128][2] =  { HID_ASCII_TO_KEYCODE };
static bool g_changingProfile = false;

/* temp profile swap support vars */
static uint8_t g_curFuncProfile  = 1;
static uint8_t g_prevFuncProfile = 1;
static bool g_tempProfileChange = false;

// static hid_keyboard_report_nkro_t g_currentReport = {0};
static hid_keyboard_report_nkro_t g_currentReport = {0};
static uint8_t                    g_currentReportItems = 0;


static button_func_t *gp_button_profiles[NUM_PROFILES] = {g_buttonFuncMap1, 
                                                          g_buttonFuncMap2, 
                                                          g_buttonFuncMap3
                                                          };


#if DO_ENCODERS
static button_func_t *gp_encoder_profiles[NUM_PROFILES] = {g_encoderFuncMap1, 
                                                           g_encoderFuncMap2, 
                                                           g_encoderFuncMap3
                                                           };

RotaryEncoder encoder1(ENCODER_1_CLK_PIN, ENCODER_1_DAT_PIN, 
                       RotaryEncoder::LatchMode::FOUR0);


static int g_en1LastPos = 0;
#endif

Adafruit_SSD1306 display(OLED_SCREEN_WIDTH, OLED_SCREEN_HEIGHT, &Wire, 
                         OLED_RESET);

Adafruit_MCP23X17 mcp;



#if DO_KEYBOARD

/* Report ID */
enum
{
  RID_KEYBOARD = 1,
  RID_CONSUMER_CONTROL, /* Media, volume etc ..*/
};

/* HID report descriptor using TinyUSB's template */
uint8_t const gc_descHidReport[] =
{
  TUD_HID_REPORT_DESC_KEYBOARD_NKRO( HID_REPORT_ID(RID_KEYBOARD) ),
  TUD_HID_REPORT_DESC_CONSUMER( HID_REPORT_ID(RID_CONSUMER_CONTROL) )
};

/* USB HID object */
Adafruit_USBD_HID usbHid;
#endif

/************************************************
 * Foward Declarations 
 * *********************************************/
static void _oledOnOff(bool onoff);
static void _oledFuncMsg(char * word);
static void _status1LedBlink(int times);
static void _status2LedBlink(int times);

/************************************************
 * Function Implementations
 ***********************************************/
static void _oledProtect(bool justTurnedOn)
{
    static uint32_t s_lastOnTime;

    uint32_t curTime = millis();

    if(curTime - s_lastOnTime >= OLED_MAX_ON_TIME_MS && justTurnedOn == false)
    {
        _oledOnOff(false);
    }
    else if(justTurnedOn == true)
    {
        s_lastOnTime = millis();
    }
    /* otherwise, keep waiting */
}


static void _oledOnOff(bool onoff)
{
    static bool s_curOnoff = false;

    if (onoff && !s_curOnoff)
    {
        s_curOnoff = onoff;
        _oledProtect(true);
    }
    else if(!onoff && s_curOnoff)
    {
        display.clearDisplay();
        display.display();
        s_curOnoff = onoff;
    }
}

static void _oledBanner(char * text)
{
    display.setTextSize(1);
    display.setTextColor(BLACK, WHITE);
    
    display.drawRect(0, 0, OLED_SCREEN_WIDTH, 10, WHITE);
    display.fillRect(0, 0, OLED_SCREEN_WIDTH, 10, WHITE);
    display.setCursor(10, 1);
    display.println(text);
}

static void _oledFuncMsg(char *word)
{
    _oledOnOff(true);
    display.clearDisplay();


    char banner_msg[20];
    snprintf(banner_msg, 20, "Profile: %i", g_curFuncProfile);
    _oledBanner(banner_msg);

    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(5, 30);
    display.println(word);
    display.display();
}

static void _oledDebug(char *msg)
{
    display.drawRect(0, OLED_SCREEN_HEIGHT-8, OLED_SCREEN_WIDTH, 8, BLACK);
    display.fillRect(0, OLED_SCREEN_HEIGHT-8, OLED_SCREEN_WIDTH, 8, BLACK);
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, OLED_SCREEN_HEIGHT - 8);
    display.println(msg);
    display.display();
}

#if DO_ENCODERS
static void _encoder1TickIsr()
{
  encoder1.tick();
}
#endif

static void _safeSendReportNKRO()
{
    if (USBDevice.suspended())
    {
        USBDevice.remoteWakeup();
    }
    while(!usbHid.ready()) delay(1);
    tud_hid_report(RID_KEYBOARD,
                   &g_currentReport,
                   (uint8_t)sizeof(g_currentReport));
}

static void _safeSendReport16(uint16_t key)
{
    if (USBDevice.suspended())
    {
        USBDevice.remoteWakeup();
    }
    while(!usbHid.ready()) delay(1);
    usbHid.sendReport16(RID_CONSUMER_CONTROL, key);

}


static void _reportInsert(button_func_t &buttonFunc)
{

    uint16_t *p_func = &buttonFunc.func[0];

    /* if we're changing profile, we ignore all keys */
    if (g_changingProfile == true)
    {
        return;
    }

    /* figure out how many keys we need to put into report */
    /* only regular keys count, not media keys */
    int numReportKeys = 0;
    for (int i = 0; i < MAX_BUTTON_FUNCS; i++)
    {
        uint16_t key = *(p_func + i);
        if (key != 0 && key < 0xFF)
        {
            /* this "should" be a standard ascii HID key */
            numReportKeys++;
        }
    }

    /* handle non report keys */
    for (int i = 0; i < MAX_BUTTON_FUNCS; i++)
    {
        uint16_t key = *(p_func + i);
        switch (key)
        {
        /* no func */
        case (0):
        {
            break;
        }
        case (KEY_PROFILE1_TEMP):
        {
            if (g_tempProfileChange == true)
            {
                /* if we're already in a temp profile change, don't
                   allow "nested" changes */
                break;
            }
            if (g_curFuncProfile != 1)
            {
                g_prevFuncProfile = g_curFuncProfile;
                g_curFuncProfile = 1;
                g_tempProfileChange = true;
                buttonFunc.funcFired = true;
            }
            break;
        }
        case (KEY_PROFILE2_TEMP):
        {
            if (g_curFuncProfile != 2)
            {
                g_prevFuncProfile = g_curFuncProfile;
                g_curFuncProfile = 2;
                g_tempProfileChange = true;
                buttonFunc.funcFired = true;
            }
            break;
        }
        case (KEY_PROFILE3_TEMP):
        {
            if (g_curFuncProfile != 3)
            {
                g_prevFuncProfile = g_curFuncProfile;
                g_curFuncProfile = 3;
                g_tempProfileChange = true;
                buttonFunc.funcFired = true;
            }
            break;
        }
        /* media keys require a sendReport16 because they are 16 bits */
        case (HID_PLAY_PAUSE):
        case (HID_SCAN_NEXT):
        case (HID_SCAN_PREVIOUS):
        case (HID_STOP):
        case (HID_VOLUME):
        case (HID_MUTE):
        case (HID_BASS):
        case (HID_TREBLE):
        case (HID_BASS_BOOST):
        case (HID_VOLUME_INCREMENT):
        case (HID_VOLUME_DECREMENT):
        case (HID_BASS_INCREMENT):
        case (HID_BASS_DECREMENT):
        case (HID_TREBLE_INCREMENT):
        case (HID_TREBLE_DECREMENT):
        {
            int unmaskedKey = key & ~HID_CONSUMER_CONTROL_FLAG;
            _safeSendReport16(unmaskedKey);
            buttonFunc.funcFired = true;
            break;
        }
        default:
            break;
        }
    }

    /* Handle report keys */
    if (numReportKeys > 0)
    {
        /* find the first spot in the report we can shove 
        these keys. The full func is always added and 
        removed so there should always be enough sequential
        spots */
        int seqEmpties = 0;
        for (size_t i = 0; i < sizeof(g_currentReport.keycode); i++)
        {
            if (g_currentReport.keycode[i] == 0x00) /* found possible spot */
            {
                if(seqEmpties >= 1)
                {
                    /* check if last guy was empty */
                    if(g_currentReport.keycode[i - 1] == 0x00)
                    {
                        /* it was so this is sequential empty */
                        seqEmpties++;
                    }
                    else
                    {
                        /* it wasn't so this is just first */
                        seqEmpties = 1;
                    }
                }
                else
                {   
                    /* count the first empty */
                    seqEmpties++;
                }
                
                /* if we found a big enough spot */
                if(seqEmpties == numReportKeys)
                {
                    buttonFunc.inReportIdx = i - (numReportKeys - 1);
                    break;
                }
            }
        }
        
        /* verify we found a spot */
        if(buttonFunc.inReportIdx == FUNC_NOT_IN_REPORT)
        {
            /* oof */
            _oledFuncMsg((char *)"Hid Report Full.");
            delay(2000);
            return;
        }

        for (int i = 0; i < MAX_BUTTON_FUNCS; i++)
        {
            uint16_t key = *(p_func + i);

            if(key == 0)
            {
                continue;
            }

            /* See if this is an ASCII key */
            if (key < 128)
            {
                if (gc_ascii2Keycode[key][1])
                {
                    /* it's an ascii key, see if shift modifier is needed */
                    if (gc_ascii2Keycode[key][0])
                    {
                        g_currentReport.modifier |=
                            KEYBOARD_MODIFIER_LEFTSHIFT;
                    }

                    /* convert it to the hid representation */
                    key = gc_ascii2Keycode[key][1];
                    SerialUSB.println(key);
                }
            }
            /* handle modifiers */
            else if (key >= HID_KEY_CONTROL_LEFT &&
                     key <= HID_KEY_GUI_RIGHT)
            {
                switch (key)
                {
                case (HID_KEY_CONTROL_LEFT):
                {
                    g_currentReport.modifier |=
                        KEYBOARD_MODIFIER_LEFTCTRL;
                    break;
                }
                case (HID_KEY_CONTROL_RIGHT):
                {
                    g_currentReport.modifier |=
                        KEYBOARD_MODIFIER_RIGHTCTRL;
                    break;
                }
                case (HID_KEY_SHIFT_LEFT):
                {
                    g_currentReport.modifier |=
                        KEYBOARD_MODIFIER_LEFTSHIFT;
                    break;
                }
                case (HID_KEY_SHIFT_RIGHT):
                {
                    g_currentReport.modifier |=
                        KEYBOARD_MODIFIER_RIGHTSHIFT;
                    break;
                }
                case (HID_KEY_ALT_LEFT):
                {
                    g_currentReport.modifier |=
                        KEYBOARD_MODIFIER_LEFTALT;
                    break;
                }
                case (HID_KEY_ALT_RIGHT):
                {
                    g_currentReport.modifier |=
                        KEYBOARD_MODIFIER_RIGHTALT;
                    break;
                }
                case (HID_KEY_GUI_LEFT):
                {
                    g_currentReport.modifier |=
                        KEYBOARD_MODIFIER_LEFTGUI;
                    break;
                }
                case (HID_KEY_GUI_RIGHT):
                {
                    g_currentReport.modifier |=
                        KEYBOARD_MODIFIER_RIGHTGUI;
                    break;
                }
                }
            }
            else /* NON ascii HID keys */
            {
                key &= ~HID_NON_ASCII_FLAG;
            }

            int addKeyIdx = buttonFunc.inReportIdx + buttonFunc.keysInReport;
            g_currentReport.keycode[addKeyIdx] = key;
            g_currentReportItems++;
            buttonFunc.keysInReport++;
        }
        _safeSendReportNKRO();
        buttonFunc.funcFired = true;
    }
}

static void _reportRemove(button_func_t &buttonFunc)
{
    uint16_t *p_func = &buttonFunc.func[0];
    if (g_changingProfile == true)
    {
        return;
    }
    for (int i = 0; i < MAX_BUTTON_FUNCS; i++)
    {
        uint16_t key = *(p_func + i);
        
        switch (key)
        {
        /* media keys require a sendReport16 because they are 16 bits */
        case (HID_PLAY_PAUSE):
        case (HID_SCAN_NEXT):
        case (HID_SCAN_PREVIOUS):
        case (HID_STOP):
        case (HID_VOLUME):
        case (HID_MUTE):
        case (HID_BASS):
        case (HID_TREBLE):
        case (HID_BASS_BOOST):
        case (HID_VOLUME_INCREMENT):
        case (HID_VOLUME_DECREMENT):
        case (HID_BASS_INCREMENT):
        case (HID_BASS_DECREMENT):
        case (HID_TREBLE_INCREMENT):
        case (HID_TREBLE_DECREMENT):
        {
            /* Sending 0 releases consumer control key */
            _safeSendReport16(0);
            break;
        }
        case (KEY_PROFILE1_TEMP):
        case (KEY_PROFILE2_TEMP):
        case (KEY_PROFILE3_TEMP):
        {
            g_tempProfileChange = false; /* we're done with temp swap */
            g_curFuncProfile = g_prevFuncProfile;
            break;
        }
        case (0):
        {
            break;
        }
        default:
        {
            if (buttonFunc.keysInReport > 0)
            {
                int removeKeyIdx = buttonFunc.inReportIdx 
                                   + (buttonFunc.keysInReport - 1);
                
                uint16_t key = *(p_func + i);

                if (key < 128)
                {
                    if (gc_ascii2Keycode[key][1])
                    {
                        /* See if shift modifier was needed */
                        if (gc_ascii2Keycode[key][0])
                        {
                            /* remove it */
                            g_currentReport.modifier &=
                                ~KEYBOARD_MODIFIER_LEFTSHIFT;
                        }
                    }
                }
                /* handle modifiers */
                else if (key >= HID_KEY_CONTROL_LEFT &&
                         key <= HID_KEY_GUI_RIGHT)
                {
                    switch (key)
                    {
                    case (HID_KEY_CONTROL_LEFT):
                    {
                        g_currentReport.modifier &=
                            ~KEYBOARD_MODIFIER_LEFTCTRL;
                        break;
                    }
                    case (HID_KEY_CONTROL_RIGHT):
                    {
                        g_currentReport.modifier &=
                            ~KEYBOARD_MODIFIER_RIGHTCTRL;
                        break;
                    }
                    case (HID_KEY_SHIFT_LEFT):
                    {
                        g_currentReport.modifier &=
                            ~KEYBOARD_MODIFIER_LEFTSHIFT;
                        break;
                    }
                    case (HID_KEY_SHIFT_RIGHT):
                    {
                        g_currentReport.modifier &=
                            ~KEYBOARD_MODIFIER_RIGHTSHIFT;
                        break;
                    }
                    case (HID_KEY_ALT_LEFT):
                    {
                        g_currentReport.modifier &=
                            ~KEYBOARD_MODIFIER_LEFTALT;
                        break;
                    }
                    case (HID_KEY_ALT_RIGHT):
                    {
                        g_currentReport.modifier &=
                            ~KEYBOARD_MODIFIER_RIGHTALT;
                        break;
                    }
                    case (HID_KEY_GUI_LEFT):
                    {
                        g_currentReport.modifier &=
                            ~KEYBOARD_MODIFIER_LEFTGUI;
                        break;
                    }
                    case (HID_KEY_GUI_RIGHT):
                    {
                        g_currentReport.modifier &=
                            ~KEYBOARD_MODIFIER_RIGHTGUI;
                        break;
                    }
                    }
                }
                else
                {
                    key &= ~HID_NON_ASCII_FLAG;
                }

                g_currentReport.keycode[removeKeyIdx] = 0x00;
                g_currentReportItems--;

                buttonFunc.keysInReport--;

                if (buttonFunc.keysInReport == 0)
                {
                    buttonFunc.inReportIdx = FUNC_NOT_IN_REPORT;
                }
            }
        }
        }
    }
    _safeSendReportNKRO();
}

static void _processProfile(uint32_t tNow_ms)
{
    static uint8_t s_newProfile = 0;
    static bool s_buttonBeenReleased = true;
    uint32_t tPressed_ms =
        G_BUTTON_HW_MAP[PROFILE_CHANGE_BUTTON].tPressed_ms;
    uint32_t tReleased_ms =
        G_BUTTON_HW_MAP[PROFILE_CHANGE_BUTTON].tReleased_ms;

    /* check if button is still being held down and it's been long enough */
    if (tPressed_ms > tReleased_ms &&
        tNow_ms - tPressed_ms >= PROFILE_CHANGE_DWELL && 
        s_buttonBeenReleased == true)
    {
        s_buttonBeenReleased = false;
        if (g_changingProfile == false)
        {
            s_newProfile = g_curFuncProfile;
            /* release all keys */

            usbHid.keyboardRelease(RID_KEYBOARD);
            usbHid.sendReport16(RID_CONSUMER_CONTROL, 0);

            _oledProtect(true);
            display.clearDisplay();
            display.setTextSize(2);
            display.setTextColor(WHITE);
            display.setCursor(5, 20);
            char msg[16];
            snprintf(msg, 16, "Profile: %i", s_newProfile);
            display.println(msg);
            display.display();
        }
        else
        {
            g_curFuncProfile = s_newProfile;
            _oledProtect(true);
            display.clearDisplay();
            display.setTextSize(2);
            display.setTextColor(WHITE);
            display.setCursor(20, 10);
            char msg[16];
            snprintf(msg, 16, "Profile");
            display.println(msg);
            display.setCursor(20, 10 + 18);
            snprintf(msg, 16, "Changed");
            display.println(msg);
            display.display();

            /* ignore all the encoder value changes during this segue */
            g_en1LastPos = encoder1.getPosition();
            delay(500); /* force a delay here */
        }
        g_changingProfile = !g_changingProfile;
    }
    else if (tReleased_ms > tPressed_ms)
    {
        /* we've released the button after holding it for at least
           PROFILE_CHANGE_DWELL.  
        */
        s_buttonBeenReleased = true;
    }

    if (g_changingProfile == true)
    {
        static uint32_t s_Enos = 0;
        static uint32_t s_lastChangeTime = 0; /* to slow down encoder */
        uint32_t new_pos = encoder1.getPosition();
        if (s_Enos != new_pos)
        {
            if (tNow_ms - s_lastChangeTime > 200)
            {
                s_lastChangeTime = tNow_ms;
                if (new_pos < s_Enos)
                {
                    if (s_newProfile > 1)
                        s_newProfile--;
                }
                else
                {
                    if (s_newProfile < NUM_PROFILES)
                        s_newProfile++;
                }
                _oledProtect(true);
                display.clearDisplay();
                display.setTextSize(2);
                display.setTextColor(WHITE);
                display.setCursor(5, 20);
                char msg[16];
                snprintf(msg, 16, "Profile: %i", s_newProfile);
                display.println(msg);
                display.display();
            }
            s_Enos = new_pos;
        }
    }
}

static void _processButtons(uint32_t tNow_ms)
{
    button_func_t *p_buttonFuncMap = gp_button_profiles[g_curFuncProfile - 1];
    for (int i = 0; i < NUM_BUTTONS; i++)
    {
        if (G_BUTTON_HW_MAP[i].button == -1)
            continue;

        button_func_t *p_buttonFunc = (p_buttonFuncMap + i);

        int buttonState = mcp.digitalRead(G_BUTTON_HW_MAP[i].button);

        if (buttonState != G_BUTTON_HW_MAP[i].prevState)
        {
            G_BUTTON_HW_MAP[i].prevState = buttonState;

            if (buttonState == G_BUTTON_HW_MAP[i].actState)
            {
                G_BUTTON_HW_MAP[i].tPressed_ms = tNow_ms;
            }
            else
            {
                G_BUTTON_HW_MAP[i].tReleased_ms = tNow_ms;
            }
        }

        uint32_t tPressedDelta_ms = tNow_ms - G_BUTTON_HW_MAP[i].tPressed_ms;
        uint32_t tReleasedDelta_ms = tNow_ms - G_BUTTON_HW_MAP[i].tReleased_ms;

        /* check if button is released and we've passed debounce threshold */
        if (buttonState != G_BUTTON_HW_MAP[i].actState 
                 && tReleasedDelta_ms > G_BUTTON_HW_MAP[i].tDebounce_ms)
        {
            if (p_buttonFunc->func != 0)
            {
                /* if we're in a temp profile change, check for any release */
                if (p_buttonFunc->funcFired == true 
                    || g_tempProfileChange == true)
                {
                    _reportRemove(*p_buttonFunc);
                }
                p_buttonFunc->funcFired = false;
            }
        }
        /* check if button is pressed and we've passed debounce threshold */
        else if (buttonState == G_BUTTON_HW_MAP[i].actState 
            && tPressedDelta_ms > G_BUTTON_HW_MAP[i].tDebounce_ms)
        {
            if (p_buttonFunc->func != 0 &&
                p_buttonFunc->funcFired == false)
            {
                _reportInsert(*p_buttonFunc);
                
                if(p_buttonFunc->oneShot == true || p_buttonFunc->turbo == true)
                {
                    _reportRemove(*p_buttonFunc);
                }

                /* turbo will keep insert/remove cycle until released */
                if(p_buttonFunc->turbo == true)
                {
                    p_buttonFunc->funcFired = false;
                }

                if (g_changingProfile == false)
                {
                    _oledFuncMsg(p_buttonFunc->msg);
                }
                _status1LedBlink(2);

            }
        }

        /* button is not active state */
       
    }
}

#if DO_ENCODERS
static void _processEncoders()
{
    if (g_changingProfile == true)
    {
        return;
    }

    button_func_t *p_encoderFuncMap = gp_encoder_profiles[g_curFuncProfile - 1];
    button_func_t enc1CFunc = *(p_encoderFuncMap);
    button_func_t enc1CcFunc = *(p_encoderFuncMap + 1);

    int newPos1 = encoder1.getPosition();
    if (g_en1LastPos != newPos1)
    {
        _status2LedBlink(1);
        if (newPos1 < g_en1LastPos)
        {
            _reportInsert(enc1CcFunc);
            _reportRemove(enc1CcFunc);
            _oledFuncMsg(enc1CcFunc.msg);
        }
        else
        {
            _reportInsert(enc1CFunc);
            _reportRemove(enc1CFunc);
            _oledFuncMsg(enc1CFunc.msg);
        }
        g_en1LastPos = newPos1;
    }
}
#endif

void setup()
{

    /* setup led pins on xiao (they are active low)*/
    pinMode(HEARTBEAT_LED_PIN, OUTPUT);
    digitalWrite(HEARTBEAT_LED_PIN, LOW);

    pinMode(STATUS1_LED_PIN, OUTPUT);
    digitalWrite(STATUS1_LED_PIN, HIGH);

    pinMode(STATUS2_LED_PIN, OUTPUT);
    digitalWrite(STATUS2_LED_PIN, HIGH);


    SerialUSB.begin(9600);

    /* setup xiao pins */
#if DO_ENCODERS
    attachInterrupt(digitalPinToInterrupt(ENCODER_1_CLK_PIN), 
                    _encoder1TickIsr, CHANGE);
    attachInterrupt(digitalPinToInterrupt(ENCODER_1_DAT_PIN), 
                    _encoder1TickIsr, CHANGE);
#endif

    if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_SCREEN_ADDRESS))
    {
        while (1)
        {
            SerialUSB.println("Display Error.");
            delay(1000); /* stay here...dirty boy */
        } 
    }

    display.ssd1306_command(SSD1306_SETCONTRAST); // 0x81    
    display.ssd1306_command(0x25);
    display.clearDisplay();
    display.drawBitmap(0, 0, logo, LOGO_WIDTH, LOGO_HEIGHT, WHITE);
    display.display();
    _oledOnOff(true);

    /* take MCP out of reset */
    pinMode(MCP_RESET_CTRL_PIN, OUTPUT);
    digitalWrite(MCP_RESET_CTRL_PIN, HIGH);

    /* initialize the mcp */
    if (!mcp.begin_I2C())
    {    
        while (1)
        {
            SerialUSB.println("MCP Error.");
            delay(1000);
        }
    }


    /* initialize pins */
    for (int i = 0; i < NUM_BUTTONS; i++)
    {

        if (G_BUTTON_HW_MAP[i].button == -1)
            continue;

        if (G_BUTTON_HW_MAP[i].actState == HIGH)
        {
            mcp.pinMode(G_BUTTON_HW_MAP[i].button, INPUT);
        }
        else
        {
            mcp.pinMode(G_BUTTON_HW_MAP[i].button, INPUT_PULLUP);
        }
    }

#if DO_KEYBOARD
    usbHid.setPollInterval(2);
    usbHid.setReportDescriptor(gc_descHidReport, sizeof(gc_descHidReport));
    usbHid.setStringDescriptor("RRR Macro Keyboard");
    usbHid.begin();
#endif
    delay(1000); // wait long enough to let the host configure device

}

static void _status1LedBlink(int times)
{
    static uint32_t s_tLast_ms;
    static int  s_timesLeft = 0; 
    static int  s_ledState = LOW;

    if(s_timesLeft == 0)
    {
        s_timesLeft = times;
    }

    if(s_timesLeft == 0)
    {
        return;
    }

    uint32_t tNow_ms = millis();
    
    if(s_ledState == LOW && (tNow_ms - s_tLast_ms > LED_BLINK_OFF_MS))
    {
        digitalWrite(STATUS1_LED_PIN, LOW); /* led is active low */
        s_ledState = HIGH;
        s_tLast_ms = tNow_ms;
    }
    else if(s_ledState == HIGH && (tNow_ms - s_tLast_ms > LED_BLINK_ON_MS))
    {
        digitalWrite(STATUS1_LED_PIN, HIGH);
        s_ledState = LOW;
        s_timesLeft--;
        s_tLast_ms = tNow_ms;
    }
}

static void _status2LedBlink(int times)
{
    static uint32_t s_tLast_ms;
    static int  s_timesLeft = 0; 
    static int  s_ledState = LOW;

    if(s_timesLeft == 0)
    {
        s_timesLeft = times;
    }

    if(s_timesLeft == 0)
    {
        return;
    }

    uint32_t tNow_ms = millis();
    
    if(s_ledState == LOW && (tNow_ms - s_tLast_ms > LED_BLINK_OFF_MS))
    {
        digitalWrite(STATUS2_LED_PIN, LOW); /* led is active low */
        s_ledState = HIGH;
        s_tLast_ms = tNow_ms;
    }
    else if(s_ledState == HIGH && (tNow_ms - s_tLast_ms > LED_BLINK_ON_MS))
    {
        digitalWrite(STATUS2_LED_PIN, HIGH);
        s_ledState = LOW;
        s_timesLeft--;
        s_tLast_ms = tNow_ms;
    }
}


static void _heartbeatLed(uint32_t tNow_ms)
{
    static uint32_t s_tLast_ms = 0;
    static int      s_ledState = LOW;

    if (tNow_ms - s_tLast_ms > 500)
    {
        digitalWrite(HEARTBEAT_LED_PIN, !s_ledState);
        s_ledState = !s_ledState;
        s_tLast_ms = tNow_ms;
    }
}

void loop()
{
    uint32_t tNow_ms = millis();
    _heartbeatLed(tNow_ms);
    _oledProtect(false);
    _processButtons(tNow_ms);

#if DO_ENCODERS
    _processEncoders();
#endif
    _processProfile(tNow_ms);

    _status1LedBlink(0); /* Update any running blink requests */
    _status2LedBlink(0); /* Update any running blink requests */

}