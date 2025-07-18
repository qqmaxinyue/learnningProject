#include "efficiencyAnalysis.h"

#include <ctime>
#include <sstream>
#include <iomanip>

void SyncLog::init(const std::string& path)
{
    std::lock_guard<std::mutex> lock(m_logMutex);
    m_file.open(path, std::ios::out | std::ios::app);
}

void SyncLog::log(LogLevel level, const std::string& logMsg)
{
    std::lock_guard<std::mutex> lock(m_logMutex);

    // 获取当前时间
    auto now = std::chrono::system_clock::now();
    auto now_time_t = std::chrono::system_clock::to_time_t(now);
    auto now_tm = *std::localtime(&now_time_t);

    // 格式化时间
    std::ostringstream time_stream;
    time_stream << std::put_time(&now_tm, "%Y-%m-%d %H:%M:%S");

    // 格式化日志级别
    std::string level_str;
    switch (level) {
    case LogLevel::DEBUG: level_str = "DEBUG"; break;
    case LogLevel::INFO: level_str = "INFO"; break;
    case LogLevel::WARNING: level_str = "WARNING"; break;
    case LogLevel::ERROR: level_str = "ERROR"; break;
    }

    // 获取线程ID
    std::ostringstream thread_stream;
    thread_stream << std::this_thread::get_id();

    // 构造完整日志消息
    std::ostringstream log_stream;
    log_stream << "[" << time_stream.str() << "] "
        << "[" << thread_stream.str() << "] "
        << "[" << level_str << "] "
        << logMsg << "\n";

    // 输出到控制台和文件
    std::cout << log_stream.str();
    if (m_file.is_open()) {
        m_file << log_stream.str();
        m_file.flush(); // 确保及时写入
    }
}