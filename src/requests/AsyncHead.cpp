//
// Created by elpresedente on 24.07.2024.
//

#include "AsyncHead.hpp"
using namespace Application::Requests;

AsyncHead::AsyncHead(cpr::AsyncWrapper<cpr::Response> resp_promise) : promise(std::move(resp_promise)) {}

bool AsyncHead::get(){
    promise.wait();
    auto response = promise.get();
    if(response.status_code != 200)
        return false;
    else
        return true;
}
