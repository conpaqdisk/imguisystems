cmake_minimum_required(VERSION 3.15)
project(SteellBoxNew)

set(CMAKE_CXX_STANDARD 17)

# ImGui
set(IMGUI_DIR ${CMAKE_CURRENT_SOURCE_DIR}/external/imgui)
file(GLOB IMGUI_SOURCES 
    ${IMGUI_DIR}/*.cpp 
    src/Core/AppState.cpp
    src/Core/PipeClient.cpp
    src/Core/GameData.cpp
    src/Core/Logger.cpp
    src/Core/Memory.cpp
    src/Core/KOData.cpp
    src/Core/PacketHandler.cpp
    src/UI/Core/UIComponents.cpp
    ${IMGUI_DIR}/backends/imgui_impl_win32.cpp 
    ${IMGUI_DIR}/backends/imgui_impl_dx11.cpp
)

file(GLOB IMPLOT_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/external/implot/*.cpp
)

file(GLOB IMGUI_MISC_SOURCES
    ${IMGUI_DIR}/misc/cpp/*.cpp
)

file(GLOB_RECURSE SRC_FILES "src/*.cpp")

add_executable(SteellBoxNew WIN32 ${SRC_FILES} ${IMGUI_SOURCES} ${IMPLOT_SOURCES} ${IMGUI_MISC_SOURCES} src/UI/Panels/DemoPanel.cpp)

target_include_directories(SteellBoxNew PRIVATE 
    ${IMGUI_DIR} 
    ${IMGUI_DIR}/backends
    ${IMGUI_DIR}/misc/cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/external/implot
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(SteellBoxNew d3d11 d3dcompiler dxgi)
