#include <cppunit/ui/text/TestRunner.h>
#include "iniparserTest.hpp"

int main()
{
    CppUnit::TextUi::TestRunner runner;
    runner.addTest(iniparserTest::suite());
    return !runner.run("", false);
}
