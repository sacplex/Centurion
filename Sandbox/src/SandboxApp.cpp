#include "Centurion.h"

class Sandbox : public Centurion::Application
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}
};

Centurion::Application* Centurion::CreateApplication()
{
	return new Sandbox();
}