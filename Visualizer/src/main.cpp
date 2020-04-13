#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <cstdio>

#if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
#include <GL/gl3w.h>            // Initialize with gl3wInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
#include <GL/glew.h>            // Initialize with glewInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
#include <glad/glad.h>          // Initialize with gladLoadGL()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLBINDING2)
#define GLFW_INCLUDE_NONE       // GLFW including OpenGL headers causes ambiguity or multiple definition errors.
#include <glbinding/Binding.h>  // Initialize with glbinding::Binding::initialize()
#include <glbinding/gl/gl.h>
using namespace gl;
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLBINDING3)
#define GLFW_INCLUDE_NONE       // GLFW including OpenGL headers causes ambiguity or multiple definition errors.
#include <glbinding/glbinding.h>// Initialize with glbinding::initialize()
#include <glbinding/gl/gl.h>
using namespace gl;
#else
#include IMGUI_IMPL_OPENGL_LOADER_CUSTOM
#endif

#include <GLFW/glfw3.h>
#include <fstream>
#include <vector>
#include <sstream>
#include <iostream>

static void glfw_error_callback(int error, const char* description)
{
	fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

# define LOG_FILE_FULL_PATH		"/tmp/com.lreznak-.malloc.log"

int main(int, char**)
{
	// Setup window
	glfwSetErrorCallback(glfw_error_callback);
	if (!glfwInit())
		return 1;

	// GL 3.2 + GLSL 150
	const char* glsl_version = "#version 150";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac


	// Create window with graphics context
	GLFWwindow* window = glfwCreateWindow(1280, 720, "AllocVisualizer", NULL, NULL);
	if (window == nullptr)
		return 1;
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1); // Enable vsync

	// Initialize OpenGL loader

#if defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
	bool err = glewInit() != GLEW_OK;
#endif
	if (err)
	{
		fprintf(stderr, "Failed to initialize OpenGL loader!\n");
		return 1;
	}

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsClassic();

	// Setup Platform/Renderer bindings
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);

	// Our state
	bool show_memory_window = false;
	bool show_tiny_clusters = false, show_small_clusters = false, show_huge_clusters = false;

	std::fstream logFile(LOG_FILE_FULL_PATH);
	if (!logFile.is_open())
	{
		fprintf(stderr, "Failed to open malloc logfile!\n");
		return 1;
	}
	std::vector<ImColor>	colorBoxes;
	ImColor ImWhite{255, 255, 255}; // Free Cell
	ImColor CellFireRed{178,34,34};
	ImColor CellUnknown{0, 0, 0};
	ImColor CellZoneHead{0,255,255};
	ImColor CellBlockHead{102,102,0};
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	// Main loop
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		// service panel window
		{
			static float f = 0.0f;
			static int counter = 0;
			ImGui::Begin("Service Panel");
			static bool HWstart = false;
			if (!HWstart)
			{
				HWstart = true;
				ImGui::SetWindowSize({350, 200});
			}
			// Config boxes
			ImGui::Checkbox("memory Window", &show_memory_window);
			ImGui::Checkbox("Tiny Clusters", &show_tiny_clusters);
			ImGui::Checkbox("Small Clusters", &show_small_clusters);
			ImGui::Checkbox("Huge Clusters", &show_huge_clusters);

//			ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
//			ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

			if (ImGui::Button("<<"))
				counter++;
			ImGui::SameLine();
			if (ImGui::Button(">>"))
			{
				colorBoxes.clear();
				std::string line;
				while (getline(logFile, line))
				{
					std::stringstream ss(line);
					char c;
					ss >> c;
					if (c == 'C')
					{colorBoxes.push_back(CellZoneHead);}
					else if (c == 'B')
					{
						colorBoxes.push_back(CellBlockHead);
						ss >> c;
						size_t		address;
						ss >> std::hex >> address;
						ss >> c;
						ss >> std::dec >> address;
						std::cout << "room: " << address << std::endl;
						ss >> c >> c;

						while (address)
						{
							colorBoxes.push_back(c == '1' ? CellFireRed : ImWhite);
							address >>= 2U;
						}
					}
					if (line == "***")
						break;

				}
				std::cout << "COUNT" << colorBoxes.size() << std::endl;
			}
			ImGui::Text("counter = %d", counter);

			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			ImGui::End();
		}

		if (show_memory_window)
		{
			ImGui::Begin("Memory");
			static bool SMstart = false;
			if (!SMstart)
			{
				SMstart = true;
				ImGui::SetWindowSize({870, 620});
			}
			ImDrawList* draw_list = ImGui::GetWindowDrawList();
			const ImVec2 p = ImGui::GetCursorScreenPos();
			static ImVec4 colf = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
			const ImU32 col = ImColor(colf);
			float x = p.x + 4.0f, y = p.y + 4.0f;
			static float sz = 100.0f;
			static float thickness = 10.0f;
			size_t color = 0;

			{
				float i = p.x;
				float j = p.y;
				for (auto & colorBoxe : colorBoxes)
				{
					if (p.x + ImGui::GetWindowSize().x < i + 10)
					{
						i = p.x;
						j += 20;
					}
					draw_list->AddRectFilled(ImVec2(i, j), ImVec2(i + 20, j + 20), colorBoxe);
					i += 20;
				}
			}
			ImGui::End();
		}

		// Rendering
		ImGui::Render();
		int display_w, display_h;
		glfwGetFramebufferSize(window, &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);
		glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
		glClear(GL_COLOR_BUFFER_BIT);
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		glfwSwapBuffers(window);
	}

	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}
