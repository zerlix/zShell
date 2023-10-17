#include <zShell.h>
#include <zShellCommands.h> // Buildin Commands

// Konstruktor
zShell::zShell()
{
    command = "";
    init();
    return;
}


// Initialisierungsmethode
void zShell::init()
{
    addCommand("free", &free); 
    addCommand("reboot", &reboot); 
    addCommand("sysinfo", &sysinfo); 
    addCommand("help", &help);

    setupSerial();
    prompt();
    return;
}


// Serielle Konfiguration
void zShell::setupSerial()
{
    Serial.write(27);
    Serial.print("[2J"); // clear console

    Serial.write(27);
    Serial.print("[H"); // Set cursor 
}



// Behandlung der seriellen Eingabe
void zShell::handleSerialInput()
{
    if (Serial.available() > 0)
    {
        char receivedChar = Serial.read();
        if (receivedChar == '\n')
        {
            processInput();
        }
        else
        {
            handleCharacter(receivedChar);
        }
    }
}


// Zeichenverarbeitung
void zShell::handleCharacter(char receivedChar)
{
    Serial.print(receivedChar);
    if (inputIndex >= MAX_INPUT_LENGTH)
    {
        inputIndex = 0;
    }
    inputBuffer[inputIndex] = receivedChar;
    inputIndex++;
}



// Eingabe verarbeiten
void zShell::processInput()
{
    inputBuffer[inputIndex] = '\0';
    inputIndex = 0;

    Serial.println();
    if (parseCommand())
    {
        executeCommand();
    }
    else
    {
        Serial.println("Unbekannter Befehl");
        Serial.print("Verfügbare Kommandos: ");
        help(0,nullptr);
        prompt();
    }
}


// Befehl parsen
bool zShell::parseCommand()
{
    String inputString(inputBuffer); // Zeichenkette aus dem Puffer erstellen
    inputString.trim();              // Leerzeichen am Anfang und Ende entfernen

    int spaceIndex = inputString.indexOf(' ');

    if (spaceIndex >= 0)
    {
        // Befehl und Argumente aufteilen
        command = inputString.substring(0, spaceIndex);
        inputString = inputString.substring(spaceIndex + 1);

        // Argumente in ein Array aufteilen
        argc = 0;
        while (!inputString.isEmpty() && argc < MAX_ARGUMENTS_LENGTH)
        {
            spaceIndex = inputString.indexOf(' ');

            if (spaceIndex >= 0)
            {
                String arg = inputString.substring(0, spaceIndex);
                argv[argc] = new char[arg.length() + 1];
                strcpy(argv[argc], arg.c_str());
                inputString = inputString.substring(spaceIndex + 1);
            }
            else
            {
                String arg = inputString;
                argv[argc] = new char[arg.length() + 1];
                strcpy(argv[argc], arg.c_str());
                inputString = "";
            }

            argc++;
        }
    }
    else
    {
        command = inputString;
    }

    // Existiert das Kommando in der Map?
    command.trim();
    if (commandMap.find(command) != commandMap.end())
    {
        return true;
    }
    return false;
}


// Befehl ausführen
void zShell::executeCommand()
{
    commandMap[command](argc, argv);

    // Speicher freigeben
    for (int i = 0; i < argc; i++)
    {
        if (argv[i] != nullptr)
        {
            delete[] argv[i];
            argv[i] = nullptr;
        }
    }
    inputIndex = 0; // Eingabepuffer leeren.

    prompt();
}


// Methode zum Hinzufügen eines Befehls zur commandMap
void zShell::addCommand(const String &cmd, fptr function)
{
    commandMap[cmd] = function;
}

void zShell::listCommands()
{
    for (const auto &entry : commandMap)
    {
        Serial.print(entry.first);  // Befehlsname
        Serial.print(", ");
     }
}

