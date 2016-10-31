#pragma once
class Engine
{
public:
	virtual void onStart();
	virtual void onEnd();
	virtual void preRender(double timeSinceLastFrame);
	virtual void render();
	virtual void postRender();
};

