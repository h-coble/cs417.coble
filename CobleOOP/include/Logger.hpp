#pragma once

#include<fstream>
#include<iostream>
#include<iomanip>
#include<string>


class Logger
{
    private:
        static Logger* instancePtr;
        std::ofstream outFile;
        std::string fileName;
        bool instanceFlag = false;

        void Shutdown()
        {
            if(outFile.is_open())
                outFile.close();
        }
        Logger()
        {
        }


    public:

        ~Logger()
        {
            Shutdown();
            instancePtr = nullptr;
        }

        void LogMessage(int severity, std::string service, std::string error)
        {
            if (outFile.is_open())
            {
                outFile << severity << "::" << service << "::" << error << std::endl;
            }
            else
                std::cerr << "ERROR: Log File isn't open; startup failed.\n";
        }

        Logger(const Logger& log) = delete;

        static Logger* getInstance()
        {
            
            if(instancePtr == nullptr)
            {
                instancePtr = new Logger();
                return instancePtr;
            }
            else
            {
                return instancePtr;
            }

        }

        void Startup()
        {
            while (true)
            {
                std::cout << "\nEnter the log file's name: ";
                std::getline(std::cin, fileName);

                outFile.open(fileName);

                if (outFile.is_open())
                    break;
                else
                    std::cerr << "ERROR: Could not open file with the given name, \"" << fileName << "\"\n";
            }
        }  
};
Logger* Logger ::instancePtr = nullptr;