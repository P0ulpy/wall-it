cmake_minimum_required(VERSION 3.16)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake)

project(wall-it)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")

set(EXECUTABLE_TARGET_NAME wall-it-app)

set_target_properties(${ENGINE_TARGET_NAME}
    PROPERTIES LINKER_LANGUAGE CXX
)

# Libs
# include(${CMAKE_SOURCE_DIR}/src/vendors)

find_package(raylib CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_path(RAYGUI_INCLUDE_DIRS "raygui.h")

add_executable(${EXECUTABLE_TARGET_NAME}
    src/main.cpp
)

add_subdirectory(src/vendors)

target_link_libraries(${EXECUTABLE_TARGET_NAME}
    PRIVATE raylib ${RAYGUI_INCLUDE_DIRS}
    PRIVATE imgui::imgui
)
