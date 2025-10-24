#include <iostream>
#include <fstream>
#include <limits>
#include <string>

// структура данных
struct Provision {
    int id;
    std::string name;
    std::string category;
    std::string unit;
    float quantity;
    double price;
    int expiryDays;
};

// прототипы функций
void addProvision(Provision*& provisions, int& count, const Provision& newProvision);
void loadData(Provision*& provisions, int& count, const std::string& filename);
void showData(const Provision* provisions, int count);
void editData(Provision* provisions, int count);
void performCalculations(const Provision* provisions, int count);
void saveData(const Provision* provisions, int count);

int main() {
    setlocale(LC_ALL, "Russian");

    Provision* provisions = nullptr; // указатель на динамический массив
    int provisionCount = 0; // счетчик элементов в массиве

    loadData(provisions, provisionCount, "provisions.txt");

    int choice = 0;
    while (choice != 6) {
        // ... здесь будет меню ...
    }

    delete[] provisions;
    return 0;
}

// функция для добавления нового товара в массив
void addProvision(Provision*& provisions, int& count, const Provision& newProvision) {
    int newCount = count + 1;
    Provision* newArray = new Provision[newCount]; 
    for (int i = 0; i < count; ++i) { newArray[i] = provisions[i]; }
    newArray[count] = newProvision; 
    if (provisions != nullptr) { delete[] provisions; }
    provisions = newArray; 
    count = newCount; 
}

// заглушки для остальных функций
void loadData(Provision*& provisions, int& count, const std::string& filename) {}
void showData(const Provision* provisions, int count) {}
void editData(Provision* provisions, int count) {}
void performCalculations(const Provision* provisions, int count) {}
void saveData(const Provision* provisions, int count) {}
