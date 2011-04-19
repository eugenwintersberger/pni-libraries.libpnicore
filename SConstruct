env = Environment()

debug = ARGUMENTS.get("DEBUG",0)

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



