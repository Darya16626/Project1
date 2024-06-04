#include <iostream>
#include <string>
#include <Windows.h>

// �������� ������� �� DLL
typedef bool(*CheckStringFunction)(const char*, const char*);

int main() {
    std::string inputString, searchChars;
    bool containsChars;

    // ������ ����� ������ � �������� ��� ������
    std::cout << "������� ������: ";
    std::getline(std::cin, inputString);
    std::cout << "������� ������� ��� ������: ";
    std::getline(std::cin, searchChars);

    // �������� ���������� DLL
    HINSTANCE hLib = LoadLibrary(L"StringCheckLib.dll");
    if (hLib == NULL) {
        std::cerr << "������ �������� ����������" << std::endl;
        return 1;
    }

    // ��������� ������ ������� �� ����������
    CheckStringFunction checkString = (CheckStringFunction)GetProcAddress(hLib, "CheckString");
    if (checkString == NULL) {
        std::cerr << "������ ��������� �������" << std::endl;
        FreeLibrary(hLib);
        return 1;
    }

    // ����� ������� �� ����������
    containsChars = checkString(inputString.c_str(), searchChars.c_str());

    // ������������ ����������
    FreeLibrary(hLib);

    // ����� ����������
    if (containsChars) {
        std::cout << "������ �������� ��� ��������� �������" << std::endl;
    }
    else {
        std::cout << "������ �� �������� ��� ��������� �������" << std::endl;
    }

    return 0;
}