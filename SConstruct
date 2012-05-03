#load python modules
import os.path as path
import platform
import os

###================================================================================
#Function to assemble library filenames depending on the operating system for
#which the library is built.
class LibFileNames(object):
    def __init__(self,libname,version,soversion):
        self.libname = libname
        self.version = version
        self.soversion = soversion
    
    def full_name(self,env):
        rstr = env["LIBPREFIX"]+self.libname
        if os.name == "posix":
            rstr += env["SHLIBSUFFIX"]+"."+self.soversion+"."+self.version
        if os.name == "nt":
            rstr += "."+self.soversion+"."+self.version+env["SHLIBSUFFIX"]
            
        return rstr
    
    def so_name(self,env):
        rstr = env["LIBPREFIX"]+self.libname
        if os.name == "posix":
            rstr += env["SHLIBSUFFIX"]+"."+self.soversion
        if os.name == "nt":
            rstr += "."+self.soversion+env["SHLIBSUFFIX"]
            
        return rstr
    
    def link_name(self,env):
        rstr = env["LIBPREFIX"]+self.libname+env["SHLIBSUFFIX"]
        return rstr
#==================================================================================

debug = ARGUMENTS.get("DEBUG",0)


var = Variables('BuildConfig.py')
if os.name == "nt":
	var.Add(PathVariable("PREFIX","set installation prefix",
                         "C:\\Program Files\\libpniutils",
                         PathVariable.PathAccept))
elif os.name=="posix":
	var.Add(PathVariable("PREFIX","set installation prefix","/usr",
                         PathVariable.PathAccept))

if os.name == "nt":
	var.Add(PathVariable("BOOSTPREFIX",
            "set the installation prefix for boost",
            "C:\\Program Files\\boost",PathVariable.PathAccept))
elif os.name == "posix":	
	var.Add(PathVariable("BOOSTPREFIX","set the installation prefix for boost",
                         "/usr"))

#this are variables which should not be used by a user
var.Add("VERSION","library version","0.0.0")
var.Add("LIBNAME","library name","pniutils")
var.Add("SOVERSION","SOVersion of the library (binary interface version)","0")
var.Add("MAINTAINER","package maintainer for the project","Eugen Wintersberger")
var.Add("MAINTAINER_MAIL","e-mail of the package maintainer","eugen.wintersberger@desy.de")
var.Add("LIBSONAME","name of the library including the SO-version","")
var.Add("LIBLINKNAME","name of the library used for linking","")
var.Add("LIBFULLNAME","full name of the library binary","")
var.Add("PKGNAME","name of the package for installation","")

#build variables interesting for users that want to build from source
var.Add("CXX","set the compiler to use","g++")
var.Add("DOCDIR","installation directory for the documentation","")
var.Add("INCDIR","installation path for header files","")
var.Add("LIBDIR","library installation path","")
var.Add(PathVariable("VTKINCDIR","header installation path for VTK","/usr/include/vtk"))
var.Add(PathVariable("VTKLIBDIR","VTK library installation","/usr/lib"))
var.Add(PathVariable("BOOSTINCDIR","BOOST header installation path","/usr/include"))
var.Add(PathVariable("BOOSTLIBDIR","BOOST library installation path","/usr/lib"))
var.Add(PathVariable("CPPUINCDIR","CPPUnit header installation path","/usr/include"))
var.Add(PathVariable("CPPULIBDIR","CPPUnit library installation path","/usr/lib"))

#need now to create the proper library suffix

#create the build environment
env = Environment(variables=var,ENV={'PATH':os.environ['PATH']},
				  tools=['default','packaging','textfile'])

#create library namesl
libname = LibFileNames(env["LIBNAME"],env["VERSION"],env["SOVERSION"])
env.Append(LIBFULLNAME = libname.full_name(env))
env.Append(LIBSONAME   = libname.so_name(env))
env.Append(LIBLINKNAME = libname.link_name(env))


#create installation paths
if not env["INCDIR"]:
    env.Append(INCDIR = path.join(env["PREFIX"],"include/pni/utils"))

if not env["LIBDIR"]:
    env.Append(LIBDIR = path.join(env["PREFIX"],"lib"))

if not env["DOCDIR"]:
    #set default documentation directory for installation
    env.Append(DOCDIR = path.join(env["PREFIX"],"share/doc/"+
                                  env["LIBPREFIX"]+env["LIBNAME"]
                                  +env["SOVERSION"]+"-doc"))


print env["LIBDIR"]
#set default compiler flags
env.Append(CXXFLAGS = ["-Wall","-std=c++0x"])
env.Append(LIBS=["dl"])
env.AppendUnique(LIBPATH=[env["VTKLIBDIR"],env["BOOSTLIBDIR"],env["CPPULIBDIR"]])
env.AppendUnique(CPPPATH=[env["VTKINCDIR"],env["BOOSTINCDIR"],env["CPPUINCDIR"]])

#set the proper compiler - this should be changed to something 
#more general - independent of the underlying operating system
env.Replace(CXX = env["CXX"])


nullptr_test_code="""
int main(int argc,char **argv){
    char *ptr=nullptr;
    return 0;
}
"""

def CheckNullPtr(context):
    context.Message("Checking if compiler supports nullptr idiom ...")
    result = context.TryCompile(nullptr_test_code,".cpp")
    context.Result(result)
    return result

foreach_test_code="""
#include<iostream>
#include<vector>
int main(int argc,char **arv){
std::vector<int> vec = {1,2,3,4};
for(int &v: vec){
   std::cout<<v<<std::endl; 
}
return 0;
}
"""

