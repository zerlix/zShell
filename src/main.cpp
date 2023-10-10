#include <Arduino.h>
#include <zShell.h>
#include <map>

zShell shell;


// Einfaches Beispiel für ein Kommando
void myCommand(int argc, char *argv)
{

  Serial.println("Mein Commando");
}


void setup()
{

  Serial.begin(115200);
  shell.init(); // SHell initialisieren
  shell.addCommand("myCommand", &myCommand); // eigenes Kommando der "commandoMap" hinzufügrn
}


void loop()
{

  shell.handleSerialInput();
}
