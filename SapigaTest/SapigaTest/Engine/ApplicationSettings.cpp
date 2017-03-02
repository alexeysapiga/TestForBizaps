#include "ApplicationSettings.h"
#include <iostream>
#include <fstream>

const char* APPLICATION_SETTINGS_PATH = "../../config.ini";

ApplicationSettings* ApplicationSettings::instance_ = 0;
extern void showError(const string& message);

ApplicationSettings* ApplicationSettings::instance() {
    if (instance_ == 0)
        instance_ = new ApplicationSettings();

    return instance_;
}

float ApplicationSettings::getFloat(const string& key, float def) {
    auto i = variables_.find(key);
    if (i == variables_.end()) return def;

    float result = def;
    try {
        result = stof(i->second);
    } 
    catch (invalid_argument) {
        showError("Can't parse to float value = " + i->second);
    }
    catch (out_of_range) {
        showError("float value = " + i->second + " is out of range");
    }

    return result;
}

int ApplicationSettings::getInt(const string& key, int def) {
    auto i = variables_.find(key);
    if (i == variables_.end()) return def;

    int result = def;
    try {
        result = stoi(i->second);
    }
    catch (invalid_argument) {
        showError("Can't parse to int value = " + i->second);
    }
    catch (out_of_range) {
        showError("int value = " + i->second + " is out of range");
    }

    return result;
}

string ApplicationSettings::getString(const string& key, string def) {
    auto i = variables_.find(key);
    if (i == variables_.end()) return def;

    return i->second;
}

Vector3  ApplicationSettings::getVector3(const string& key, Vector3 def) {
    auto i = variables_.find(key);
    if (i == variables_.end()) return def;

    
    float x = def.x;
    float y = def.y;
    float z = def.z;
    sscanf_s(i->second.c_str(), "%f;%f;%f", &x, &y, &z);
    
    return Vector3(x, y, z);
}

ApplicationSettings::ApplicationSettings() {
    readFile();
}

void ApplicationSettings::readFile() {
    string line;
    ifstream myfile(APPLICATION_SETTINGS_PATH);
    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            if (line.length() > 0)
                ParseLine(line.c_str());
        }
        myfile.close();
    }
    else
    {
        showError("Can't open file " + string(APPLICATION_SETTINGS_PATH));
    }
}

void ApplicationSettings::ParseLine(const char* line) {
    char bufKey[64];
    char bufValue[64];
    int index = 0;
    int indexKey = 0;
    int indexValue = 0;
    bool keyParsed = false;
    while (line[index])
    {
        if (line[index] != ' ' && line[index] != ':')
        {
            if (keyParsed) {
                bufValue[indexValue++] = line[index];
            }
            else {
                bufKey[indexKey++] = line[index];
            }
        }

        if (line[index] == ':')
        {
            keyParsed = true;
        }
        index++;
    }

    bufKey[indexKey] = '\0';
    bufValue[indexValue] = '\0';

    if (strlen(bufKey) > 0 && strlen(bufValue) > 0)
        variables_[string(bufKey)] = bufValue;
}
