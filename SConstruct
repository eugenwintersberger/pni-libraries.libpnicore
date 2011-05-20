env = Environment()

#need a builder to run doxygen

#need something to build debian and RPM packages automatically 
#or at least some shell scripts that do the job

debug = ARGUMENTS.get("DEBUG",0)
prefix= ARGUMENTS.get("PREFIX","")
instroot= ARGUMENTS.get("INSTALLROOT",0)

import os.path as path

install_prefix=""
if instroot:
    install_prefix += instroot
else:
    install_prefix += "./install"
    
if prefix:
    install_prefix = path.join(install_prefix,prefix)
else:
    install_prefix = path.join(install_prefix,"/")
    
env.SetDefault(INSTALL_PREFIX=install_prefix)
print "install prefix: ",env["INSTALL_PREFIX"]
    

#set the proper compiler
env.Replace(CXX = "g++")

#set default libraries


#set default compiler flags
env.Append(CXXFLAGS = ["-Wall"])



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

Export("build_env")


#build
SConscript(["src/SConscript","test/SConscript"])



