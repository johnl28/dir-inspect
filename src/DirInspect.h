#pragma once
#include <filesystem>
#include <format>
#include <math.h>
#include <vector>
#include <map>
#include <string>

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

            constexpr const char* units[]{ "B", "KB", "MB", "GB", "TB", "PB" };
            return std::format("{}{}", std::ceil(mantissa * 10.) / 10., units[o]);
        }
    };



    class DirInspect {
    public:
        DirInspect(const DirInspectConfig& config);
        ~DirInspect() = default;

        void PrintDirectoriesContents(const std::vector<std::string>& directories) const;
        void PrintDirectoryContents(std::string_view dirPath) const;

    protected:
        bool IsExtensionRequired(const std::string& ext) const;
        void PrintSummary(std::string_view dirPath, int totalFiles, uintmax_t totalSize, const std::map<std::string, int>& extensionCount) const;

    private:
        DirInspectConfig m_Config;

    };


};