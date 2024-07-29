//
// Created by elpresedente on 24.07.2024.
//

#ifndef NETWORK_HPP
#define NETWORK_HPP

#include <random>

#include <cpr/cpr.h>
#include <boost/url.hpp>
#include <boost/regex.hpp>

#include "Types.hpp"

#include "requests/AsyncHead.hpp"
#include "requests/AsyncGet.hpp"

namespace Application {

class Network {
public:
    static Requests::AsyncHead async_head(Url);
    static Requests::AsyncGet async_get(Url);
    static cpr::Response get(Url);

    static void add_user_agent(std::string);
    static void clear_user_agents();
    static std::string& get_user_agent();

    static Url normalize_url(const Url& url, const Url &base_url);
    static bool is_same_domain(const Url& url, const Url &child_url);
    static bool is_file(const Url&);
    static bool is_valid_url(Url);

    static std::vector<std::string> user_agents; // пул юзер агентов
};

} // Application

#endif //NETWORK_HPP
