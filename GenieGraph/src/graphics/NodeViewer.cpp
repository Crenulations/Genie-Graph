#include "NodeViewer.h"

NodeViewer::NodeViewer(RuntimeVars* settings) 
    :settings(settings), renderer(Renderer(settings)), main_gui(settings)
{

    /* Initialize the library */
    if (!glfwInit())
        std::cout << "GLFW init error!!!" << std::endl;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(1920, 1080, "Genie", NULL, NULL);
    glfwSetWindowPos(window, 0, 50);

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSwapInterval(1); // Set FPS to refresh rate of vsync

    // Load GLEW and log if that fails
    if (glewInit() != GLEW_OK)
        std::cout << "GLEW init error!!!" << std::endl;

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_POINT_SMOOTH);
    glPointSize(4.0f);

    ImGui::CreateContext();
    ImGui::StyleColorsDark();    // Setup Dear ImGui style
    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");
    // Load Fonts
    ImGuiIO& io = ImGui::GetIO();
    io.Fonts->AddFontFromFileTTF("res/ProggyTiny.ttf", 16.0f);

}
NodeViewer::~NodeViewer() {

}

void NodeViewer::SetColonyManager(ColonyManager* c) {
    colony_manager = c;
    current_colony = colony_manager->colonies[0];

    main_gui.LoadGeneData(current_colony);
}

void NodeViewer::Draw() {

    current_colony = colony_manager->colonies[settings->focused_colony];

    static float r = 0.0f;
    static int counter = 0;

    main_gui.updateHighlight(current_colony->chromo_data[1], current_colony->read_pos[1]);

    if (glfwWindowShouldClose(window)) {
        settings->window_close = true;
    }

    renderer.Clear();

    if (settings->auto_rotate) {
        renderer.camera.AutoRotate();
    }

    // Colony 
    current_colony->nodeModel.Bind();
    renderer.DrawNodeModelVerts(current_colony->nodeModel);
    renderer.DrawNodeModelEdges(current_colony->nodeModel);

    // GUI
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    main_gui.DrawMenuBar();
    main_gui.DrawOverlay();
//    main_gui.DrawWindow(settings);

    if (show_demo_window)
        ImGui::ShowDemoWindow(&show_demo_window);

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


    //====== END RENDER AREA =====//
    /* Swap front and back buffers */
    glfwSwapBuffers(window);
    /* Poll for and process events */
    glfwPollEvents();

}