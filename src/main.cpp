#include <algorithm>
#include <cctype>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

// Get the filesystem
namespace fs = std::filesystem;

// Count how many times `word` appears in `text` (case-insensitive, non-overlapping)
size_t countOccurrences(const std::string& text, const std::string& word) {
    if (word.empty()) return 0;
    std::string lowerText = text, lowerWord = word;

    // To lowercase (using c++20 ranges)
    std::ranges::transform(lowerText,  lowerText.begin(), ::tolower);
    std::ranges::transform(lowerWord, lowerWord.begin(), ::tolower);

    // Loop through the text and count the number of times the word shows up
    size_t count = 0, pos = 0;

    // Check if the lower word is an empty string (to prevent infinite while loop)
    if(lowerWord.empty()) {
        return count;
    }

    // std::cout << lowerText << "\n";

    // Find the first occurrence of lowerWord AFTER index 'pos'. If it doesn't return npos, continue.
    while ((pos = lowerText.find(lowerWord, pos)) != std::string::npos) {
        // We found a word
        ++count;

        // Move pos to the next word
        pos += lowerWord.length();
    }

    // Return the number of words
    return count;
}

int main(int argc, char* argv[]) {
    // Start timer
    auto start = std::chrono::high_resolution_clock::now();

    if (argc != 2) {
        // Show users what they need to type in
        std::cerr << "Usage: " << argv[0] << " <path-to-csv-folder>\n";
        return 1;
    }

    // Get the path
    fs::path folder = argv[1];

    // If it's not a folder, throw err
    if (!fs::is_directory(folder)) {
        std::cerr << "Error: not a directory: " << folder << "\n";
        return 2;
    }

    // Word counter init
    size_t total = 0;

    // Loop through every file in the folder
    for (auto& entry : fs::directory_iterator(folder)) {
        // Skip directories, sockets, symlinks etc...
        if (!entry.is_regular_file()) continue;

        // Skip all files with no .csv extension
        if (entry.path().extension() != ".csv") continue;

        // Open file at entry.path() and put it inside the infile object.
        std::ifstream infile(entry.path());

        // If the file fail to open?
        if (!infile) {
            std::cerr << "Warning: cannot open " << entry.path() << "\n";
            continue;
        }

        // Initialise a string (it will hold the contents of the file)
        std::string line;

        // Read, line by line, and count the occurrences of 'ian' in said line
        while (std::getline(infile, line)) {
            total += countOccurrences(line, "ian");
        }
    }

    // Present result
    std::cout << "Found “Ian” " << total << " times across all CSVs.\n";

    // Stop timer
    auto stop = std::chrono::high_resolution_clock::now();
    auto elapsed = stop - start;  // a std::chrono::duration

    // Convert to milliseconds (as double)
    double ms = duration_cast<std::chrono::duration<double, std::milli>>(elapsed).count();

    if (ms < 1000.0) {
        // < 1 second
        std::cout << "Time taken: " << ms << " milliseconds\n";
    }
    else {
        double sec = ms / 1000.0;
        if (sec < 60.0) {
            // < 1 minute
            std::cout << "Time taken: " << sec << " seconds\n";
        }
        else {
            double mins = sec / 60.0;
            std::cout << "Time taken: " << mins << " minutes\n";
        }
    }
    
    // Exit
    return 0;
}
