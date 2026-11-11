#include <conio.h>
#include <windows.h>

#include <cctype>
#include <iostream>
#include <string_view>

namespace {
constexpr std::string_view pianoKeys = "ASDFGHJKL;'";

void printGreeting() {
    constexpr std::wstring_view message = L"Jakieś tam pianino :O\r\n";
    DWORD written;
    if (!WriteConsoleW(GetStdHandle(STD_OUTPUT_HANDLE), message.data(),
                       static_cast<DWORD>(message.size()), &written, nullptr)) {
        std::cout << "Jakieś tam pianino :O" << std::endl;
    }
}
}

int main() {
    DWORD modifier = 1;
    printGreeting();

    for (int key = _getch(); key != '\x1b'; key = _getch()) {
        if (key == 0 || key == 0xe0) {
            _getch(); // Consume the scan code of a function or arrow key.
            continue;
        }

        if ((key == '-' || key == '_') && modifier > 1) {
            --modifier;
            std::cout << "Mod decreased to " << modifier << '!' << std::endl;
        } else if ((key == '+' || key == '=') && modifier < 10) {
            ++modifier;
            std::cout << "Mod increased to " << modifier << '!' << std::endl;
        } else {
            const auto note = pianoKeys.find(static_cast<char>(std::toupper(key)));
            if (note != std::string_view::npos) {
                const DWORD frequency = note == 0 ? 50 * modifier
                                                  : 100 * static_cast<DWORD>(note) * modifier + 1;
                Beep(frequency, 100);
            }
        }
    }
}
