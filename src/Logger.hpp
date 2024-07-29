//
// Created by elpresedente on 28.07.2024.
//

#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <future>
#include <mutex>

#include <OpenXLSX.hpp>

#include "Types.hpp"
#include "Utility.hpp"

namespace Application{

class Logger {
public:
    void log(Url url, Url parent_url, int status_code, std::string error_str = "");

    void set_table_filename(const std::string &name);

    ~Logger();
private:
    std::string table_filename;
    OpenXLSX::XLDocument doc;
    std::mutex write_mutex;

    int error_line{2};
    int success_line{2};

    void write_to_xlsx(Url url, Url parent_url, int status_code, std::string error_str);
};

}

#endif //LOGGER_HPP
