#ifndef CONSOLE_H
#define CONSOLE_H
#include <string>

class Console {
    public:
        Console();

        static void clearConsole();
        static void waitForKeyPress();

        static int getValidatedInput(const std::string &prompt, const std::string &infoType);

        static std::string getValidatedStringInput(const std::string &prompt, const std::string &infoType);

        static std::string getInformation(const std::string infoRequired);

        static void showInfoMessage(const std::string &message);
        static void showInfoMessage(const char* message);

    private:
    
};

#endif // CONSOLE_H