#ifndef ZSHELL
#define ZSHELL
#include <Arduino.h>
#include <map>


#define MAX_INPUT_LENGTH  64
#define MAX_ARGUMENTS_LENGTH 12

typedef void (*fptr)(int argc, char *argv[]);

class zShell
{
private:
    int inputIndex = 0;
    int argc = 0;
    char* argv[MAX_ARGUMENTS_LENGTH];
    char inputBuffer[MAX_INPUT_LENGTH];
    
    String command;
    String ErrorMsg;
    
    std::map<String, fptr> commandMap;

    inline void prompt() { Serial.print("zDisplay:~# "); }

public:
    zShell();
    void init();
    void setupSerial();
    void handleSerialInput();
    void handleCharacter(char receivedChar);
    void processInput();
    bool parseCommand();
    void executeCommand();
    void addCommand(const String& cmd, fptr function);
    void listCommands();
};
#endif
