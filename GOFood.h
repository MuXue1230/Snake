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
};

