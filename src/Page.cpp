//
// Created by elpresedente on 24.07.2024.
//

#include "Page.hpp"

#include <utility>

using namespace Application;

Page::Page(int depth, const std::string &content, Url url, Encoding encoding) :
    depth(depth),
    url(std::move(url)),
    content(boost::locale::conv::to_utf<char>(content, encoding)),
    encoding(std::move(encoding))
{}

std::vector<Url>& Page::get_links(const std::string &css_query) {
    if(links) {
        return *links;
    }
    links.emplace();
    auto& links_vector = *links;

    CDocument document;
    document.parse(content);

    CSelection raw_links = document.find(css_query);

    for(auto i = 0u; i < raw_links.nodeNum(); i++){
        links_vector.emplace_back(Network::normalize_url(raw_links.nodeAt(i).attribute("href"), url));
    }

    return *links;
}

