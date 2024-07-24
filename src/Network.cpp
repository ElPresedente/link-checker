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

void Network::add_user_agent(std::string user_agent) {
    user_agents.emplace_back(std::move(user_agent));
}

void Network::clear_user_agents() {
    user_agents.clear();
}

std::string& Network::get_user_agent() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, Network::user_agents.size()-1);

    return user_agents.at(dis(gen));
}

std::vector<std::string> Network::user_agents{};