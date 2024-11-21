cmake_minimum_required(VERSION 3.10)
project(VideoEditor)

set(CMAKE_CXX_STANDARD 17)

# Use the ucrt64 environment
set(MSYS2_PREFIX "C:/msys64/ucrt64")

# Update the find_package calls
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED PATHS "${MSYS2_PREFIX}/lib")
find_package(glfw3 REQUIRED PATHS "${MSYS2_PREFIX}/lib")

# Update include directories
include_directories(src/imgui)
include_directories("${MSYS2_PREFIX}/include")

# ImGui sources
set(IMGUI_SOURCES
    src/imgui/imgui.cpp
    src/imgui/imgui_draw.cpp
    src/imgui/imgui_widgets.cpp
    src/imgui/imgui_tables.cpp
    src/imgui/imgui_impl_glfw.cpp
    src/imgui/imgui_impl_opengl3.cpp
)

# Project sources
set(SOURCES
    src/main.cpp
    ${IMGUI_SOURCES}
)

add_executable(${PROJECT_NAME} ${SOURCES})

# Link libraries
target_link_libraries(${PROJECT_NAME}
    GLEW::GLEW
    glfw
    OpenGL::GL
    -lkernel32
    -luser32
    -lgdi32
    -lwinspool
    -lshell32
    -lole32
    -loleaut32
    -luuid
    -lcomdlg32
    -ladvapi32
)
