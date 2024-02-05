#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

std::ifstream openFile(const std::string& fileName);
void printFileContent(std::ifstream& file);
std::vector<std::string> findLongestWordsInLine(const std::string& line);
void processFile(const std::string& fileName);
int handleArguments(int argc, char* argv[]);


int main(int argc, char* argv[]) {
    return handleArguments(argc, argv);
}

int handleArguments(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>\n";
        return 1;
    }
    processFile(argv[1]);
    return 0;
}

std::ifstream openFile(const std::string& fileName) {
    std::ifstream file(fileName);
    if (!file.is_open()) {
        std::cerr << "Can't open the file!" << std::endl;
        exit(1);
    }
    return file;
}

void printFileContent(std::ifstream& file) {
    std::string line;
    std::cout << "Original file content:\n";
    while (getline(file, line)) {
        std::cout << line << std::endl;
    }
}

std::vector<std::string> findLongestWordsInLine(const std::string& line) {
    std::istringstream iss(line);
    std::vector<std::string> longestWords;
    std::string word;
    int maxLength = 0;

    while (iss >> word) {
        if (word.length() > maxLength) {
            maxLength = word.length();
            longestWords.clear();
            longestWords.push_back(word);
        }
        else if (word.length() == maxLength) {
            longestWords.push_back(word);
        }
    }
    return longestWords;
}

void processFile(const std::string& fileName) {
    std::ifstream file = openFile(fileName);
    printFileContent(file);
    file.clear();
    file.seekg(0, std::ios::beg);

    std::string line;
    int lineNumber = 1;
    std::cout << "Processing each line:\n";
    while (getline(file, line)) {
        if (line.empty()) continue;

        auto longestWords = findLongestWordsInLine(line);
        if (!longestWords.empty()) {
            std::cout << "String: " << lineNumber << ", Longest words: ";
            for (const auto& word : longestWords) {
                std::cout << word << " ";
            }
            std::cout << ", Length: " << longestWords[0].length() << std::endl;
        }

        lineNumber++;
    }
    file.close();
}
