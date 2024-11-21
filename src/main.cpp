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

    // GLfloat vertices[] =
    // {
    //     -0.5f,-0.5f * float(sqrt(3)) / 3,0.0f,
    //     0.5f,-0.5f * float(sqrt(3)) / 3,0.0f,
    //     0.5f,0.5f * float(sqrt(3)) * 2 /3, 0.0f
    // };

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

    // ビューポートの設定
    glViewport(0, 0, 700, 500);

    // Gluint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // glShaderSource(vertexShader,1,&vertexShaderSource,NULL);
    // glCompileShader(vertexShader);

    // Guint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    // ウィンドウサイズ変更時のコールバック設定
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // ImGuiの初期化
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;
    ImGui::StyleColorsDark();

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
        ImGui::Begin("Windows Lmnrz"); // ウィンドウ開始
        ImGui::Text("HAPPY");          // テキスト描画
        if (ImGui::Button("Close Window"))
        { // ボタン作成
            glfwSetWindowShouldClose(window, true);
        }
        if (ImGui::Begin("my window"))
        {

            ImGui::ColorEdit4("edit", color);
            ImGui::ColorPicker4("picker", color);

            ImGui::End(); // ウィンドウ終了
        }
        ImGui::End(); // ウィンドウ終了

        // ImGuiの描画ss
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