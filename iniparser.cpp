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
                insertSection(std::pair<std::string, std::map<std::string, std::string> >(currentSection, currentOptions));
                currentOptions.clear();

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
        insertSection(std::pair<std::string, std::map<std::string, std::string> >(currentSection, currentOptions));
        ifs.close();
    }
}

iniparser::~iniparser()
{
}

iniparser &iniparser::operator+=(const iniparser &rhs)
{
    // merge rhs into us (without overwriting existing entries)
    for (std::pair<std::string, std::map<std::string, std::string> > section : rhs.options)
        insertSection(section);
    return *this;
}

std::string iniparser::getString(const std::string &section, const std::string &key, std::string defaultValue) const
{
    auto sectionOptions = options.find(section);
    if (sectionOptions == options.end())
        return defaultValue;

    auto keyvaluePair = sectionOptions->second.find(key);
    if (keyvaluePair == sectionOptions->second.end())
        return defaultValue;

    return keyvaluePair->second;
}

int iniparser::getInt(const std::string &section, const std::string &key, int defaultValue) const
{
    return std::stoi(getString(section, key, std::to_string(defaultValue)));
}

float iniparser::getFloat(const std::string &section, const std::string &key, float defaultValue) const
{
    return std::stof(getString(section, key, std::to_string(defaultValue)));
}

bool iniparser::getBool(const std::string &section, const std::string &key, bool defaultValue) const
{
    std::string tmp = getString(section, key);
    if (tmp.empty())
        return defaultValue;

    tmp = toLower(tmp);
    if (tmp == "true" || tmp == "1" || tmp == "yes" || tmp == "y")
        return true;
    return false;
}

std::ostream &iniparser::dump(std::ostream &out) const
{
    for (std::pair<std::string, std::map<std::string, std::string> > section : options) {
        if(!section.first.empty()) // don't print "[]"
            out << "[" << section.first << "]" << std::endl;
        for (std::pair<std::string, std::string> keyval : section.second)
            out << keyval.first << " = " << keyval.second << std::endl;
        out << std::endl;
    }
    return out;
}

void iniparser::insertSection(std::pair<std::string, std::map<std::string, std::string> > pair)
{
    auto it = options.find(pair.first);
    if (it != options.end()) { // sections already exists -> merge
        it->second.insert(pair.second.begin(), pair.second.end());
    } else {
        options.insert(pair);
    }
}

std::string &iniparser::trim(std::string &str) const
{
    str = str.erase(0, str.find_first_not_of(" \n\r\t")); // ltrim
    return str.erase(str.find_last_not_of(" \n\r\t") + 1); // rtrim
}

std::string &iniparser::toLower(std::string &str) const
{
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}


// free functions
iniparser operator+(const iniparser &rhs, const iniparser &lhs)
{
    return iniparser(rhs) += lhs;
}

std::ostream &operator<<(std::ostream &out, const iniparser &rhs)
{
    return rhs.dump(out);
}
