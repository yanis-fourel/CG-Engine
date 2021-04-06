cmake_minimum_required (VERSION 3.8)


add_executable(Sandbox
	"src/main.cpp"
	
	"src/Sandbox.cpp" 
	"src/GameObjects/FreeCameraManager.cpp"
	"src/GameObjects/Tile.cpp"
	"src/GameObjects/Grid.cpp")

target_link_libraries(Sandbox PUBLIC CG_Engine)

target_include_directories(Sandbox PUBLIC include/)
