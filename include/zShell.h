#ifndef ZSHELL
#define ZSHELL
#include <Arduino.h>
#include <map>

#define MAX_INPUT_LENGTH  64
#define MAX_ARGUMENTS_LENGTH 12

typedef void (*fptr)(int argc, char *argv);
extern std::map<String, fptr> commandMap;

class zShell
{
    private:
        char inputBuffer[MAX_INPUT_LENGTH];
        String command;
        String arguments[MAX_ARGUMENTS_LENGTH];
        int inputIndex = 0;
        
        inline void prompt(){Serial.print("zDisplay:~# "); }

    public:
        zShell();
        void init();
        void parseCommand();
        void doCommand();
        void handleSerialInput();
        
};
#endif