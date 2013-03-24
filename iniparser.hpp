/* iniparser
 * Copyright (C) 2012 Giuliano Schneider <gs93@gmx.net>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef INIPARSER_HPP
#define INIPARSER_HPP

#include <fstream>
#include <ostream>
#include <string>
#include <map>
#include <list>
#include <algorithm>

class iniparser {
public:
    iniparser(const std::string &path);
    ~iniparser();
    /**
    * @brief adds the options from rhs (without overwriting)
    *
    * @param rhs
    *
    * @return 
    */
    iniparser &operator+=(const iniparser &rhs);
    
    std::list<std::string> getSections() const;
    bool sectionExist(const std::string &section) const;

    std::string getString(const std::string &section, const std::string &key, std::string defaultValue = "") const;
    int getInt(const std::string &section, const std::string &key, int defaultValue = 0) const;
    float getFloat(const std::string &section, const std::string &key, float defaultValue = 0.f) const;
    bool getBool(const std::string &section, const std::string &key, bool defaultValue = false) const;

    std::ostream &dump(std::ostream &out) const;

private:
    /**
    * @brief section, {key, value}
    */
    std::map<std::string, std::map<std::string, std::string> > options;

    void insertSection(std::pair<std::string, std::map<std::string, std::string> > pair);
    std::string &trim(std::string &str) const;
    std::string &toLower(std::string &str) const;
};

iniparser operator+(const iniparser &rhs, const iniparser &lhs);
std::ostream &operator<<(std::ostream &out, const iniparser &rhs);

#endif // INIPARSER_HPP
