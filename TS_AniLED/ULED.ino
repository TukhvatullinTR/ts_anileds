#include <Arduino.h>
#include "FastLED.h"
#define  LED_CNT 60

CRGB leds[LED_CNT];

struct TLight {
  float x;
  float dx;
  byte ticks;
  CRGB color;
};

void LED_init() {
  FastLED.addLeds<WS2812B, STRIP_PIN, GRB>(leds, LED_CNT);
  FastLED.clear();
  FastLED.show();
}

void LED_run(byte effect, byte bright) {
  if (showEffect) {
    FastLED.setBrightness(bright);
    switch (effect) {
      case  1: effect_flicker      (128,255, 128,255, 128,255, 0.1,1.0, 5,3); break; //white
      case  2: effect_flicker      (128,255,   0, 64,   0,  0, 0.1,1.0, 3,5); break; //fire
      case  3: effect_rainbow      (); break; //rainbow
      case  4: effect_solid        (255,255,255); break;//white
      case  5: effect_solid        (  0,255,  0); break;//green
      case  6: effect_bpm          ()  ; break;
      case  7: effect_runing_lights(); break;
      case  8: effect_runing_sinus (); break;
      case  9: effect_confetti     (); break;
      case 10: effect_juggle       (); break;
    }
    FastLED.show();
  }
  // Отключаем холостую работу ленты если яркость  = 0
  curr_brightness == 0
  ? showEffect = false
  : showEffect = true;
}

void effect_flicker(byte minR, byte maxR, byte minG, byte maxG, byte minB, byte maxB, byte minIntensity, byte maxIntensity, byte speedColor, byte speedIntensity) {
  unsigned int time = millis();
  static float nc;
  static float ni;
  for (int i = 0; i < LED_CNT; i++) {
    //adjust the mult and divide to change the global effect
    nc = inoise8(i*250 , (time+i) / speedColor);
    ni = inoise8(i*500 , (time+i) / speedIntensity);
    //You can change the easing function here
    float pc = nc / 255;
    float pi = nc / 255;
    float vc = pc < 0.5 ? 4*pow(pc,3) : 0.5*pow(2*pc-2,3)+1;
    float vi = pi < 0.5 ? 4*pow(pi,3) : 0.5*pow(2*pi-2,3)+1;
    vi = (maxIntensity - minIntensity) * vc + minIntensity;
    float r = vi * ((maxR - minR)*vc + minR);
    float g = vi * ((maxG - minG)*vc + minG);
    float b = vi * ((maxB - minB)*vc + minB);
    leds[i] = CRGB(r , g , b);
  }
}

void effect_rainbow() {
  static float step;
  for (int i = 0; i < LED_CNT; i++) { 
      leds[i] = CHSV(i * 4.25 + step, 255, 255);
  }
  step < 255
  ? step = step + 0.5
  : step = 0;
}

void effect_solid(byte red, byte green, byte blue) {
  for (int i = 0; i < LED_CNT; i++) leds[i] = CRGB(red, green, blue);
}

void effect_runing_lights() {
  static uint32_t tmr, interval = 100;
  if (millis() - tmr > interval) {
    tmr = millis();
    for (int i = LED_CNT - 1; i >= 1; i--) leds[i] = leds[i - 1];
    leds[0] = CHSV(random(255),random(255),random(255));
  }
}

void effect_runing_sinus() {
  static float step;
  fadeToBlackBy( leds, LED_CNT, 1);
  leds[beatsin16(13,0,LED_CNT-1)]  += CHSV(step, 255, 255);
  step = step + 0.01;
}

void effect_confetti()
{
  static uint32_t tmr, interval = 20;
  static float step;
  fadeToBlackBy( leds, LED_CNT, 1);
  if (millis() - tmr > interval) {
    tmr = millis();  
    int pos = random16(LED_CNT);
    leds[pos] += CHSV( step + random8(64), 255, 255);
    step = step + 0.01;
  }
}

void effect_juggle() {
  static float step;
  fadeToBlackBy( leds, LED_CNT, 5);
  for( int i = 0; i < 8; i++) {
    leds[beatsin16( i+7, 0, LED_CNT-1 )] |= CHSV(step, 255, 255);
    step += 32;
  }
}

void effect_bpm()
{
  static float step;
  fadeToBlackBy( leds, LED_CNT, 20);
  uint8_t BeatsPerMinute = 42;
  CRGBPalette16 palette = PartyColors_p;
  uint8_t beat = beatsin8( BeatsPerMinute, 64, 255);
  for( int i = 0; i < LED_CNT; i++) { //9948
    leds[i] = ColorFromPalette(palette, step+(i*2), beat-step+(i*10));
    step += 32;
  }
}
