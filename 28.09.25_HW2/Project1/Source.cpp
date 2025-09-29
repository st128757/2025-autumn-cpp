#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <conio.h>

class TextEditor {
private:
    std::vector<std::string> lines;
    int cursor_row;
    int cursor_col;

public:
    TextEditor() {
        lines.push_back("");
        cursor_row = 0;
        cursor_col = 0;
    }

    // Обработка ввода с клавиатуры
    void HandleKeyPress(char key) {
        switch (key) {
        case 8:   // Backspace
            DeleteText(1);
            break;
        case 13:  // Enter
            AddNewLine();
            break;
        case 77:  // Стрелка вправо
            CursorRight(1);
            break;
        case 75:  // Стрелка влево
            CursorLeft(1);
            break;
        case 72:  // Стрелка вверх
            CursorUp(1);
            break;
        case 80:  // Стрелка вниз
            CursorDown(1);
            break;
        default:
            // Обычный символ
            if (key >= 32 && key <= 126) {
                AddText(std::string(1, key));
            }
            break;
        }
    }

    void AddText(std::string text) {
        std::string& current_line = lines[cursor_row];

        if (cursor_col < current_line.length()) {
            std::string prefix = current_line.substr(0, cursor_col);
            std::string suffix = current_line.substr(cursor_col);
            current_line = prefix + text + suffix;
        }
        else {
            current_line += text;
        }

        cursor_col += text.length();
        RefreshDisplay();
    }

    int DeleteText(int k) {
        int deleted = 0;

        for (int i = 0; i < k; i++) {
            if (cursor_col > 0) {
                // Удаляем символ слева от курсора
                std::string& current_line = lines[cursor_row];
                current_line.erase(cursor_col - 1, 1);
                cursor_col--;
                deleted++;
            }
            else if (cursor_row > 0) {
                // Переход на конец предыдущей строки
                std::string& prev_line = lines[cursor_row - 1];
                std::string& current_line = lines[cursor_row];

                cursor_col = prev_line.length();
                prev_line += current_line;
                lines.erase(lines.begin() + cursor_row);
                cursor_row--;
                deleted++;
            }
        }

        RefreshDisplay();
        return deleted;
    }

    std::string CursorLeft(int k) {
        for (int i = 0; i < k; i++) {
            if (cursor_col > 0) {
                cursor_col--;
            }
            else if (cursor_row > 0) {
                cursor_row--;
                cursor_col = lines[cursor_row].length();
            }
        }
        RefreshDisplay();
        return GetTextBeforeCursor();
    }

    std::string CursorRight(int k) {
        for (int i = 0; i < k; i++) {
            if (cursor_col < lines[cursor_row].length()) {
                cursor_col++;
            }
            else if (cursor_row < lines.size() - 1) {
                cursor_row++;
                cursor_col = 0;
            }
        }
        RefreshDisplay();
        return GetTextBeforeCursor();
    }

    std::string CursorUp(int k) {
        for (int i = 0; i < k; i++) {
            if (cursor_row > 0) {
                cursor_row--;
                cursor_col = std::min(cursor_col,
                    static_cast<int>(lines[cursor_row].length()));
            }
        }
        RefreshDisplay();
        return GetTextBeforeCursor();
    }

    std::string CursorDown(int k) {
        for (int i = 0; i < k; i++) {
            if (cursor_row < lines.size() - 1) {
                cursor_row++;
                cursor_col = std::min(cursor_col,
                    static_cast<int>(lines[cursor_row].length()));
            }
        }
        RefreshDisplay();
        return GetTextBeforeCursor();
    }

    void AddNewLine() {
        std::string& current_line = lines[cursor_row];

        if (cursor_col < current_line.length()) {
            std::string new_line = current_line.substr(cursor_col);
            current_line = current_line.substr(0, cursor_col);
            lines.insert(lines.begin() + cursor_row + 1, new_line);
        }
        else {
            lines.insert(lines.begin() + cursor_row + 1, "");
        }

        cursor_row++;
        cursor_col = 0;
        RefreshDisplay();
    }

private:
    std::string GetTextBeforeCursor() {
        std::string& current_line = lines[cursor_row];
        int start_pos = std::max(0, cursor_col - 10);
        return current_line.substr(start_pos, cursor_col - start_pos);
    }

    void RefreshDisplay() {
        system("cls");  // Очистка экрана (Windows)

        std::cout << "=== Text editor ===" << std::endl;
        std::cout << "Enter - new line, Esc - exit" << std::endl;
        std::cout << "==========================" << std::endl << std::endl;

        for (int i = 0; i < lines.size(); i++) {
            // Показываем номер строки
            std::cout << (i + 1) << ": ";

            // Выводим строку
            if (i == cursor_row) {
                // Выделяем текущую строку курсором
                std::string line = lines[i];

                // Текст до курсора
                std::cout << line.substr(0, cursor_col);

                // Курсор (мигающий символ)
                std::cout << "|";

                // Текст после курсора
                if (cursor_col < line.length()) {
                    std::cout << line.substr(cursor_col);
                }
            }
            else {
                std::cout << lines[i];
            }

            std::cout << std::endl;
        }

        std::cout << std::endl << "position: line " << (cursor_row + 1) << ", position "
            << cursor_col << std::endl;
    }

public:
    // Запуск интерактивного режима
    void RunInteractive() {
        std::cout << "type smth..." << std::endl << std::endl;

        RefreshDisplay();

        while (true) {
            char key = _getch();  // Чтение клавиши без ожидания Enter

            if (key == 27) {  // Esc - выход
                break;
            }
            else if (key == 0 || key == -32) {
                // Обработка специальных клавиш (стрелки)
                key = _getch();
                HandleKeyPress(key);
            }
            else {
                HandleKeyPress(key);
            }
        }

        std::cout << std::endl << "work ended" << std::endl;
    }

    // Методы для программируемого использования
    void PrintText() { RefreshDisplay(); }

    std::string GetFullText() {
        std::string result;
        for (int i = 0; i < lines.size(); i++) {
            result += lines[i];
            if (i < lines.size() - 1) {
                result += "\n";
            }
        }
        return result;
    }

    std::pair<int, int> GetCursorPosition() {
        return std::make_pair(cursor_row, cursor_col);
    }
};

int main() {
    TextEditor editor;

    editor.RunInteractive();

    return 0;
}