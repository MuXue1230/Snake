#include "Shader.h"

Shader::Shader()
{
    SDL_Log("[With OpenGL][Shader]New shader pair was created.");
}

Shader::~Shader()
{
}

bool Shader::Load(const std::string& vertName, const std::string& fragName)
{
    SDL_Log("[With OpenGL][Shader]Loading shader pair: %s+%s...", vertName.c_str(), fragName.c_str());
    if (!this->CompileShader(vertName, GL_VERTEX_SHADER, this->mVertexShader) || !this->CompileShader(fragName, GL_FRAGMENT_SHADER, this->mFragShader)) {
        SDL_Log("[With OpenGL][Shader]Error when compile shaders.");
        return false;
    }

    SDL_Log("[With OpenGL][Shader]Creating shader program...");
    this->mShaderProgram = glCreateProgram();
    glAttachShader(this->mShaderProgram, this->mVertexShader);
    glAttachShader(this->mShaderProgram, this->mFragShader);
    SDL_Log("[With OpenGL][Shader]Linking shader program...");
    glLinkProgram(this->mShaderProgram);

    SDL_Log("[With OpenGL][Shader]Validating program...");
    if (!this->IsValidProgram()) {
        SDL_Log("[With OpenGL][Shader]Program is invalid.");
        return false;
    }
    return true;
}

void Shader::Unload()
{
    SDL_Log("[With OpenGL][Shader]Doing Destruction of Shader Program");
    glDeleteProgram(this->mShaderProgram);
    SDL_Log("[With OpenGL][Shader]Doing Destruction of Shaders");
    glDeleteShader(this->mVertexShader);
    glDeleteShader(this->mFragShader);
}

void Shader::SetActive()
{
    glUseProgram(this->mShaderProgram);
}

void Shader::SetMatrixUniform(const char* name, const Matrix4& matrix)
{
    GLuint loc = glGetUniformLocation(mShaderProgram, name);
    glUniformMatrix4fv(loc, 1, GL_TRUE, matrix.GetAsFloatPtr());
}

void Shader::SetIntUniform(const char* name, const int& Int)
{
    GLuint loc = glGetUniformLocation(mShaderProgram, name);
    glUniform1i(loc, Int);
}

bool Shader::CompileShader(const std::string& fileName, GLenum shaderType, GLuint& outShader)
{
    SDL_Log("[With OpenGL][Shader][Compiler]Reading shader file...");
    std::ifstream shaderFile("shaders\\" + fileName);
    if (shaderFile.is_open()) {
        SDL_Log("[With OpenGL][Shader][Compiler]Handling file context...");
        std::stringstream sstream;
        sstream << shaderFile.rdbuf();
        std::string contents = sstream.str();
        const char* contentsChar = contents.c_str();

        SDL_Log("[With OpenGL][Shader][Compiler]Creating shader...");
        outShader = glCreateShader(shaderType);
        glShaderSource(outShader, 1, &contentsChar, nullptr);
        SDL_Log("[With OpenGL][Shader][Compiler]Compiling shader...");
        glCompileShader(outShader);

        if (!IsCompiled(outShader)) {
            SDL_Log("[With OpenGL][Shader][Compiler]Failed to compile shader %s", fileName.c_str());
            return false;
        }
    }
    else {
        SDL_Log("[With OpenGL][Shader][Compiler]Failed to read shader %s", fileName.c_str());
        return false;
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
