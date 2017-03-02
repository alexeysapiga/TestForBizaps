#ifndef APPLICATION_SETTINGS_H
#define APPLICATION_SETTINGS_H

#include <string>
#include <map>
#include "Math/Vector3.h"

using namespace std;

class ApplicationSettings {
public:
    static ApplicationSettings* instance();

    float    getFloat(const string& key, float def = 0.0f);
    int      getInt(const string& key, int def = 0);
    string   getString(const string& key, string def = "");
    Vector3  getVector3(const string& key, Vector3 def = Vector3());
private:
    void ParseLine(const char* line);
    void readFile();
    static ApplicationSettings* instance_;
    ApplicationSettings();
    map<string, string> variables_;
};

#endif
