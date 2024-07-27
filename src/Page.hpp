//
// Created by elpresedente on 24.07.2024.
//

#ifndef PAGE_HPP
#define PAGE_HPP

#include <vector>
#include <optional>

#include <boost/locale.hpp>
#include <gumbo-query/Document.h>
#include <gumbo-query/Node.h>

#include "Types.hpp"
#include "Network.hpp"

namespace Application {

class Page {
public:
    explicit Page(int depth, const std::string &content, Url url, Encoding encoding);
    std::vector<Url>& get_links(const std::string &css_query);
    int depth;
    Url url;
private:
    std::string content;
    Encoding encoding;
    std::optional<std::vector<Url>> links;
};

} // Application

#endif //PAGE_HPP
