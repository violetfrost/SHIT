#include <iostream>
#include <filesystem>

/*
 * Simple HTML Include Tool
 * See LICENSE.md for details
 */

/// @brief Check whether or not a directory exists in the filesystem
/// @param path The directory you want to checks
/// @return True if the path exists, false if not.
bool does_dir_exist(std::filesystem::path path)
{
    return std::filesystem::exists(path);
}

/// @brief Program entry point
/// @param argc Number of command line arguments
/// @param argv Array of provided command line arguments as strings
/// @return Program exit code.
int main(int argc, char *argv[])
{
    std::filesystem::path inputPath;
    std::filesystem::path outputPath;

    // We want to check for the program arguments
    // -i is the input folder, -o is the output folder
    for (int i = 0; i < argc; i++)
    {
        std::string arg = argv[i];

        if (arg == "-i" && i + 1 < argc)
            inputPath = argv[i + 1];
        if (arg == "-o" && i + 1 < argc)
            outputPath = argv[i + 1];
    }

    // One or more of the arguments isn't present for some reason
    if (inputPath.empty() || outputPath.empty())
    {
        std::cerr << "Missing or malformed arguments." << std::endl;
        std::cerr << "Usage: shit -i path_to_import_folder -o path_to_export_folder" << std::endl;
        return 100;
    }

    // One of the file paths doesn't exist
    // TODO create ouput dir if nonexistent, maybe?
    if (!does_dir_exist(inputPath) || !does_dir_exist(outputPath))
    {
        std::cerr << "One or more of the provided paths does not exist." << std::endl;
        return 101;
    }

    // Iterate over all the files in the input directory looking for HTML files
    // TODO make recursive
    std::vector<std::string> htmlFiles;

    for (const auto &entry : std::filesystem::directory_iterator(inputPath))
    {
        if (entry.is_regular_file() && entry.path().extension() == ".html")
        {
            htmlFiles.push_back(entry.path().string());
        }
    }

    // That bitch has no HTML files
    if (htmlFiles.size() == 0)
    {
        std::cerr << "The input directory contains no HTML files." << std::endl;
        return 101;
    }
    
    for(int i = 0; i < htmlFiles.size(); i++)
    {
        std::cout << htmlFiles[i] << std::endl; 
    }

    return 0;
}