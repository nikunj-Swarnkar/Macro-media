#define USE_NIMBLE 
#include <BleKeyboard.h>
#include <Bounce2.h>
#include <ESP32Encoder.h>
#include "driver/rtc_io.h"

const uint8_t SWITCH_PINS[6] = {1, 2, 3, 4, 5, 6};
const uint8_t NUM_SWITCHES = 6;
const uint8_t ENCODER_A_PINS[2] = {8,11};
const uint8_t ENCODER_B_PINS[2] = {9,12};
const uint8_t ENCODER_BTN_PINS[2] = {10,13};

BleKeyboard blekeyboard;
Bounce2::Button switches[6];
ESP32Encoder encoders[1];
ESP32Encoder encoders[2];
long lastEnc1 = 0;
long lastEnc2 = 0;

const unsigned long SLEEP_TIMEOUT = 300000; 
unsigned long lastActivityTime = 0;

void setup() 
{
    Serial.begin(115200);

    blekeyboard.begin();

    for (int i = 0; i < NUM_SWITCHES; i++)
    {
        switches[i].attach(SWITCH_PINS[i], INPUT_PULLUP);
        switches[i].interval(15);
        switches[i].setPressedState(LOW);
    }
    pinMode(ENCODER_BIN_PINS[0], INPUT_PULLUP);
    pinMode(ENCODER_BIN_PINS[1], INPUT_PULLUP);

    encoder1.attachSingleEdge(ENCODER_A_PINS[0], ENCODER_B_PINS[0]);
    encoder2.attachSingleEdge(ENCODER_A_PINS[1], ENCODER_B_PINS[1]);
    encoder1.setCount(0);
    encoder2.setCount(0);

    lastActivityTime = millis();
}

void loop()
{
    bool activityDetected = false;

    long enc1Pos = encoder1.getCount();
    if (enc1Pos != lastEnc1)
    {
        if (enc1pos < lastEnc1)
        {
            if (blekeyboard.isConnected())
            {
                blekeyboard.write(KEY_MEDIA_VOLUME_UP);
            }
            else{
                if(blekeyboard.isConnected())
                {
                    blekeyboard.write(KEY_MEDIA_VOLUME_DOWN);
                }
            }
        }
        lastEnc1 = enc1Pos;
        activityDetected = true;
    }
    long enc2Pos = encoder2.getCount();
    if (enc2Pos != lastEnc2)
    {
        if (enc2Pos < lastEnc2)
        {
            if (blekeyboard.isConnected())
            {
                blekeyboard.write(KEY_RIGHT_ARROW);
            }
        }
        else
        {
            if (blekeyboard.isConnected())
            {
                blekeyboard.write(KEY_LEFT_ARROW);
            }
        }
        lastEnc2 = enc2Pos;
        activityDetected = true;
    }
    for (int i = 0; i < NUM_SWITCHES; i++)
    {
        switches[i].update();
        if (switches[i].pressed())
        {
            handleSwitchPress(i);
            activityDetected = true;
        }
    }
    for (int i = 0; i < NUM_SWITCHES; i++)
    {
        switches[i].update();
        if (switches[i].pressed())
        {
            handleSwitchPress(i);
            activityDetected = true;
        }
    }
    for (int i = 0; i< 2; i++)
    {
        if (digitalRead(ENCODER_BIN_PINS[i])== LOW)
        {
            delay(30);
            if (digitalRead(ENCODER_BIN_PINS[i])== LOW)
            {
                handleEncoderClick(i);
                while(digitalRead(ENCODER_BTN_PINS[i]) == LOW) delay(10);
                activityDetected = true;
            }
        }
    }
    if (activityDetected)
    {
        lastActivityTime = millis();
    }
    if (millis() - lastActivityTime > SLEEP_TIMEOUT)
    {
        goToSleep();
    }
    delay(2);

}
void goToSleep()
{
    Serial.println("Going to sleep...");
    if (bleKeyboard.isConnected())
    {
        bleKeyboard.releaseAll();
    }
     delay(100);
    uint64_t wakeupBinMask = 0;
    for (int i = 0; i < NUM_SWITCHES; i++)
    {
        wakeupBinMask |= (1ULL << SWITCH_PINS[i]);
        rtc_gpio_pullup_en((gpio_num_t)SWITCH_PINS[i]);
        rtc_gpio_pulldown_dis((gpio_num_t)SWITCH_PINS[i]);
    }
    wakeupBinMask |= (1ULL << ENCODER_BTN_PINS[0]);
    rtc_gpio_pullup_en((gpio_num_t)ENCODER_BTN_PINS[0]);
    rtc_gpio_pulldown_dis((gpio_num_t)ENCODER_BTN_PINS[0]);

    wakeupBinMask |= (1ULL << ENCODER_BTN_PINS[1]);
    rtc_gpio_pullup_en((gpio_num_t)ENCODER_BTN_PINS[1]);
    rtc_gpio_pulldown_dis((gpio_num_t)ENCODER_BTN_PINS[1]);
    esp_sleep_enable_ext1_wakeup(wakeupBinMask, ESP_EXT1_WAKEUP_ANY_HIGH);
    esp_sleep_pd_config(ESP_PD_DOMAIN_RTC_PERIPH, ESP_PD_OPTION_ON);
    esp_deep_sleep_start();
}  
void handleSwitchPress(uint8_t switchNum)
{
    if (!blekeyboard.isConnected()) return;
    switch (switchNum)
    {
        case 0:
            blekeyboard.write(KEY_MEDIA_NEXT_TRACK);
            break;
        case 1:
            blekeyboard.write(KEY_MEDIA_PLAY_PAUSE);
            break;
        case 2:
            blekeyboard.write(KEY_MEDIA_PREV_TRACK);
            break;
        case 3:
            blekeyboard.write(KEY_RIGHT_ARROW);
            break;
        case 4:
            blekeyboard.press(KEY_LEFT_GUI);
            blekeyboard.press('d');
            delay(50);
            blekeyboard.releaseAll();
            break;
        case 5:
            blekeyboard.write(KEY_LEFT_ARROW);
            break;
    }
}
void handleEncoderClick(int encoderNum)
{
    if(!blekeyboard.isConnected()) return;
    switch (encoderNum)
    {
        case 0:
            blekeyboard.write(KEY_MEDIA_MUTE);
            break;
        case 1:
            blekeyboard.write(KEY_ESC);
            break;
    }
}

 