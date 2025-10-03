#pragma once
#include <boost/beast/http.hpp>
#include <filesystem>
#include <string>

namespace http = boost::beast::http;

class FileResponder {
public:
    explicit FileResponder(std::filesystem::path doc_root);
    http::response<http::string_body>
    serve(const http::request<http::string_body>& req);

private:
    std::filesystem::path root_;
};
