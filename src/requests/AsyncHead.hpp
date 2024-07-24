//
// Created by elpresedente on 24.07.2024.
//

#ifndef ASYNCHEAD_HPP
#define ASYNCHEAD_HPP

#include <cpr/async_wrapper.h>


namespace Application::Requests{

class AsyncHead {
public:
    explicit AsyncHead(cpr::AsyncWrapper<cpr::Response>);

    bool get();
private:
    cpr::AsyncWrapper<cpr::Response> promise;
};

}

#endif //ASYNCHEAD_HPP
