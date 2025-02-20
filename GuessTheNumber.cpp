#include <bits/stdc++.h>
#include <thread>
#include <chrono>
#include <windows.h>
#include <fstream>
using namespace std;
using namespace chrono;

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

void clearScreen()
{
#ifdef _WIN32
    system("CLS");
#else
    system("clear");
#endif
}

void printLargeNumber(int num)
{
    clearScreen();
    if (num == 3)
    {
        cout << " ***** \n"
             << "     * \n"
             << "  **** \n"
             << "     * \n"
             << " ***** \n";
    }
    else if (num == 2)
    {
        cout << " ***** \n"
             << "     * \n"
             << " ***** \n"
             << " *     \n"
             << " ***** \n";
    }
    else if (num == 1)
    {
        cout << "   *   \n"
             << "  **   \n"
             << "   *   \n"
             << "   *   \n"
             << " ***** \n";
    }
}

void countdown()
{
    SetConsoleTextAttribute(hConsole,11);
    for (int i = 3; i >= 1; i--)
    {
        printLargeNumber(i);
        this_thread::sleep_for(seconds(1));
        clearScreen();
    }
    SetConsoleTextAttribute(hConsole,7);
}

void updateLeaderboard(int score)
{
    vector<int> scores;
    ifstream fin("leaderboard.txt");
    if (fin.is_open())
    {
        int s;
        while (fin >> s)
        {
            scores.push_back(s);
        }
        fin.close();
    }

    scores.push_back(score);

    sort(scores.begin(), scores.end(), greater<int>());

    ofstream fout("leaderboard.txt");
    if (fout.is_open())
    {
        SetConsoleTextAttribute(hConsole,11);
        cout << "\n===== Leaderboard =====\n";
        int count = 0;
        for (int s : scores)
        {
            cout << s << endl;
            fout << s << "\n";
            if (++count == 5)
                break;
        }
        fout.close();
    }
    else
    {
        cout << "Error updating leaderboard." << endl;
    }
    SetConsoleTextAttribute(hConsole,7);
}

void playGame(int range, int maxAttempts)
{
    srand(time(0));
    int numberToGuess = rand() % range + 1;
    int guess, attempts = 0, score = 0;

    SetConsoleTextAttribute(hConsole,11);
    cout << "Guess the number between 1 and " << range << "!" << endl << endl;
    SetConsoleTextAttribute(hConsole,7);

    while (attempts < maxAttempts)
    {
        SetConsoleTextAttribute(hConsole,14);
        cout << "Attempt " << attempts + 1 << " of " << maxAttempts << ": ";
        SetConsoleTextAttribute(hConsole,11);
        cin >> guess;
        SetConsoleTextAttribute(hConsole,7);

        if (guess < 1 || guess > range)
        {
            SetConsoleTextAttribute(hConsole,4);
            cout << "Invalid input! Please enter a number between 1 and " << range << "." << endl;
            SetConsoleTextAttribute(hConsole,7);
            continue;
        }

        attempts++;

        if (guess == numberToGuess)
        {
            score = (maxAttempts - attempts + 1) * 10;
            clearScreen();
            SetConsoleTextAttribute(hConsole,14);
            cout << "Congratulations! You guessed the number correctly!" << endl;
            cout << "Your score: " << score << endl;
            SetConsoleTextAttribute(hConsole,7);
            updateLeaderboard(score);
            return;
        }
        else
        {
            int diff = abs(numberToGuess - guess);

            int threshold = min(10, range / 10);
            if (diff <= threshold)
            {
                SetConsoleTextAttribute(hConsole,13);
                cout << "Very close! ";
            }
            else
            {
                SetConsoleTextAttribute(hConsole,12);
                cout << "Far away! ";
            }

            if (guess < numberToGuess)
            {
                SetConsoleTextAttribute(hConsole,2);
                cout << "Too low!" << endl;
            }
            else
            {
                SetConsoleTextAttribute(hConsole,4);
                cout << "Too high!" << endl;
            }
            SetConsoleTextAttribute(hConsole,7);
        }
    }
    clearScreen();
    SetConsoleTextAttribute(hConsole,14);
    cout << "Game over! The number was " << numberToGuess << "." << endl;
    cout << "Better luck next time!" << endl;
    SetConsoleTextAttribute(hConsole,7);
}

int main()
{
    int choice;
    char playAgain;

    do
    {
        clearScreen();
        SetConsoleTextAttribute(hConsole,11);
        cout << "Welcome to 'Guess the Number' Game!" << endl << endl;
        SetConsoleTextAttribute(hConsole,14);
        cout << "Select difficulty level:" << endl;
        cout << "1. Easy (1-100, 10 attempts)" << endl;
        cout << "2. Medium (1-500, 7 attempts)" << endl;
        cout << "3. Hard (1-1000, 5 attempts)" << endl << endl;

        SetConsoleTextAttribute(hConsole,6);
        cout << "Enter your choice (1/2/3): ";
        SetConsoleTextAttribute(hConsole,11);
        cin >> choice;
        SetConsoleTextAttribute(hConsole,7);
        cout << endl;

        switch (choice)
        {
        case 1:
            countdown();
            playGame(100, 10);
            break;
        case 2:
            countdown();
            playGame(500, 7);
            break;
        case 3:
            countdown();
            playGame(1000, 5);
            break;
        default:
            SetConsoleTextAttribute(hConsole,4);
            cout << "Invalid choice! Exiting game." << endl;
            SetConsoleTextAttribute(hConsole,7);
            return 0;
        }
        SetConsoleTextAttribute(hConsole,14);
        cout << "\nDo you want to play again? (y/n): ";
        SetConsoleTextAttribute(hConsole,11);
        cin >> playAgain;
        SetConsoleTextAttribute(hConsole,14);
    }
    while (playAgain == 'y' || playAgain == 'Y');

    cout << "\nThank you for playing!" << endl;
    SetConsoleTextAttribute(hConsole,7);
    return 0;
}