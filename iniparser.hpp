#ifndef INIPARSER_HPP
#define INIPARSER_HPP

#include <fstream>
#include <ostream>
#include <string>
#include <map>
#include <algorithm>

class iniparser {
public:
    iniparser(const std::string &path);
    ~iniparser();
    iniparser &operator+=(const iniparser &rhs);
    
    std::string getString(const std::string &section, const std::string &key, std::string defaultValue = "") const;
    int getInt(const std::string &section, const std::string &key, int defaultValue = 0) const;
    float getFloat(const std::string &section, const std::string &key, float defaultValue = 0.f) const;
    bool getBool(const std::string &section, const std::string &key, bool defaultValue = false) const;

    std::ostream &dump(std::ostream &out) const;

private:
    // section, key, value
    std::map<std::string, std::map<std::string, std::string> > options;

    void insertSection(std::pair<std::string, std::map<std::string, std::string> > pair);
    std::string &trim(std::string &str) const;
    std::string &toLower(std::string &str) const;
};

iniparser operator+(const iniparser &rhs, const iniparser &lhs);
std::ostream &operator<<(std::ostream &out, const iniparser &rhs);

#endif // INIPARSER_HPP
