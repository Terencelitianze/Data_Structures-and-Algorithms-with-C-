// Author: Tianze Li
// Date: January 23, 2025
// Description: a program that calculates and prints the total score followed by the 
// grade letter of a student. The program should prompt the user to enter the marks scored 
// in assignments (out of 20), lab (out of 10), midterm exam (out of 30), and final exam (out of40). 
// The grade letter should be determined based on the following criteria:
// 1. score >= 90 : "A"2. score >= 80 : "B"3. score >= 70 : "C"4. score >= 60 : "D"5. score <  60 : "F"
#include<iostream>
#include<cstdlib>

using namespace std;

int main()
{
    //initaillising the variables to store scores
    int assigmentScore, labScore, midtermScore, finalScore;
    //inputing the assignment score
    cout << "Enter the score of assignment (out of 20): ";
    cin >> assigmentScore;
    //validating the entered score using while loop
    while (assigmentScore < 0 || assigmentScore > 20){
        cout << "Invalid input !!" << endl;
        cout << "Enter the score of assignment (out of 20): ";
        cin >> assigmentScore;
    }
    //inputing the lab score
    cout << "Enter the score of lab (out of 10): ";
    cin >> labScore;
    //validating the entered score using while loop
    while(labScore < 0 || labScore > 10){
        cout << "Invalid input !!" << endl;
        cout << "Enter the score of lab (out of 10): ";
        cin >> labScore;
    }
    //inputing the midterm score
    cout << "Enter the score of midterm exam (out of 30): ";
    cin >> midtermScore;
    //validating the entered score using while loop
    while (midtermScore < 0 || midtermScore > 30){
        cout << "Invalid input !!" << endl;
        cout << "Enter the score of midterm exam (out of 30): ";
        cin >> midtermScore;
    }
    //inputing the final exam score
    cout << "Enter the score of final exam (out of 40): ";
    cin >> finalScore;
    //validating the entered score using while loop
    while (finalScore < 0 || finalScore > 40){
        cout << "Invalid input !!" << endl;
        cout << "Enter the score of final exam (out of 40): ";
        cin >> finalScore;
    }
    // adds all the scores together
    int totalScore = assigmentScore + labScore + midtermScore + finalScore;
    // checks which grade the total score corresponds to
    char grade;
    if (totalScore >= 90){
        grade = 'A';
    }
    else if (totalScore >= 80){
        grade = 'B';
    }
    else if (totalScore >= 70){
        grade = 'C'; 
    }
    else if (totalScore >= 60){
        grade = 'D'; 
    }
    else {
        grade = 'F';
    }
    //outputs the total score and the final grade
    cout << "Total Score = " << totalScore << endl;
    cout << "Grade = " << grade << endl;
    return 0;
}