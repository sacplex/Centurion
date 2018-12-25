#pragma once

#ifdef CTN_PLATFORM_WINDOWS

extern Centurion::Application* Centurion::CreateApplication();

int main(int argc, char** argv)
{
	Centurion::Log::Init();
	CTN_CLIENT_INFO("Welcome to the Centurion Engine");

	auto app = Centurion::CreateApplication();
	app->Run();
	delete app;
}

#endif