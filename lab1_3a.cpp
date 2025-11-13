// Author: Tianze Li
// Date: January 23, 2025
// Description: A program that asks the user to enter a positive integer number and 
// checks and prints if the number is a prime number or not
#include<iostream>
#include<cstdlib>

using namespace std;

int main()
{
    //initiallising a value for positive integer and a boolean value
    int PositiveInteger;
    bool isPrime = true;
    //input a positive number from user
    cout << "Please enter a positive number: ";
    cin >> PositiveInteger;
    //validates to make sure number entered is postive
    while (PositiveInteger < 0){
        cout << "Please enter a positive number: ";
        cin >> PositiveInteger;
    }
    //checks is the value enter is positive and not divisable by any other number except itself
    if (PositiveInteger > 1){
        //it has to be greater than 1, since 1 is not a prime number
        //loops from 2 to the nearest root of the number so all possible divisor is checked
        for (int i = 2; i * i <= PositiveInteger; i++){
            // if divisor found the boolean value becomes false, else true
            if (PositiveInteger % i == 0){
                isPrime = false;
                break;
            }
            else {
                isPrime = true;
            }
        }
    }
    //checks if the boolean value is true or not and output accordingly
    if (isPrime){
        cout << PositiveInteger << " is a prime number.." << endl;
    }
    else {
        cout << PositiveInteger << " is a not prime number.." << endl;
    }
    return 0;
}