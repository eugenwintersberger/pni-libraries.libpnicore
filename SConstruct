#load python modules
import os.path as path

#need something to build debian and RPM packages automatically 
#or at least some shell scripts that do the job

debug = ARGUMENTS.get("DEBUG",0)

var = Variables('BuildConfig.py')
var.Add(PathVariable("PREFIX","set installation prefix","/usr/local"))
var.Add(PathVariable("BOOSTPREFIX","set the installation prefix for boost","/usr"))
var.Add("VERSION","library version","0.0.0")
var.Add("LIBNAME","library name","pniutils")
var.Add("SOVERSION","SOVersion of the library (binary interface version)","0")
var.Add("CXX","set the compiler to use","g++")
var.Add("MAINTAINER","package maintainer for the project","Eugen Wintersberger")
var.Add("MAINTAINER_MAIL","e-mail of the package maintainer","eugen.wintersberger@desy.de")
var.Add("DOCDIR","installation directory for the documentation","")
var.Add("MANDIR","installation directory for man pages","share/man")
var.Add("LIBSONAME","name of the library including the SO-version","")
var.Add("LIBLINKNAME","name of the library used for linking","")
var.Add("LIBFULLNAME","full name of the library binary","")
var.Add("INCINSTPATH","installation path for header files","")
var.Add("LIBINSTPATH","library installation path","")
var.Add("PKGNAMEROOT","root package name (actually only used for Debian packages)","")

#need now to create the proper library suffix

#create the build environment
env = Environment(variables=var,tools=['default','packaging','textfile'])

#create library names
env.Append(LIBFULLNAME = env["LIBPREFIX"]+env["LIBNAME"]+env["SHLIBSUFFIX"]+"."
                         +env["SOVERSION"]+"."+env["VERSION"])
env.Append(LIBSONAME = env["LIBPREFIX"]+env["LIBNAME"]+env["SHLIBSUFFIX"]+"."+
                         env["SOVERSION"])
env.Append(LIBLINKNAME = env["LIBPREFIX"]+env["LIBNAME"]+env["SHLIBSUFFIX"])

#create installation paths
env.Append(INCINSTPATH = path.join(env["PREFIX"],"include/pni/utils"))
env.Append(LIBINSTPATH = path.join(env["PREFIX"],"lib"))

if env["DOCDIR"] == "":
    #set default documentation directory for installation
    env.Append(DOCDIR = path.join(env["PREFIX"],"share/doc/"+
                                  env["LIBPREFIX"]+env["LIBNAME"]
                                  +env["SOVERSION"]+"-doc"))

if env["PKGNAMEROOT"] == "":
    env.Append(PKGNAMEROOT = env["LIBPREFIX"]+env["LIBNAME"]+env["SOVERSION"])



#print env["LINKFLAGS"]
    

#set the proper compiler - this should be changed to something 
#more general - independent of the underlying operating system
env.Replace(CXX = env["CXX"])

#set default libraries


#set default compiler flags
env.Append(CXXFLAGS = ["-Wall"])
env.Append(LIBPATH=path.join(env["BOOSTPREFIX"],"lib"))
env.Append(CPPPATH=path.join(env["BOOSTPREFIX"],"include"))


#create optimized environment
opt_env = env.Clone()
opt_env.Append(CXXFLAGS = ["-O2"])


#create debugging environment
dbg_env = env.Clone()
dbg_env.Append(CXXFLAGS = ["-O0","-g"])

if debug:
    build_env = dbg_env.Clone()
else:
    build_env = opt_env.Clone()


test_build_env = build_env.Clone()
#the next line is necessary for the linker on Debian system - this needs 
#a bit more information
build_env.Append(LINKFLAGS=["-Wl,-h$LIBSONAME"]) #+env["LIBPREFIX"]+env["LIBNAME"]+env["SHLIBSUFFIX"]+"."+env["SOVERSION"]])

Export("build_env")
Export("test_build_env")


#build
SConscript(["src/SConscript"])
SConscript(["test/SConscript","debian/SConscript"])
SConscript(["doc/SConscript"])

