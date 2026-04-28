#include <iostream>
#include <unordered_map>
#include <vector>
#include <sstream>
#include <cmath>

std::vector<std::string> tokenize(const std::string& text)
{
    std::vector<std::string> words;
    std::stringstream ss(text);
    std::string w;

    while (ss >> w)
        words.push_back(w);

    return words;
}

std::unordered_map<std::string, int>
word_freq(const std::vector<std::string>& words)
{
    std::unordered_map<std::string, int> freq;

    for (auto& w : words)
        freq[w]++;

    return freq;
}

double cosine_similarity(
    const std::unordered_map<std::string, int>& A,
    const std::unordered_map<std::string, int>& B)
{
    double dot = 0;
    double lenA = 0;
    double lenB = 0;

    for (auto& [w, c] : A)
    {
        lenA += c * c;

        if (B.count(w))
            dot += c * B.at(w);
    }

    for (auto& [w, c] : B)
        lenB += c * c;

    lenA = std::sqrt(lenA);
    lenB = std::sqrt(lenB);

    if (lenA == 0 || lenB == 0)
        return 0;

    return dot / (lenA * lenB);
}

int main()
{
    std::string t1 =
        "machine learning improves search";

    std::string t2 =
        "search engines use machine learning";

    auto w1 = tokenize(t1);
    auto w2 = tokenize(t2);

    auto f1 = word_freq(w1);
    auto f2 = word_freq(w2);

    std::cout << cosine_similarity(f1, f2) << "\n";
}