def CheckForEach(context):
    context.Message("Check if compiler supports foreach loops ...")
    result = context.TryCompile(foreach_test_code,".cpp")
    context.Result(result)
    return result
    
#-------------------------------------------------------------------------------   
#start with configuration
conf = Configure(env,custom_tests = {"CheckNullPtr":CheckNullPtr,"CheckForEach":CheckForEach})


#checking compiler capabilities
if not conf.CheckNullPtr():
    print "nullptr not supported - use NULL"
    env.Append(CXXFLAGS=["-Dnullptr=NULL"])

if not conf.CheckForEach():
    print "foreach construction not supported - use workaround"
    env.Append(CXXFLAGS=["-DNOFOREACH"])

#check type sizes
if not conf.CheckTypeSize('char',expect=1):
    pass

if not conf.CheckTypeSize('unsigned char',expect=1):
    pass

if not conf.CheckTypeSize('short',expect=2):
    pass

if not conf.CheckTypeSize('unsigned short',expect=2):
    pass

if not conf.CheckTypeSize('int',expect=4):
    pass

if not conf.CheckTypeSize('unsigned int',expect=4):
    pass

if not conf.CheckTypeSize('long',expect=8):
    pass

if not conf.CheckTypeSize('unsigned long',expect=8):
    pass

if not conf.CheckTypeSize('float',expect=4):
    pass

if not conf.CheckTypeSize('double',expect=8):
    pass

if not conf.CheckTypeSize('long double',expect = 16):
    #in this case we are on 32Bit PC platform
    pass


#check for mandatory header files
if not conf.CheckCXXHeader("boost/numeric/conversion/cast.hpp"):
	print "BOOST header file cast.hpp does not exist!"
	Exit(1)
	
if not conf.CheckCXXHeader("boost/shared_ptr.hpp"):
	print "BOOST header shared_ptr.hpp does not exist!"
	Exit(1)
	
if not conf.CheckCXXHeader("boost/static_assert.hpp"):
	print "BOOST header static_assert.hpp does not exist!"
	Exit(1)
	

if not conf.CheckCXXHeader("boost/regex.hpp"):
    print "Boost regular expressions header file not found!"
    Exit(1)
	

#check for boost regular expressions library
if not conf.CheckLib("boost_regex",language="C++"):
    print "BOOST regular expression library not found"
    Exit(1)


if not conf.CheckLib("vtkFiltering",language="C++") or \
   not conf.CheckLib("vtkftgl",language="C++") or \
   not conf.CheckLib("vtkGenericFiltering",language="C++") or \
   not conf.CheckLib("vtkGraphics",language="C++") or \
   not conf.CheckLib("vtkHybrid",language="C++") or \
   not conf.CheckLib("vtkImaging",language="C++") or \
   not conf.CheckLib("vtkInfovis",language="C++") or \
   not conf.CheckLib("vtkCommon",language="C++") or \
   not conf.CheckLib("vtkRendering",language="C++") or \
   not conf.CheckLib("vtkIO",language="C++"):
    print "VTK libraries are missing!"
    Exit(1)

#check for CPPUNIT headers and library if building tests

	
env = conf.Finish()

#create the build environments for the library and the test
build_env = env.Clone()
test_env  = env.Clone()

#============================start configuration for tests=====================
test_conf = Configure(test_env)

if not test_conf.CheckCXXHeader("cppunit/TestFixture.h"):
    print "CPPUNIT header TestFixture.h does not exist!"
    Exit(1)
    
if not test_conf.CheckCXXHeader("cppunit/TestRunner.h"):
    print "CPPUNIT header TestRunner.h does not exist!"
    Exit(1)
    
if not test_conf.CheckCXXHeader("cppunit/extensions/HelperMacros.h"):
    print "CPPUNIT header HelperMacros.h does not exist!"
    Exit(1)
    
if not test_conf.CheckCXXHeader("cppunit/TestCaller.h"):
    print "CPPUNIT header TestCaller.h does not exist!"
    Exit(1)
    
if not test_conf.CheckCXXHeader(["string","cppunit/TestResult.h"]):
    print "CPPUNIT header TestResult.h does not exist!"
    Exit(1)
    
if not test_conf.CheckCXXHeader("cppunit/TextTestProgressListener.h"):
    print "CPPUNIT header TextTestProgressListener.h does not exist!"
    Exit(1)
    
if not test_conf.CheckCXXHeader("cppunit/ui/text/TextTestRunner.h"):
    print "CPPUNIT header TextTestRunner.h does not exist!"
    Exit(1)

#check for mandatory libraries
if not test_conf.CheckLib("cppunit",language="C++"):
    print "CPPUNIT unit test libraray is not installed!"
    Exit(1)

test_env = test_conf.Finish()


#============================set debugging options=============================
if debug:
    build_env.Append(CXXFLAGS=["-O2"])
    test_env.Append(CXXFLAGS=["-O2"])
else:
    build_env.Append(CXXFLAGS=["-O0","-g"])
    test_env.Append(CXXFLAGS=["-O0","-g"])


#the next line is necessary for the linker on Debian system - this needs 
#a bit more information
if os.name == "posix":
	build_env.Append(LINKFLAGS=["-Wl,-h$LIBSONAME"]) 

Export("build_env")
Export("test_env")


#build
SConscript(["src/SConscript"])
SConscript(["test/SConscript"])
SConscript(["doc/SConscript"])

#set the default target
Default("all")
