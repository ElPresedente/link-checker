//
// Created by elpresedente on 24.07.2024.
//

#include "MainWindow.hpp"
#include <OpenXLSX.hpp>
#include "../Types.hpp"

using namespace Application;


MainWindow::MainWindow()
    : depth_adjustment(Gtk::Adjustment::create(1.0, 1.0, 4.0, 1.0, 1.0, 0.0)),
    string_list(Gtk::StringList::create({"Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/126.0.0.0 Safari/537.36"}))
{
#ifndef NDEBUG
    url_entry.set_text("https://oreluniver.ru/sveden");
    encoding_entry.set_text("windows-1251");
    css_query_entry.set_text(".page-content a");
#endif

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
    start_button.signal_clicked().connect(
        sigc::mem_fun(*this, &Application::MainWindow::start)
    );
    main_grid.attach(start_button, 1, 3);

    user_agent_input_label.set_label("Добавить User-Agent в пул");
    user_agent_input_label.set_expand(true);
    user_agent_input_label.set_child(user_agent_entry);
    main_grid.attach(user_agent_input_label, 0, 4);

    add_user_agent_button.set_label("Добавить");
    add_user_agent_button.signal_clicked().connect(
        sigc::mem_fun(*this, &Application::MainWindow::add_user_agent)
    );
    main_grid.attach(add_user_agent_button, 1, 4);

    auto selection_model = Gtk::SingleSelection::create(string_list);
    selection_model->set_autoselect(false);
    selection_model->set_can_unselect(true);
    user_agent_list.set_model(selection_model);
    user_agent_list.set_expand(true);
    user_agent_list.add_css_class("data-table");

    // взято из оф примера, без этого не завелось лол
    auto factory = Gtk::SignalListItemFactory::create();
    factory->signal_setup().connect(
      sigc::mem_fun(*this, &Application::MainWindow::on_setup_label));
    factory->signal_bind().connect(
      sigc::mem_fun(*this, &Application::MainWindow::on_bind_name));
    user_agent_list.set_factory(factory);


    scroll_list.set_child(user_agent_list);
    scroll_list.set_expand(true);
    main_grid.attach(scroll_list, 2, 0, 1, 4);

    clear_user_agent_button.set_label("Очистить список");
    clear_user_agent_button.signal_clicked().connect(
        sigc::mem_fun(*this, &Application::MainWindow::clear_user_agents)
    );
    main_grid.attach(clear_user_agent_button, 2, 4);
    set_child(main_grid);
    // конец UI

    Network::add_user_agent("Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/126.0.0.0 Safari/537.36");
    logger.set_table_filename("report");
    dispatcher.connect(sigc::mem_fun(*this, &MainWindow::on_dispather));
    finish_dispatcher.connect(sigc::mem_fun(*this, &MainWindow::on_end));
}

void MainWindow::on_setup_label(const Glib::RefPtr<Gtk::ListItem>& list_item)
{
    list_item->set_child(*Gtk::make_managed<Gtk::Label>("", Gtk::Align::START));
}

void MainWindow::on_bind_name(const Glib::RefPtr<Gtk::ListItem>& list_item)
{
    auto pos = list_item->get_position();
    if (pos == GTK_INVALID_LIST_POSITION)
        return;
    auto label = dynamic_cast<Gtk::Label*>(list_item->get_child());
    if (!label)
        return;
    label->set_text(string_list->get_string(pos));
}


void MainWindow::on_dispather() {
    std::lock_guard<std::mutex> m{state_mutex};
    try
    {
        for(auto&& state : progress_state){
            progress_labels.at(state.depth).set_text(state.label_text);
            progress_bars.at(state.depth).set_fraction(state.progress);
        }
    }
    catch(std::exception& ex) {
        std::string a = ex.what();
        a.push_back('1');
    }

}

void MainWindow::on_end() {
    progress_bars.clear();
    progress_labels.clear();
    int row = grid_size + progress_state.size() - 1;
    for(auto&& item : progress_state) {
        main_grid.remove_row(row--);
    }
    progress_state.clear();
}

