#include "text_stats.h"

#include <map>
#include <sstream>
#include <stdexcept>
#include <string>

#include <gtest/gtest.h>

namespace {

/// Считает частоты слов в строке.
std::map<std::string, std::size_t> CountFrom(const std::string& text) {
    std::istringstream input(text);
    return textstats::CountWords(input);
}

}  // namespace

TEST(TextStats, CountsWords) {
    const std::map<std::string, std::size_t> counts = CountFrom("a b a");
    ASSERT_EQ(counts.size(), 2u);
    EXPECT_EQ(counts.at("a"), 2u);
    EXPECT_EQ(counts.at("b"), 1u);
}

TEST(TextStats, IgnoresCaseAndPunctuation) {
    const std::map<std::string, std::size_t> counts = CountFrom("Cat, cat! CAT?");
    ASSERT_EQ(counts.size(), 1u);
    EXPECT_EQ(counts.at("cat"), 3u);
}

TEST(TextStats, EmptyInputGivesEmptyResult) {
    EXPECT_TRUE(CountFrom("").empty());
}

TEST(TextStats, ThrowsOnMissingFile) {
    EXPECT_THROW(textstats::CountWordsInFile("no_such_file_12345.txt"), std::runtime_error);
}

TEST(TextStats, TopWordsSortedByCountThenAlphabet) {
    const std::vector<textstats::WordCount> rows = textstats::TopWords(CountFrom("b a b c a b"), 3);
    ASSERT_EQ(rows.size(), 3u);
    EXPECT_EQ(rows[0].first, "b");
    EXPECT_EQ(rows[0].second, 3u);
    EXPECT_EQ(rows[1].first, "a");
    EXPECT_EQ(rows[1].second, 2u);
    EXPECT_EQ(rows[2].first, "c");
}

TEST(TextStats, TopWordsRespectsLimit) {
    const std::vector<textstats::WordCount> rows =
        textstats::TopWords(CountFrom("one two three four five"), 2);
    EXPECT_EQ(rows.size(), 2u);
}

TEST(TextStats, FiltersShortWords) {
    const textstats::Counts counts = CountFrom("a cat dog");
    const textstats::Counts filtered = textstats::FilterByLength(counts, 3);
    ASSERT_EQ(filtered.size(), 2u);
    EXPECT_EQ(filtered.at("cat"), 1u);
    EXPECT_EQ(filtered.count("a"), 0u);
}
