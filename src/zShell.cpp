#include <Arduino.h>
#include <zShell.h>
#include <zShellCommands.h>

std::map<String, fptr> commandMap;

/**
 * @brief *commands und *arguments 
 * auf NULL initialisieren, um sicherzustellen, dass sie nicht auf zufällige Speicherbereiche zeigen.
 **/
zShell::zShell()
{
    command = NULL;
    for (int i = 0; i < MAX_ARGUMENTS_LENGTH; i++)
    {
        arguments[i] = NULL;
    }
    init();
    return; 
}


/**
 * @brief: init
 **/
void zShell::init()
{
    commandMap["mem"] = &mem;
    commandMap["free"] = &free;

    Serial.write(27);
    Serial.print("[2J"); // Escape-Sequenz für das Löschen des Bildschirms
    
    Serial.write(27);
    Serial.print("[H");  // Escape-Sequenz für das Setzen des Cursors auf (0,0)

    //Serial.print("zDisplay:~# "); // prompt ausgeben
    prompt();
    return;
}



/**
 * @brief: liest, falls vorhanden, eingabe aus dem Seriellen Buffer
 **/
void zShell::handleSerialInput()
{
    if (Serial.available() > 0) // TODO: While() ????
    {
        char receivedChar = Serial.read(); // zeichen lesen

        if (receivedChar == '\n')
        {
            inputBuffer[inputIndex] = '\0'; // Null-terminieren, um eine Zeichenkette zu erstellen
            inputIndex = 0; // Zurücksetzen des Eingabe-Index
            parseCommand();
            //Serial.println(" ");
        }
        else
        {
            Serial.print(receivedChar);
            inputBuffer[inputIndex] = receivedChar;
            inputIndex++;
            if (inputIndex >= MAX_INPUT_LENGTH)
            {
                // Pufferüberlauf verhindern
                inputIndex = 0;
            }
        }   
    }
}


/**
 * @brief parse den inputBuffer (Command/Arguments)
 **/
void zShell::parseCommand()
{
    char *commandToken = strtok(inputBuffer, " "); // Befehl (erstes Token)
    
    int argc = 0; // Anzahl der Argumente

    // Zerlege die Zeichenkette in Tokens
    while (commandToken != NULL)
    {
        if (argc == 0) {
            command = commandToken; // Das erste Token ist der Befehl
        } else if (argc < MAX_ARGUMENTS_LENGTH) {
            arguments[argc - 1] = commandToken; // Argumente (ignoriere das erste Token)
        } else {
            Serial.println("Zu viele Argumente!");
            return;
        }
        argc++;
        commandToken = strtok(NULL, " "); // Nächstes Token
    }
    
    doCommand();
}



/**
 * @brief checkt command und führt passende funktion aus
 **/
void zShell::doCommand() 
{
    Serial.println(command);
    String cmd = String(command);
    cmd.trim();
    
    if (commandMap.find(cmd) != commandMap.end()) {
        commandMap[cmd](0, nullptr);
    }
    else {
        Serial.println("Unbekannter Befehl");
    }
    prompt();
}
