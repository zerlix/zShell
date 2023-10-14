#include <Arduino.h>
#include <zShell.h>
#include <map>

zShell shell;


// Einfaches Beispiel für ein Kommando
void cmd(int argc, char *argv[])
{
    Serial.println(argc);

    if (argc > 0)
    {
        Serial.println("Hallo: " + String(argv[0]));
    }
    else
    {
        Serial.println("Mein Commando");
    }

    
}


void setup()
{
  Serial.begin(115200);
  shell.init(); // SHell initialisieren
  shell.addCommand("cmd", &cmd); // eigenes Kommando der "commandoMap" hinzufügen
}


void loop()
{
  shell.handleSerialInput();
}
