#include <iostream>
#include <string>
#include <map>
#include <vector>
//#include "windows.h"
using namespace std;

struct Phones {
    vector<string> contactInfo;
};

void displayHelp();
string getCommand();
void insertIntoMaps(map<string, Phones> &namesMap,
                    map<string, string> &phoneMap,
                    const string &name, const string &phone);
void addRecord(map<string, Phones> &namesMap, map<string, string> &phoneMap);
void deleteRecord(map<string, Phones> &namesMap, map<string, string> &phoneMap);
void displayContact(map<string, Phones>::iterator it);
void findByPhone(map<string, Phones> &namesMap, map<string, string> &phoneMap);
void findByName(map<string, Phones> &namesMap);

int main() {
//    SetConsoleCP(1251);
//    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "RUS");

    map<string, Phones> namesMap;   // map < names is KEY, collection of numbers is parameter>
    map<string, string> phoneMap;   // indexing phone numbers map
    insertIntoMaps(namesMap, phoneMap, "Google Inc", "+1 800 800-0001");
    insertIntoMaps(namesMap, phoneMap, "Google Inc", "+1 800 800-0011");
    insertIntoMaps(namesMap, phoneMap, "Google Inc", "+1 800 800-0111");

    displayHelp();
    while (true) {
        string comm = getCommand();
        if (comm == "quit") break;
        if (comm == "add") {
            // add record to map
            addRecord(namesMap, phoneMap);
        } else if (comm == "del") {
            // delete record from map
            deleteRecord(namesMap, phoneMap);
        } else if (comm == "phone") {
            // look for map record by phone number (not key)
            findByPhone(namesMap, phoneMap);
        } else if (comm == "name") {
            // display map record by name (key)
            findByName(namesMap);
        } else if (comm == "list") {
            // print list on map records
            if (namesMap.empty()) {
                cout << "Список абонентов пуст\n";
            } else {
                for (auto it = namesMap.begin(); it != namesMap.end(); it++)
                    displayContact(it);
                cout << endl;
            }
        } else if (comm == "help" || comm == "?") {
            // display scroll of controls
            displayHelp();
        } else if (comm == "see") {
            if (phoneMap.empty()) {
                cout << "Индексная карта пустая\n";
            } else {
                for (auto & it : phoneMap)
                    cout << it.first << " :: " << it.second << endl;
                cout << endl;
            }
        }
    }

    return 0;
}


void displayHelp() {
    cout << endl;
    cout << "Список команд:\n";
    cout << "add\t- добавить абонента\n";
    cout << "del\t- удалить данные абонента\n";
    cout << "list\t- вывод списка абонентов\n";
    cout << "phone\t- поиск по номеру телефона\n";
    cout << "name\t- поиск по имени абонента\n";
    cout << "quit\t- выход\n";
}

string getCommand() {
    cout << "\nВведите команду: ";
    string command;
    getline(cin,command);
    for (char & i : command) {
        i = (char) tolower(i);
    }
    return command;
}

bool phoneNumberIsCorrect(string& s) {
    const string regex = "+0123456789()- ";
    for (char i : s) {
        if (regex.find(i) == string::npos) return false;
    }
    return true;
}
void insertIntoMaps(map<string, Phones> &namesMap,
                    map<string, string> &phoneMap,
                    const string &name, const string &phone) {
    if (name.empty() || phone.empty()) return;

    auto it = namesMap.find(name);
    if (it == namesMap.end()) {
        // новый контакт - заводим запись
        namesMap.insert(pair<string, Phones>(name, *(new Phones())));
    }
    // добавляем данные по контакту
    namesMap[name].contactInfo.emplace_back(phone);
    phoneMap.insert(pair<string, string>(phone, name));
}

void addRecord(map<string, Phones> &namesMap, map<string, string> &phoneMap) {
    string phone, name;

    cout << "Введите имя абонента: ";
    getline(cin, name);
    if (name.empty()) return;

    cout << "Введите номер телефона: ";
    getline(cin, phone);
    if (phone.empty()) return;
    if (!phoneNumberIsCorrect(phone)) {
        // TODO: например вывести сообщение
    }

    insertIntoMaps(namesMap, phoneMap, name, phone);
}

void deleteRecord(map<string, Phones> &namesMap, map<string, string> &phoneMap) {

    string phone;
    cout << "Введите номер телефона (Enter - дальше): ";
    getline(cin, phone);
    if (!phone.empty()) {
        auto phoneIter = phoneMap.find(phone);
        if (phoneIter == phoneMap.end()) {
            cout << "Совпадений не найдено\n";
        } else {
            auto namesIter = namesMap.find(phoneIter->second);
            auto it = namesIter->second.contactInfo.begin();
            for (; it < namesIter->second.contactInfo.end(); it++) {
                if (*it == phone) {
                    namesIter->second.contactInfo.erase(it);
                    cout << "Количество удаленных записей: " << phoneMap.erase(phone) << endl;
                }
            }
        }
        return;
    }

    string name;
    cout << "Введите имя абонента: ";
    getline(cin, name);
    if (name.empty()) return;

    auto namesIter = namesMap.find(name);
    if (namesIter != namesMap.end()) {
        for (auto & i : namesIter->second.contactInfo)
            phoneMap.erase(i);
    }
    cout << "Количество удаленных записей: " << namesMap.erase(name) << endl;
}

void displayContact(map<string, Phones>::iterator it) {

    if (it->second.contactInfo.empty()) {
        printf("\nАбонент:  %-20s :: %s\n", it->first.c_str(), "данных нет");
    } else {
        printf("\nАбонент:  %-20s :: %s\n", it->first.c_str(), it->second.contactInfo.at(0).c_str());
        for (int i = 1; i < it->second.contactInfo.size(); i++) {
            printf("%-30s :: %s\n", " ", it->second.contactInfo.at(i).c_str());
        }
    }
}

void findByPhone(map<string, Phones> &namesMap, map<string, string> &phoneMap) {

    string phone;
    cout << "Введите номер телефона: ";
    getline(cin,phone);
    if (phone.empty()) return;

    auto phoneIter = phoneMap.find(phone);
    if (phoneIter == phoneMap.end()) {
        cout << "Совпадений не найдено\n";
    } else {
        auto namesIter = namesMap.find(phoneIter->second);
        if (namesIter != namesMap.end())
            displayContact(namesIter);
    }
}

void findByName(map<string, Phones> &namesMap) {

    string name;
    cout << "Введите имя абонента: ";
    getline(cin,name);
    if (name.empty()) return;

    auto it = namesMap.find(name);
    if (it == namesMap.end()) {
        cout << "Совпадений не найдено\n";
    } else {
        displayContact(it);
    }
}
