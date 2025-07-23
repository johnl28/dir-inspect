#include <iostream>
#include <filesystem>

#include "CLI11/CLI11.hpp"

#include "DirInspect.h"

namespace fs = std::filesystem;

struct HumanReadable
{
    std::uintmax_t size{};

    private:
        friend std::ostream& operator<<(std::ostream& os, HumanReadable hr)
        {
            int o{};
            double mantissa = hr.size;

            for (; mantissa >= 1024.; mantissa /= 1024., ++o);

            os << std::ceil(mantissa * 10.) / 10. << "BKMGTPE"[o];
            
            return o ? os << "B (" << hr.size << ')' : os;
        }
};


void printDirectoryContents(const fs::path& dirPath, bool recursive = false)
{
    if (!fs::exists(dirPath)) 
    {
        std::cout << "Directory not found\n";
        return;
    }

    for (const auto& dir_entry : fs::directory_iterator{dirPath})
    {
        if (fs::is_directory(dir_entry.status()))
        {
            if (recursive) 
            {
                printDirectoryContents(dir_entry.path(), true);
            }
            continue;
        }
        std::cout << dir_entry.path() << " size = " << HumanReadable{fs::file_size(dir_entry.path())} << '\n';
    } 
}

int main(int argc, char** argv)
{
    CLI::App app{"Directory Inspector", "dir-inspect"};

    std::string dirPathStr;
    app.add_option("-D, --directory", dirPathStr, "Target directory")->required();

    bool recursive = false;
    app.add_flag("-r, --recursive", recursive, "Recursively inspect directories");


    CLI11_PARSE(app, argc, argv);

    const fs::path dirPath{dirPathStr};
    if (!fs::exists(dirPath)) 
    {
        std::cout << "Directory not found\n";
        return 0;
    }

    printDirectoryContents(dirPath, recursive);

 
    return 0;
} 

