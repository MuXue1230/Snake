#include "Shader.h"

Shader::Shader()
{
}

Shader::~Shader()
{
}

bool Shader::Load(const std::string& vertName, const std::string& fragName)
{
    if (!this->CompileShader(vertName, GL_VERTEX_SHADER, this->mVertexShader) || !this->CompileShader(fragName, GL_FRAGMENT_SHADER, this->mFragShader)) {
        return false;
    }

    this->mShaderProgram = glCreateProgram();
    glAttachShader(this->mShaderProgram, this->mVertexShader);
    glAttachShader(this->mShaderProgram, this->mFragShader);
    glLinkProgram(this->mShaderProgram);

    if (!this->IsValidProgram()) {
        return false;
    }
    return true;
}

void Shader::Unload()
{
    glDeleteProgram(this->mShaderProgram);
    glDeleteShader(this->mVertexShader);
    glDeleteShader(this->mFragShader);
}

void Shader::SetActive()
{
    glUseProgram(this->mShaderProgram);
}

bool Shader::CompileShader(const std::string& fileName, GLenum shaderType, GLuint& outShader)
{
    std::ifstream shaderFile("shaders\\" + fileName);
    if (shaderFile.is_open()) {
        std::stringstream sstream;
        sstream << shaderFile.rdbuf();
        std::string contents = sstream.str();
        const char* contentsChar = contents.c_str();

        outShader = glCreateShader(shaderType);
        glShaderSource(outShader, 1, &contentsChar, nullptr);
        glCompileShader(outShader);

        if (!IsCompiled(outShader)) {
            SDL_Log("[With OpenGL][Shader]Failed to compile shader %s", fileName.c_str());
            return false;
        }
    }
    return true;
}

bool Shader::IsCompiled(GLuint shader)
{
    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (status != GL_TRUE) {
        char buffer[512];
        memset(buffer, 0, 512);
        glGetShaderInfoLog(shader, 511, nullptr, buffer);
        SDL_Log("[With OpenGL][Shader]GLSL Compile Failed: \n%s", buffer);
        return false;
    }
    return true;
}

bool Shader::IsValidProgram()
{
    GLint status;
    glGetProgramiv(this->mShaderProgram, GL_LINK_STATUS, &status);
    if (status != GL_TRUE) {
        char buffer[512];
        memset(buffer, 0, 512);
        glGetProgramInfoLog(this->mShaderProgram, 511, nullptr, buffer);
        SDL_Log("[With OpenGL][Shader]Program Link Failed: \n%s", buffer);
        return false;
    }
    return true;
}
