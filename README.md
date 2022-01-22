# TS_AniLEDs

## Ночник с датчиком движения

### Оборудование:
- микроконтроллер **Arduino Nano**
- адресная лента **WS2812B** (плотность: 30 диодов на метр, количество диодов: 60)
- Датчик движения **Датчик движения HC-SR501**
- 2 кнопки MENU и SET
  
### Схема подключения:

- Кнопка MENU     - D8
- Кнопка SET      - D7
- Датчик движения - D2
- Адресная лента  - D6

![alt text](https://github.com/TukhvatullinTR/ts_anileds/blob/main/%D0%A1%D1%85%D0%B5%D0%BC%D0%B0%20%D0%BF%D0%BE%D0%B4%D0%BA%D0%BB%D1%8E%D1%87%D0%B5%D0%BD%D0%B8%D1%8F.png?raw=true)

### Настраиваемые параметры в меню:
  - **Эффекты**
  - - Значение по умолчанию: 1
  - - Минимальное значение: 1
  - - Максимальное значение: 10
  - - Шаг изменения: 1
  - **Длительность** (секунд)
  - - Значение по умолчанию: 30
  - - Минимальное значение: 10
  - - Максимальное значение: 60
  - - Шаг изменения: 5
  - **Яркость MIN**
  - - Значение по умолчанию: 0
  - - Минимальное значение: 0
  - - Максимальное значение: 127
  - - Шаг изменения: 5
  - **Яркость MAX**
  - - Значение по умолчанию: 255
  - - Минимальное значение: 128
  - - Максимальное значение: 255
  - - Шаг изменения: 5
  - **Интервал автоматического переключения эффектов** (минут)
  - - Значение по умолчанию: 0
  - - Минимальное значение: 0
  - - Максимальное значение: 60
  - - Шаг изменения: 5

### Управление

#### Режим "Работа"
- Переключение в режим "Меню параметров" - кнопка MENU (долгое)
- Следующий эффект - кнопка SET (однократное, выбранный эффект не сохраняется в энергонезависимую память)

#### Режим "Меню параметров"
- Переключение в режим "Работа" - кнопка MENU (долгое, с сохранением всех текущих параметров в энергонезависимую память)
- следующий параметр - кнопка MENU (однократное)
- увеличить значение параметра на шаг - кнопка SET (однократное, при достижении максимума, переключится на минимум)
- непрерывное увеличение значения параметра - кнопка SET (долгое, остановится на максимуме для данного параметра)
