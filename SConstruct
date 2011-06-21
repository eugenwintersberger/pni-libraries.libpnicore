#load python modules
import os.path as path

#need something to build debian and RPM packages automatically 
#or at least some shell scripts that do the job

debug = ARGUMENTS.get("DEBUG",0)

var = Variables()
var.Add(PathVariable("PREFIX","set installation prefix","/usr/local"))
var.Add(PathVariable("DESTDIR","set destination directory","/",PathVariable.PathAccept))
var.Add(PathVariable("BOOSTPREFIX","set the installation prefix for boost","/usr"))
var.Add("LIBSONAME","set SONAME for the library","libpniutils.so")


#create the build environment
env = Environment(variables=var)

#set the prefix for the installation
if env["PREFIX"][0] == "/": env["PREFIX"]=env["PREFIX"][1:]

env["ENV"]["INSTALL_PREFIX"]=path.join(env["DESTDIR"],env["PREFIX"])
    

#set the proper compiler - this should be changed to something 
#more general - independent of the underlying operating system
env.Replace(CXX = "g++")

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
build_env.Append(LINKFLAGS=["-Wl,-h$LIBSONAME"])
build_env.Append(LIBS=["tiff"])
Export("build_env")
Export("test_build_env")


#build
SConscript(["src/SConscript","test/SConscript"])



