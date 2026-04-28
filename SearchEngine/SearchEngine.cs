using System;
using System.Collections.Generic;
using System.Linq;

// Класс поискового движка
class SearchEngine
{
    // Индекс: слово -> (документ -> частота)
    private Dictionary<string, Dictionary<int, int>> index =
        new Dictionary<string, Dictionary<int, int>>();

    // Добавление документа в индекс
    public void AddDocument(int id, string text)
    {
        if (string.IsNullOrWhiteSpace(text))
            return;

        // Разделяем текст на слова по пробелам
        var words = text.Split((char[])null, StringSplitOptions.RemoveEmptyEntries);
        foreach (var w in words)
        {
            var word = w;
            if (!index.TryGetValue(word, out var docMap))
            {
                docMap = new Dictionary<int, int>();
                index[word] = docMap;
            }

            if (!docMap.TryGetValue(id, out var freq))
                docMap[id] = 1;
            else
                docMap[id] = freq + 1;
        }
    }

    // Поиск документов по запросу
    public List<KeyValuePair<int,int>> Search(string query)
    {
        var score = new Dictionary<int, int>();

        if (!string.IsNullOrWhiteSpace(query))
        {
            var words = query.Split((char[])null, StringSplitOptions.RemoveEmptyEntries);
            foreach (var w in words)
            {
                if (!index.TryGetValue(w, out var docMap))
                    continue;

                foreach (var kv in docMap)
                {
                    var doc = kv.Key;
                    var freq = kv.Value;
                    if (!score.TryGetValue(doc, out var s))
                        score[doc] = freq;
                    else
                        score[doc] = s + freq;
                }
            }
        }

        // Сортировка: сначала по убыванию score, затем по возрастанию doc id
        var result = score.ToList();
        result.Sort((a, b) =>
        {
            int cmp = b.Value.CompareTo(a.Value);
            if (cmp != 0) return cmp;
            return a.Key.CompareTo(b.Key);
        });

        return result;
    }
}

// Пример использования
class Program
{
    static void Main()
    {
        var engine = new SearchEngine();

		// Добавляем документы
        engine.AddDocument(1, "apple banana apple");
        engine.AddDocument(2, "banana orange");
        engine.AddDocument(3, "apple orange apple apple");
        engine.AddDocument(4, "banana apple");

		Console.WriteLine("Query: apple");
        var r1 = engine.Search("apple");
        foreach (var kv in r1)
            Console.WriteLine($"doc {kv.Key} score={kv.Value}");

        Console.WriteLine();
        Console.WriteLine("Query: apple banana");
        var r2 = engine.Search("apple banana");
        foreach (var kv in r2)
            Console.WriteLine($"doc {kv.Key} score={kv.Value}");
    }
}