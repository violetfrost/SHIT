#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <regex>

/*
 * Simple HTML Include Tool
 * See LICENSE.md for details
 */

// Side note, I really hate regex.
// Like seriously, vehemently hate regex.
// It works, though. Second try, too!
static const std::regex CustomTagRegex(R"re(^\s*<%\s*(?:"([^"]+)"|([^\s>]+))\s*%>\s*$)re");
// We want to set this up outside of a loop because... well, duh ^

/// @brief Check whether or not a directory exists in the filesystem
/// @param path The directory you want to checks
/// @return True if the path exists, false if not.
bool does_dir_exist(std::filesystem::path path)
{
    return std::filesystem::exists(path);
}

/// @brief Compiles an HTML file with SHIT templates into a final deliverable
/// @param path Path to the file you want to compile
/// @return The compiled file, as a string array.
std::vector<std::string> compile_html_file(std::string path)
{
    std::vector<std::string> compiledFile;

    // Emergency breakout for if there's some filesystem fuckery going on
    std::ifstream file(path);
    if (!file.is_open())
    {
        std::cerr << "Failed to open file " << path << std::endl;
        return compiledFile;
    }

    // Now we have access to the file and can actually begin to compile it
    std::vector<std::string> exportLines;
    std::string line;
    while (std::getline(file, line))
    {
        std::smatch match;
        if (std::regex_match(line, match, CustomTagRegex))
        {
            // We have a regex match! A custom tag was detected...
            // If we didn't get a quoted or unquoted path, we continue the loop.
            if (!match[1].matched && !match[2].matched)
                continue;
            
            // This is probably really stupid code but it works. Convert relative paths from the tag into absolute directories.
            std::string relativePath = match[1].matched ? match[1].str() : match[2].str();
            std::string templatePath = path.substr(0, path.find_last_of("/\\") + 1) + relativePath;
            std::vector<std::string> compiledTemplate = compile_html_file(templatePath); // Recursive!

            // TODO do we want to add protections to prevent users from fork bombing themselves?
            // Too lazy to do it right now.
            
            compiledFile.insert(compiledFile.end(), compiledTemplate.begin(), compiledTemplate.end());
        } else {
            compiledFile.push_back(line);
        }
    }

    return compiledFile;
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

    std::vector<std::string> htmlFiles;

    for (const auto &entry : std::filesystem::recursive_directory_iterator(inputPath))
    {
        if (entry.is_regular_file() && entry.path().extension() == ".html")
        {
            htmlFiles.push_back(entry.path().string());
        }
    }

    if (htmlFiles.size() == 0)
    {
        std::cerr << "The input directory contains no HTML files." << std::endl;
        return 101;
    }

    // Iterate over all of the HTML filepaths in the input directory & its children
    for (int i = 0; i < htmlFiles.size(); i++)
    {
        std::vector<std::string> compiled = compile_html_file(htmlFiles[i]);
        
        std::cout << std::endl << std::endl << "HTML FILE GENERATED FROM " << htmlFiles[i] << std::endl << std::endl;

        for(int x = 0; x < compiled.size(); x++)
        {
            std::cout  << compiled[x] << std::endl;
        }
    }

    return 0;
}