#include <iostream>
#include <filesystem>
#include <format>
#include <vector>

#include "CLI11/CLI11.hpp"
#include "tabulate/tabulate.hpp"

#include "DirInspect.h"



int main(int argc, char** argv)
{
    CLI::App app{ "Directory Inspector", "DirInspect" };
    dirinspect::DirInspectConfig config{};

    std::vector<std::string> directories;
    app.add_option("-D, --directories", directories, "Target directories")->required();
    app.add_option("--ext", config.extensions, "File extensions to include (e.g. .txt .md)")
        ->expected(-1);

    app.add_flag("-R, --recursive", config.recursive, "Recursively inspect directories");
    app.add_flag("-S, --summary-only", config.summaryOnly, "Print summary only, no file details");

    app.set_config("-C, --config",
        "config.ini",
        "Read an ini file");

    CLI11_PARSE(app, argc, argv);

    dirinspect::DirInspect dirInspector{ config };
    dirInspector.PrintDirectoriesContents(directories);

    return 0;
}

