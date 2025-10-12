#include "string.h"

String::String(const char* str) {
    size = strlen(str);
    this->str = new char[size + 1];
    for (size_t i = 0; i <= size; ++i) {
        this->str[i] = str[i];
    }
}

String::String(size_t n, char c) : size(n), str(nullptr) {
    this->str = new char[size + 1];
    for (size_t i = 0; i < size; ++i) {
        this->str[i] = c;
    }
    str[size] = '\0';
}

String::~String() {
    delete[] str;
}

String::String(const String& other) : size(other.size) {
    str = new char[size + 1];
    strcpy(str, other.str);
}

String& String::operator=(const String& other) {
    if (this != &other) {
        delete[] this->str;
        this->size = other.size;
        this->str = new char[this->size + 1];
        strcpy(this->str, other.str);
    }
    return *this;
}

void String::append(const String& other) {
    size += other.size;
    char* new_str = new char[size + 1];
    strcpy(new_str, str);
    strcat(new_str, other.str);
    delete[] str;
    str = new_str;
}

char* String::GetStr() {
    return str;
}

void String::Print() const {
    for (size_t p = 0; p < this->size - 1; ++p) {
        std::cout << this->str[p];
    }
    std::cout << "\n";
}

Substring::Substring(const String& string, size_t start)
    : string(string), start(start) {}

Substring::~Substring() {}

Substring::Substring(const Substring& other)
    : start(other.start), string(other.string) {}

Substring String::operator[](size_t start) const {
    return Substring(*this, start);
}

String Substring::operator[](size_t end) {
    if (end < start) {
        return String();
    }
    else {
        size_t length = end - start;
        char* str = new char[length + 1];
        String temp_string = string;
        for (size_t i = 0; i < length; ++i) {
            str[i] = temp_string.GetStr()[start + i];
        }
        str[length + 1] = '\0';
        return String(str);
    }
}