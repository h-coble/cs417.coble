#include<iostream>

enum class ErrorLevel {SEVERE, ERROR, WARNING, INFO};
struct ErrorContext   {
      ErrorLevel errlevel;
      const char * logmsg;
   } logcontext;    // 


extern void SDAOSlogger(struct ErrorContext &logcontext);  

class loggerfacade
{
   private:
      static loggerfacade* instance;
      char * message;
      ErrorContext a;
      loggerfacade() {}

      void logError(ErrorContext ec) 
      {
        SDAOSlogger(ec);
      }
   public:
      static loggerfacade* getInstance() 
      {
        if (instance == nullptr) 
        {
            instance = new loggerfacade();
        }
        return instance;
      }

      void logSev()
      {
         a.logmsg = "Severe error";
         a.errlevel = ErrorLevel::SEVERE;
         logError(a);
      }

      void logErr()
      {
         a.logmsg = "Error";
         a.errlevel = ErrorLevel::ERROR;
         SDAOSlogger(a);
      }

      void logWarn()
      {
         a.logmsg = "Warning";
         a.errlevel = ErrorLevel::WARNING;
         SDAOSlogger(a);
      }

      void logInfo()
      {
         a.logmsg = "Info";
         a.errlevel = ErrorLevel::INFO;
         SDAOSlogger(a);
      }
};
loggerfacade* loggerfacade::instance = nullptr;

void SDAOSlogger(struct ErrorContext &logcontext)
{
   std::cout << logcontext.logmsg << "\n";
}
int main() {
    loggerfacade* logger = loggerfacade::getInstance();

    // Log messages using the simplified interface
    logger->logSev();
    logger->logErr();
    logger->logWarn();
    logger->logInfo();

    return 0;
}