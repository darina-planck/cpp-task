#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

int main() {
    // русский ввод не работает
    setlocale(LC_ALL, "RU");
    string massage;
    int min_size = 0, max_size = 0;
    vector<string> words={};
    vector<string> max={};
    vector<string> min={};

    cout << "Введите строку " << "\n";
    getline(cin, massage);
    // istringstream позволяет "читать" строку massage как поток ввода

    istringstream stream(massage); // строка massage содержится внутри потока stream и мы можем из нее извлекать слова
    string word; // для вычленения отдельных слов из строки
    while (stream >> word) { // последовательное извлечение слов из строки которые автоматом разделяются по пробелам
        words.push_back(word);
    } // каждое слово поочерёдно считывается и сохраняется в переменной word, а затем добавляется в массив words
    min_size = words[0].size();
    max_size = words[0].size();
    for (int i = 0; i < words.size(); i++) {
        int len = words[i].size();
        if (len < min_size) {
            min_size = len;
            min.clear();
            min.push_back(words[i]);
            
        } else if (len == min_size) {
            min.push_back(words[i]);
        }
           
        if (len > max_size) {
            max_size = len;
            max.clear();
            max.push_back(words[i]);
        } else if (len == max_size) {
            max.push_back(words[i]);
        }
    }
    cout << "Самое длинное слово: ";
    for (const string &w : max)
    {
        cout << w << " ";
    }
    cout << "\nСамое короткое слово: ";
    for (const string &w : min)
    {
        cout << w << " ";
    }
    return 0;
}