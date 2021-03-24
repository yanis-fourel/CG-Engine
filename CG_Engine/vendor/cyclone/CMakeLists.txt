cmake_minimum_required (VERSION 3.8)


add_library(cyclone STATIC 
	"src/body.cpp"
	"src/collide_fine.cpp"
	"src/core.cpp"
	"src/joints.cpp"
	"src/pcontacts.cpp"
	"src/plinks.cpp"
	"src/random.cpp" 
	"src/collide_coarse.cpp"
	"src/contacts.cpp"
	"src/fgen.cpp"
	"src/particle.cpp"
	"src/pfgen.cpp"
	"src/pworld.cpp"
	"src/world.cpp" 
)

target_include_directories(cyclone INTERFACE include) # makes it required to put <cyclone/*.h> when including
target_include_directories(cyclone PRIVATE include/cyclone)
