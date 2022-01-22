// Пины
#define LED_PIN   LED_BUILTIN
#define MOVE_PIN  2
#define STRIP_PIN 6
// Режимы работы
#define WORK_MODE 0
#define MENU_MODE 1
byte    mode = WORK_MODE;

// Параметры
#define PAR_EFFECT     0
#define PAR_DURATION   1
#define PAR_BRIGHT_MIN 2
#define PAR_BRIGHT_MAX 3
#define PAR_AUTOCHANGE 4
struct TParam {
  float   value;
  float     min;
  float     max;
  float    step;
};
TParam  params[5];
byte    param_index, param_count;
// Текущие показатели
volatile bool curr_motion;        // Движение
bool          showEffect = false; // Работа ленты
float         curr_brightness;    // Яркость
long          curr_duration;      // Продолжительность свечения

void  MotionDetected() {
  curr_motion = true;
  digitalWrite(LED_PIN, true);
}

// Инициализация
void setup() {
//  Serial.begin(9600);
//  Serial.println("curr_motion curr_duration curr_brightness PAR_EFFECT showEffect");
  pinMode(LED_PIN, OUTPUT);
  attachInterrupt(0, MotionDetected, RISING);
  Menu_init();
  Work_init();
  LED_init();
}

void loop() {
  Menu_run();
  if (mode == MENU_MODE) Menu_show();
  if (mode == WORK_MODE) {
    Work_run();
    Work_show();
  }
}
