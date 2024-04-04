#include "GOFood.h"

GOFood::GOFood(int x, int y)
{
    this->SetColor(0, 0, 0, 0);
    this->SetSize(0, 0);
    this->SetPos(x, y);
    this->SetName("GOFood<x:" + std::to_string(x) + ", y:" + std::to_string(y) + ">");
}

void GOFood::Initialize()
{
    this->SetColor(255, 0, 0, 255);
    this->SetSize(5, 5);
    //this->SetPos(x, y); // In constructor
}

void GOFood::UpdateObject()
{
    // No need for static object
}

void GOFood::UpdateRenderer()
{
    SDL_SetRenderDrawColor(this->GetRenderer(), this->GetStatus().color.R, this->GetStatus().color.G, this->GetStatus().color.B, this->GetStatus().color.A);
    SDL_Rect food;
    food.x = this->GetStatus().pos.x;
    food.y = this->GetStatus().pos.y;
    food.h = this->GetStatus().size.h;
    food.w = this->GetStatus().size.w;
    SDL_RenderFillRect(this->GetRenderer(), &food);
}

void GOFood::GLInitialize()
{
    this->SetColor(255, 0, 0, 255);
    this->SetSize(5, 5);
    //this->SetPos(x, y); // In constructor
}

void GOFood::GLUpdateObject()
{
    // No need for static object
}

void GOFood::GLUpdateRenderer(Shader* shader)
{
    SDL_Rect food;
    food.x = this->GetStatus().pos.x;
    food.y = this->GetStatus().pos.y;
    food.h = this->GetStatus().size.h;
    food.w = this->GetStatus().size.w;

    this->worldTransform = Matrix4::CreateScale(5.0f);
    this->worldTransform *= Matrix4::CreateTranslation(Vector3(food.x - 1920, 1080 - food.y, 0.0f));
    shader->SetMatrixUniform("worldTransform", this->worldTransform);
    shader->SetIntUniform("colorId", 2);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}
