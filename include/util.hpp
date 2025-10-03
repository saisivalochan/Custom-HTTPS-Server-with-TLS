#pragma once
#include <string>
#include <filesystem>
#include <chrono>
#include <ctime>
#include <fstream>

inline std::string http_date() {
    using clock_type = std::chrono::system_clock;
    auto now = clock_type::now();
    std::time_t t = clock_type::to_time_t(now);
    char buf[64];
#if defined(_WIN32)
    std::tm tm_buf;
    gmtime_s(&tm_buf, &t);
    std::strftime(buf, sizeof(buf), "%a, %d %b %Y %H:%M:%S GMT", &tm_buf);
#else
    std::tm tm_buf;
    gmtime_r(&t, &tm_buf);
    std::strftime(buf, sizeof(buf), "%a, %d %b %Y %H:%M:%S GMT", &tm_buf);
#endif
    return buf;
}

inline std::string mime_type(std::string const& path) {
    auto ext = std::filesystem::path(path).extension().string();
    for (auto& c : ext) c = static_cast<char>(std::tolower(c));
    if (ext == ".htm" || ext == ".html") return "text/html";
    if (ext == ".css")  return "text/css";
    if (ext == ".txt")  return "text/plain";
    if (ext == ".js")   return "application/javascript";
    if (ext == ".json") return "application/json";
    if (ext == ".png")  return "image/png";
    if (ext == ".jpg" || ext == ".jpeg") return "image/jpeg";
    if (ext == ".gif")  return "image/gif";
    if (ext == ".svg")  return "image/svg+xml";
    if (ext == ".ico")  return "image/x-icon";
    return "application/octet-stream";
}

inline std::string sanitize_target(const std::string& target) {
    if (target.empty() || target[0] != '/') return {};
    if (target.find("..") != std::string::npos) return {};
    return target;
}

inline bool slurp_file(const std::filesystem::path& p, std::string& out) {
    std::ifstream ifs(p, std::ios::binary);
    if (!ifs) return false;
    ifs.seekg(0, std::ios::end);
    std::streamoff sz = ifs.tellg();
    if (sz < 0) return false;
    out.resize(static_cast<size_t>(sz));
    ifs.seekg(0, std::ios::beg);
    ifs.read(out.data(), static_cast<std::streamsize>(out.size()));
    return true;
}

inline void log_line(const std::string& ip,
                     const std::string& method,
                     const std::string& target,
                     unsigned status,
                     const std::string& tls_ver,
                     const std::string& cipher)
{
    std::cout
        << "[" << http_date() << "] "
        << ip << " " << method << " " << target
        << " -> " << status
        << (tls_ver.empty() ? "" : (" tls=" + tls_ver))
        << (cipher.empty() ? "" : (" cipher=" + cipher))
        << "\n";
}
