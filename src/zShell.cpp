#include <Arduino.h>
#include <zShell.h>
#include <zShellCommands.h>
#include <map>


zShell::zShell()
{
    command = ""; // Anstatt NULL einen leeren String verwenden
    for (int i = 0; i < MAX_ARGUMENTS_LENGTH; i++)
    {
        arguments[i] = "";
    }
    init();
    return;
}

void zShell::init()
{
    commandMap["free"] = &free;
    commandMap["sysinfo"] = &sysinfo;

    Serial.write(27);
    Serial.print("[2J");

    Serial.write(27);
    Serial.print("[H");

    prompt();
    return;
}

void zShell::handleSerialInput()
{
    // falls Serielle eingabe vorhanden, lesen
    if (Serial.available() > 0)
    {
        char receivedChar = Serial.read();

        // Zeilenumbruch -> commando parsen und ausführen
        if (receivedChar == '\n')
        {
            inputBuffer[inputIndex] = '\0';
            inputIndex = 0;
            
            Serial.println();
            if (parseCommand())
            {
                doCommand();
            }
            else
            {
                Serial.println("Unbekannter Befehl");
                prompt();
            }
        }
        else // weitere zeichen einlesen
        {
            Serial.print(receivedChar);
            inputBuffer[inputIndex] = receivedChar;
            inputIndex++;
            
            if (inputIndex >= MAX_INPUT_LENGTH)
            {
                inputIndex = 0;
            }
        }
    }
}

bool zShell::parseCommand()
{
    String inputString(inputBuffer); // Zeichenkette aus dem Puffer erstellen
    int spaceIndex = inputString.indexOf(' ');

    if (spaceIndex >= 0)
    {
        // Befehl und Argumente aufteilen
        command = inputString.substring(0, spaceIndex);
        inputString = inputString.substring(spaceIndex + 1);
        int argc = 0;

        while (inputString.length() > 0 && argc < MAX_ARGUMENTS_LENGTH)
        {
            spaceIndex = inputString.indexOf(' ');
            if (spaceIndex >= 0)
            {
                arguments[argc] = inputString.substring(0, spaceIndex);
                inputString = inputString.substring(spaceIndex + 1);
            }
            else
            {
                arguments[argc] = inputString;
                inputString = "";
            }
            argc++;
        }
    }
    else
    {
        command = inputString;
    }

    // existiert das Kommando in der Map
    command.trim();
    if (commandMap.find(command) != commandMap.end())
    {
        return true;
    }
    return false;
}

// commando ausführen
void zShell::doCommand()
{
    commandMap[command](0, nullptr);
    prompt();
}


// Methode zum Hinzufügen eines Befehls zur commandMap
void zShell::addCommand(const String &cmd, fptr function)
{
    commandMap[cmd] = function;
}