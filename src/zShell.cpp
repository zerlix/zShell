#include <Arduino.h>
#include <zShell.h>
#include <zShellCommands.h>
#include <map>

std::map<String, fptr> commandMap;

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
    if (Serial.available() > 0)
    {
        char receivedChar = Serial.read();

        if (receivedChar == '\n')
        {
            inputBuffer[inputIndex] = '\0';
            inputIndex = 0;
            parseCommand();
        }
        else
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

void zShell::parseCommand()
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

        doCommand();
    }
    else
    {
        // Nur Befehl, keine Argumente
        command = inputString;
        doCommand();
    }
}

void zShell::doCommand() 
{
    Serial.println();
    command.trim();
    
    if (commandMap.find(command) != commandMap.end()) {
        // Führen Sie die Befehlsfunktion mit Standardargumenten aus
        commandMap[command](0, nullptr);
    }
    else {
        Serial.println("Unbekannter Befehl");
    }
    prompt();
}
