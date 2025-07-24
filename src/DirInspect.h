#pragma once
#include <filesystem>
#include <format>
#include <math.h>
#include <vector>

namespace dirinspect {

    struct DirInspectConfig
    {
        bool summaryOnly{ false };
        bool recursive{ false };
        std::vector<std::string> extensions;
    };


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
        DirInspect(const DirInspectConfig& config);
        ~DirInspect() = default;

        void PrintDirectoriesContents(const std::vector<std::string>& directories) const;
        void PrintDirectoryContents(const std::string_view dirPath) const;

    private:
        DirInspectConfig m_Config;

    };


};