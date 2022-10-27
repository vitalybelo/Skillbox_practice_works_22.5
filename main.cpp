#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "windows.h"
using namespace std;

struct Phones {
    vector<string> contactInfo;
};

void displayHelp();
string getCommand();
void addRecord(map<string, Phones> &map);
void deleteRecord(map<string, Phones> &map);
void displayContact(map<string, Phones>::iterator it);
void findByPhone(map<string, Phones> &map);
void findByName(map<string, Phones> &map);


int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "RUS");

    map<string, Phones> phoneMap; // map < names is KEY, collection of numbers is parameter>
    phoneMap.insert(pair<string, Phones>("Google Inc", *(new Phones())));
    phoneMap["Google Inc"].contactInfo.emplace_back("+1 800 800-0001");
    phoneMap["Google Inc"].contactInfo.emplace_back("+1 800 800-0011");
    phoneMap["Google Inc"].contactInfo.emplace_back("+1 800 800-0111");

    displayHelp();
    while (true) {
        string comm = getCommand();
        if (comm == "quit") break;
        if (comm == "add") {
            // add record to map
            addRecord(phoneMap);
        } else if (comm == "del") {
            // delete record from map
            deleteRecord(phoneMap);
        } else if (comm == "phone") {
            // look for map record by phone number (not key)
            findByPhone(phoneMap);
        } else if (comm == "name") {
            // display map record by name (key)
            findByName(phoneMap);
        } else if (comm == "list") {
            // print list on map records
            if (phoneMap.empty()) {
                cout << "������ ����\n";
            } else {
                for (auto it = phoneMap.begin(); it != phoneMap.end(); it++)
                    displayContact(it);
                cout << endl;
            }
        } else if (comm == "help" || comm == "?") {
            // display scroll of controls
            displayHelp();
        }
    }

    return 0;
}


void displayHelp() {
    cout << endl;
    cout << "������ ������:\n";
    cout << "add\t- �������� ��������\n";
    cout << "del\t- ������� ��������\n";
    cout << "list\t- ����� ������ ���������\n";
    cout << "phone\t- ����� �� ������ ��������\n";
    cout << "name\t- ����� �� ����� ��������\n";
    cout << "quit\t- �����\n";
}

string getCommand() {
    cout << "\n������� �������: ";
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

void addRecord(map<string, Phones> &map) {

    string phone, name;
    cout << "������� ��� ��������: ";
    getline(cin, name);
    if (name.empty()) return;

    cout << "������� ����� ��������: ";
    getline(cin, phone);
    if (phone.empty()) return;
    if (!phoneNumberIsCorrect(phone)) {
        // TODO: �������� ������� ���������
    }
    auto it = map.find(name);
    if (it == map.end()) {
        // ����� ������� - ������� ������
        map.insert(pair<string, Phones>(name, *(new Phones())));
    }
    // ��������� ������ �� ��������
    map[name].contactInfo.emplace_back(phone);
}

void deleteRecord(map<string, Phones> &map) {

    string name;
    cout << "������� ��� ��������: ";
    getline(cin, name);
    if (name.empty()) return;

    cout << "���������� ��������� �������: " << map.erase(name) << endl;
}

void displayContact(map<string, Phones>::iterator it) {

    printf("\n�������:  %-20s :: %s\n", it->first.c_str(), it->second.contactInfo.at(0).c_str());
    for (int i = 1; i < it->second.contactInfo.size(); i++) {
        printf("%-30s :: %s\n", " ", it->second.contactInfo.at(i).c_str());
    }
}

void findByPhone(map<string, Phones> &map) {

    string phone;
    cout << "������� ����� ��������: ";
    getline(cin,phone);
    if (phone.empty()) return;

    for (auto it = map.begin(); it != map.end(); it++)
        for (int i = 0; i < it->second.contactInfo.size(); i++) {
            if (it->second.contactInfo.at(i) == phone) {
                displayContact(it);
                return;
            }
        }
    cout << "���������� �� �������\n";
}

void findByName(map<string, Phones> &map) {

    string name;
    cout << "������� ��� ��������: ";
    getline(cin,name);
    if (name.empty()) return;

    auto it = map.find(name);
    if (it == map.end()) {
        cout << "���������� �� �������\n";
    } else {
        displayContact(it);
    }
}
