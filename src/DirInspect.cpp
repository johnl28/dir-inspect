#include "DirInspect.h"

#include <iostream>
#include <filesystem>
#include <format>
#include <map>

#include "tabulate/tabulate.hpp"

namespace fs = std::filesystem;


dirinspect::DirInspect::DirInspect(const dirinspect::DirInspectConfig& config)
    : m_Config(config) 
{
}

void dirinspect::DirInspect::PrintDirectoriesContents(const std::vector<std::string>& directories) const
{
    for (const auto& dirPath : directories)
    {
        PrintDirectoryContents(dirPath);
        std::cout << "\n\n\n";
    }
}

void dirinspect::DirInspect::PrintDirectoryContents(std::string_view dirPathStr) const
{
    const fs::path dirPath{ dirPathStr };

    if (!fs::exists(dirPath))
    {
        std::cout << std::format("Directory {} not found", dirPathStr) << std::endl;
        return;
    }

    tabulate::Table table;
    table.add_row({ "Directory", "File", "Size" });

    int totalFiles{ 0 };
    std::map<std::string, int> extensionCount;
    std::uintmax_t totalSize{ 0 };

    auto reqExt = m_Config.extensions;

    for (const auto& dir_entry : fs::directory_iterator{ dirPath })
    {

        auto path = dir_entry.path();
        if (fs::is_directory(dir_entry.status()))
        {
            if (m_Config.recursive)
            {
                PrintDirectoryContents(path.c_str());
            }
            continue;
        }


        auto ext = path.extension().string();

        if (!IsExtensionRequired(ext))
        {
            continue;
        }


        if (extensionCount.find(ext) == extensionCount.end())
        {
            extensionCount[ext] = 1;
        }
        else
        {
            ++extensionCount[ext];
        }

        auto fileSize = fs::file_size(path);
        auto outputVal = HumanReadable{ fileSize };

        table.add_row({ path.parent_path().c_str(), path.filename().c_str(), outputVal.GetValue() });
        totalSize += fileSize;
        ++totalFiles;
    }

    if (!m_Config.summaryOnly && totalFiles > 0)
    {
        std::cout << table << std::endl;
    }

    PrintSummary(dirPathStr, totalFiles, totalSize, extensionCount);

}

void dirinspect::DirInspect::PrintSummary(std::string_view dirPath, int totalFiles, uintmax_t totalSize, const std::map<std::string, int>& extensionCount) const
{

    tabulate::Table summary;
    summary.add_row({ "Summary", dirPath });

    for (const auto& [ext, count] : extensionCount)
    {
        const auto totalFiles = std::format("Total {} files", ext);
        const auto totalFilesNumber = std::format("{}", count);

        summary.add_row({ totalFiles, totalFilesNumber });
    }

    summary.add_row({ "Total Files", std::format("{}", totalFiles) });

    summary.add_row({ "Total Size", HumanReadable{totalSize}.GetValue() });
    std::cout << summary << std::endl;

}

bool dirinspect::DirInspect::IsExtensionRequired(const std::string& ext) const
{
    if (m_Config.extensions.empty())
    {
        return true; // If no extensions specified, include all files
    }

    return std::find(m_Config.extensions.begin(), m_Config.extensions.end(), ext) != m_Config.extensions.end();
}
