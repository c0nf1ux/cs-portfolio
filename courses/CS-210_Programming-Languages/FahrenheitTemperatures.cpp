#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

// Function to convert Fahrenheit to Celsius
double fahrenheitToCelsius(int fahrenheit) {
    return (fahrenheit - 32) * 5.0 / 9.0;
}

int main() {
    // Open input file
    std::ifstream inputFile("FahrenheitTemperature.txt");
    if (!inputFile.is_open()) {
        std::cerr << "Error opening input file. Make sure FahrenheitTemperature.txt is in the same directory as this program." << std::endl;
        return 1;
    }

    // Open output file
    std::ofstream outputFile("CelsiusTemperature.txt");
    if (!outputFile.is_open()) {
        std::cerr << "Error opening output file." << std::endl;
        inputFile.close();
        return 1;
    }

    std::string city;
    int fahrenheit;

    // Set precision for output file
    outputFile << std::fixed << std::setprecision(2);

    // Read from input file, convert temperature, and write to output file
    while (inputFile >> city >> fahrenheit) {
        double celsius = fahrenheitToCelsius(fahrenheit);
        outputFile << city << " " << celsius << std::endl;
    }

    // Close files
    inputFile.close();
    outputFile.close();

    std::cout << "Conversion complete. Results written to CelsiusTemperature.txt" << std::endl;

    return 0;
}