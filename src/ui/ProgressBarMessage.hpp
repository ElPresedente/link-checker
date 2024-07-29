//
// Created by elpresedente on 29.07.2024.
//

#ifndef PROGRESSBARMESSAGE_HPP
#define PROGRESSBARMESSAGE_HPP

#include <string>

namespace Application{

class ProgressBarMessage {
public:
    std::string label_text;
    double progress;
    int depth;
};

}

#endif //PROGRESSBARMESSAGE_HPP
