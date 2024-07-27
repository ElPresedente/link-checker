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
protected: // здесь значимые элементы
    Gtk::Grid main_grid;
    Gtk::Entry url_entry, encoding_entry, css_query_entry;
    Gtk::SpinButton depth_entry;
    // Gtk::CheckButton async_mode;
    Gtk::Button start_button, check_encoding_button;
    // Gtk::Entry user_agent_entry;
    // Gtk::Button add_user_agent_button, clear_user_agent_button;

private: //здесь промежуточные контейнеры
    Gtk::Frame url_input_label, encoding_input_label, css_query_input_label, depth_entry_input_label;
    Glib::RefPtr<Gtk::Adjustment> depth_adjustment;
};

} // Application

#endif //MAINWINDOW_HPP
