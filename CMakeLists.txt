cmake_minimum_required(VERSION 3.15)
project(BloodDonationEligibilityChecker C)

# 1. Set C Standard
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# 2. Define the executable and its source files
add_executable(${PROJECT_NAME} main.c)

# 3. Tell CMake where to look for headers (like raylib.h and raygui.h)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# 4. Tell CMake where to find your precompiled libraries (like libraylib.a)
target_link_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/lib)

# 5. Link raylib and system dependencies based on the Operating System
if(WIN32)
    # Windows specific system libraries required by raylib
    target_link_libraries(${PROJECT_NAME} PRIVATE raylib winmm gdi32 opengl32)
elseif(APPLE)
    # macOS specific frameworks
    target_link_libraries(${PROJECT_NAME} PRIVATE raylib)
    target_link_options(${PROJECT_NAME} PRIVATE "-framework" "OpenGL" "-framework" "Cocoa" "-framework" "IOKit" "-framework" "CoreVideo")
else()
    # Linux specific system libraries
    target_link_libraries(${PROJECT_NAME} PRIVATE raylib GL m pthread dl rt X11)
endif()