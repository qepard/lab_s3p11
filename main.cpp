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
void saveData(const Provision* provisions, int count, const std::string& defaultFilename); // ИСПРАВЛЕНО: Добавлен параметр

int main() {
    setlocale(LC_ALL, "Russian");

    const std::string sourceFilename = "provisions.txt"; // Имя файла для загрузки и сохранения по умолчанию
    Provision* provisions = nullptr; // указатель на динамический массив
    int provisionCount = 0; // счетчик элементов в массиве

    loadData(provisions, provisionCount, sourceFilename);

    int choice = 0;
    while (choice != 6) {
        std::cout << "\n--- Меню склада провианта ---\n";
        std::cout << "1. Просмотр всех товаров\n";
        std::cout << "2. Редактировать товар\n";
        std::cout << "3. Вычисления (найти самый дорогой товар)\n";
        std::cout << "4. Добавить новый товар\n";
        std::cout << "5. Сохранить данные\n";
        std::cout << "6. Выход\n";
        std::cout << "Ваш выбор: ";

        // проверяем ввод на корректность
        if (!(std::cin >> choice)) {
            std::cout << "\nОшибка: Пожалуйста, введите число от 1 до 6.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        // ИСПРАВЛЕНО: Ключевая очистка буфера после чтения choice. Решает проблему с saveData.
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case 1:
                showData(provisions, provisionCount);
                break;
            case 2:
                editData(provisions, provisionCount);
                break;
            case 3:
                performCalculations(provisions, provisionCount);
                break;
            case 4:
                {
                    Provision newProvision;
                    std::cout << "--- Добавление нового товара ---\n";

                    std::cout << "Введите ID: ";
                    std::cin >> newProvision.id;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // очистка буфера

                    std::cout << "Введите Название: ";
                    std::getline(std::cin, newProvision.name);

                    std::cout << "Введите Категорию: ";
                    std::getline(std::cin, newProvision.category);

                    std::cout << "Введите Ед. изм.: ";
                    std::getline(std::cin, newProvision.unit);

                    std::cout << "Введите Кол-во: ";
                    std::cin >> newProvision.quantity;

                    std::cout << "Введите Цену: ";
                    std::cin >> newProvision.price;

                    std::cout << "Введите Срок годности (дни): ";
                    std::cin >> newProvision.expiryDays;

                    if(std::cin.fail()) {
                        std::cout << "\nОшибка: Введено неверное значение (например, текст вместо числа).\n";
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    } else {
                        addProvision(provisions, provisionCount, newProvision);
                        std::cout << "Товар успешно добавлен.\n";
                    }
                }
                break;
            case 5:
                saveData(provisions, provisionCount, sourceFilename); // ИСПРАВЛЕНО: передаем имя файла
                break;
            case 6:
                std::cout << "Работа завершена.\n";
                break;
            default:
                std::cout << "Неверный выбор. Попробуйте снова.\n";
        }
    }

    delete[] provisions;
    return 0;
}

// функция для добавления нового товара в массив
void addProvision(Provision*& provisions, int& count, const Provision& newProvision) {
    int newCount = count + 1;
    Provision* newArray = new Provision[newCount]; 
    for (int i = 0; i < count; ++i) {
        newArray[i] = provisions[i];
    }
    newArray[count] = newProvision; 
    if (provisions != nullptr) {
        delete[] provisions; 
    }
    provisions = newArray; 
    count = newCount; 
}

// загрузка данных из файла
void loadData(Provision*& provisions, int& count, const std::string& filename) {
    std::ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        std::cerr << "Ошибка: не удалось открыть файл " << filename << std::endl;
        return;
    }
    Provision temp;
    while (inputFile >> temp.id >> temp.name >> temp.category >> temp.unit 
                     >> temp.quantity >> temp.price >> temp.expiryDays) {
        addProvision(provisions, count, temp);
    }
    inputFile.close();
    std::cout << "Данные успешно загружены." << std::endl;
}

// просмотр товаров
void showData(const Provision* provisions, int count) {
    if (count == 0) {
        std::cout << "Нет данных для отображения." << std::endl;
        return;
    }
    std::cout << "\n--- Список товаров на складе ---\n";
    for (int i = 0; i < count; ++i) {
        const Provision& p = provisions[i];
        std::cout << "ID: " << p.id << ", " << p.name << " (" << p.category << "), "
                  << p.quantity << " " << p.unit << ", Цена: " << p.price 
                  << ", Срок годности: " << p.expiryDays << " дн." << std::endl;
    }
}

// редактирование товара
void editData(Provision* provisions, int count) {
    int idToEdit;
    std::cout << "Введите ID товара для редактирования: ";
    std::cin >> idToEdit;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ИСПРАВЛЕНО: добавлена очистка буфера

    for (int i = 0; i < count; ++i) {
        if (provisions[i].id == idToEdit) {
            std::cout << "Найден товар: " << provisions[i].name << std::endl;
            // ИСПРАВЛЕНО: Переход на getline для надежного ввода строк
            std::cout << "Введите новое Название: ";
            std::getline(std::cin, provisions[i].name);
            std::cout << "Введите новую Категорию: ";
            std::getline(std::cin, provisions[i].category);
            std::cout << "Введите новые Ед. изм.: ";
            std::getline(std::cin, provisions[i].unit);
            std::cout << "Введите новое Кол-во: ";
            std::cin >> provisions[i].quantity;
            std::cout << "Введите новую Цену: ";
            std::cin >> provisions[i].price;
            std::cout << "Введите новый Срок годности (дни): ";
            std::cin >> provisions[i].expiryDays;
            std::cout << "Данные обновлены." << std::endl;
            return;
        }
    }
    std::cout << "Товар с ID " << idToEdit << " не найден." << std::endl;
}

// различные вычисления
void performCalculations(const Provision* provisions, int count) {
    if (count == 0) {
        std::cout << "Нет данных для вычислений." << std::endl;
        return;
    }
    double maxPrice = 0.0;
    const Provision* mostExpensive = nullptr;
    for (int i = 0; i < count; ++i) {
        if (provisions[i].price > maxPrice) {
            maxPrice = provisions[i].price;
            mostExpensive = &provisions[i];
        }
    }
    if (mostExpensive) {
        std::cout << "Самый дорогой товар (" << maxPrice << " руб.): "
                  << mostExpensive->name << std::endl;
    }
}

// сохранение данных в новый файл
void saveData(const Provision* provisions, int count, const std::string& defaultFilename) {
    std::string outputFilename;
    std::cout << "Введите имя файла для сохранения (Enter, чтобы сохранить в " << defaultFilename << "): ";
    
    // ИСПРАВЛЕНО: теперь getline будет работать правильно, так как буфер в main очищен
    std::getline(std::cin, outputFilename);

    if (outputFilename.empty()) {
        outputFilename = defaultFilename;
    }

    std::ofstream outputFile(outputFilename);
    if (!outputFile.is_open()) {
        std::cerr << "Ошибка: не удалось создать файл " << outputFilename << std::endl;
        return;
    }
    for (int i = 0; i < count; ++i) {
        const Provision& p = provisions[i];
        outputFile << p.id << " " << p.name << " " << p.category << " " << p.unit << " "
                   << p.quantity << " " << p.price << " " << p.expiryDays << std::endl;
    }
    outputFile.close();
    std::cout << "Данные успешно сохранены в файл " << outputFilename << std::endl;
}