void MainWindow::start() {
    if(Network::user_agents.empty()) {
        user_agent_entry.error_bell();
        user_agent_entry.grab_focus_without_selecting();
        return;
    }

    std::string url = url_entry.get_text();
    if(url.empty() || !Network::is_valid_url(url)) {
        url_entry.error_bell();
        url_entry.grab_focus_without_selecting();
        return;
    }
    Encoding encoding = encoding_entry.get_text();
    if(encoding.empty()) {
        encoding_entry.error_bell();
        encoding_entry.grab_focus_without_selecting();
        return;
    }
    std::string css_query = css_query_entry.get_text();
    if(css_query.empty()) {
        css_query_entry.error_bell();
        css_query_entry.grab_focus_without_selecting();
        return;
    }
    int depth;
    std::istringstream (depth_entry.get_text()) >> depth;
    int row = grid_size;
    for(int i = 0; i < depth; i++) {
        auto&& bar = progress_bars.emplace_back();
        bar.set_expand(true);
        auto&& label = progress_labels.emplace_back();
        main_grid.attach(label, 0, row);
        main_grid.attach(bar, 1, row++, 2, 1);
        label.set_text("[0/0]");
        bar.set_fraction(0.5);
        auto&& state = progress_state.emplace_back();
        state.depth = i;
    }
    program_thread = std::thread{&Application::MainWindow::main_program, this, url, encoding, css_query, depth};
    program_thread.value().detach();
}

void MainWindow::add_user_agent() {
    auto ua = user_agent_entry.get_text();
    if(ua.empty()) {
        user_agent_entry.error_bell();
        user_agent_entry.grab_focus_without_selecting();
        return;
    }
    string_list->append(ua);
    Network::add_user_agent(ua);
}

void MainWindow::clear_user_agents() {
    string_list = Gtk::StringList::create();
    auto selection_model = Gtk::SingleSelection::create(string_list);
    selection_model->set_autoselect(false);
    selection_model->set_can_unselect(true);
    user_agent_list.set_model(selection_model);
    Network::clear_user_agents();
}

void MainWindow::main_program(const Url& url, const Encoding& encoding, const std::string &css_query, int depth) {
    auto start_page_content = Network::async_get(url).get();
    if(start_page_content.status_code != 200)
        return;

    std::stack<Page> pages_queue;
    std::set<Url> visited_pages;
    pages_queue.emplace(0, start_page_content.text, url, encoding); //стартовая страница

    while(!pages_queue.empty()) {
        auto& page = pages_queue.top();
        if(page.depth >= depth) {
            pages_queue.pop();
            continue;
        }
        std::vector<Application::Requests::AsyncHead> requests;
        auto links = page.get_links(css_query);

        for(auto&& link : links) {
            requests.emplace_back(Network::async_head(link));
        }
        for(int i = 0; auto&& promise : requests) {
            // изменение GUI
            try
            {
                std::lock_guard<std::mutex> m{state_mutex};
                progress_state.at(page.depth) = {std::format("[{}/{}]", i, requests.size()),
                    static_cast<double>(i) / static_cast<double>(requests.size()), page.depth};
            }
            catch(std::exception& ex) {
                std::string a = ex.what();
                a.push_back('1');
            }
            dispatcher.emit();

            auto response = promise.get_full();
            if(response.status_code == 200) {
                const std::string& current_url = response.url.str();
                logger.log(current_url, page.url, response.status_code);
                try {
                    if(Network::is_same_domain(page.url, current_url) &&
                        !Network::is_file(current_url) &&
                        !visited_pages.contains(current_url) &&
                        page.depth < depth)
                    {
                        auto resp = Network::get(current_url);
                        if(resp.status_code != 200) {
                            logger.log(current_url, page.url, resp.status_code, resp.error.message);
                        }
                        else {
                            pages_queue.emplace(page.depth + 1, resp.text, current_url, encoding);
                            visited_pages.emplace(current_url);
                        }
                    }
                }
                catch(std::exception& ex) {
                    logger.log(current_url, page.url, -1, ex.what());
                }
            }
            else {
                logger.log(response.url.c_str(), "none", response.status_code, response.error.message);
            }
            i++;
        }

        pages_queue.pop();
    }
    finish_dispatcher.emit();
}
