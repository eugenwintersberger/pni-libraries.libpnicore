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
var.Add("MAINTAINER","package maintainer for the project","None")
var.Add("MAINTAINER_MAIL","e-mail of the package maintainer","None")

#need now to create the proper library suffix

#create the build environment
env = Environment(variables=var,tools=['default','packaging','textfile'])


#the next line is necessary for the linker on Debian system - this needs 
#a bit more information
env.Append(LINKFLAGS=["-Wl,-h"+env["LIBPREFIX"]+env["LIBNAME"]+env["SHLIBSUFFIX"]+"."+env["SOVERSION"]])

    

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

Export("build_env")
Export("test_build_env")


#build
SConscript(["src/SConscript"],variant_dir="build",duplicate=0)
SConscript(["test/SConscript","debian/SConscript"])
(api_html_doc_install,api_pdf_doc_install,api_man_doc_install) = SConscript(["doc/SConscript"])


#build an RPM package
rpm_doc = build_env.Package(
                            #source=[api_html_doc_install,api_pdf_doc_install,api_man_doc_install],
                            NAME = "%s" %(build_env["LIBPREFIX"]+build_env["LIBNAME"]+"-doc"),
                            VERSION = "%s" %(build_env["VERSION"]),
                            PACKAGEVERSION = 0,
                            PACKAGETYPE = "rpm",
                            LICENSE = "gpl",
                            SUMMARY = "a testing package",
                            DESCRIPTION = "a more verbose description",
                            X_RPM_GROUP = "Development/Libraries",
                            SOURCE_URL = "http://www.desy.de"
                           )
build_env.Alias("rpm",[rpm_doc])