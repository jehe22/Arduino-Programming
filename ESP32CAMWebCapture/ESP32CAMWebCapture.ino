#include <WiFi.h>
#include <NetworkClient.h>
#include <NetworkServer.h>
#include "esp_camera.h"

// objek untuk server
NetworkServer server(80);

// HTTP header, num untuk jumlah data framebuffer, dan framebuffer untuk data sensor
const char HEADER1[34] = "HTTP/1.1 200 OK\r\nContent-Length: ";
const char HEADER2[50] = "\r\nContent-Type: image/jpeg\r\nConnection: close\r\n\r\n";
camera_fb_t* fb = NULL;
char num[9];

void setup() {
  // mengatur frekuensi clock CPU
  setCpuFrequencyMhz(80);

  // init esp sebagai Access Point WiFi
  WiFi.softAPbandwidth(WIFI_BW_HT20);
  WiFi.softAPConfig("192.168.1.1", "192.168.1.1", "255.255.255.0");
  WiFi.softAP("CONNECT", "123456789");

  // memulai network server
  server.begin();

  // mematikan brownout detector
  WRITE_PERI_REG(DR_REG_RTCCNTL_BASE + 0xd4, 0);

  // konfigurasi esp32cam
  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = 5;
  config.pin_d1 = 18;
  config.pin_d2 = 19;
  config.pin_d3 = 21;
  config.pin_d4 = 36;
  config.pin_d5 = 39;
  config.pin_d6 = 34;
  config.pin_d7 = 35;
  config.pin_xclk = 0;
  config.pin_pclk = 22;
  config.pin_vsync = 25;
  config.pin_href = 23;
  config.pin_sccb_sda = 26;
  config.pin_sccb_scl = 27;
  config.pin_pwdn = 32;
  config.pin_reset = -1;
  config.xclk_freq_hz = 20000000;
  config.frame_size = FRAMESIZE_UXGA;
  config.pixel_format = PIXFORMAT_JPEG;
  config.grab_mode = CAMERA_GRAB_LATEST;
  config.fb_location = CAMERA_FB_IN_PSRAM;
  config.jpeg_quality = 10;
  config.fb_count = 2;
  esp_camera_init(&config);

  // konfigurasi sensor kamera
  sensor_t * s = esp_camera_sensor_get();
  s->set_brightness(s, 0);     // -2 to 2
  s->set_contrast(s, 0);       // -2 to 2
  s->set_saturation(s, 0);     // -2 to 2
  s->set_special_effect(s, 0); // 0 to 6 (0 - No Effect, 1 - Negative, 2 - Grayscale, 3 - Red Tint, 4 - Green Tint, 5 - Blue Tint, 6 - Sepia)
  s->set_whitebal(s, 1);       // 0 = disable , 1 = enable
  s->set_awb_gain(s, 1);       // 0 = disable , 1 = enable
  s->set_wb_mode(s, 0);        // 0 to 4 - if awb_gain enabled (0 - Auto, 1 - Sunny, 2 - Cloudy, 3 - Office, 4 - Home)
  s->set_exposure_ctrl(s, 1);  // 0 = disable , 1 = enable
  s->set_aec2(s, 0);           // 0 = disable , 1 = enable
  s->set_ae_level(s, 1);       // -2 to 2
  s->set_aec_value(s, 600);    // 0 to 1200
  s->set_gain_ctrl(s, 1);      // 0 = disable , 1 = enable
  s->set_agc_gain(s, 5);       // 0 to 30
  s->set_gainceiling(s, (gainceiling_t) 2);  // 0 to 6
  s->set_bpc(s, 0);            // 0 = disable , 1 = enable
  s->set_wpc(s, 1);            // 0 = disable , 1 = enable
  s->set_raw_gma(s, 1);        // 0 = disable , 1 = enable
  s->set_lenc(s, 1);           // 0 = disable , 1 = enable
  s->set_hmirror(s, 0);        // 0 = disable , 1 = enable
  s->set_vflip(s, 0);          // 0 = disable , 1 = enable
  s->set_dcw(s, 1);            // 0 = disable , 1 = enable
  s->set_colorbar(s, 0);       // 0 = disable , 1 = enable
}

void loop() {
  // client menyambungkan ke gateway
  NetworkClient client = server.accept();

  if(client) {
    // ambil gambar satu kali kemudian kirim melalui http
    fb = esp_camera_fb_get();
    client.write(HEADER1, 33);
    sprintf(num, "%d", fb->len);
    client.write(num, strlen(num));
    client.write(HEADER2, 49);
    client.write((char*) fb->buf, fb->len);
    client.write("\r\n\r\n");

    // kosongkan framebuffer
    esp_camera_fb_return(fb);
  }
}
