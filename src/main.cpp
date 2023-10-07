#include <Arduino.h>
#include <zShell.h>

zShell shell;

void setup() {
  Serial.begin(115200);
  shell.init();
}

void loop() 
{

  shell.handleSerialInput();

  
 
}

