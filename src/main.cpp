#include <Arduino.h>
#include <zShell.h>
//#include <zShellCommands.h>
#include <map>

zShell shell;

// typedef void (*fptr)(int argc, char *argv); zShell.h
// std::map<String, fptr> commandMap;

void setup()
{
  String command = String("free");

  Serial.begin(115200);
  //commandMap["mem"] = &mem; -->  shell.init();
  //commandMap["free"] = &free; -- > shell.init();


  shell.init();
/*
  if (commandMap.find(command) != commandMap.end())
  {
    commandMap[command](0, nullptr);
  }
  else
  {
    Serial.println("Unbekannter Befehl");
  }
  */
}


void loop()
{

  shell.handleSerialInput();
}
