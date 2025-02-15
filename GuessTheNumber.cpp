#include<bits/stdc++.h>
using namespace std;

void playGame(int range, int maxAttempts)
{
    srand(time(0));
    int numberToGuess = rand() % range + 1;
    int guess, attempts = 0, score = 0;
 
    cout << "Guess the number between 1 and " << range << "!" << endl;
 
    while (attempts < maxAttempts)
    {
        cout << "Attempt " << attempts + 1 << " of " << maxAttempts << ": ";
        cin >> guess;
 
        if (guess < 1 || guess > range)
        {
            cout << "Invalid input! Please enter a number between 1 and " << range << "." << endl;
            continue;
        }
 
        attempts++;
 
        if (guess == numberToGuess)
        {
            score = (maxAttempts - attempts + 1) * 10;
            cout << "Congratulations! You guessed the number correctly!" << endl;
            cout << "Your score: " << score << endl;
            return;
        }
        else if (guess < numberToGuess)
        {
            cout << "Too low!" << endl;
        }
        else
        {
            cout << "Too high!" << endl;
        }
    }
 
    cout << "Game over! The number was " << numberToGuess << "." << endl;
    cout << "Better luck next time!" << endl;
}



int  main()
{
    int choice;
    cout << "Welcome to 'Guess the Number' Game!" << endl;
    cout << "Select difficulty level:" << endl;
    cout << "1. Easy (1-100, 10 attempts)" << endl;
    cout << "2. Medium (1-500, 7 attempts)" << endl;
    cout << "3. Hard (1-1000, 5 attempts)" << endl;
    cout << "Enter your choice (1/2/3): ";
    cin >> choice;

    switch (choice)
    {
    case 1:
        playGame(100, 10);
        break;
    case 2:
        playGame(500, 7);
        break;
    case 3:
        playGame(1000, 5);
        break;
    default:
        cout << "Invalid choice! Exiting game." << endl;
    }
 
    return 0;

}