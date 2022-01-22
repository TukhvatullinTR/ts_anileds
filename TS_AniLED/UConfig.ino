#include "EEPROM.h"

char configExists = 'w';

void defaultConfig() {
  params[PAR_EFFECT    ] = (TParam) {  1,   1,  10,  1};
  params[PAR_DURATION  ] = (TParam) { 30,  10,  60,  5};
  params[PAR_BRIGHT_MIN] = (TParam) {  0,   0, 127,  5};
  params[PAR_BRIGHT_MAX] = (TParam) {255, 128, 255,  5};
  params[PAR_AUTOCHANGE] = (TParam) {  0,   0,  60,  5};
}

bool checkConfig() {
  return EEPROM.length() > 0 && EEPROM.read(0) == configExists;
}

void resetConfig() {
  defaultConfig();
  saveConfig();
}

void loadConfig() {
  defaultConfig();
  EEPROM.get(4 * PAR_EFFECT     + 10, params[PAR_EFFECT    ].value); // Эффект
  EEPROM.get(4 * PAR_DURATION   + 10, params[PAR_DURATION  ].value); // Длительность
  EEPROM.get(4 * PAR_BRIGHT_MIN + 10, params[PAR_BRIGHT_MIN].value); // Яркость MIN
  EEPROM.get(4 * PAR_BRIGHT_MAX + 10, params[PAR_BRIGHT_MAX].value); // Яркость MAX
  EEPROM.get(4 * PAR_AUTOCHANGE + 10, params[PAR_AUTOCHANGE].value); // Карусель
}

void saveConfig() {
  EEPROM.put(4 * PAR_EFFECT     + 10, params[PAR_EFFECT    ].value); // Эффект
  EEPROM.put(4 * PAR_DURATION   + 10, params[PAR_DURATION  ].value); // Длительность
  EEPROM.put(4 * PAR_BRIGHT_MIN + 10, params[PAR_BRIGHT_MIN].value); // Яркость MIN
  EEPROM.put(4 * PAR_BRIGHT_MAX + 10, params[PAR_BRIGHT_MAX].value); // Яркость MAX
  EEPROM.put(4 * PAR_AUTOCHANGE + 10, params[PAR_AUTOCHANGE].value); // Карусель
  EEPROM.write(0, configExists); // Устанавливаем флаг, что конфиг записан в память
}
