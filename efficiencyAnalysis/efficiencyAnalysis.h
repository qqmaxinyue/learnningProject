// Efficiency analysis.h: 标准系统包含文件的包含文件
// 或项目特定的包含文件。

#pragma once

#include <iostream>
#include <atomic>
#include <thread>
#include <mutex>
#include <fstream>
#include <queue>

enum class LogLevel
{
	DEBUG,
	INFO,
	WARNING,
	ERROR
};

class ILogInterface
{
public:
	//virtual ILogInterface getInstance() = 0;
	virtual void init(const std::string& path) = 0;

	virtual void log(LogLevel level, const std::string& logMsg) = 0;

};

class SyncLog : public ILogInterface
{
public:
	static SyncLog& getInstacne() {
		static SyncLog logImp;
		return logImp;
	};

	void init(const std::string& path) override;

	void log(LogLevel level, const std::string& logMsg) override;

	SyncLog(const SyncLog&) = delete;
	SyncLog& operator=(const SyncLog&) = delete;

private:
	SyncLog();

private:
	std::mutex m_logMutex;
	std::ofstream m_file;      // 日志文件流
};

class ASyncLog : public ILogInterface
{
public:
	static ASyncLog& getInstacne() {
		static ASyncLog logImp;
		return logImp;
	};

	void init(const std::string& path) override;

	void log(LogLevel level, const std::string& logMsg) override;

	ASyncLog(const ASyncLog&) = delete;
	ASyncLog& operator=(const ASyncLog&) = delete;

private:
	ASyncLog();

private:
	std::mutex m_logMutex;
	std::ofstream m_file;      // 日志文件流
	std::queue<std::string> m_logQueue;
};

// TODO: 在此处引用程序需要的其他标头。
