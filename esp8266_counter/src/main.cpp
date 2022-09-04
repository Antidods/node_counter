#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h> 
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
WiFiClient wifiClient;
boolean recievedFlag;
String strData, Link;

// ловим степ с накликиванием
#define BTN_PIN 5				// кнопка подключена сюда (BTN_PIN --- КНОПКА --- GND)
#include "GyverButton.h"
GButton butt1(BTN_PIN);

//Вводим параметры своей точки доступа WIFI 
const char *ssid = "xiaomi mi3";                           //Название точки доступа
const char *password = "chipolino";                           //Пароль точки доступа 
const char *host = "94.158.219.206:3000";       //Адрес нашего веб сервера
const int httpsPort = 80;                                    //Адрес порта для HTTPS= 443 или HTTP = 80

// Обьявление функции подключения к точкt доступа WIFI 
void setup() {
 delay(1000);                                                 //Ждем
 Serial.begin(9600);                                          //Настройка скорости UART
 WiFi.mode(WIFI_OFF);                                         //Перезапуск точки доступа
 delay(1000);                                                 //Ждем
 WiFi.mode(WIFI_STA);                                         //Настраиваем ESP в режиме клиента
 WiFi.begin(ssid, password);                                  //Подключаемся к точке доступа
 Serial.println("");
 Serial.print("Connecting");                                  //Пишем в UART что соединяемся
 // Ждем соединения
 while (WiFi.status() != WL_CONNECTED) {delay(500);
 Serial.print(".");}                                          //Пока пытаемся соединиться отправляем в UART точки
 Serial.println("");                                          //Если удачно подключились
 Serial.print("Connected to ");                               //Пишем в UART:
 Serial.println(ssid);                                        //Название точки доступа
 Serial.print("IP address: ");
 Serial.println(WiFi.localIP());                              //IP адрес назначенный нашему ESP
}

// Обьявление функции передачи данных
void transmit() {
 WiFiClientSecure httpsClient;                                //Обьявляем обьект класса WiFiClient
 Serial.println(host);                                        //Пишем в UART: адрес нашего веб сервера,
 httpsClient.setTimeout(15000);                               //Присваиваем значение паузы (15 секунд)
 delay(1000);                                                 //Ждем                                     
 Serial.print("HTTPS Connecting");                            //Пишем в UART: Соединяемся с нашим веб сервером
 int r=0;                                                     //Обьявляем переменную счетчика попыток подключения
 while((!httpsClient.connect(host, httpsPort)) && (r < 30))
 {delay(100);Serial.print(".");r++;}                          //Пока пытаемся соединиться с веб сервером отправляем в UART точки
 if(r==30) {Serial.println("Connection failed");}             //Если не получилось соединиться пишем в UART, что не получилось  
 else {Serial.println("Connected to web");}                   //Если получилось соединиться пишем в UART, что получилось  
 Link = "/sqladd";                                            //Формируем строку для GET запроса
 Serial.print("requesting URL: ");                            //Пишем в UART что отправляем GET запрос
 Serial.println(host+Link);                                   //Пишем в UART GET запрос
 httpsClient.print(String("GET ") + Link + " HTTP/1.1\r\n" +  
 "Host: " + host + "\r\n" + 
 "Connection: close\r\n\r\n");                                //Отправляем GET запрос через ESP
 Serial.println("request sent");                              //Пишем в UART что GET запрос отправлен
 while (httpsClient.connected())                              //Ловим ответ веб сервера
 {String line = httpsClient.readStringUntil('\n');
 if (line == "\r") {Serial.println("headers received");break;}}
 Serial.println("reply was:");                                //Пишем в UART что веб сервер ответил
 Serial.println("==========");                                //Для красоты выводим в UART разграничивающую линию
 String line;                                                 //Формируем строку для ответа веб сервера
 while(httpsClient.available()){                              //Ловим строку от веб сервера
 line = httpsClient.readStringUntil('\n');                    
 Serial.println(line);}                                       //Пишем в UART строку от веб сервера
 Serial.println("==========");                                //Для красоты выводим в UART разграничивающую линию
 Serial.println("closing connection");}                       //Пишем в UART, что закрыли соединение с веб сервером
 
//Основная функция
void loop() {
    // два клика
   butt1.tick();  
   if (butt1.isDouble()) {
    Serial.println("double click");
    transmit();
   }

}