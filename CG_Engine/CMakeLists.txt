cmake_minimum_required (VERSION 3.8)


include(cmake/Conan.cmake)
run_conan()


set(imgui_version "1.78")

macro(download_imgui file)
  if(NOT EXISTS "${CMAKE_BINARY_DIR}/download/imgui/${imgui_version}/${file}")
    message(STATUS "Downloading from https://github.com/ocornut/imgui/tree/v${imgui_version}/examples/${file}")
    file(DOWNLOAD "https://raw.githubusercontent.com/ocornut/imgui/v${imgui_version}/examples/${file}"
         "${CMAKE_BINARY_DIR}/download/imgui/${imgui_version}/${file}")
  endif()
endmacro()

download_imgui(imgui_impl_glfw.cpp)
download_imgui(imgui_impl_glfw.h)
download_imgui(imgui_impl_opengl3.cpp)
download_imgui(imgui_impl_opengl3.h)

add_library(glfw_imgui_impl STATIC ${CMAKE_BINARY_DIR}/download/imgui/${imgui_version}/imgui_impl_glfw.cpp
                                   ${CMAKE_BINARY_DIR}/download/imgui/${imgui_version}/imgui_impl_opengl3.cpp "include/CG/ui/imfilebrowser.h")

target_link_libraries(glfw_imgui_impl PUBLIC CONAN_PKG::glew CONAN_PKG::glfw CONAN_PKG::imgui)
target_compile_definitions(glfw_imgui_impl PUBLIC IMGUI_IMPL_OPENGL_LOADER_GLEW)

add_subdirectory(vendor/cyclone)

add_library(CG_Engine STATIC
    "src/Window.cpp"
    "src/Camera.cpp"
    "src/internal/ShaderManager.cpp"
    "src/Core.cpp"
    "src/GameObject.cpp"
    "src/Game.cpp"
    "src/InputManager.cpp"
    "src/internal/Drawable.cpp"
    "src/components/renderer/CubeRenderer.cpp"
    "src/components/renderer/PlaneRenderer.cpp"
    "src/prefabs/PointLight.cpp"
    "src/components/renderer/SphereRenderer.cpp"
    "src/components/renderer/MeshRenderer.cpp"
    "src/internal/DrawableBuilder.cpp"
    "src/internal/Texture.cpp"
    "src/internal/GlError.cpp"
    "src/prefabs/Sphere.cpp" 
    "src/prefabs/Cube.cpp"
    "src/math/Utility.cpp"
    "src/math/Ray.cpp"
    "src/physic/Raycast.cpp"
     "include/CG/components/collider/PlaneCollider.hpp" "include/CG/prefabs/Plane.hpp" "src/prefabs/Plane.cpp")

target_include_directories(CG_Engine PUBLIC   
    ${CMAKE_BINARY_DIR}/download/imgui/${imgui_version}
    ${CMAKE_CURRENT_SOURCE_DIR}/include/
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/stb_image/
)
target_include_directories(CG_Engine PUBLIC include)   


target_link_libraries(CG_Engine PUBLIC 
    glfw_imgui_impl
    cyclone
    CONAN_PKG::glm
    CONAN_PKG::fmt
    CONAN_PKG::spdlog
    CONAN_PKG::entt
    CONAN_PKG::assimp
)

target_compile_features(CG_Engine PUBLIC cxx_std_17)

target_compile_definitions(CG_Engine PRIVATE 
    CG_SHADER_DIR="${CMAKE_CURRENT_SOURCE_DIR}/shaders/"
    
)
