#pragma once
#include <glad/glad.h>  // ✅ This must come *before* anything using GLuint
#include <string>

// Add forward declaration for LoadTextureFromFile
GLuint LoadTextureFromFile(const char* filename);
