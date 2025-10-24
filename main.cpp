#include <iostream>
#include <fstream>
#include <vector>
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
void loadData(std::vector<Provision>& provisions, const std::string& filename);
void showData(const std::vector<Provision>& provisions);
void editData(std::vector<Provision>& provisions);
void performCalculations(const std::vector<Provision>& provisions);
void saveData(const std::vector<Provision>& provisions);

int main() {
    // Программа будет здесь
    return 0;
}
