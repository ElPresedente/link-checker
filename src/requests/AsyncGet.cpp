//
// Created by elpresedente on 24.07.2024.
//

#include "AsyncGet.hpp"
using namespace Application::Requests;

AsyncGet::AsyncGet(cpr::AsyncWrapper<cpr::Response> request_promise) : promise(std::move(request_promise)) {}

cpr::Response AsyncGet::get() {
    promise.wait();
    return promise.get();
}


