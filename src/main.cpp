#include <iostream>
#include <filesystem>
#include <format>
#include <vector>

#include "CLI11/CLI11.hpp"
#include "tabulate/tabulate.hpp"

#include "DirInspect.h"



int main(int argc, char** argv)
{
    CLI::App app{ "Directory Inspector", "dir-inspect" };

    std::string dirPathStr;
    app.add_option("-D, --directory", dirPathStr, "Target directory")->required();

    bool recursive{ false };
    app.add_flag("-r, --recursive", recursive, "Recursively inspect directories");

    std::vector<std::string> extensions{};
    app.add_option("--ext", extensions, "File extensions to include (e.g. .txt, .md)")
        ->expected(-1);

    app.set_config("-c, --config",
        "config.ini",
        "Read an ini file");

    CLI11_PARSE(app, argc, argv);


    if (dirPathStr.empty()) {
        std::cerr << "Error: Directory path is required." << std::endl;
        return 1;
    }

    std::cout << "Including files with extension: ";
    for (const auto& ext : extensions) {
        std::cout << " " << ext;
    }
    std::cout << std::endl;

    dirinspect::DirInspect dirInspector{ extensions };
    dirInspector.printDirectoryContents(dirPathStr, recursive);


    return 0;
}

