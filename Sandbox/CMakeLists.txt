cmake_minimum_required (VERSION 3.8)


add_executable(Sandbox
	"src/main.cpp"
	
	"src/Sandbox.cpp" 
	"src/GameObjects/FreeCameraManager.cpp"
	
	"src/GameObjects/TestBall.cpp" 
	"src/GameObjects/Spring.cpp"
	"src/GameObjects/AnchorSpring.cpp"
	"src/GameObjects/WaterCube.cpp"
	"src/GameObjects/BuoyancyFApplier.cpp"
 "src/GameObjects/Floor.cpp" "include/GameObjects/Floor.hpp")

target_link_libraries(Sandbox PUBLIC CG_Engine)

target_include_directories(Sandbox PUBLIC include/)

target_compile_features(Sandbox PUBLIC cxx_std_20)
