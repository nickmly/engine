#include "LogManager.h"
#include <fstream>
unique_ptr<LogManager> LogManager::instance(nullptr);
string LogManager::threshold;
LogManager::LogManager()
{

}


LogManager::~LogManager()
{

}

LogManager * LogManager::getInstance()
{
	if (instance.get() == nullptr) { // If the instance is null
		instance.reset(new LogManager()); // Reset instance to a new logmanager
	}
	return instance.get();
}

void LogManager::Init() 
{
	//Open the file stream and create a new log file (overwrite if it already exists)
	ofstream out;
	out.open("log.txt", ios::out);
	out.close();

	threshold = "NONE"; // Set the threshold to none by default
}

void LogManager::Trace(string & msg, const string & filename, const int line)
{
	string* type = new string("TRACE");
	Log(msg, *type, filename, line);
}

void LogManager::Error(string & msg, const string & filename, const int line)
{
	string* type = new string("ERROR");
	Log(msg, *type, filename, line);
}

void LogManager::Warn(string & msg, const string & filename, const int line)
{
	string* type = new string("WARN");
	Log(msg, *type, filename, line);
}

void LogManager::Info(string & msg, const string & filename, const int line)
{
	string* type = new string("INFO");
	Log(msg, *type, filename, line);
}

void LogManager::Log(string & msg, string & type, const string & filename, const int line)
{
	ofstream out;
	out.open("log.txt", ios::app | ios::out); // Open file for writing
	if(type == threshold || threshold == "NONE") // Only write to file if threshold is met or there is no threshold
		out << type.c_str() << ": " << msg.c_str() << " ("  << filename.c_str() << ": " << line << ")" << endl; // Append message to file with the message type
	out.flush(); // Flush output stream
	out.close(); // Close file
}
