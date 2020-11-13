cmake_minimum_required (VERSION 3.8)


add_executable(Sandbox
	"src/main.cpp"
	"src/Cube.cpp"
	"src/Sandbox.cpp")

target_link_libraries(Sandbox PUBLIC CG_Engine)

target_include_directories(Sandbox PUBLIC include/)
