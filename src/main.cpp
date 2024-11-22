#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

// 背景色の色を保持するグローバル変数
static float color[] = {0.18f, 0.19f, 0.23f, 1.0f};

// フレームバッファサイズ変更コールバック
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

// レンダリング関数
void render(GLFWwindow *window)
{
    // フレームバッファサイズを取得してビューポートを設定
    int fbWidth, fbHeight;
    glfwGetFramebufferSize(window, &fbWidth, &fbHeight);
    glViewport(0, 0, fbWidth, fbHeight);

    // 背景色をクリア
    glClearColor(color[0], color[1], color[2], color[3]);
    glClear(GL_COLOR_BUFFER_BIT);

    // ImGuiフレームの開始
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // ImGuiウィジェットの設定
    ImGui::Begin("Giant"); // ウィンドウ開始
    ImGui::Text("Happy");  // テキスト描画
    if (ImGui::Button("Close Window"))
    { // ボタン作成
        glfwSetWindowShouldClose(window, true);
    }
    if (ImGui::Begin("Color Picker"))
    {

        ImGui::ColorEdit4("Edit Color", color);
        ImGui::ColorPicker4("Pick Color", color);
    }
    ImGui::End(); // ウィンドウ終了

    ImGui::End(); // ウィンドウ終了

    ImGui::Begin("Tools");

    static char str0[128] = "Hello, world!";
    static int i1 = 50, i2 = 42;
    ImGui::DragInt("drag int", &i1, 1);

    ImGui::InputText("input text", str0, IM_ARRAYSIZE(str0));
    static float col2[4] = {0.4f, 0.7f, 0.0f, 0.5f};
    ImGui::ColorEdit4("color 2", col2);

    ImGui::Text("Tool");
    if (ImGui::IsItemHovered())
        ImGui::SetTooltip("Nice");

    ImGui::BulletText("1");
    ImGui::BulletText("2\n3");
    ImGui::Bullet();
    ImGui::Text("5");
    ImGui::Bullet();
    ImGui::SmallButton("Bye");
    ImGui::End();

    // ImGuiの描画
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    // バッファのスワップ
    glfwSwapBuffers(window);
}

// ウィンドウリフレッシュコールバック
void window_refresh_callback(GLFWwindow *window)
{
    render(window); // レンダリング関数を呼び出し
}

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
    // GLFWのウィンドウヒントで透明を有効化
    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);

    // ウィンドウの作成
    GLFWwindow *window = glfwCreateWindow(1200, 800, "Lmnrz", NULL, NULL);
    if (window == NULL)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // OpenGLコンテキストの設定
    glfwMakeContextCurrent(window);

    // GLEWの初期化
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        return -1;
    }
    // ブレンディングを有効化
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // フレームバッファサイズ変更時のコールバック設定
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // ウィンドウリフレッシュコールバック設定
    glfwSetWindowRefreshCallback(window, window_refresh_callback);

    // ImGuiの初期化
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    // 追加: カスタムフォントとスタイルの設定
    {
        ImGuiIO &io = ImGui::GetIO();
        (void)io; // 未使用の変数警告を防ぐ

        ImFontConfig config;

        // フォントの追加 (フォントファイルのパスを確認してください)
        ImFont *custom_font = io.Fonts->AddFontFromFileTTF("../resource/Inter-Regular.ttf", 32.0f, &config);
        if (!custom_font)
        {
            std::cerr << "Failed to load font: ../resource/Inter-Regular.ttf" << std::endl;
        }

        // io.Fonts->AddFontFromFileTTF("../resource/Hutogo.OTF", 32.0f, nullptr, graphyto); // 必要に応じてコメント解除

        // フォントのスケーリング設定
        io.Fonts->TexGlyphPadding = 20.0f; // フォント間隔を少し広げる
        io.FontGlobalScale = 0.5f;         // スケールをデフォルト値に
        // io.ConfigFlags |= ImGuiConfigFlags_DockingEnable; // ドッキングを有効化

        // 必要に応じてアイコンフォントの統合を行う
        // 例: io.Fonts->AddFontFromFileTTF("path_to_icon_font.ttf", size, &config, icon_ranges);

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
    }

    // ImGuiのバックエンド初期化
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    // メインループ
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents(); // イベントの処理
        render(window);   // レンダリング
    }

    // ImGuiの終了処理
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    // GLFWの終了処理
    glfwTerminate();
    return 0;
}
