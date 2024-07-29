//
// Created by vova1 on 03.11.2023.
//

#include "Utility.hpp"

namespace Utility {

    std::string string_trim(std::string str) {
        std::string::size_type first_space = str.find_last_not_of(' ');
        if(first_space != std::string::npos)
            str.erase(first_space + 1);
        return str;
    }

    int range_rand(int min, int max) {
        return (std::rand() % (max - min)) + min;
    }

    namespace chrono{
        time_point now(){
            return std::chrono::steady_clock::now();
        }

        std::chrono::weekday get_day_of_week(decltype(current_zone_now()) t){
            return std::chrono::weekday{std::chrono::floor<std::chrono::days>(t)};
        }

        decltype(std::chrono::current_zone()->to_local(std::chrono::system_clock::now())) current_zone_now(){
            return std::chrono::current_zone()->to_local(std::chrono::system_clock::now());
        }
        std::string current_day_time() {
            auto time = std::chrono::current_zone()
                    ->to_local(std::chrono::system_clock::now());
            return std::format("{:%d.%m.%y-%H.%M.%S}", time);
        }

        std::chrono::year_month_day get_year_month_day(decltype(current_zone_now()) t) {
            return std::chrono::year_month_day{std::chrono::floor<std::chrono::days>(t)};
        }

        std::string tm_to_string(tm &tm) {
            return std::format("{}-{}-{}", tm.tm_year + 1900, tm.tm_mon+  1, tm.tm_mday);
        }
    }
};