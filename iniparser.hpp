#ifndef INIPARSER_HPP
#define INIPARSER_HPP

#include <fstream>
#include <string>
#include <map>
#include <algorithm>

class iniparser {
public:
    iniparser(const std::string &path);
    ~iniparser();
    
    std::string getString(const std::string &section, const std::string &key, std::string defaultValue = "");
    int getInt(const std::string &section, const std::string &key, int defaultValue = 0);
    float getFloat(const std::string &section, const std::string &key, float defaultValue = 0.f);
    bool getBool(const std::string &section, const std::string &key, bool defaultValue = false);

private:
    // section, key, value
    std::map<std::string, std::map<std::string, std::string> > options;

    void insertSection(std::pair<std::string, std::map<std::string, std::string> > pair);
    std::string &trim(std::string &str);
    std::string &toLower(std::string &str);
};

#endif // INIPARSER_HPP
