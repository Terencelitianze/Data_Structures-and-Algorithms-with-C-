// C++ Program: Enter Celsius and output Fahrenheit
// Author: Tianze Li
// Date: January 23, 2025
// Description: The user will input the number for celsius and the program will output
// the corresponding Fahrenheit using the formula: F = C x 1.8+32
#include<iostream>
#include<cstdlib>

using namespace std;

int main(){
    // intiallze a variable call i (for temperature in Celsius)
    float i;
    // Get user input for the temperature in Celsius
    cout << "Enter the temperature in Celsius: ";
    cin >> i; 
    // Using the equation F = C x 1.8+32 to get temperature in Fahrenheit
    float Fahrenheit = i * 1.8 + 32;
    // outputs the fahrenheit temperature
    cout << "Tempertaure in Fahrenheit is: " << Fahrenheit << endl;
    return 0;
}