#include <fstream>
#include <iostream>
#include <stack>
#include <string>

bool isOperator(const std::string& smb) {
    return smb == "+" || smb == "-" || smb == "*" || smb == "/" || smb == "^";
}

bool isNumber(const std::string& smb) {
    if (smb.empty()) {
        return false;
    }

    bool yesDecimal = false;
    int start = 0;
    if (smb[0] == '-' && smb[1] != ' ') {
        ++start;
    }

    for (int i = start; i < smb.size(); ++i) {
        char c = smb[i];

        if (c == '.') {
            if (yesDecimal) return false;
            yesDecimal = true;
        }
        else if (c < '0' || c > '9') {
            return false;
        }
    }

    return true;
}

double stringToDouble(const std::string& smb) {
    double result = 0.0;
    double decimal = 0.0;
    double sign = 1.0;
    bool afterDecimal = false;
    double decimalPlace = 1.0;

    int start = 0;
    if (smb[0] == '-') {
        sign = -1.0;
        start = 1;
    }
    else if (smb[0] == '+') {
        start = 1;
    }

    for (int i = start; i < smb.size(); ++i) {
        char c = smb[i];

        if (c == '.') {
            afterDecimal = true;
        }
        else {
            int digit = c - '0';
            if (afterDecimal) {
                decimalPlace *= 10.0;
                decimal = decimal * 10.0 + digit;
            }
            else {
                result = result * 10.0 + digit;
            }
        }
    }

    return sign * (result + decimal / decimalPlace);
}

double performOperation(double a, double b, std::string& smb, bool& error,
    std::string& errorMsg) {
    error = false;

    if (smb == "+") return a + b;
    if (smb == "-") return a - b;
    if (smb == "*") return a * b;
    if (smb == "/") {
        if (b == 0) {
            error = true;
            errorMsg = "Division by zero";
            return 0.0;
        }
        return a / b;
    }
    if (smb == "^") {
        double result = 1.0;
        for (int i = 0; i < b; ++i) {
            result *= a;
        }
        return result;
    }

    error = true;
    errorMsg = "Unknown operator: " + smb;
    return 0.0;
}

double evaluate(const std::string& expression, bool& error, std::string& errorMsg) {
    std::stack<double> stack;
    error = false;
    errorMsg = "";

    std::string smb;
    int pos = 0;

    while (pos < expression.size()) {
        while (pos < expression.size() && expression[pos] == ' ') {
            ++pos;
        }
        if (pos >= expression.size()) break;

        int smbStart = pos;
        while (pos < expression.size() && expression[pos] != ' ') {
            ++pos;
        }

        smb = expression.substr(smbStart, pos - smbStart);

        if (smb.empty()) {
            continue;
        }

        if (isOperator(smb)) {
            if (stack.size() < 2) {
                error = true;
                errorMsg = "Not enough numbers for operation: " + smb;
                return 0.0;
            }

            double b = stack.top();
            stack.pop();
            double a = stack.top();
            stack.pop();

            bool operationError = false;
            std::string opErrorMsg;
            double result = performOperation(a, b, smb, operationError, opErrorMsg);

            if (operationError) {
                error = true;
                errorMsg = opErrorMsg;
                return 0.0;
            }

            stack.push(result);
        }
        else if (isNumber(smb)) {
            double num = stringToDouble(smb);
            stack.push(num);
        }
        else {
            error = true;
            errorMsg = "Incorrect symbol: " + smb;
            return 0.0;
        }
    }

    if (stack.size() != 1) {
        error = true;
        errorMsg = "Incorrect expression";
        return 0.0;
    }

    return stack.top();
}

std::string DoubleToString(double res) {
    std::string str = std::to_string(res);
    int dotPos = str.find('.');

    if (dotPos != std::string::npos) {
        str = str.substr(0, str.find_last_not_of('0') + 1);
        if (str.back() == '.') {
            str.pop_back();
        }
    }
    return str;
}

void processFile(std::string& inadd, std::string& outadd) {
    std::fstream inFile;
    std::fstream outFile;
    inFile.open(inadd, std::fstream::in);
    outFile.open(outadd, std::fstream::out);

    if (!inFile) {
        std::cout << "Error: input File isn't open" << std::endl;
        return;
    }
    if (!outFile) {
        std::cout << "Error: output File isn't open" << std::endl;
        return;
    }

    std::string line;
    int lineNumber = 0;

    while (std::getline(inFile, line)) {
        lineNumber++;

        if (line.empty()) {
            continue;
        }

        bool error = false;
        std::string errorMsg;
        double result = evaluate(line, error, errorMsg);

        if (error) {
            outFile << "ERROR: " << errorMsg << std::endl;
            std::cout << "failure in line " << lineNumber << ": " << errorMsg << std::endl;
        }
        else {
            std::string formatted = DoubleToString(result);
            outFile << line << " = " << formatted << std::endl;
            std::cout << lineNumber << ": " << line << " = " << formatted << std::endl;
        }
    }

    inFile.close();
    outFile.close();
}

int main() {
    std::string inadd = "C://input.txt";
    std::string outadd = "C://output.txt";

    processFile(inadd, outadd);

    return 0;
}