cmake_minimum_required(VERSION 3.10)
project(VideoEditor)

# C++のバージョン設定
set(CMAKE_CXX_STANDARD 17)

# OSごとの設定
if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    set(MSYS2_PREFIX "C:/msys64/ucrt64")
    include_directories("${MSYS2_PREFIX}/include")
    link_directories("${MSYS2_PREFIX}/lib")
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin") # Darwin = macOS
    # Macの場合、特別な設定は不要
endif()

# 必要なライブラリを検索
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED PATHS ${MSYS2_PREFIX}/lib)
find_package(glfw3 REQUIRED PATHS ${MSYS2_PREFIX}/lib)

# ImGuiのインクルードディレクトリを追加
include_directories(src/imgui)

# resourceディレクトリをインクルードディレクトリに追加
include_directories(resource)

# ImGuiのソースファイル
set(IMGUI_SOURCES
    src/imgui/imgui.cpp
    src/imgui/imgui_draw.cpp
    src/imgui/imgui_widgets.cpp
    src/imgui/imgui_tables.cpp
    src/imgui/imgui_impl_glfw.cpp
    src/imgui/imgui_impl_opengl3.cpp
)

# プロジェクトのソース
set(SOURCES
    src/main.cpp
    ${IMGUI_SOURCES}
)

# 実行ファイルを作成
add_executable(${PROJECT_NAME} ${SOURCES})

# ライブラリをリンク
if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
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
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    target_link_libraries(${PROJECT_NAME} OpenGL::GL GLEW::GLEW glfw)
endif()
