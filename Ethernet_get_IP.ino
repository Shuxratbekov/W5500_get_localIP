#include "SPI.h"
#include "Ethernet.h"

EthernetClient client;

// Задаём MAC-адрес устройству. Главное, чтобы в сети не было уже зарегистрированно устройство с таким адресом
//  Задаём статический IP-адрес на тот случай, если динамическое присвоение адреса даст сбой
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(10, 10, 10, 80);
IPAddress myDns(1, 1, 1, 1);
IPAddress gateway(10,10,10,1);
byte subnet[] = {255, 255, 248, 0};

void setup() {
  Serial.begin(9600);
  Serial.println("Initialize Ethernet with DHCP:");

  //  Если соединение с динамической адресацией не было установлено, то
  if (Ethernet.begin(mac) == 0) {
    //  Выводим сообщение об этом в монитор последовательного порта и
    Serial.println("Failed to configure Ethernet using DHCP");
    //  проверяем наличие самого Shield'а
    if (Ethernet.hardwareStatus() == EthernetNoHardware) {
      //  Если Shield не найден, то выводим соответствующее сообщение в монитор порта
      Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :( ");
      //  Ничего больше не выполняется
      while (true) {
        delay(1); // do nothing, no point running without Ethernet hardware
      }
    }
    //  Проверяем наличие соединения
    if (Ethernet.linkStatus() == LinkOFF) {
      //  Если соеднинение не установлено, то выводим соответствующее сообщение в монитор порта
      Serial.println("Ethernet cable is not connected.");
    }
    // Пробуем установить соединение, используя статический IP-адрес
    Ethernet.begin(mac, ip, myDns, gateway, subnet);
  }
  //  Если соединение с динамической адресацией было установлено, то
  else {
    Ethernet.begin(mac, ip, myDns, gateway, subnet);
    Serial.print("  DHCP assigned IP ");
    Serial.println(Ethernet.localIP());
  }
}

void loop() {}