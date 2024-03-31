#pragma once
#include "sdl_include.h"
#include "Math.h"

class Shader
{
public:
    Shader();
    ~Shader();
    bool Load(const std::string& vertName, const std::string& fragName);
    void Unload();
    void SetActive();
private:
    bool CompileShader(const std::string& fileName, GLenum shaderType, GLuint& outShader);

    bool IsCompiled(GLuint shader);
    bool IsValidProgram();

    GLuint mVertexShader;
    GLuint mFragShader;
    GLuint mShaderProgram;
};

