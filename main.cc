#include <gtkmm.h>

#include "src/ui/MainWindow.hpp"

#ifdef WINDOWS

#include <windows.h>

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
#else
int main(int __argc, char** __argv)
#endif
{
    auto app = Gtk::Application::create("org.oreluniver.linkchecker");

    return app->make_window_and_run<Application::MainWindow>(__argc, __argv);
}
