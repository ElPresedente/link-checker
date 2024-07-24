#include <gtkmm.h>

#include "src/ui/MainWindow.hpp"

int main(int argc, char* argv[]) {
    auto app = Gtk::Application::create("org.oreluniver.linkchecker");

    return app->make_window_and_run<Application::MainWindow>(argc, argv);
}
