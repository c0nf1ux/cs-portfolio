/*
 * Calculator.cpp
 *
 *  Date: 9/15/2024
 *  Author: Heath Davis
 */
#include <iostream>
#include <string> // Added for std::string

using namespace std;

int main() // Changed from void main() to int main()
{
    // Removed unused variable: char statement[100];
    double op1, op2; // Changed to double for floating-point operations
    char operation;
    char answer = 'Y'; // Changed from "Y" to 'Y' for char literal
    
    while (answer == 'Y' || answer == 'y') // Added lowercase 'y' check
    {
        cout << "Enter expression" << endl;
        cin >> op1 >> operation >> op2; // Swapped op1 and op2 to match output
        
        if (operation == '+')
            cout << op1 << " + " << op2 << " = " << op1 + op2 << endl;
        else if (operation == '-') // Changed to else if and removed semicolon
            cout << op1 << " - " << op2 << " = " << op1 - op2 << endl;
        else if (operation == '*') // Fixed operator symbol in output
            cout << op1 << " * " << op2 << " = " << op1 * op2 << endl;
        else if (operation == '/') // Fixed operator symbol in output
        {
            if (op2 != 0) // Added division by zero check
                cout << op1 << " / " << op2 << " = " << op1 / op2 << endl;
            else
                cout << "Error: Division by zero" << endl;
        }
        else
            cout << "Error: Invalid operation" << endl;
        
        cout << "Do you wish to evaluate another expression? (Y/N) " << endl;
        cin >> answer;
    }

    cout << "Program Finished." << endl; // Added exit message

    return 0; // Added return statement
}