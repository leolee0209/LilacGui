#pragma once
#include <string>

#ifndef LOGGER_MACRO
#define LOGGER_MACRO
#define NOTE(TEXT) note(__FILE__, __LINE__, TEXT)
#define WARN(TEXT) warn(__FILE__, __LINE__, TEXT)
#define ERROR(TEXT) error(__FILE__, __LINE__, TEXT)
// #define NOTE(TEXT, STACKTRACE) note(__FILE__, __LINE__, TEXT, STACKTRACE)
// #define WARN(TEXT, STACKTRACE) warn(__FILE__, __LINE__, TEXT, STACKTRACE)
// #define ERROR(TEXT, STACKTRACE) error(__FILE__, __LINE__, TEXT, STACKTRACE)
#endif // LOGGER_MACRO

void note(const char *file, int line, std::string s, bool stacktrace = false);
void error(const char *file, int line, std::string s, bool stacktrace = false);
void warn(const char *file, int line, std::string s, bool stacktrace = false);
void note(const char *file, int line, char *s, bool stacktrace = false);
void error(const char *file, int line, char *s, bool stacktrace = false);
void warn(const char *file, int line, char *s, bool stacktrace = false);

void LoggerInit(std::string name = "", bool cut = true);
