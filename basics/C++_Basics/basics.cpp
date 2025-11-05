#include <iostream>
#include <string>
#include <limits>

int main() {
    /*
    Personal Finance Calculator
    real cool stuff
    */
    std::cout << "Welcome to the first program!" << '\n';
    
    std::cout << "Enter your monthly income: ";
    double monthlyIncome{};
    std::cin >> monthlyIncome; // also prints \n

    // clear buffer i guess (memorise this)
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::string fullName{};
    std::cout << "Enter your full name: ";
    std::getline(std::cin, fullName);

    std::cout << "Enter your monthly money spent on all your stuff: ";
    double monthlyMoneySpent{};
    std::cin >> monthlyMoneySpent;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "\n";
    double remainingMoney{monthlyIncome - monthlyMoneySpent};
    std::cout << "You are saving " << remainingMoney << " each month." << '\n';

    constexpr int monthsInYear{12}; // constexpr means known before program even runs (unlike const which means it may be found during the run)
    double annualRemainingMoney{remainingMoney * monthsInYear};
    if (annualRemainingMoney < 0)
        std::cout << "You're in the red";
    else if (annualRemainingMoney < 100)
        std::cout << "Looking rough";
    else
        std::cout << "Looking good";
    std::cout << " with " << annualRemainingMoney << " left each year." << '\n';

    // use {} for variable creation literally always unless using auto, or making a list
    // use std::size_t, never pull in std

    constexpr int n{10}; // cleanest way to loop over a simple integer
    for (std::size_t i{0}; i<n; ++i) {
        std::cout << i << " ";
    }
    std::cout << '\n';

    return 0; // good habit (no error, error is -1)
}