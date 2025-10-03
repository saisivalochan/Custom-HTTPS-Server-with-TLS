#pragma once
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/ssl.hpp>
#include <boost/asio.hpp>
#include <memory>
#include <filesystem>

class HttpsSession : public std::enable_shared_from_this<HttpsSession> {
public:
    HttpsSession(boost::asio::ip::tcp::socket&& socket,
                 boost::asio::ssl::context& ctx,
                 std::filesystem::path doc_root);

    void run(); // blocking per-connection loop

private:
    void perform_handshake();
    void serve_loop();

    boost::beast::ssl_stream<boost::beast::tcp_stream> stream_;
    boost::beast::flat_buffer buffer_;
    std::string client_ip_;
    std::string tls_version_;
    std::string cipher_;
    std::filesystem::path doc_root_;
};
