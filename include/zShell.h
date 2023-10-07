#ifndef ZSHELL
#define ZSHELL

#define MAX_INPUT_LENGTH  64
#define MAX_ARGUMENTS_LENGTH 12

class zShell
{
    private:
        char inputBuffer[MAX_INPUT_LENGTH];
        char *command;
        char *arguments[MAX_ARGUMENTS_LENGTH];
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