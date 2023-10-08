#include <Arduino.h>
#include <zShell.h>
#include <map>

zShell shell;

void setup()
{

  Serial.begin(115200);
  shell.init();
}


void loop()
{

  shell.handleSerialInput();
}
