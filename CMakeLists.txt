cmake_minimum_required(VERSION 3.10)
project(VideoEditor)

# C++のバージョン設定
set(CMAKE_CXX_STANDARD 17)

# GLFW、GLEW、OpenGLのリンク設定
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)

# ImGuiのインクルードディレクトリを追加
include_directories(src/imgui)

# ImGuiのソースファイルを明示的に追加
set(IMGUI_SOURCES
    src/imgui/imgui.cpp
    src/imgui/imgui_draw.cpp
    src/imgui/imgui_widgets.cpp
    src/imgui/imgui_tables.cpp
    src/imgui/imgui_impl_glfw.cpp
    src/imgui/imgui_impl_opengl3.cpp
)

# プロジェクトのソースを設定
set(SOURCES
    src/main.cpp
    ${IMGUI_SOURCES}
)

# 実行ファイルを作成
add_executable(${PROJECT_NAME} ${SOURCES})

# ライブラリをリンク
target_link_libraries(${PROJECT_NAME} OpenGL::GL GLEW::GLEW glfw)
