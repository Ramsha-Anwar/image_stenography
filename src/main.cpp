#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <string>
#include <windows.h> // Add this line at the top of your file

#include "steganography.h"
#include "image_loader.h"

// Globals
GLuint imageTexture = 0;
std::string imagePath = "assets/sample.png";
char inputBuffer[1024] = "";  // Fixed: char buffer or ImGui input
std::string inputMessage = "";  // Will hold message when encoding
std::string decodedMessage = "";
cv::Mat loadedImage;
bool imageLoaded = false;

void LoadImage() {
    loadedImage = cv::imread(imagePath);
    if (!loadedImage.empty()) {
        imageTexture = LoadTextureFromFile(imagePath.c_str());
        imageLoaded = true;
    } else {
        std::cerr << "Failed to load image at: " << imagePath << std::endl;
    }
}

int main() {
    // Init GLFW
    if (!glfwInit()) return -1;

    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    GLFWwindow* window = glfwCreateWindow(1280, 720, "Steganography ImGui", NULL, NULL);
    if (!window) return -1;
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) return -1;

    // Setup ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);
    ImGui::StyleColorsDark();

    LoadImage();

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("Image Steganography Tool");

        if (imageLoaded && imageTexture) {
            ImGui::Text("Loaded Image Preview:");
            ImGui::Image((ImTextureID)(intptr_t)imageTexture, ImVec2(300, 300));
        } else {
            ImGui::Text("Failed to load image.");
        }

        // ? Fixed InputTextMultiline usage
        ImGui::InputTextMultiline("Text to Hide", inputBuffer, IM_ARRAYSIZE(inputBuffer));

        if (ImGui::Button("Encode and Save")) {
            inputMessage = std::string(inputBuffer);
            encodeMessage(loadedImage, inputMessage);
            cv::imwrite("assets/output.png", loadedImage);

            char absPath[MAX_PATH];
            _fullpath(absPath, "assets/output.png", MAX_PATH);
            std::cout << "Trying to load: " << absPath << std::endl;
        }

        if (ImGui::Button("Decode Message from Image")) {
            cv::Mat outputImg = cv::imread("assets/output.png");
            if (!outputImg.empty()) {
                decodedMessage = decodeMessage(outputImg);
            } else {
                decodedMessage = "Failed to load output image.";
            }
        }

        if (!decodedMessage.empty()) {
            ImGui::TextWrapped("Decoded Message:");
            ImGui::TextWrapped("%s", decodedMessage.c_str());
        }

        ImGui::End();

        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
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

