#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h> // 標準エラー出力用
#include <iostream>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
static float color[] = {0.2f, 0.3f, 0.3f, 1.0f};

int main()
{
    std::cout << "Hello, World!" << std::endl;

    // GLFWの初期化
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // OpenGLバージョンの設定
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // ウィンドウの作成
    GLFWwindow *window = glfwCreateWindow(700, 500, "Lmnrz", NULL, NULL);
    if (window == NULL)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // コンテキストの設定
    glfwMakeContextCurrent(window);

    // GLEWの初期化（必要に応じて）
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        return -1;
    }

    // ビューポートの設定
    glViewport(0, 0, 700, 500);

    // ウィンドウサイズ変更時のコールバック設定
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // ImGuiの初期化
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;

    ImFontConfig config;
    config.OversampleH = 3; // 水平方向のオーバーサンプリング
    config.OversampleV = 1; // 垂直方向のオーバーサンプリング
    // io.Fonts->AddFontFromFileTTF("/Users/sirem/Library/Fonts/A-OTF-JOMINSTD-LIGHT.OTF", 16.0f);
    io.Fonts->AddFontFromFileTTF("../resource/Inter-Regular.ttf", 16.0f);
    // フォントのスケーリング設定
    io.Fonts->TexGlyphPadding = 20; // フォント間隔を少し広げる
    io.FontGlobalScale = 1.0f;      // スケールをデフォルト値に

    // 必要に応じてアイコンフォントの統合を行う

    // スタイルの設定
    ImGui::StyleColorsDark(); // ベースをダークテーマに
    ImGuiStyle &style = ImGui::GetStyle();

    // Blender風のスタイル設定
    style.WindowRounding = 5.0f;
    style.FrameRounding = 3.0f;
    style.GrabRounding = 2.0f;
    style.PopupRounding = 3.0f;

    // カラーパレットの設定
    ImVec4 *colors = style.Colors;
    colors[ImGuiCol_WindowBg] = ImVec4(0.1f, 0.1f, 0.1f, 1.0f);
    colors[ImGuiCol_Header] = ImVec4(0.2f, 0.2f, 0.2f, 1.0f);
    colors[ImGuiCol_HeaderHovered] = ImVec4(0.3f, 0.3f, 0.3f, 1.0f);
    colors[ImGuiCol_HeaderActive] = ImVec4(0.25f, 0.25f, 0.25f, 1.0f);
    colors[ImGuiCol_Button] = ImVec4(0.2f, 0.2f, 0.2f, 1.0f);
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.3f, 0.3f, 0.3f, 1.0f);
    colors[ImGuiCol_ButtonActive] = ImVec4(0.25f, 0.25f, 0.25f, 1.0f);
    colors[ImGuiCol_FrameBg] = ImVec4(0.15f, 0.15f, 0.15f, 1.0f);
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.25f, 0.25f, 0.25f, 1.0f);
    colors[ImGuiCol_FrameBgActive] = ImVec4(0.35f, 0.35f, 0.35f, 1.0f);
    colors[ImGuiCol_TitleBg] = ImVec4(0.15f, 0.15f, 0.15f, 1.0f);
    colors[ImGuiCol_TitleBgActive] = ImVec4(0.2f, 0.2f, 0.2f, 1.0f);
    colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.1f, 0.1f, 0.1f, 1.0f);
    // 必要に応じて他の色も調整

    // ImGuiバックエンドの初期化
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    // メインループ
    while (!glfwWindowShouldClose(window))
    {
        // 背景色を設定
        glClearColor(color[0], color[1], color[2], color[3]);
        glClear(GL_COLOR_BUFFER_BIT);

        // ImGuiフレーム開始
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // ImGuiウィジェットの設定
        ImGui::Begin("Blender-like Window"); // ウィンドウ開始
        ImGui::Text("HAPPY");                // テキスト描画
        if (ImGui::Button("Close Window"))
        { // ボタン作成
            glfwSetWindowShouldClose(window, true);
        }
        if (ImGui::Begin("Color Picker"))
        {
            ImGui::ColorEdit4("Edit Color", color);
            ImGui::ColorPicker4("Pick Color", color);

            ImGui::End(); // ウィンドウ終了
        }
        ImGui::End(); // ウィンドウ終了

        // ImGuiの描画
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // バッファのスワップとイベント処理
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // ImGuiの終了処理
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    // GLFWの終了処理
    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    // ビューポートを再設定
    glViewport(0, 0, width, height);
}
