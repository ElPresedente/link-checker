//
// Created by elpresedente on 28.07.2024.
//

#include "Logger.hpp"

#include <utility>

using namespace Application;

void Logger::log(Url url, Url parent_url, int status_code, std::string error_str) {
    auto f = std::async(std::launch::async, &Logger::write_to_xlsx, this, url ,parent_url, status_code, error_str);
}

void Logger::set_table_filename(const std::string &name) {
    std::stringstream ss;
    ss << name  << ".xlsx";
    table_filename = ss.str();
    try {
        doc.create(table_filename);
    }
    catch (std::exception& ex) {
        std::string e = ex.what();
        e.push_back('1');
    }
    auto wbk = doc.workbook();
    wbk.addWorksheet("Success");
    wbk.addWorksheet("Errors");
    wbk.deleteSheet("Sheet1");
    auto wks_s = wbk.worksheet("Success");
    wks_s.cell("A1").value() = "Ссылка";
    wks_s.cell("B1").value() = "Страница на которой расположена ссылка";
    wks_s.cell("C1").value() = "Код запроса";
    wks_s.cell("D1").value() = "Доп информация";

    auto wks_e = wbk.worksheet("Errors");
    wks_e.cell("A1").value() = "Ссылка";
    wks_e.cell("B1").value() = "Страница на которой расположена ссылка";
    wks_e.cell("C1").value() = "Код запроса";
    wks_e.cell("D1").value() = "Доп информация";
}

Logger::~Logger() {
    doc.save();
    doc.close();
}

void Logger::write_to_xlsx(Url url, Url parent_url, int status_code, std::string error_str) {
    std::lock_guard<std::mutex> guard{write_mutex};

    auto wks = doc.workbook().worksheet(
        status_code == 200? "Success" : "Errors"
    );

    auto& capacitor = status_code == 200? success_line : error_line;

    wks.row(capacitor).values() = std::vector<std::string>{std::move(url), std::move(parent_url), std::to_string(status_code), std::move(error_str)};
    capacitor++;
}
