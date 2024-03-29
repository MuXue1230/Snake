#pragma once
#include "GBehavior.h"
#include "GOFood.h"

template <class T>
class GBSnakeCheckFood :
    public GBehavior<T>
{
public:
    GBSnakeCheckFood(std::vector<GOFood>* foods, bool occupied[216][144]);
    GBSnakeCheckFood(std::string name, std::vector<GOFood>* foods, bool occupied[216][144]);

    void Initialize() override;
    void UpdateObject() override;
    void HandleEvent(SDL_Event& event) override;
private:
    std::vector<GOFood>* foods;
    bool occupied[216][144];
    const int gridWidth = 216;
    const int gridHeight = 144;
};

template<class T>
inline GBSnakeCheckFood<T>::GBSnakeCheckFood(std::vector<GOFood>* foods, bool occupied[216][144])
    :foods(foods)
{
    this->SetName("GBSnakeCheckDeath");
    this->occupied = occupied;
}

template<class T>
inline GBSnakeCheckFood<T>::GBSnakeCheckFood(std::string name, std::vector<GOFood>* foods, bool occupied[216][144])
    :foods(foods)
{
    this->SetName("GBSnakeCheckDeath<" + name + ">");
    for (int x = 0; x < 216; x++) {
        for (int y = 0; y < 144; y++) {
            this->occupied[x][y] = occupied[x][y];
        }
    }
}

template<class T>
inline void GBSnakeCheckFood<T>::Initialize()
{
}

template<class T>
inline void GBSnakeCheckFood<T>::UpdateObject()
{
    unsigned int index = 0;
    for (auto food : *this->foods) {
        int x = food.GetStatus().pos.x, y = food.GetStatus().pos.y;
        if (x == this->GetObject()->GetStatus().pos.x && y == this->GetObject()->GetStatus().pos.y) {
            this->GetObject()->SetLength(this->GetObject()->GetStatus().body.length + 1);
            this->occupied[x / 5][y / 5] = false;
            int a, b;
            do {
                a = (rand() % gridWidth) * 5;
                b = (rand() % gridHeight) * 5;
            } while (this->occupied[a / 5][b / 5]);
            this->foods->at(index).SetPos(a, b);
            this->occupied[a / 5][b / 5] = true;
            SDL_Log("[%s->%s] Ate a food: %s", this->GetObject()->GetName().c_str(), this->GetName().c_str(), food.GetName().c_str());
        }
        index++;
    }
}

template<class T>
inline void GBSnakeCheckFood<T>::HandleEvent(SDL_Event& event)
{
}
