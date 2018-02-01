cmake_minimum_required(VERSION 3.9)
project(myGameEngine)

set(CMAKE_CXX_STANDARD 11)

include_directories(
    include
    src/deps/glad
    src/deps/glfw
)

file(
    GLOB_RECURSE
    glfw_files
    src/deps/glad/glad.c
    src/deps/glfw/vulkan.c
    src/deps/glfw/input.c
    src/deps/glfw/context.c
    src/deps/glfw/window.c
    src/deps/glfw/init.c
    src/deps/glfw/monitor.c
)

if (UNIX)
    file(
        GLOB_RECURSE
        glfw_os_dependences
        src/deps/glfw/cocoa_init.m
        src/deps/glfw/cocoa_joystick.m
        src/deps/glfw/cocoa_monitor.m
        src/deps/glfw/cocoa_time.c
        src/deps/glfw/cocoa_window.m
        src/deps/glfw/getopt.c
        src/deps/glfw/posix_tls.c
        src/deps/glfw/nsgl_context.m
        src/deps/glfw/tinycthread.c
    )
    add_definitions(
        -D_GLFW_COCOA
        -D_GLFW_WGL
        -D_GLFW_USE_OPENGL=1
    )
elseif (WIN32)
    file(
        GLOB_RECURSE
        glfw_os_dependences
        src/deps/glfw/wgl_context.c
        src/deps/glfw/win32_init.c
        src/deps/glfw/win32_joystick.c
        src/deps/glfw/win32_monitor.c
        src/deps/glfw/win32_time.c
        src/deps/glfw/win32_tls.c
        src/deps/glfw/win32_window.c
        src/deps/glfw/egl_context.c
    )
    add_definitions(
        -D_GLFW_WIN32
        -D_GLFW_WGL
        -D_GLFW_USE_OPENGL=1
    )
endif (UNIX)


file(
    GLOB_RECURSE
    my_files
    src/main.cpp
    src/shader.cpp
    src/Camera.cpp
    src/Mouse.cpp
    src/Cube.cpp
    src/Transform.cpp
    src/GameObject.cpp
    src/Buffer.cpp
    src/Geometry.cpp
    src/Sphere.cpp
)

add_executable(myGameEngine
    ${glfw_files}
    ${glfw_os_dependences}
    ${my_files}
)

if (UNIX)
    target_link_libraries(
        myGameEngine
        "-framework Cocoa"
        "-framework AppKit"
        "-framework CoreData"
        "-framework Foundation"
        "-framework IOKit"
        "-framework CoreVideo"
    )
endif (UNIX)
