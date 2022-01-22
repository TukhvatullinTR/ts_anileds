#include "OneButton.h"

// Кнопки
OneButton btnMenu(8, true, true);
OneButton btnSet (7, true, true);

// таймер долгого нажатия клавиши
long  tmrHold, intervalHold = 50;

// Меню
void btnMenuClick() {
  if (mode == MENU_MODE) {
    param_index < param_count - 1
    ? param_index++
    : param_index = 0;
  }
}
void btnMenuHold() {
  if (mode == MENU_MODE) {
    mode = WORK_MODE;
    saveConfig();
  } else {
    mode = MENU_MODE;
    param_index = 0;
  }
  curr_brightness = 0;
  curr_duration   = 0;
  curr_motion     = false;
}
void btnSetClick() {
  if (mode == MENU_MODE) {
    params[param_index].value < params[param_index].max
    ?  params[param_index].value = params[param_index].value + params[param_index].step
    :  params[param_index].value = params[param_index].min;
  } 
  if (mode == WORK_MODE) {
    params[PAR_EFFECT].value < params[PAR_EFFECT].max
    ?  params[PAR_EFFECT].value = params[PAR_EFFECT].value + params[PAR_EFFECT].step
    :  params[PAR_EFFECT].value = params[PAR_EFFECT].min;
  }  
}
void btnSetHold() {
  if (mode == MENU_MODE && millis() - tmrHold > intervalHold) {
    tmrHold = millis();
    params[param_index].value < params[param_index].max
    ?  params[param_index].value = params[param_index].value + params[param_index].value
    :  params[param_index].value = params[param_index].max;
  }
}

void Menu_init() {
  btnMenu.attachClick(btnMenuClick);
  btnMenu.attachLongPressStart(btnMenuHold);
  btnSet.attachClick(btnSetClick);
  btnSet.attachDuringLongPress(btnSetHold);
  param_index = 0;
  param_count = 5;
}

void Menu_run() {
  btnMenu.tick();
  btnSet.tick();
}

void Menu_show() {
  FastLED.clear();
  FastLED.setBrightness(127);
  for (byte i = 0; i < LED_CNT; i++) {
    i < 10
    ? ( i <= param_index ? leds[i] = CRGB(128,0,0): leds[i] = CRGB(60,45,15) )
    : ( i <= map(params[param_index].value, params[param_index].min, params[param_index].max, 10, 59) ? leds[i] = CRGB(0,128,0) : leds[i] = CRGB(15,45,60) ); 
  }
  FastLED.show();
}
