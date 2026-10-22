#include "text_stats.h"

#include <cstddef>
#include <exception>
#include <iostream>
#include <stdexcept>
#include <string>

namespace {

/// Печатает подсказку по запуску программы.
void PrintUsage() {
    std::cout << "usage: textstats <file> [--top N]\n";
}

/// Разбирает строку как неотрицательное число.
std::size_t ParseCount(const std::string& text) {
    std::size_t consumed = 0;
    const unsigned long value = std::stoul(text, &consumed);
    if (consumed != text.size()) {
        throw std::runtime_error("not a number: " + text);
    }
    return static_cast<std::size_t>(value);
}

}  // namespace

int main(int argc, char** argv) {
    std::string path;
    std::size_t top = 10;

    try {
        for (int index = 1; index < argc; ++index) {
            const std::string argument = argv[index];
            if (argument == "--top" && index + 1 < argc) {
                top = ParseCount(argv[++index]);
            } else if (path.empty()) {
                path = argument;
            } else {
                std::cerr << "unknown argument: " << argument << '\n';
                PrintUsage();
                return 2;
            }
        }
    } catch (const std::exception& error) {
        std::cerr << "error: " << error.what() << '\n';
        return 2;
    }

    if (path.empty()) {
        PrintUsage();
        return 2;
    }

    try {
        const std::map<std::string, std::size_t> counts = textstats::CountWordsInFile(path);
        for (const textstats::WordCount& row : textstats::TopWords(counts, top)) {
            std::cout << row.first << ": " << row.second << '\n';
        }
    } catch (const std::exception& error) {
        std::cerr << "error: " << error.what() << '\n';
        return 1;
    }
    return 0;
}
