#include "LLog.hpp"
#include <stdlib.h>
#include <fstream>
#include <iomanip>
#include <time.h>
#include <sstream>
#include <algorithm>
#include <iostream>
#include <thread>
#include <stacktrace>
#include <cstring>
#include <string>

using namespace std;

string folderPath = "";
string fileName = "log.txt";
string completePath = "";
bool cutFileName = true;
ios_base::openmode mode = ios_base::app | ios::out;

void logging(string level, string s, int line, const char *file, bool stacktrace)
{
    auto t = time(nullptr);
    tm tm;
    localtime_r(&t,&tm);

    ostringstream oss;
    oss << put_time(&tm, "%m/%d %Y %H-%M-%S");
    auto timeS = oss.str();

    char *fileNameOut = nullptr;
    if (cutFileName)
    {
        int pathLength = strlen(file);
        for (int i = pathLength - 1; i >= 0; i--)
        {
            if (file[i] == '\\')
            {
                if (i != pathLength - 1)
                {
                    fileNameOut = (char *)malloc(sizeof(char) * (pathLength - i));
                    if (fileNameOut)
                        strncpy(fileNameOut, &file[i + 1], (pathLength - i));
                }
                break;
            }
        }
    }
    else
    {
        fileNameOut = (char *)file;
    }

    string output;
    if (fileNameOut)
        output = string(fileNameOut) + string(":") + to_string(line) + " " + timeS + level + s + "\n";
    else
        output = string("fileName_NOT_LOADED") + string(":") + to_string(line) + " " + timeS + level + s + "\n";

    if (true)
    {
        ofstream of;
        of.open(completePath, mode);
        of << output;
        of.close();
    }
    if (true)
    {
        cout << output;
    }
    free(fileNameOut);
}

void logWrapper(string level, string s, int line, const char *file, bool stacktrace)
{
    thread t(logging, level, s, line, file, stacktrace);
    t.detach();
}

void note(const char *file, int line, string s, bool stacktrace)
{
    logWrapper(" NOTE: ", s, line, file, stacktrace);
}
void note(const char *file, int line, char *s, bool stacktrace)
{
    logWrapper(" NOTE: ", string(s), line, file, stacktrace);
}

void error(const char *file, int line, string s, bool stacktrace)
{
    logWrapper(" ERROR: ", s, line, file, stacktrace);
}
void error(const char *file, int line, char *s, bool stacktrace)
{
    logWrapper(" ERROR: ", string(s), line, file, stacktrace);
}

void warn(const char *file, int line, string s, bool stacktrace)
{
    logWrapper(" WARNING: ", s, line, file, stacktrace);
}
void warn(const char *file, int line, char *s, bool stacktrace)
{
    logWrapper(" WARNING: ", string(s), line, file, stacktrace);
}

void LoggerInit(string path, bool cut)
{
    // name is initialized to "", cut is initialized to true
    cutFileName = cut;
    completePath = path;
    ifstream inFile(completePath);
    int lineCount = count(istreambuf_iterator<char>(inFile),
                          istreambuf_iterator<char>(), '\n');
    if (lineCount > 200)
    {
        mode = ios::out;
    }
}