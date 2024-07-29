//
// Created by vova1 on 03.11.2023.
//

#ifndef OSU_SCHEDULE_SERVICE_UTILITY_HPP
#define OSU_SCHEDULE_SERVICE_UTILITY_HPP

#include <cstdint>
#include <chrono>

#include <boost/locale.hpp>


namespace Utility {
    std::string string_trim(std::string str);
    int range_rand(int min, int max);
    namespace chrono{
        using time_point = decltype(std::chrono::steady_clock::now());
        time_point now();

        std::string current_day_time();

        using default_period = std::milli;

        template <class Period = default_period>
        using duration_t = decltype(std::chrono::duration<double, Period>());

        template <class Period = default_period>
        duration_t<Period> duration(time_point start, time_point end){
            return std::chrono::duration<double, Period>(end - start);
        }

        decltype(std::chrono::current_zone()->to_local(std::chrono::system_clock::now())) current_zone_now();

        std::chrono::weekday get_day_of_week(decltype(current_zone_now()) t);

        std::chrono::year_month_day get_year_month_day(decltype(current_zone_now()) t);

        template<typename Clock = std::chrono::system_clock, class Period = default_period>
        std::string to_string(std::chrono::time_point<Clock, Period> tp){
            return std::format("{0:%F}", tp);
        }

        std::string tm_to_string(std::tm& tm);
    }
};


#endif //OSU_SCHEDULE_SERVICE_UTILITY_HPP
