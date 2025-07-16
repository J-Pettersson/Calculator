#include <iostream>

void printHowTo() {
    std::cout << "This calculator has the following features:\n"
              << "\t1. + (Addition)\n"
              << "\t2. - (Subtraction)\n"
              << "\t3. * (Multiplication)\n"
              << "\t4. / (Division)\n\n"
              << "Rules:\n"
              << "The equation has to be a legal mathematical equation.\n"
              << "Numbers cannot exceed 10 digits.\n"
              << "The equation cannot exceed 50 digits.\n\n"
              << "To exit program, type 'e'\n\n";
}

std::string requestEquation() {
    std::string equation;

    std::cout << "Insert equation: ";
    std::getline(std::cin >> std::ws, equation);

    return equation;
}

bool isExit(std::string equation) {
    if (equation.length() == 1 && equation.at(0) == 'e') {
        return true;
    }
    return false;
}

bool isLegal(std::string equation) {
    int digitCount = 0;
    int operatorCount = 0;
    int negativeCount = 0;

    if (equation.length() > 50) {
        return false;
    }

    for (int i = 0 ; i < equation.length() ; i++) {
        if ((equation.at(i) >= '1' && equation.at(i) <= '9') ||
                (digitCount > 0 && equation.at(i) == '0')) {
            digitCount++;
            negativeCount = 0;
            operatorCount = 0;
        } else if (equation.at(i) == ' ') {
            // Do nothing
        } else if (digitCount == 0 && equation.at(i) == '-' &&
                   negativeCount == 0) {
            negativeCount++;
        } else if (operatorCount > 0) {
            return false;
        } else if (digitCount > 0 && (equation.at(i) == '+' ||
                equation.at(i) == '-' || equation.at(i) == '*' ||
                equation.at(i) == '/')) {
            digitCount = 0;
            operatorCount++;
        } else {
            return false;
        }
    }

    if (operatorCount > 0) {
        return false;
    }

    return true;
}

double calculate(std::string equation) {
    double result = 0;

    return result;
}

int main() {
    std::string equation;

    printHowTo();

    while (true) {
        equation = requestEquation();

        if (isExit(equation)) {
            return 0;
        }

        if (isLegal(equation)) {
            std::cout << calculate(equation) << "\n";
        } else {
            std::cout << "Invalid equation, try again.\n";
        }
    }
    
    return 0;
}

