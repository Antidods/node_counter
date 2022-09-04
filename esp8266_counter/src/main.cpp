#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h> 
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
// WiFiClient wifiClient;
String Link;

#define BTN_PIN 5				// кнопка подключена сюда (BTN_PIN --- КНОПКА --- GND)
#include "GyverButton.h"
GButton butt1(BTN_PIN);

// void setDebounce(uint16_t debounce);        // установка времени антидребезга (по умолчанию 80 мс)
// void setTimeout(uint16_t timeout);          // установка таймаута удержания (по умолчанию 300 мс)
// void setClickTimeout(uint16_t timeout);      // установка таймаута между кликами (по умолчанию 500 мс)  
// void setStepTimeout(uint16_t step_timeout); // установка таймаута между инкрементами (по умолчанию 400 мс)  
// void setType(uint8_t type);     // установка типа кнопки (HIGH_PULL - подтянута к питанию, LOW_PULL - к gnd)  
// void setDirection(uint8_t dir); // установка направления (разомкнута/замкнута по умолчанию - NORM_OPEN, NORM_CLOSE)  
  
// void setTickMode(uint8_t tickMode); // (MANUAL / AUTO) ручной или автоматический опрос кнопки функцией tick()  
// // MANUAL - нужно вызывать функцию tick() вручную                            
// // AUTO - tick() входит во все остальные функции и опрашивается сама
  
// void tick();               // опрос кнопки  
// void tick(boolean state);  // опрос внешнего значения (0 нажато, 1 не нажато) (для матричных, резистивных клавиатур и джойстиков)
  
// boolean isPress();    // возвращает true при нажатии на кнопку. Сбрасывается после вызова
// boolean isRelease();  // возвращает true при отпускании кнопки. Сбрасывается после вызова
// boolean isClick();    // возвращает true при клике. Сбрасывается после вызова
// boolean isHolded();   // возвращает true при удержании дольше timeout. Сбрасывается после вызова
// boolean isHold();     // возвращает true при нажатой кнопке, не сбрасывается
// boolean state();      // возвращает состояние кнопки
// boolean isSingle();   // возвращает true при одиночном клике. Сбрасывается после вызова
// boolean isDouble();   // возвращает true при двойном клике. Сбрасывается после вызова
// boolean isTriple();   // возвращает true при тройном клике. Сбрасывается после вызова
  
// boolean hasClicks();  // проверка на наличие кликов. Сбрасывается после вызова
// uint8_t getClicks();  // вернуть количество кликов
// uint8_t getHoldClicks();// вернуть количество кликов, предшествующее удерживанию
  
// boolean isStep();     // возвращает true по таймеру setStepTimeout, смотри пример
// void resetStates();   // сбрасывает все is-флаги и счётчики

const char *ssid = "xiaomi mi3";
const char *password = "chipolino";
const char *host = "94.158.219.206";

void setup() {
   delay(1000);
   Serial.begin(9600);
   WiFi.mode(WIFI_OFF);
   delay(1000);
   WiFi.mode(WIFI_STA);
   WiFi.begin(ssid, password);
   Serial.println("");
   Serial.print("Connecting");
   while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
}
   Serial.println("");
   Serial.print("Connected to ");
   Serial.println(ssid);
   Serial.print("IP address: ");
   Serial.println(WiFi.localIP());
}

// Обьявление функции передачи данных
void transmit() {
   WiFiClient httpClient;
   const int httpPort = 3000;
   if (!httpClient.connect(host, httpPort)) {
      Serial.println("connection failed");
      return;
   }
   
   String url = "/sqladd";
   Serial.print("Requesting URL: ");
   Serial.print("http://");
   Serial.print(host);
   Serial.print(url);
   httpClient.print(String("GET ") + url + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Connection: close\r\n\r\n");
   unsigned long timeout = millis();
   while (httpClient.available() == 0) {
      if (millis() - timeout > 5000)
      { Serial.println(">>> httpClient Timeout !");
      httpClient.stop(); return; } 
   }
   while (httpClient.available()){
      String line = httpClient.readStringUntil('\r'); Serial.print(line);
   }
   Serial.println();
   Serial.println("closing connection");
 }
 
void loop() {
    // два клика
   butt1.tick();  
   if (butt1.isDouble()) {
      Serial.println("===============================");
      Serial.println("double click");
      Serial.println("===============================");
      transmit();
      Serial.println("===============================");
   }

}