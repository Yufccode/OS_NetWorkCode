

#pragma once

// 日志是有日志级别的
// 不同的级别代表不同的响应方式
#define DEBUG 0
#define NORMAL 1  // 正常的
#define WARNING 2 // 警告
#define ERROR 3   // 错误
#define FATAL 4   // 致命的

#include <string>
#include <iostream>
#include <stdarg.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

// 完整的日志功能
// 至少：日志等级、时间、内容、支持用户自定义

const char *gLevelMap[] = {
    "DEBUG",
    "NORMAL",
    "WARNING",
    "ERROR",
    "FATAL"};

#define LOGFILE "./threadpool.log"

void logMessage(int level, const char *format, ...)
{
#ifdef __DEBUG_SHOW
    if (level == DEBUG)
        return;
#else
    // va_list ap; //va_list -> char*
    // va_start(ap, format);
    // while()
    // int x = va_arg(ap, int);
    // va_end(ap);
    char stdBuffer[1024]; // 标准部分
    time_t timestamp = time(nullptr);
    // struct tm *tmlocaltime = localtime(&timestamp);
    // ...

    snprintf(stdBuffer, sizeof stdBuffer, "[%s] [%ld] ", gLevelMap[level], timestamp);

    char logBuffer[1024]; // 自定义部分
    va_list args;
    va_start(args, format); // 初始化一下
    // vprintf(format, args); //格式化到stdout中
    vsnprintf(logBuffer, sizeof logBuffer, format, args); // 可以直接格式化到字符串中
    // 这样v开头的函数有4个，要用的话可以man一下
    // printf("%s", logBuffer);
    va_end(args);

#endif

    FILE *fp = fopen(LOGFILE, "a");
    fprintf(stdout, "%s%s\n", stdBuffer, logBuffer);
    fflush(stdout);
    fclose(fp);
}