#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "gui.h"
#include "steganography.h"
#include "image_loader.h"
#include <opencv2/opencv.hpp>
#include <string>
#include <iostream>

static GLuint imageTexture = 0;
static int imageWidth = 0, imageHeight = 0;
static char message[1024] = "";
static std::string decodedMessage;
static std::string loadedPath;

void SetupGUI() {}

void RenderGUI() {
    ImGui::Begin("Steganography Tool");

    if (ImGui::Button("Load Image")) {
        loadedPath = "assets/sample.png";
        imageTexture = LoadTextureFromFile(loadedPath.c_str());
    }

    if (imageTexture) {
        ImGui::Image((ImTextureID)(intptr_t)imageTexture, ImVec2(300, 300));

        ImGui::InputTextMultiline("Message to Hide", message, IM_ARRAYSIZE(message));

        if (ImGui::Button("Encode Message")) {
            cv::Mat img = cv::imread(loadedPath);
            if (!img.empty()) {
                encodeMessage(img, std::string(message));
                imageTexture = LoadTextureFromFile(loadedPath.c_str());
            } else {
                std::cerr << "Failed to load image for encoding." << std::endl;
            }
        }

        if (ImGui::Button("Decode Message")) {
            cv::Mat img = cv::imread(loadedPath);
            if (!img.empty()) {
                decodedMessage = decodeMessage(img);
            } else {
                std::cerr << "Failed to load image for decoding." << std::endl;
            }
        }

        if (!decodedMessage.empty()) {
            ImGui::TextWrapped("Decoded Message: %s", decodedMessage.c_str());
        }
    }

    ImGui::End();
}

void CleanupGUI() {}

