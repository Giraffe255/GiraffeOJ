#pragma once
#include <cstdlib>
#include <stdint.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sys/time.h>


////////////////////////////////////
// 准备一个时间戳获取工具
///////////////////////////////////
class TimeUtil {
public:
    // 获取当前的时间戳
    static int64_t TimeStamp() {
        struct timeval tv;
        ::gettimeofday(&tv , NULL);// 获得精确度为秒级的时间戳
        return  tv.tv_sec;
    }
    static int64_t TimeStampMS() { // 获取精确度为毫秒级的时间戳
        struct timeval tv;
        ::gettimeofday(&tv , NULL);// 获得精确度为秒级的时间戳
        return  tv.tv_sec * 1000 + tv.tv_usec / 1000;
    }
};

///////////////////////////////////
// 打印日志的工具
///////////////////////////////////

// 日志输出格式：
// [I1554675265 util.hpp:29] hello
// [W1554675265 util.hpp:29] hello
// [E1554675265 util.hpp:29] hello
// [F1554675265 util.hpp:29] hello
// 日志使用方式：LOG(INFO) << "hello" << "\n";
// 日志级别：FATAL 致命的；ERROR 错误；WARNING 警告；INFO 提示.

enum Level {
    INFO,
    WARNING,
    ERROR,
    FATAL,
};

inline std::ostream& Log(Level level , const std::string& file_name , int line_num) {
    std::string prefix = "[";
    if (level == INFO) {
        prefix += "I";
    } else if (level == WARNING) {
        prefix += "W";
    } else if (level == ERROR) {
        prefix += "E";
    } else if (level == FATAL) {
        prefix += "F";
    }
    prefix += std::to_string(TimeUtil::TimeStamp());
    prefix += " ";
    prefix += file_name;
    prefix += ";";
    prefix += std::to_string(line_num);
    prefix += "] ";
    std::cout << prefix;
    return std::cout;
}

#define LOG(level) log(level , __FILE__ , __LINE__)

/////////////////////////////////////
// 准备文件相关工具类
/////////////////////////////////////

class FileUtil {
public:
    // 传入一个文件路径，把文件的所有内容都读出来放到 content 字符串中
    static bool Read(const std::string& file_path , std::string* content) {
        content->clear();
        std::ifstream file(file_path.c_str());
        if (!file.is_open()) {
            return false;
        } 
        std::string line;
        while(std::getline(file , line)) {
            *content += line + "\n";
        }
        file.close();
        return true;
    }

    static bool Write(const std::string& file_path , const std::string& content) {
        std::ofstream file(file_path.c_str());
        if (!file.is_open()) {
            return false;
        }
        file.write(content.c_str() , content.size());
        file.close();
        return true;
    }
};







