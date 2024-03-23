#pragma once
#include "sdl_include.h"
#include "GBehavior.h"

struct GObjectStatus
{
	struct Color
	{
	 	unsigned short R;
		unsigned short G;
		unsigned short B;
		unsigned short A;
	};
	struct Size
	{
		unsigned int w;
		unsigned int h;
	};
	struct Postion
	{
		int x;
		int y;
	};
	Color color;
	Size size;
	Postion pos;
};

class ColorError {};

class GObject
{
public:
	GObject();
	GObject(std::string name);

	void PreInitialize(SDL_Renderer* renderer);
	void InitializeBehaviors();
	void UpdateBehaviors();
	void HandleBehaviorsEvent(SDL_Event event);

	virtual void Initialize();
	virtual void UpdateObject();
	virtual void HandleEvent(SDL_Event event);
	virtual void UpdateRenderer();

	// Getter & Setter
	std::string GetName() const { return this->name; }
	GObjectStatus GetStatus() const { return this->status; }
	void SetName(std::string name)
	{
		this->name = name;
	}
	void SetColor(unsigned short R, unsigned short G, unsigned short B, unsigned short A) 
	{ 
		if (R >225 || G > 225 || B > 225 || A > 225) throw ColorError();
		this->status.color = { R, G, B, A };
	}
	void SetSize(unsigned int w, unsigned int h)
	{
		this->status.size = { w, h };
	}
	void SetPos(int x, int y) {
		this->status.pos = { x, y };
	}

	// Handle Behaviors
	void AddBehaviors(GBehavior<GObject> behavior) 
	{
		this->behaviors.push_back(std::make_shared<GBehavior<GObject>>(behavior));
	}
private:
	std::string name;
	GObjectStatus status;
	std::vector<std::shared_ptr<GBehavior<GObject>>> behaviors;
	SDL_Renderer* renderer;
};

