#load python modules
import os.path as path
import platform
import os

###--------------------------------------------------------------------------------
#add some command line options
AddOption("--enable-vtk",dest="with_vtk",action="store_true",default=False)
AddOption("--enable-tiff",dest="with_tiff",action="store_true",default=False)

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
var.Add(PathVariable("BOOSTINCDIR","BOOST header installation path","/usr/include"))
var.Add(PathVariable("BOOSTLIBDIR","BOOST library installation path","/usr/lib"))
var.Add(PathVariable("CPPUINCDIR","CPPUnit header installation path","/usr/include"))
var.Add(PathVariable("CPPULIBDIR","CPPUnit library installation path","/usr/lib"))

if GetOption("with_vtk"):
    var.Add(PathVariable("VTKINCDIR","header installation path for VTK","/usr/include/vtk"))
    var.Add(PathVariable("VTKLIBDIR","VTK library installation","/usr/lib"))

#need now to create the proper library suffix

#create the build environment
env = Environment(variables=var,ENV={'PATH':os.environ['PATH']},
				  tools=['default','packaging','textfile'])

#set the proper compiler - this should be changed to something 
#more general - independent of the underlying operating system
env.Replace(CXX = env["CXX"])
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


#set default compiler flags
env.Append(CXXFLAGS = ["-Wall","-std=c++0x","-fno-deduce-init-list"])
env.Append(LIBS=["dl"])
env.AppendUnique(LIBPATH=[env["BOOSTLIBDIR"],env["CPPULIBDIR"]])
env.AppendUnique(CPPPATH=[env["BOOSTINCDIR"],env["CPPUINCDIR"]])

if GetOption("with_vtk"):
    env.AppendUnique(LIBPATH=[env["VTKLIBDIR"]])
    env.AppendUnique(CPPPATH=[env["VTKINCDIR"]])


#==========================run configuration===================================
Export('env')
(build_env,test_env) = SConscript('configure/SConscript')

#============================set debugging options=============================
if debug:
    build_env.Append(CXXFLAGS=["-O0","-g"])
    test_env.Append(CXXFLAGS=["-O0","-g"])
else:
    build_env.Append(CXXFLAGS=["-O2"])
    test_env.Append(CXXFLAGS=["-O2"])


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
