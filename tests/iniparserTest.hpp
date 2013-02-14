#ifndef INIPARSER_TEST_HPP
#define INIPARSER_TEST_HPP

#include <cppunit/TestFixture.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>
#include <cppunit/extensions/HelperMacros.h>
#include "../iniparser.hpp"

class iniparserTest : public CppUnit::TestFixture {
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
        CPPUNIT_ASSERT(ini->getString("", "name") == "bla");
        CPPUNIT_ASSERT(ini->getString("sec1", "name") == "kk");
        CPPUNIT_ASSERT(ini->getString("sec2", "name") == "asdf");
        CPPUNIT_ASSERT(ini->getString("sec2", "does not exist") == "");
    }

    void testGetBool()
    {
        CPPUNIT_ASSERT(ini->getBool("sec1", "bool") == false);
        CPPUNIT_ASSERT(ini->getBool("sec1", "none") == true);
    }

    void testGetInt()
    {
        CPPUNIT_ASSERT(ini->getInt("sec1", "id") == 123);
    }

    void testGetFloat()
    {
//        CPPUNIT_ASSERT(ini->getInt("sec2", "fl") == 1.3);
    }

    void testOperator()
    {
        iniparser ini2("test2.ini");
        CPPUNIT_ASSERT(ini->getString("sec2", "name") == "asdf");
        CPPUNIT_ASSERT(ini->getBool("sec2", "bla") == false); // doesn't exist
        *ini += ini2;
        CPPUNIT_ASSERT(ini->getString("sec2", "name") == "asdf");
        CPPUNIT_ASSERT(ini->getBool("sec2", "bl") == true);
    }

    static CppUnit::Test *suite()
    {
        CppUnit::TestSuite *suiteOfTests = new CppUnit::TestSuite("iniparserTest");
        suiteOfTests->addTest(new CppUnit::TestCaller<iniparserTest>("testGetString", &iniparserTest::testGetString));
        suiteOfTests->addTest(new CppUnit::TestCaller<iniparserTest>("testGetBool", &iniparserTest::testGetBool));
        suiteOfTests->addTest(new CppUnit::TestCaller<iniparserTest>("testGetInt", &iniparserTest::testGetInt));
        suiteOfTests->addTest(new CppUnit::TestCaller<iniparserTest>("testGetFloat", &iniparserTest::testGetFloat));
        suiteOfTests->addTest(new CppUnit::TestCaller<iniparserTest>("testOperator", &iniparserTest::testOperator));
        return suiteOfTests;
    }
};

#endif // INIPARSER_TEST_HPP
