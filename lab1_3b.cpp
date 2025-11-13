// Author: Tianze Li
// Date: January 23, 2025
// Description: A program that asks the user to enter a positive integer number N.
// The program then displays the number (count)of prime numbers that are smaller than N.
#include<iostream>
#include<cstdlib>

using namespace std;

int main()
{
    //initiallising a value for positive integer and a count to count how many primes there are
    int Ncount = 0;
    int Num;
    //inputs the poistive integer
    cout << "Please enter a positive number: ";
    cin >> Num;
    //validates so it is a positive integer is entered
    while (Num < 0){
        cout << "Please enter a positive number: ";
        cin >> Num;
    }
    //loops through all the numbers that are smaller than the number entered
    for (int i = 2; i < Num; i++)
    {
        //intiallises a boolean value
        bool isPrime = true;
        //loops from 2 to the nearest root of the number so all possible divisor is checked
        for (int j = 2; j * j <= i; j++){
            // if divisor found the boolean value becomes false
            if (i % j == 0){
                isPrime = false;
                break;
            }
        }
        // if no divisor is found, it means it is a prime number, so count increments by 1
        if (isPrime){
            Ncount++;
        }
    }
    //outputs the number of primes that is smaller than the original value
    cout << "Number of prime numbers smaller than " << Num << " are: " << Ncount << endl;
    return 0;
}