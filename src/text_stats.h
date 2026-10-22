#pragma once

#include <cstddef>
#include <istream>
#include <map>
#include <string>
#include <utility>
#include <vector>

namespace textstats {

/// Пара «слово — число вхождений».
using WordCount = std::pair<std::string, std::size_t>;

/// Частоты слов: слово → число вхождений.
using Counts = std::map<std::string, std::size_t>;

/// Приводит слово к нижнему регистру и отбрасывает пунктуацию по краям.
std::string Normalize(const std::string& word);

/// Считает частоты слов в потоке. Слова разделены пробельными символами.
std::map<std::string, std::size_t> CountWords(std::istream& input);

/// Возвращает не более limit слов, отсортированных по убыванию частоты,
/// при равной частоте — по алфавиту.
std::vector<WordCount> TopWords(const std::map<std::string, std::size_t>& counts,
                                std::size_t limit);

/// Отбрасывает слова длиной меньше min_length символов.
Counts FilterByLength(const Counts& counts, std::size_t min_length);

/// Читает файл и возвращает частоты слов.
/// Бросает std::runtime_error, если файл не удалось открыть.
std::map<std::string, std::size_t> CountWordsInFile(const std::string& path);

}  // namespace textstats
