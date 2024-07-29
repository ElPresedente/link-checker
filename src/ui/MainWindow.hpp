//
// Created by elpresedente on 24.07.2024.
//

#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <queue>
#include <stack>
#include <sstream>
#include <thread>

#include <gtkmm.h>

#include "../Types.hpp"
#include "../Page.hpp"
#include "../Logger.hpp"
#include "ProgressBarMessage.hpp"

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
    Gtk::Entry user_agent_entry;
    Gtk::Button add_user_agent_button, clear_user_agent_button;

    Gtk::ScrolledWindow scroll_list;
    Gtk::ListView user_agent_list;
    Glib::RefPtr<Gtk::StringList> string_list;
    std::vector<Gtk::ProgressBar> progress_bars;
    std::vector<Gtk::Label> progress_labels;

    Glib::Dispatcher dispatcher, finish_dispatcher;
    std::vector<ProgressBarMessage> progress_state;
    mutable std::mutex state_mutex;

    void on_dispather();
    void on_end();

    void start();

    void add_user_agent();
    void clear_user_agents();

    void on_setup_label(const Glib::RefPtr<Gtk::ListItem>& list_item);
    void on_bind_name(const Glib::RefPtr<Gtk::ListItem>& list_item);


private: //здесь промежуточные контейнеры
    Gtk::Frame url_input_label, encoding_input_label, css_query_input_label, depth_entry_input_label, user_agent_input_label;
    Glib::RefPtr<Gtk::Adjustment> depth_adjustment;
    Logger logger;
    std::optional<std::thread> program_thread;
    const int grid_size = 5; //константа для динамического добавления элементов под основным гридом

    void main_program(const Url& url, const Encoding& encoding, const std::string &css_query, int depth);
};

} // Application

#endif //MAINWINDOW_HPP
