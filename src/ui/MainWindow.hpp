//
// Created by elpresedente on 24.07.2024.
//

#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <gtkmm.h>

namespace Application  {

class MainWindow final : public Gtk::Window {
public:
    explicit MainWindow();
    ~MainWindow() override = default;
private:
    Gtk::Box main_box;
    Gtk::Grid grid;
};

} // Application

#endif //MAINWINDOW_HPP
