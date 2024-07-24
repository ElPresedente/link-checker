//
// Created by elpresedente on 24.07.2024.
//

#ifndef ASYNCGET_HPP
#define ASYNCGET_HPP

#include <cpr/async_wrapper.h>


namespace Application::Requests {


class AsyncGet {
public:
    explicit AsyncGet(cpr::AsyncWrapper<cpr::Response>);

    cpr::Response get();

private:
    cpr::AsyncWrapper<cpr::Response> promise;
};


}


#endif //ASYNCGET_HPP
