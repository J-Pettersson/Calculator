#include <iostream>
#include <cmath>
#include <vector>

struct element {
    char operation;
    double operand;
};

void printHowTo() {
    std::cout << "\n******************* CALCULATOR *******************\n\n"
              << "This calculator has the following features:\n"
              << "\t1. + (Addition)\n"
              << "\t2. - (Subtraction)\n"
              << "\t3. * (Multiplication)\n"
              << "\t4. / (Division)\n\n"
              << "Rules:\n"
              << "\t1. The equation has to be a legal mathematical equation.\n"
              << "\t2. The numbers must be an integer.\n"
              << "\t3. Numbers cannot exceed 10 digits.\n"
              << "\t4. The equation cannot exceed 50 digits.\n\n"
              << "To exit program, type 'e'\n\n";
}

std::string requestEquation() {
    std::string equation;

    while (equation.empty()) {
        std::cout << "Insert equation: ";
        std::getline(std::cin, equation);
    }
    
    return equation;
}

bool isExit(std::string equation) {
    if (equation.length() == 1 && equation.at(0) == 'e') {
        return true;
    }
    return false;
}

element updateOperand(element element, char digit, int exp) {
    element.operand += ((digit - '0') * pow(10, exp));
    return element;
}

std::vector<element> parse(std::string str) {
    std::vector<element> equation;
    element element;
    int digitCount = 0;
    int operatorCount = 0;
    int negativeCount = 0;

    if (str.length() > 50) {
        return {};
    }

    element = {};
    for (int i = str.size() - 1 ; i >= 0 ; i--) {
        if (str.at(i) == ' ') {
            str.erase(i, 1);
        } else if ((str.at(i) >= '1' && str.at(i) <= '9') ||
                (digitCount > 0 && str.at(i) == '0')) {
            element = updateOperand(element, str.at(i), digitCount);
            digitCount++;
            negativeCount = 0;
            operatorCount = 0;
        } else if (operatorCount == 0 && digitCount > 0 && (str.at(i) == '+' ||
                str.at(i) == '-' || str.at(i) == '*' || str.at(i) == '/')) {
            digitCount = 0;
            operatorCount++;
            element.operation = str.at(i);

            if (element.operation == '-') {
                element.operand *= -1;
                negativeCount++;
            }

            equation.push_back(element);
            element = {};
        } else if (operatorCount == 1 && negativeCount == 1 &&
                (str.at(i) == '+' || str.at(i) == '-' || str.at(i) == '*' ||
                str.at(i) == '/')) {
            element = equation.back();

            if (str.at(i) == '-') {
                element.operation = '+';
                element.operand *= -1;
            } else {
                element.operation = str.at(i);
            }

            equation.pop_back();
            equation.push_back(element);
            negativeCount++;
            element = {}; 
        } else {
            return {};
        }
    }

    if (negativeCount > 1) {
        return {};
    }

    if (negativeCount == 0) {
        if (operatorCount > 0) {
            return {};
        }

        element.operation = '+';
        equation.push_back(element);
    }

    return equation;
}

double multiply(double one, double two) {
    return one * two;
}

double divide(double one, double two) {
    return one / two;
}

double add(double one, double two) {
    return one + two;
}

double minus(double one, double two) {
    return one - two;
}

element calculate(element element1, element element2) {
    element element = {};
    double operand;

    switch (element2.operation) {
        case '*':
            operand = multiply(element1.operand, element2.operand);
            break;
        case '/':
            operand = divide(element1.operand, element2.operand);
            break; 
        default:
            operand = add(element1.operand, element2.operand);
            break;
    }

    element.operation = element1.operation;
    element.operand = operand;

    return element;
}

std::vector<element> updateVector(std::vector<element> equation, 
                                  element element, int index) {
    equation.erase(equation.begin() + index, equation.begin() + index + 2);
    equation.insert(equation.begin() + index, element);
    return equation;
}

double getResult(std::vector<element> equation) {
    double result;
    element element = {};
    int size;
    int index;

    // Multiplication and Division
    size = equation.size();
    for (int i = size - 2 ; i >= 0 ; i--) {
        if (equation.at(i).operation == '*' || equation.at(i).operation == '/') {
            element = calculate(equation.at(i + 1), equation.at(i));
            equation = updateVector(equation, element, i);
        }
    }

    // Addition and Subtraction
    size = equation.size();
    for (int i = size - 2 ; i >= 0 ; i--) {
        element = calculate(equation.at(i + 1), equation.at(i));
        equation = updateVector(equation, element, i);
    }

    return equation.at(0).operand;
}


int main() {
    std::string str;
    std::vector<element> equation;
    double result;

    printHowTo();

    while (true) {

        str = requestEquation();

        if (isExit(str)) {
            return 0;
        }

        equation = parse(str);

        if (!equation.empty()) {
            std::cout << "The result is: " << getResult(equation) << "\n\n";
        } else {
            std::cout << "Invalid equation, try again.\n\n";
        }
    }
    
    return 0;
}

