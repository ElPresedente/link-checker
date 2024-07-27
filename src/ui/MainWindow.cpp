//
// Created by elpresedente on 24.07.2024.
//

#include "MainWindow.hpp"

using namespace Application;


MainWindow::MainWindow()
    : depth_adjustment(Gtk::Adjustment::create(1.0, 1.0, 4.0, 1.0, 1.0, 0.0))
{
    set_title("Утилита проверки ссылок");
    main_grid.set_margin(10);
    main_grid.set_expand(true);

    url_input_label.set_child(url_entry);
    url_input_label.set_expand(true);
    url_input_label.set_label("Ссылка для проверки");
    main_grid.attach(url_input_label, 0, 0, 2, 1);

    encoding_input_label.set_child(encoding_entry);
    encoding_input_label.set_expand(true);
    encoding_input_label.set_label("Кодировка страницы");
    main_grid.attach(encoding_input_label, 0, 1);

    check_encoding_button.set_label("Обнаружить кодировку");
    main_grid.attach(check_encoding_button, 1, 1);

    css_query_input_label.set_label("CSS запрос к ссылкам на странице");
    css_query_input_label.set_child(css_query_entry);
    css_query_input_label.set_expand(true);
    main_grid.attach(css_query_input_label, 0, 2, 2, 1);

    depth_entry_input_label.set_label("Глубина проверки ссылкок");
    depth_entry_input_label.set_expand(true);

    depth_entry.set_adjustment(depth_adjustment);

    depth_entry_input_label.set_child(depth_entry);
    main_grid.attach(depth_entry_input_label, 0, 3);

    start_button.set_label("Начать проверку");
    main_grid.attach(start_button, 1, 3);

    set_child(main_grid);
}