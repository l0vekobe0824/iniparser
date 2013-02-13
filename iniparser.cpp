#include "iniparser.hpp"

iniparser::iniparser(const std::string &path) : options()
{
    std::ifstream ifs(path.c_str());
    if (ifs.is_open()) {
        std::string line;
        std::string currentSection = "";
        std::map<std::string, std::string> currentOptions;
        while (ifs.good()) {
            std::getline(ifs, line);
            line = trim(line);

            // it's a comment
            if (line.front() == '#')
                continue;

            // it's a section
            if (line.front() == '[' && line.back() == ']') {
                // insert options from old sections into map
                options.insert(std::pair<std::string, std::map<std::string, std::string> >(currentSection, currentOptions));

                currentSection = line.substr(1, line.length() - 2); // remove [ and ]
                currentSection = trim(currentSection);
                continue;
            }
            
            size_t pos = line.find_first_of("=");
            if (pos == std::string::npos) // no key = value pair
                continue;

            std::string key = line.substr(0, pos), value = line.substr(pos + 1);
            key = toLower(trim(key));
            value = trim(value);
            currentOptions.insert(std::pair<std::string, std::string>(key, value));
        }
        options.insert(std::pair<std::string, std::map<std::string, std::string> >(currentSection, currentOptions));
        ifs.close();
    }
}

iniparser::~iniparser()
{
}

std::string iniparser::getString(const std::string &section, const std::string &key, std::string defaultValue)
{
    auto sectionOptions = options.find(section);
    if (sectionOptions == options.end())
        return defaultValue;

    auto keyvaluePair = sectionOptions->second.find(key);
    if (keyvaluePair == sectionOptions->second.end())
        return defaultValue;

    return keyvaluePair->second;
}

int iniparser::getInt(const std::string &section, const std::string &key, int defaultValue)
{
    return std::stoi(getString(section, key, std::to_string(defaultValue)));
}

float iniparser::getFloat(const std::string &section, const std::string &key, float defaultValue)
{
    return std::stof(getString(section, key, std::to_string(defaultValue)));
}

bool iniparser::getBool(const std::string &section, const std::string &key, bool defaultValue)
{
    std::string tmp = getString(section, key);
    if (tmp.empty())
        return defaultValue;

    tmp = toLower(tmp);
    if (tmp == "true" || tmp == "1" || tmp == "yes" || tmp == "y")
        return true;
    return false;
}

std::string &iniparser::trim(std::string &str)
{
    str = str.erase(0, str.find_first_not_of(" \n\r\t")); // ltrim
    return str.erase(str.find_last_not_of(" \n\r\t") + 1); // rtrim
}

std::string &iniparser::toLower(std::string &str)
{
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}
