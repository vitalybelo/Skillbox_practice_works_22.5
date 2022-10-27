#include <iostream>
#include <map>
#include "windows.h"
using namespace std;


int main() {
    setlocale(LC_ALL, "RUS");

    string name;
    map<string, int> registryMap;
    map<string, int>::iterator iter;

    for (int i = 0;; i++) {

        cout << "<--- ";
        getline(cin, name);
        if (name.empty()) break;

        if (name == "next") { // вытаскиваем из очереди первое по алфавиту имя

            if (!registryMap.empty()) {
                iter = registryMap.begin();
                cout << "\t ---> " << iter->first << endl;
                if (--(iter->second) <= 0) registryMap.erase(iter);
            } else {
                cout << "Никого нет в очереди" << endl;
            }
        } else if (name == "see") { // отображаем весь список очереди

            if (!registryMap.empty()) {
                for (iter = registryMap.begin(); iter != registryMap.end(); iter++)
                    cout << "\t ---> " << iter->first << " (" << iter->second << ")" << endl;
            }
        } else {// добавляем имя в очередь

            iter = registryMap.find(name);
            if (iter == registryMap.end()) { // новое имя, создаем сопоставление
                registryMap.insert(pair<string, int>(name, 0));
            }
            registryMap[name]++;
        }
    }

    return 0;
}
