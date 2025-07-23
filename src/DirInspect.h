#pragma once
#include <filesystem>
#include <format>
#include <math.h>
#include <vector>

namespace dirinspect {

    struct HumanReadable
    {
        std::uintmax_t size{};

        std::string GetValue() const
        {
            int o{ 0 };
            double mantissa = size;

            for (; mantissa >= 1024.; mantissa /= 1024., ++o);

            constexpr const char* units[]{ "B", "KB", "MB", "GB", "TB", "PB", "EB", "ZB", "YB" };
            return std::format("{}{}", std::ceil(mantissa * 10.) / 10., units[o]);
        }
    };



    class DirInspect {
    public:
        DirInspect(const std::vector<std::string>& extensions) : m_Extensions(extensions) {};
        ~DirInspect() = default;


        void printDirectoryContents(const std::string_view dirPath, bool recursive) const;


    private:
        std::vector<std::string> m_Extensions{};


    };



};