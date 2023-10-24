#include "Logger.hpp"

enum sevLevel { WARNING = 0, ERROR, UNRECOVERABLE };

int main()
{
	
	Logger* log = Logger ::getInstance();
	log->Startup();
	log-> LogMessage(WARNING,"Input","CAPS LOCK IS ON");

	Logger* secondLog = Logger ::getInstance();

	secondLog->LogMessage(UNRECOVERABLE, "HELP", "AAAAA");

	std::cout << "Logger 1: " << log << std::endl;
	std::cout << "Logger 2: " << secondLog << std::endl;

	bool same = (secondLog == log);
	delete log;
	if (!same)
		return 0;
	else
		return -1;
}