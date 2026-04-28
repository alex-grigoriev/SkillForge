#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>

// Класс поискового движка
class SearchEngine {
private:
    // Индекс: слово -> (документ -> частота)
    std::unordered_map<std::string, std::unordered_map<int, int>> index;

public:
    // Добавление документа в индекс
    void AddDocument(int id, const std::string& text) {
        if (text.empty()) return;

        size_t start = 0;
        while (start < text.size()) {
            // Находим конец слова (по пробелам)
            size_t end = text.find_first_of(" \t\n\r", start);
            if (end == std::string::npos) end = text.size();

            std::string word = text.substr(start, end - start);
            if (!word.empty()) {
                auto& docMap = index[word]; // создаём, если нет
                docMap[id] += 1; // увеличиваем частоту
            }

            start = end + 1;
        }
    }

    // Поиск документов по запросу
    std::vector<std::pair<int,int>> Search(const std::string& query) {
        std::unordered_map<int,int> score;

        if (!query.empty()) {
            size_t start = 0;
            while (start < query.size()) {
                size_t end = query.find_first_of(" \t\n\r", start);
                if (end == std::string::npos) end = query.size();

                std::string word = query.substr(start, end - start);
                if (!word.empty()) {
                    auto it = index.find(word);
                    if (it != index.end()) {
                        for (auto& kv : it->second)
                            score[kv.first] += kv.second;
                    }
                }

                start = end + 1;
            }
        }

        // Сортировка: сначала по убыванию score, затем по возрастанию doc id
        std::vector<std::pair<int,int>> result(score.begin(), score.end());
        std::sort(result.begin(), result.end(),
                  [](const auto& a, const auto& b) {
                      if (b.second != a.second) return b.second < a.second ? false : true;
                      return a.first < b.first;
                  });

        return result;
    }
};

int main() {
    SearchEngine engine;

    // Добавляем документы
    engine.AddDocument(1, "apple banana apple");
    engine.AddDocument(2, "banana orange");
    engine.AddDocument(3, "apple orange apple apple");
    engine.AddDocument(4, "banana apple");

    std::cout << "Query: apple\n";
    auto r1 = engine.Search("apple");
    for (auto& kv : r1)
        std::cout << "doc " << kv.first << " score=" << kv.second << "\n";

    std::cout << "\nQuery: apple banana\n";
    auto r2 = engine.Search("apple banana");
    for (auto& kv : r2)
        std::cout << "doc " << kv.first << " score=" << kv.second << "\n";

    return 0;
}