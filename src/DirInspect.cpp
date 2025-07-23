#include "DirInspect.h"

#include <iostream>
#include <filesystem>
#include <format>

#include "tabulate/tabulate.hpp"

namespace fs = std::filesystem;


void dirinspect::DirInspect::printDirectoryContents(const std::string_view dirPathStr, bool recursive) const
{
    const fs::path dirPath{ dirPathStr };

    if (!fs::exists(dirPath))
    {
        std::cout << std::format("Directory {} not found\n", dirPathStr);
        return;
    }

    tabulate::Table table;
    table.add_row({ "Directory", "File", "Size" });

    int rows{ 0 };
    std::uintmax_t totalSize{ 0 };
    for (const auto& dir_entry : fs::directory_iterator{ dirPath })
    {

        auto path = dir_entry.path();
        if (fs::is_directory(dir_entry.status()))
        {
            if (recursive)
            {
                printDirectoryContents(path.c_str(), true);
            }
            continue;
        }


        if (!m_Extensions.empty())
        {
            auto ext = path.extension().string();

            if (ext.empty() || std::find(m_Extensions.begin(), m_Extensions.end(), ext) == m_Extensions.end())
            {
                continue;
            }
        }

        auto fileSize = fs::file_size(path);
        auto outputVal = HumanReadable{ fileSize };

        table.add_row({ path.parent_path().c_str(), path.filename().c_str(), outputVal.GetValue() });
        totalSize += fileSize;
        ++rows;
    }

    if (rows > 0)
    {
        std::cout << table << std::endl;
    }

    tabulate::Table summary;
    summary.add_row({ "Summary", dirPath.c_str() });
    summary.add_row({ "Total Files", std::format("{}", rows) });
    summary.add_row({ "Total Size", HumanReadable{totalSize}.GetValue() });
    std::cout << summary << std::endl;
}
