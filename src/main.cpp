#include <Arduino.h>
#include <DHT.h>
#include <Wire.h> 
// библиотека для монитора (в моем проекте используется SSD1306):
// для монитора SH1106 впишите #include "SH1106.h" 
#include "SSD1306.h" 

#define DHTPIN 5       // контакт, к которому подключен DHT11
#define DHTTYPE DHT11     // DHT 11
//#define DHTTYPE DHT21   // DHT 21 (AM2301)
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321


// инициализация OLED-дисплея:
SSD1306 display(0x3c, D3, D5);
// SH1106 display(0x3c, D3, D5);

// инициализация датчика DHT11: 
DHT dht(DHTPIN, DHTTYPE);

void setup(){
  // с инициализацией UI будет инициализирован и дисплей: 
  display.init();
  // переворачивает дисплей на 180 градусов по вертикали
  display.flipScreenVertically();
  // установка шрифта
  display.setFont(ArialMT_Plain_16);
  // выравние текста
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  //  инициализация DHT
  dht.begin();
}

void loop(){
  // считывание температуры и влажности занимает около 250 мс; 
  // кроме того, данные от датчика могут запаздывать 
  // примерно на 2 секунды (это очень медленный датчик): 
  float h = dht.readHumidity();
  // считываем температуру в градусах Цельсия:
  float t = dht.readTemperature();
  // считываем температуру в градусах Фаренгейта:
  float f = dht.readTemperature(true);

  // проверяем, прочлись ли данные, и если нет,
  // то выходим и пробуем снова: 
  if (isnan(h) || isnan(t) || isnan(f)){
    display.clear();  //  очищаем дисплей
    display.drawString(5,0, "Failed DHT");
                         // "Не удалось прочесть данные от датчика DHT"
    return;
  }
  display.clear();
  display.drawString(0, 0, "Humidity: " + String(h) + "%\t"); 
                        // "Влажность: "
  display.drawString(0, 16, "Temp: " + String(t) + "C"); 
                        // "Температура: "
  display.drawString(0, 32, "Temp: " + String(f) + "F"); 
                        // "Температура: "
  display.display();
  delay(2000);
}