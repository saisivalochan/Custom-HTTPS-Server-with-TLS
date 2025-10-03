#pragma once
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/asio.hpp>
#include <memory>

class HttpRedirectSession : public std::enable_shared_from_this<HttpRedirectSession> {
public:
    HttpRedirectSession(boost::asio::ip::tcp::socket&& socket,
                        unsigned short https_port);

    void run(); // blocking single-request redirect

private:
    boost::asio::ip::tcp::socket socket_;
    boost::beast::flat_buffer buffer_;
    unsigned short https_port_;
};
