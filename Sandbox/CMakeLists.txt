cmake_minimum_required (VERSION 3.8)


add_executable(Sandbox
	"src/main.cpp"
	
	"src/Sandbox.cpp" 
	
	"src/GameObjects/PongBall.cpp" 
	"src/GameObjects/links/Spring.cpp"
	"src/GameObjects/links/AnchorSpring.cpp"
	"src/GameObjects/links/Rod.cpp" 
	"src/GameObjects/links/Cable.cpp"
	"src/GameObjects/links/AnchorCable.cpp"
	"src/GameObjects/InvisiblePlane.cpp"
	"src/GameObjects/FreeCameraManager.cpp"
	"src/GameObjects/paddles/APaddle.cpp"
	"src/GameObjects/paddles/PlayerPaddle.cpp"
	"src/LevelCreator.cpp" 
	 "include/GameObjects/paddles/AIPaddle.hpp" "src/GameObjects/paddles/AIPaddle.cpp")

target_link_libraries(Sandbox PUBLIC CG_Engine)

target_include_directories(Sandbox PUBLIC include/)

target_compile_features(Sandbox PUBLIC cxx_std_20)
