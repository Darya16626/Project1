#include <iostream>
#include <string>
#include <Windows.h>

// Прототип функции из DLL
typedef bool(*CheckStringFunction)(const char*, const char*);

int main() {
    std::string inputString, searchChars;
    bool containsChars;

    // Запрос ввода строки и символов для поиска
    std::cout << "Введите строку: ";
    std::getline(std::cin, inputString);
    std::cout << "Введите символы для поиска: ";
    std::getline(std::cin, searchChars);

    // Загрузка библиотеки DLL
    HINSTANCE hLib = LoadLibrary(L"StringCheckLib.dll");
    if (hLib == NULL) {
        std::cerr << "Ошибка загрузки библиотеки" << std::endl;
        return 1;
    }

    // Получение адреса функции из библиотеки
    CheckStringFunction checkString = (CheckStringFunction)GetProcAddress(hLib, "CheckString");
    if (checkString == NULL) {
        std::cerr << "Ошибка получения функции" << std::endl;
        FreeLibrary(hLib);
        return 1;
    }

    // Вызов функции из библиотеки
    containsChars = checkString(inputString.c_str(), searchChars.c_str());

    // Освобождение библиотеки
    FreeLibrary(hLib);

    // Вывод результата
    if (containsChars) {
        std::cout << "Строка содержит все указанные символы" << std::endl;
    }
    else {
        std::cout << "Строка не содержит все указанные символы" << std::endl;
    }

    return 0;
}