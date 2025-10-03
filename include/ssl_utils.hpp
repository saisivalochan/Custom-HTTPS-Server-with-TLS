#pragma once
#include <boost/asio/ssl.hpp>
#include <string>

namespace ssl_utils {
    void load_server_certificate(
        boost::asio::ssl::context& ctx,
        const std::string& cert_file,
        const std::string& key_file
    );
}
