#include "text_stats.h"

#include <algorithm>
#include <cctype>
#include <fstream>
#include <stdexcept>

namespace textstats {
namespace {

/// Символ относится к слову, если это буква или цифра.
bool IsWordChar(unsigned char symbol) {
    return std::isalnum(symbol) != 0;
}

}  // namespace

std::string Normalize(const std::string& word) {
    std::size_t begin = 0;
    std::size_t end = word.size();
    while (begin < end && !IsWordChar(static_cast<unsigned char>(word[begin]))) {
        ++begin;
    }
    while (end > begin && !IsWordChar(static_cast<unsigned char>(word[end - 1]))) {
        --end;
    }

    std::string result;
    result.reserve(end - begin);
    for (std::size_t index = begin; index < end; ++index) {
        const unsigned char symbol = static_cast<unsigned char>(word[index]);
        result.push_back(static_cast<char>(std::tolower(symbol)));
    }
    return result;
}

std::map<std::string, std::size_t> CountWords(std::istream& input) {
    std::map<std::string, std::size_t> counts;
    std::string token;
    while (input >> token) {
        const std::string word = Normalize(token);
        if (!word.empty()) {
            ++counts[word];
        }
    }
    return counts;
}

std::vector<WordCount> TopWords(const std::map<std::string, std::size_t>& counts,
                                std::size_t limit) {
    std::vector<WordCount> rows(counts.begin(), counts.end());
    std::sort(rows.begin(), rows.end(), [](const WordCount& left, const WordCount& right) {
        if (left.second != right.second) {
            return left.second > right.second;
        }
        return left.first < right.first;
    });

    if (rows.size() > limit) {
        rows.resize(limit);
    }
    return rows;
}

std::map<std::string, std::size_t> CountWordsInFile(const std::string& path) {
    std::ifstream input(path);
    if (!input.is_open()) {
        throw std::runtime_error("cannot open file: " + path);
    }
    return CountWords(input);
}

}  // namespace textstats
