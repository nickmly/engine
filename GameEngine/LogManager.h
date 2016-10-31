#pragma once
#include <iostream>
#include <memory>
using namespace std;
class LogManager
{
private:
	LogManager();
	~LogManager();
	static unique_ptr<LogManager> instance;
	friend default_delete<LogManager>;
	void Log(string& msg, string& type, const string& filename, const int line);
public:
	static string threshold;
	static LogManager* getInstance();
	void Init();
	void Trace(string& msg, const string& filename, const int line);
	void Error(string& msg, const string& filename, const int line);
	void Warn(string& msg, const string& filename, const int line);
	void Info(string& msg, const string& filename, const int line);
};

