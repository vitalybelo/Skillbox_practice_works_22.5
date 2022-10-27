#include <iostream>
#include <string>
#include <map>
using namespace std;

bool anagramSearch (string &s1, string &s2);

/**
 * С помощью анаграмм многие писатели создавали себе псевдонимы.
 * Среди таких Франсуа Рабле и Льюис Кэрролл. На заре своего творчества они боялись критики.
 * А те, кто хорошо знаком с романами о Гарри Поттере, могут сразу вспомнить, как писательница
 * Джоан Роулинг умело зашифровала имя главного злодея.
 * Лорд Волан-де-Морд во второй книге серии (Гарри Поттер и тайная комната) рассказывает,
 * что его настоящее имя Том Марволо Реддл. И это тоже яркий пример анаграммы.
 * (на русском не сработает)
 */

int main() {
    setlocale(LC_ALL, "RUS");

    string s1[] {"лекарство","стекловар"};
    string s2[] {"Ереван","Венера"};
    string s3[] {"Тачки и кошмары","Мартышка и очки"};

    map<string, int> registryMap;
    map<string, int>::iterator iter;

    cout << endl;
    cout << "\"" << s1[0] << "\"" << " :: " << "\"" << s1[1] << "\" = ";
    cout << (anagramSearch(s1[0], s1[1]) ? "true" : "false") << endl;

    cout << "\"" << s2[0] << "\"" << " :: " << "\"" << s2[1] << "\" = ";
    cout << (anagramSearch(s2[0], s2[1]) ? "true" : "false") << endl;

    cout << "\"" << s3[0] << "\"" << " :: " << "\"" << s3[1] << "\" = ";
    cout << (anagramSearch(s3[0], s3[1]) ? "true" : "false") << endl;

    return 0;
}

string trimAndLowerCase (string &s) {

    string result;
    for (char i : s) {
        if (i != ' ') result.push_back((char)tolower(i));
    }
    return result;
}

map<char, int> putStringIntoMap (string &s) {

    string text = trimAndLowerCase(s);
    map<char, int> m;
    for (char i : text) {
        if (m.find(i) == m.end())
            m.insert(pair<char, int>(i,0));
        m[i] += 1;
    }
    return m;
}

bool anagramSearch (string &s1, string &s2) {

    map<char, int> map1 = putStringIntoMap(s1);
    map<char, int> map2 = putStringIntoMap(s2);
    if (map1.size() != map2.size()) return false;

    auto i1 = map1.begin();
    auto i2 = map2.begin();
    while (i1 != map1.end()) {
        if ((i1->first != i2->first)
            || (i1->second != i2->second)) return false;
        i1++; i2++;
    }
    return true;
}
