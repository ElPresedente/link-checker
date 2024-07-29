//
// Created by elpresedente on 24.07.2024.
//

#include "Network.hpp"

using namespace Application;

Requests::AsyncHead Network::async_head(Url url) {
    return Requests::AsyncHead{
        cpr::HeadAsync(
            cpr::Url{std::move (url)},
            cpr::Header{{"User-Agent", get_user_agent()}}
        )
    };
}

Requests::AsyncGet Network::async_get(Url url) {
    return Requests::AsyncGet{
        cpr::GetAsync(
            cpr::Url{std::move(url)},
            cpr::Header{{"User-Agent", get_user_agent()}}
        )
    };
}

cpr::Response Network::get(Url url) {
    return cpr::Get(
        cpr::Url{std::move(url)},
        cpr::Header{{"User-Agent", get_user_agent()}}
    );
}

void Network::add_user_agent(std::string user_agent) {
    user_agents.emplace_back(std::move(user_agent));
}

void Network::clear_user_agents() {
    user_agents.clear();
}

Url Network::normalize_url(const Url& url, const Url &base_url) {
    std::function<bool(char)> charset = [](char ch){
        const std::string chars {
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz"
            "0123456789"
            "-_.~"
            ":@/?&=#+[]!$()*,;"
        };
        return chars.contains(ch); //можно переписать через .find != npos
    };
    boost::urls::encoding_opts opts;
    opts.space_as_plus = true;
    auto fixed_string = boost::urls::encode(url, charset);
    boost::urls::url parsed_link {fixed_string};
    auto fixed_base_link = boost::urls::encode(base_url, charset);
    boost::urls::url parsed_base_link {fixed_base_link};

    parsed_link.normalize();
    parsed_base_link.normalize();

    parsed_base_link.resolve(parsed_link);

    parsed_base_link.remove_fragment();

    auto ret = parsed_base_link.buffer();
    return ret;
}

bool Network::is_same_domain(const Url& url, const Url &child_url) {
    auto parsed_url1 = boost::urls::parse_uri(url);
    auto parsed_url2 = boost::urls::parse_uri(child_url);
    return (parsed_url1->host() == parsed_url2->host());
}

bool Network::is_file(const Url& url) {
    auto parsed_url = boost::urls::parse_uri(url)->path();
    return parsed_url.ends_with(".pdf") || parsed_url.ends_with(".doc") || parsed_url.ends_with(".docx");
}

bool Network::is_valid_url(Url url) {
    auto result = boost::urls::parse_uri(url);

    // Проверка на ошибки
    if (!result.error()) {
        return true;
    } else {
        return false;
    }
}

std::string& Network::get_user_agent() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, Network::user_agents.size()-1);

    return user_agents.at(dis(gen));
}

std::vector<std::string> Network::user_agents{};