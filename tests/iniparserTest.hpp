#ifndef INIPARSER_TEST_HPP
#define INIPARSER_TEST_HPP

#include <cxxtest/TestSuite.h>
#include "../iniparser.hpp"

class iniparserTest : public CxxTest::TestSuite {
private:
    iniparser *ini;

    iniparserTest(const iniparserTest &);
    iniparserTest &operator=(const iniparserTest &);

public:
    iniparserTest() : ini(0) { }
    ~iniparserTest() { }

    void setUp()
    {
        ini = new iniparser("test.ini");
    }

    void tearDown()
    {
        delete ini;
    }

    void testGetString()
    {
        TS_ASSERT_EQUALS(ini->getString("", "name"), "bla");
        TS_ASSERT_EQUALS(ini->getString("sec1", "name"), "kk");
        TS_ASSERT_EQUALS(ini->getString("sec2", "name"), "asdf");
        TS_ASSERT_EQUALS(ini->getString("sec2", "does not exist"), "");
    }

    void testGetBool()
    {
        TS_ASSERT(!ini->getBool("sec1", "bool"));
        TS_ASSERT(ini->getBool("sec1", "none"));
    }

    void testGetInt()
    {
        TS_ASSERT_EQUALS(ini->getInt("sec1", "id"), 123);
    }

    void testGetFloat()
    {
        TS_ASSERT_DELTA(ini->getFloat("sec2", "fl"), 1.3, 0.0001);
    }

    void testOperator()
    {
        iniparser ini2("test2.ini");
        TS_ASSERT_EQUALS(ini->getString("sec2", "name"), "asdf");
        TS_ASSERT_EQUALS(ini->getBool("sec2", "bla"), false); // doesn't exist
        *ini += ini2;
        TS_ASSERT_EQUALS(ini->getString("sec2", "name"), "asdf");
        TS_ASSERT_EQUALS(ini->getBool("sec2", "bl"), true);
    }
};

#endif // INIPARSER_TEST_HPP
