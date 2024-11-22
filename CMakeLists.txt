cmake_minimum_required(VERSION 3.10)
project(VideoEditor)

# ------------------------------
# 1. C++のバージョン設定
# ------------------------------
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ------------------------------
# 2. macOS用のアーキテクチャ設定
# ------------------------------
if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(CMAKE_OSX_ARCHITECTURES "arm64")
endif()

# ------------------------------
# 3. OSごとの設定
# ------------------------------
if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    set(MSYS2_PREFIX "C:/msys64/ucrt64")
    include_directories("${MSYS2_PREFIX}/include")
    link_directories("${MSYS2_PREFIX}/lib")
    add_definitions(-DGLEW_STATIC)  # WindowsではGLEW_STATICを有効化
endif()

# ------------------------------
# 4. 必要なライブラリを検索
# ------------------------------
find_package(OpenGL REQUIRED)

# ------------------------------
# 5. インクルードディレクトリの追加
# ------------------------------
include_directories(
    src/imgui
    src/glew/include
)

# ------------------------------
# 6. GLFW をサブディレクトリとして追加
# ------------------------------
add_subdirectory(src/glfw)

# ------------------------------
# 7. ソースファイルの設定
# ------------------------------

# ImGuiのソースファイル
set(IMGUI_SOURCES
    src/imgui/imgui.cpp
    src/imgui/imgui_draw.cpp
    src/imgui/imgui_widgets.cpp
    src/imgui/imgui_tables.cpp
    src/imgui/imgui_impl_glfw.cpp
    src/imgui/imgui_impl_opengl3.cpp
)

# Glewのソースファイル
set(GLEW_SOURCES
    src/glew/src/glew.c
)

# プロジェクトのソースファイル
set(SOURCES
    src/main.cpp
    ${IMGUI_SOURCES}
    ${GLEW_SOURCES}
)

# ------------------------------
# 8. 実行ファイルの作成
# ------------------------------
add_executable(${PROJECT_NAME} ${SOURCES})

# ------------------------------
# 9. ライブラリのリンク
# ------------------------------
if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    target_link_libraries(${PROJECT_NAME}
        OpenGL::GL
        glfw
        glew32s
        kernel32
        user32
        gdi32
        winspool
        shell32
        ole32
        oleaut32
        uuid
        comdlg32
        advapi32
    )
else() # macOS
    target_link_libraries(${PROJECT_NAME}
        glfw
        "-framework Cocoa"
        "-framework IOKit"
        "-framework CoreFoundation"
        "-framework CoreVideo"
        OpenGL::GL
    )

    # Objective-Cランタイムとのリンクを確実にするためのフラグ追加
    set_target_properties(${PROJECT_NAME} PROPERTIES
        LINK_FLAGS "-ObjC"
    )
endif()
