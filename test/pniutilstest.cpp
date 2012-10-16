//libddf unit test system

#include<iostream>
#include<fstream>
#include<string>
#include<vector>

#include<cppunit/extensions/HelperMacros.h>
#include<cppunit/TestCaller.h>
#include<cppunit/TestResult.h>
#include<cppunit/TestRunner.h>
#include<cppunit/XmlOutputter.h>
#include<cppunit/TextTestProgressListener.h>
#include<cppunit/ui/text/TextTestRunner.h>
#include<cppunit/extensions/TestFactoryRegistry.h>

#include<cppunit/ui/qt/TestRunner.h>


int main(int argc,char **argv){
    //setup the test runner
    CppUnit::TextTestRunner runner;
    CppUnit::TextTestProgressListener progress;
    CppUnit::TestFactoryRegistry &registry = CppUnit::TestFactoryRegistry::getRegistry();
    
    runner.addTest(registry.makeTest());
    runner.eventManager().addListener(&progress);

    std::ofstream os("unittest.xml");
    runner.setOutputter(new CppUnit::XmlOutputter(&runner.result(),os));
    
    bool result = runner.run();

    return result ? 0 : 1;
}

