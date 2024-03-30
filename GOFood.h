#pragma once
#include "GObject.h"

class GOFood :
    public GObject
{
public:
    GOFood(int x, int y);

    void Initialize() override;
    void UpdateObject() override;
    // void UpdateObject() override; // No need for static object.
    // void HandleEvent(SDL_Event event) override; // No need for static object.
    void UpdateRenderer() override;

    void GLInitialize() override;
    void GLUpdateObject() override;
    // void GLUpdateObject() override; // No need for static object.
    // void GLHandleEvent(SDL_Event event) override; // No need for static object.
    void GLUpdateRenderer() override;
private:
    bool ate = false;
};

