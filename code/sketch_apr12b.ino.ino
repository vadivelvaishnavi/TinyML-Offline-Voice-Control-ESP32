#include <Arduino.h>
#include <red_light_inferencing.h>
#include "driver/i2s.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

#define I2S_WS   15
#define I2S_SCK  14
#define I2S_SD   32
#define I2S_PORT I2S_NUM_0
#define LED_PIN  2

#define SAMPLE_BUFFER_SIZE EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE
static int32_t i2sBuffer[SAMPLE_BUFFER_SIZE];
static int16_t sampleBuffer[SAMPLE_BUFFER_SIZE];

void setupI2S() {
  i2s_config_t config = {
    .mode                 = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX),
    .sample_rate          = EI_CLASSIFIER_FREQUENCY,
    .bits_per_sample      = I2S_BITS_PER_SAMPLE_32BIT,
    .channel_format       = I2S_CHANNEL_FMT_ONLY_RIGHT,
    .communication_format = I2S_COMM_FORMAT_STAND_I2S,
    .intr_alloc_flags     = ESP_INTR_FLAG_LEVEL1,
    .dma_buf_count        = 8,
    .dma_buf_len          = 128,
    .use_apll             = false,
    .tx_desc_auto_clear   = false,
    .fixed_mclk           = 0
  };
  i2s_pin_config_t pin_config = {
    .bck_io_num   = I2S_SCK,
    .ws_io_num    = I2S_WS,
    .data_out_num = I2S_PIN_NO_CHANGE,
    .data_in_num  = I2S_SD
  };
  i2s_driver_install(I2S_PORT, &config, 0, NULL);
  i2s_set_pin(I2S_PORT, &pin_config);
  i2s_zero_dma_buffer(I2S_PORT);
  Serial.println("I2S OK");
}

static int audio_signal_get_data(size_t offset, size_t length, float *out_ptr) {
  for (size_t i = 0; i < length; i++) {
    out_ptr[i] = (float)sampleBuffer[offset + i] / 32768.0f;
  }
  return 0;
}

void oledShow(int peak, float red_score, float noise_score, bool led_on) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("=== Voice Control ===");
  display.setCursor(0, 14);
  display.print("Peak : ");
  display.println(peak);
  display.setCursor(0, 26);
  display.print("Red  : ");
  display.println(red_score, 2);
  display.setCursor(0, 38);
  display.print("Noise: ");
  display.println(noise_score, 2);
  display.setCursor(0, 52);
  display.println(led_on ? ">> LED ON  [RED] <<" : "   LED OFF");
  display.display();
}

void setup() {
  Serial.begin(115200);
  delay(500);

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  Wire.begin(21, 22);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED FAIL");
    while (1);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(10, 20);
  display.println("Starting...");
  display.display();
Serial.printf("Frame Size : %d\n", EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE);
Serial.printf("Frequency  : %d\n", EI_CLASSIFIER_FREQUENCY);
Serial.printf("Labels     : %d\n", EI_CLASSIFIER_LABEL_COUNT);

  setupI2S();

  display.clearDisplay();
  display.setCursor(10, 20);
  display.println("Say: RED");
  display.display();

  delay(500);
}

void loop() {
  size_t bytes_read = 0;

  i2s_read(I2S_PORT, (void*)i2sBuffer,
           SAMPLE_BUFFER_SIZE * sizeof(int32_t),
           &bytes_read, portMAX_DELAY);
  Serial.printf("bytes_read: %d, expected: %d\n", 
               bytes_read, SAMPLE_BUFFER_SIZE * sizeof(int32_t));
  int samples_read = bytes_read / sizeof(int32_t);

  for (int i = 0; i < samples_read; i++) {
    sampleBuffer[i] = (int16_t)(i2sBuffer[i] >> 14);
  }
  for (int i = samples_read; i < SAMPLE_BUFFER_SIZE; i++) {
    sampleBuffer[i] = 0;
  }

  int peak = 0;
  for (int i = 0; i < samples_read; i++) {
    int val = abs(sampleBuffer[i]);
    if (val > peak) peak = val;
  }
  Serial.printf("Mic peak: %d\n", peak);

  if (peak < 100) {
    Serial.println("Silent - skipping");
    oledShow(peak, 0.0f, 0.0f, false);
    delay(200);
    return;
  }

  signal_t signal;
  signal.total_length = SAMPLE_BUFFER_SIZE;
  signal.get_data     = &audio_signal_get_data;

  ei_impulse_result_t result = {0};
  if (run_classifier(&signal, &result, false) != EI_IMPULSE_OK) {
    Serial.println("Classifier error");
    return;
  }

  float red_score   = 0.0f;
  float noise_score = 0.0f;

  for (size_t i = 0; i < EI_CLASSIFIER_LABEL_COUNT; i++) {
    Serial.printf("  %s: %.2f\n",
      result.classification[i].label,
      result.classification[i].value);
    if (strcmp(result.classification[i].label, "red") == 0)
      red_score = result.classification[i].value;
    if (strcmp(result.classification[i].label, "noise") == 0)
      noise_score = result.classification[i].value;
  }

  bool led_on = (red_score > 0.70f);
  digitalWrite(LED_PIN, led_on ? HIGH : LOW);
  Serial.println(led_on ? ">>> LED ON!" : "LED OFF");

  oledShow(peak, red_score, noise_score, led_on);

  Serial.println("---");
  delay(200);
}