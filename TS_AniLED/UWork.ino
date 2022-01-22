long  tmrWork, intervalWork = 1000, // таймер в рабочем режиме
      tmrAuto; // таймер автосмены эффекта

void Work_init() {
  // Config
  checkConfig()
  ? loadConfig()
  : resetConfig();
  // Currents
  curr_duration   = 0;
  curr_brightness = params[PAR_BRIGHT_MIN].value;
  curr_motion     = LOW;
}

void Work_run() {
  // Куждую секунду смотрим - есть ли движение
  if (mode == WORK_MODE && millis() - tmrWork > intervalWork) {
    tmrWork = millis();
    if (curr_motion == HIGH) {
      curr_duration = params[PAR_DURATION].value; // Если есть, устанавливаем таймер свечения
      curr_motion = false;
      digitalWrite(LED_PIN, false);
    } else {
      curr_duration > 0                          // Если нет, уменьшаем таймер свечения до нуля
        ? curr_duration--    
        : curr_duration = 0;
    }
  }

  // Автосмена эффекта
  if (mode == WORK_MODE && params[PAR_AUTOCHANGE].value > 0 && millis() - tmrAuto > params[PAR_AUTOCHANGE].value * 60000) {
    tmrAuto = millis();
    params[PAR_EFFECT].value < params[PAR_EFFECT].max
    ?  params[PAR_EFFECT].value = params[PAR_EFFECT].value + params[PAR_EFFECT].step
    :  params[PAR_EFFECT].value = params[PAR_EFFECT].min;
  }

  // Диммер включения/выключения свечения
  if (curr_duration > 0) {
    if (curr_brightness < params[PAR_BRIGHT_MAX].value)
      curr_brightness = curr_brightness + (params[PAR_BRIGHT_MAX].value - curr_brightness) / (params[PAR_BRIGHT_MAX].value / 5) + 0.01;
    else
      curr_brightness = params[PAR_BRIGHT_MAX].value;
    if (curr_brightness > params[PAR_BRIGHT_MAX].value) curr_brightness = params[PAR_BRIGHT_MAX].value;
  } else {
    if (curr_brightness > params[PAR_BRIGHT_MIN].value)
      curr_brightness = curr_brightness - (params[PAR_BRIGHT_MAX].value - curr_brightness) / (params[PAR_BRIGHT_MAX].value / 5) - 0.01;
    else
      curr_brightness = params[PAR_BRIGHT_MIN].value;
    if (curr_brightness < params[PAR_BRIGHT_MIN].value) curr_brightness = params[PAR_BRIGHT_MIN].value;
  }

  // Лог
//  String s =  String(curr_motion   * 50) + " " +
//              String(curr_duration * 10) + " " +
//              String(curr_brightness   ) + " " +            
//              String(params[PAR_EFFECT].value * 10) + " " +
//              String(showEffect * 10);
//  Serial.println(s);
}

void Work_show() {
  LED_run(params[PAR_EFFECT].value, curr_brightness);
}
