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


#need to manager here the build and installation of the documentation

doxygen_api_doc = build_env.Command("doc/api-doc/html/index.html",Glob("src/*.hpp"),"doxygen")
pdf_api_doc = build_env.Command("refman.pdf","doc/api-doc/latex/Makefile","cd doc/api-doc/latex; make")
#man_api_doc = build_env.Command("zip.log","doc/api-doc/man/man3","cd $SOURCE; gzip -f *.3 > $TARGET")
build_env.Alias("all",[doxygen_api_doc,pdf_api_doc])

#need to prepear installation of the documentation
api_html_doc_install = build_env.Install(path.join(build_env["PREFIX"],"share/doc/libpniutils"+build_env["SOVERSION"]+"-doc/api-doc/"),"doc/api-doc/html")
api_pdf_doc_install = build_env.Install(path.join(build_env["PREFIX"],"share/doc/libpniutils"+build_env["SOVERSION"]+"-doc/api-doc/"),"doc/api-doc/latex/refman.pdf")
api_man_doc_install = build_env.Install(path.join(build_env["PREFIX"],"share/man/"),"doc/api-doc/man/man3")
build_env.Alias("install",[api_html_doc_install,api_pdf_doc_install,api_man_doc_install])


#build
SConscript(["src/SConscript","test/SConscript","debian/SConscript"])

#build an RPM package
tgz_test = build_env.Package(NAME = "test",
                   VERSION = "$VERSION",
                   PACKAGEVERSION = 0,
                   PACKAGETYPE = "targz",
                   LICENSE = "gpl",
                   SUMMARY = "a testing package",
                   DESCRIPTION = "a more verbose description",
                   X_RPM_GROUP = "Development/Libraries",
                   SOURCE_URL = "http://nix.com")
build_env.Alias("all",[tgz_test])
