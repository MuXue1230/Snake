#include "GObject.h"

GObject::GObject()
{
	this->status = {
		{ 0, 0, 0, 0 },
		{ 0, 0 },
		{ 0, 0 }
	};
}

GObject::GObject(std::string name)
{
	this->status = {
		{ 0, 0, 0, 0 },
		{ 0, 0 },
		{ 0, 0 }
	};
	this->SetName(name);
}

void GObject::PreInitialize(SDL_Renderer* renderer)
{
	this->renderer = renderer;
	for (auto& item : this->GetBehaviors()) {
		SDL_Log("> > Pre-initializing Behavior <%s>...", item->GetName().c_str());
		item->PreInitialize(*this, renderer);
	}
}

void GObject::InitializeBehaviors()
{
	for (auto& item : this->GetBehaviors()) {
		SDL_Log("> > Initializing Behavior <%s>...", item->GetName().c_str());
		item->Initialize();
	}
	this->Initialize();
}

void GObject::UpdateBehaviors()
{
	for (auto& item : this->GetBehaviors()) {
		item->UpdateObject();
	}
	this->UpdateObject();
}

void GObject::HandleBehaviorsEvent(SDL_Event event)
{
	for (auto& item : this->GetBehaviors()) {
		item->HandleEvent(event);
	}
	this->HandleEvent(event);
}

void GObject::GLPreInitialize(SDL_GLContext context)
{
    this->context = context;
    for (auto& item : this->GetBehaviors()) {
        SDL_Log("[With OpenGL]> > Pre-initializing Behavior <%s>...", item->GetName().c_str());
        item->GLPreInitialize(*this, context);
    }
}

void GObject::GLInitializeBehaviors()
{
    for (auto& item : this->GetBehaviors()) {
        SDL_Log("[With OpenGL]> > Pre-initializing Behavior <%s>...", item->GetName().c_str());
        item->GLPreInitialize(*this, context);
    }
}

void GObject::GLUpdateBehaviors()
{
    for (auto& item : this->GetBehaviors()) {
        SDL_Log("[With OpenGL]> > Initializing Behavior <%s>...", item->GetName().c_str());
        item->GLInitialize();
    }
    this->GLInitialize();
}

void GObject::GLHandleBehaviorsEvent(SDL_Event event)
{
    for (auto& item : this->GetBehaviors()) {
        item->GLHandleEvent(event);
    }
    this->GLHandleEvent(event);
}
