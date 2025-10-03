#pragma once
#include <boost/beast/http.hpp>
#include <filesystem>
#include "file_responder.hpp"

namespace http = boost::beast::http;

class Router {
public:
    explicit Router(std::filesystem::path doc_root);
    http::response<http::string_body>
    route(const http::request<http::string_body>& req);

private:
    FileResponder files_;
};
