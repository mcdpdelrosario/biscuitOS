#include <myWifi.h>

myWifi wifiNow("yshie","88888888","192.168.1.7","8000"); //initialization

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  wifiNow.wifiInit();
  wifiNow.wifiListen();
}

void loop() {
  wifiNow.wifiReceive();
  //wifiNow.sendTry();
  // put your main code here, to run repeatedly:

}
