/* Program: Simple Calculator
 * Description: A terminal-based calculator that solves math problems.
 *              This implementation of a calculator takes in a math 
 *              expression from user input and attempts to solve it.
 *              Currently, the calculator only handles math expressions that
 *              involve whole numbers and the following operations,
 *              ordered by priority:
 *                  - Multiplication and Division
 *                  - Addition and Subtraction
 *              If the expression has several operations of the same priority,
 *              the expression is solved from left to right.
 *              Furthermore, the program restricts the digits of a whole
 *              number to 10 and the digits of the whole expression to 50.
 *              If the user inputs an expression outside these restrictions,
 *              the program will prompt the user to input an expression again.
 * Author: J. Pettersson
 * Date: 2025-07-22
 */

#include <iostream>
#include <cmath>
#include <vector>

/* ---------------------------- Structs ---------------------------- */

struct element {
    char operation;
    double operand;
};

/* --------------------- Function Declarations --------------------- */

void printIntro(void);
std::string requestInputExpression(void);
bool isExit(std::string str);
std::vector<element> parse(std::string str);
element updateOperand(element element, char digit, int exp);
double getResult(std::vector<element> expression);
element calculate(element element1, element element2);
double multiply(double one, double two);
double divide(double one, double two);
double add(double one, double two);
double minus(double one, double two);
std::vector<element> updateVector(std::vector<element> expression, 
    element element, int index);

/* ------------------------- Main Function ------------------------- */

int main() {
    std::string str;
    std::vector<element> expression;
    double result;

    printIntro();

    while (true) {
        str = requestInputExpression();

        if (isExit(str)) {
            return 0;
        }

        expression = parse(str);

        if (!expression.empty()) {
            std::cout << "The result is: " << getResult(expression) << "\n\n";
        } else {
            std::cout << "Invalid expression, try again.\n\n";
        }
    }
    return 0;
}

/* --------------------- Function Definitions ---------------------- */
/* ------------------------- I/O Functions ------------------------- */

/* 
 * Prints an introduction to the terminal on how to use the program.
 */
void printIntro(void) {
    std::cout << "\n******************* CALCULATOR *******************\n\n"
              << "This calculator has the following features:\n"
              << "\t1. + (Addition)\n"
              << "\t2. - (Subtraction)\n"
              << "\t3. * (Multiplication)\n"
              << "\t4. / (Division)\n\n"
              << "Rules:\n"
              << "\t1. The input has to be a legal mathematical expression.\n"
              << "\t2. The numbers must be an integer.\n"
              << "\t3. Numbers cannot exceed 10 digits.\n"
              << "\t4. The expression cannot exceed 50 digits.\n\n"
              << "To exit program, type 'e'\n\n";
}

/*
 * Reads user input from the terminal.
 * @return the user input as a string
 */
std::string requestInputExpression(void) {
    std::string expression;

    while (expression.empty()) {
        std::cout << "Insert expression: ";
        std::getline(std::cin, expression);
    }
    
    return expression;
}

/* --------------------- Read Input Functions ---------------------- */

/*
 * Checks if user requests to exit the program.
 * @param str the user input read from the terminal
 * @return true if exit command, otherwise false
 */
bool isExit(std::string str) {
    if (str.length() == 1 && str.at(0) == 'e') {
        return true;
    }
    return false;
}

/*
 * Validates the user input and parses the math expression
 * from a string to a vector.
 * @param str the user input read from the terminal
 * @return the math expression if valid, otherwise nothing
 */
std::vector<element> parse(std::string str) {
    std::vector<element> expression;
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
        } else if (digitCount >= 10) {
            return {};
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

            expression.push_back(element);
            element = {};
        } else if (operatorCount == 1 && negativeCount == 1 &&
                (str.at(i) == '+' || str.at(i) == '-' || str.at(i) == '*' ||
                str.at(i) == '/')) {
            element = expression.back();

            if (str.at(i) == '-') {
                element.operation = '+';
                element.operand *= -1;
            } else {
                element.operation = str.at(i);
            }

            expression.pop_back();
            expression.push_back(element);
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
        expression.push_back(element);
    }

    return expression;
}

/*
 * Updates the value of the operand in the internal structure
 * during the parsing process.
 * @param element the internal structure storing the value
 * @param digit the new digit read from parsing
 * @param exp the exponent indicating the digit's positional value
 * @return the updated internal structure storing the value
 */
element updateOperand(element element, char digit, int exp) {
    element.operand += ((digit - '0') * pow(10, exp));
    return element;
}

/* ---------------------- Calculate Functions ---------------------- */

/*
 * Solves the input expression and returns its result.
 * @param expression the input expression to solve
 * @return the result of the input expression
 */
double getResult(std::vector<element> expression) {
    double result;
    element element = {};
    int size;
    int index;

    // Multiplication and Division
    size = expression.size();
    for (int i = size - 2 ; i >= 0 ; i--) {
        if (expression.at(i).operation == '*' ||
                expression.at(i).operation == '/') {
            element = calculate(expression.at(i + 1), expression.at(i));
            expression = updateVector(expression, element, i);
        }
    }

    // Addition and Subtraction
    size = expression.size();
    for (int i = size - 2 ; i >= 0 ; i--) {
        element = calculate(expression.at(i + 1), expression.at(i));
        expression = updateVector(expression, element, i);
    }

    return expression.at(0).operand;
}

/*
 * Performs an operation between two operands.
 * @param element1 the first operand
 * @param element2 the second operand
 * @return the result of the operation
 */
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

/*
 * Performs multiplication.
 * @param a the multiplicand
 * @param b the multiplier
 * @return the product
 */
double multiply(double a, double b) {
    return a * b;
}

/*
 * Performs division.
 * @param a the dividend
 * @param b the divisor
 * @return the quotient
 */
double divide(double a, double b) {
    return a / b;
}

/*
 * Performs addition.
 * @param a the addend
 * @param b the addend
 * @return the sum
 */
double add(double a, double b) {
    return a + b;
}

/*
 * Performs subtraction.
 * @param a the minuend
 * @param b the subtrahend
 * @return the difference
 */
double minus(double a, double b) {
    return a - b;
}

/*
 * Updates the expression after one operation was performed.
 * @param expression the expression
 * @param element the result of the operation
 * @param index the position in the expression where
 *        the operation was performed.
 * @return the updated vector data structure 
 */
std::vector<element> updateVector(std::vector<element> expression, 
        element element, int index) {
    expression.erase(expression.begin() + index, expression.begin() + index + 2);
    expression.insert(expression.begin() + index, element);
    return expression;
}