#include <iostream>

int main() {
    std::string equation;

    std::cout << "This calculator has the following features:\n"
              << "\t1. + (Addition)\n"
              << "\t2. - (Subtraction)\n"
              << "\t3. * (Multiplication)\n"
              << "\t4. / (Division)\n\n"
              << "Rules:\n"
              << "The equation has to be a legal mathematical equation.\n"
              << "Numbers cannot exceed 10 digits.\n"
              << "The equation cannot exceed 50 digits.\n\n";

    std::cout << "Insert equation: ";
    std::cin >> equation;
    std::cout << equation;

    return 0;
}