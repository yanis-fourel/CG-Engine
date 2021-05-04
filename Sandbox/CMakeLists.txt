cmake_minimum_required (VERSION 3.8)


add_executable(Sandbox
	"src/main.cpp"
	
	"src/Sandbox.cpp" 
	"src/GameObjects/FreeCameraManager.cpp"
	"src/GameObjects/TestBall.cpp" 
	"src/GameObjects/links/Spring.cpp"
	"src/GameObjects/links/AnchorSpring.cpp"
	"src/GameObjects/WaterCube.cpp"
	"src/GameObjects/BuoyancyFApplier.cpp"
	"src/GameObjects/Floor.cpp"
	"src/BridgeFactory.cpp"
 "include/GameObjects/links/Rod.hpp" "src/GameObjects/links/Rod.cpp" "include/GameObjects/links/Cable.hpp" "src/GameObjects/links/Cable.cpp" "include/GameObjects/links/AnchorCable.hpp" "src/GameObjects/links/AnchorCable.cpp")

target_link_libraries(Sandbox PUBLIC CG_Engine)

target_include_directories(Sandbox PUBLIC include/)

target_compile_features(Sandbox PUBLIC cxx_std_20)
