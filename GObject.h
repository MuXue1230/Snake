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

    void GLPreInitialize(SDL_GLContext context);
    void GLInitializeBehaviors();
    void GLUpdateBehaviors();
    void GLHandleBehaviorsEvent(SDL_Event event);

	virtual void Initialize() {}
	virtual void UpdateObject() {}
	virtual void HandleEvent(SDL_Event event) {}
	virtual void UpdateRenderer() {}

    virtual void GLInitialize() {}
    virtual void GLUpdateObject() {}
    virtual void GLHandleEvent(SDL_Event event) {}
    virtual void GLUpdateRenderer() {}

	// Getter & Setter
	std::string GetName() const { return this->name; }
	GObjectStatus GetStatus() const { return this->status; }
    SDL_Renderer* GetRenderer() const { return this->renderer; }
    SDL_GLContext GetContext() const { return this->context; }
	std::vector<std::shared_ptr<GBehavior<GObject>>> GetBehaviors() const { return this->behaviors; }
	void SetName(std::string name)
	{
		this->name = name;
	}
	void SetColor(unsigned short R, unsigned short G, unsigned short B, unsigned short A) 
	{ 
		if (R > 0x00ff || G > 0x00ff || B > 0x00ff || A > 0x00ff) throw ColorError();
		this->status.color = { R, G, B, A };
	}
	void SetSize(unsigned int w, unsigned int h)
	{
		this->status.size = { w, h };
	}
	void SetPos(int x, int y) {
		this->status.pos = { x, y };
	}
	void SetRenderer(SDL_Renderer* renderer) { this->renderer = renderer; }

	// Handle Behaviors
	void AddBehaviors(std::shared_ptr<GBehavior<GObject>> behavior)
	{
		this->behaviors.push_back(behavior);
	}
private:
	std::string name;
	GObjectStatus status;
	std::vector<std::shared_ptr<GBehavior<GObject>>> behaviors;
	SDL_Renderer* renderer;
    SDL_GLContext context;
};

