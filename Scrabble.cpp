/**
*
* Solution to course project # 8
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2022/2023
*
* @author Dimitar Donkov
* @idnumber 0MI0600254 @compiler GCC
*
* <main code>
*
*/

#include <iostream>

#include <time.h>

#include <fstream>

int* letterCounter = new int(10);
int* roundCounter = new int(10);
std::fstream dictionary;

char generateLetters()
{

    int r = (rand() % 26) + 97;
    return (char)r;
}

void printLetters(char toPrint[])
{
    for (int i = 0; i < *letterCounter; i++) {
        std::cout << toPrint[i];
        if (i < *letterCounter - 1) {
            std::cout << " ";
        }
        else {
            std::cout << std::endl;
        }
    }
}

void startGame()
{

    int currentRound = 1;
    int points = 0;
    int temp = 0;
    char letters[*letterCounter];
    char word[*letterCounter] = { ' ' };
    int wordLength = 0;

    int usedCounter = 0;
    bool missingLetter = true;

    while (currentRound <= *roundCounter) {

        std::cout << "Round " << currentRound << ". Available letters: ";
        for (int i = 0; i < *letterCounter; i++) {
            letters[i] = generateLetters();
        }

        printLetters(letters);

        while (wordLength == 0) {
            std::cout << "If you want to change letters enter 0" << std::endl;
            std::cin >> word;
            if (word[0] == '0') {
                for (int i = 0; i < *letterCounter; i++) {
                    letters[i] = generateLetters();
                }
                std::cout << "Round " << currentRound << ". Available letters: ";
                printLetters(letters);
                continue;
            }
            for (int i = 0; i < *letterCounter; i++) {
                if (word[i] > 123 || word[i] < 97) {
                    break;
                }
                else {
                    wordLength++;
                }
            }
            if (wordLength < 2) {
                std::cout << std::endl;
                std::cout << "Invalid word. Invalid word length. Please try again. Available letters: " << std::endl;
                printLetters(letters);
                wordLength = 0;
                continue;
            }
        }

        bool checkLetter = false;
        bool hasToBreak = false;
        bool isFound = false;

        int usedLetters[*letterCounter];
        for (int i = 0; i < *letterCounter; i++) {
            usedLetters[i] = -1;
        }

        while (true) {

            for (int i = 0; i < wordLength; i++) {

                if (wordLength == usedCounter) {
                    hasToBreak = true;
                    break;
                }
                for (int j = 0; j < *letterCounter; j++) {
                    if (word[i] == letters[j]) {

                        while (usedLetters[temp] != -1) {
                            if (j == usedLetters[temp]) {
                                checkLetter = true;
                                break;
                            }
                            temp++;
                        }
                        temp = 0;
                        if (checkLetter) {
                            checkLetter = false;
                            continue;
                        }
                        else {
                            usedLetters[usedCounter] = j;
                            usedCounter++;
                            missingLetter = false;
                            isFound = true;
                        }
                    }
                    if (isFound) {

                        isFound = false;
                        break;
                    }
                }

                if (missingLetter) {

                    wordLength = 0;
                    dictionary.close();
                    for (int t = 0; t < usedCounter; t++) {
                        usedLetters[t] = -1;
                    }
                    usedCounter = 0;
                    std::cout << std::endl;
                    std::cout << "Invalid word. Invalid letters used. Please try again. Available letters: " << std::endl;
                    printLetters(letters);

                    while (wordLength == 0) {
                        std::cout << "If you want to change letters enter 0" << std::endl;
                        std::cin >> word;
                        if (word[0] == '0') {
                            for (int i = 0; i < *letterCounter; i++) {
                                letters[i] = generateLetters();
                            }
                            std::cout << "Round " << currentRound << ". Available letters: ";
                            printLetters(letters);
                            continue;
                        }
                        for (int i = 0; i < *letterCounter; i++) {
                            if (word[i] > 123 || word[i] < 97) {

                                break;
                            }
                            else {
                                wordLength++;
                            }
                        }
                        if (wordLength < 2) {

                            std::cout << "Invalid word. Invalid word length. Please try again. Available letters: " << std::endl;
                            printLetters(letters);
                            wordLength = 0;
                            missingLetter = true;
                            continue;
                        }
                    }

                    temp = 0;
                    isFound = true;
                    break;
                }
                else {

                    missingLetter = true;
                }
            }
            if (isFound) {
                isFound = false;
                continue;
            }
            if (hasToBreak) {
                hasToBreak = false;
                break;
            }

            int counterRight = 0;
            temp = 0;
            int dictionaryLength = 0;
            bool hasWord = false;
            char dictionaryCheck[101] = { ' ' };
            dictionaryCheck[100] = '\0';
            std::fstream dictionary;
            dictionary.open("dictionary.txt", std::fstream::in);

            if (dictionary.is_open()) {

                while (!dictionary.eof()) {

                    dictionary >> dictionaryCheck[temp];

                    if (dictionaryCheck[temp] == ':') {
                        if (wordLength != temp) {

                            for (int i = 0; i < temp; i++) {
                                dictionaryCheck[i] = ' ';
                            }
                            dictionaryCheck[100] = '\0';
                            temp = 0;
                            counterRight = 0;
                            continue;
                        }
                        for (int i = 0; i < temp; i++) {
                            if (dictionaryCheck[i] != word[i]) {
                                for (int i = 0; i < temp; i++) {
                                    dictionaryCheck[i] = ' ';
                                }
                                dictionaryCheck[100] = '\0';
                                temp = 0;
                                counterRight = 0;
                                break;
                            }
                            else {
                                counterRight++;
                            }
                        }

                        if (temp == 0) {
                            continue;
                        }
                        if (counterRight == temp) {

                            hasWord = true;
                            break;
                        }
                    }

                    temp++;
                    dictionaryLength++;
                }
            }
            if (!hasWord) {
                std::cout << std::endl;
                std::cout << "Invalid word. Word is invalid or is not included in file. Please try again. Available letters: " << std::endl;
                wordLength = 0;
                for (int t = 0; t < usedCounter; t++) {
                    usedLetters[t] = -1;
                }
                usedCounter = 0;
                printLetters(letters);
                counterRight = 0;
                hasWord = false;
                dictionaryLength = 0;
                for (int i = 0; i < temp; i++) {
                    dictionaryCheck[i] = ' ';
                }
                dictionaryCheck[100] = '\0';
                temp = 0;
                while (wordLength == 0) {
                    std::cout << "If you want to change letters enter 0" << std::endl;
                    std::cin >> word;
                    if (word[0] == '0') {
                        for (int i = 0; i < *letterCounter; i++) {
                            letters[i] = generateLetters();
                        }
                        std::cout << "Round " << currentRound << ". Available letters: ";
                        printLetters(letters);
                        continue;
                    }
                    for (int i = 0; i < *letterCounter; i++) {
                        if (word[i] > 123 || word[i] < 97) {

                            break;
                        }
                        else {
                            wordLength++;
                        }
                    }
                    if (wordLength < 2) {
                        std::cout << std::endl;
                        std::cout << "Invalid word. Invalid word length. Please try again. Available letters: " << std::endl;
                        printLetters(letters);
                        wordLength = 0;
                        dictionary.close();
                        continue;
                    }
                }
                continue;
            }
            hasWord = false;
            dictionary.close();
        }

        temp = 0;
        while (usedLetters[temp] != -1) {
            usedLetters[temp] = -1;
            temp++;
            points++;
        }
        for (int i = 0; i < wordLength; i++) {
            word[i] = ' ';
        }
        wordLength = 0;
        temp = 0;
        usedCounter = 0;
        std::cout << "Points: " << points << std::endl;

        currentRound++;
        std::cout << std::endl;
    }
    std::cout << std::endl
              << "Total points: " << points << std::endl;
    ;
}

void options()
{

    int choice = 0;
    int newRecord = 0;

    while (true) {
        std::cout << std::endl
                  << "Options: " << std::endl;
        std::cout << "1. Change the number of letters the player gets" << std::endl;
        std::cout << "2. Change the number of rounds played" << std::endl;
        std::cout << "3. Return to Main menu" << std::endl;
        std::cin >> choice;

        if (choice < 1 || choice > 3) {
            std::cout << "Invalid input. Please try again." << std::endl;
            continue;
        }

        if (choice == 1) {
            while (true) {
                std::cout << "Enter new number of letters" << std::endl;
                std::cin >> newRecord;

                if (newRecord < 2) {
                    std::cout << "Invalid input. At least 2 letters needed. Please try again." << std::endl;
                    continue;
                }

                letterCounter = new int(newRecord);
                std::cout << "Number of letters changed to: " << *letterCounter << std::endl;
                break;
            }
        }

        if (choice == 2) {
            while (true) {
                std::cout << "Enter new number of rounds" << std::endl;
                std::cin >> newRecord;

                if (newRecord < 2) {
                    std::cout << "Invalid input. At least 2 letters needed. Please try again." << std::endl;
                    continue;
                }

                roundCounter = new int(newRecord);
                std::cout << "Number of rounds changed to: " << *roundCounter << std::endl;
                break;
            }
        }

        if (choice == 3) {
            return;
        }
    }

    return;
}

void addWord()
{
    dictionary.open("dictionary.txt", std::fstream::out | std::fstream::app);

    char newWord[101] = { ' ' };
    int temp = 0;
    int wordLength = 0;

    while (true) {
        std::cout << "Enter the word you wish to add to the dictionary" << std::endl;
        std::cin >> newWord;

        if (newWord[100] < 122 && newWord[100] > 97) {
            std::cout << "Invalid input. The word should have max 100 letters. Please try again." << std::endl;
            continue;
        }

        if (newWord[1] > 122 || newWord[1] < 97) {
            std::cout << "Invalid input. The word should have at least 2 letters. Please try again." << std::endl;
            continue;
        }

        while (newWord[temp] <= 122 && newWord[temp] >= 97) {
            wordLength++;
            temp++;
        }

        break;
    }

    char toAdd[wordLength + 1] = { ' ' };
    toAdd[wordLength] = '\0';

    for (int i = 0; i < wordLength; i++) {

        toAdd[i] = newWord[i];
    }

    for (int i = 0; i < wordLength; i++) {
        std::cout << toAdd[i] << " ";
    }

    dictionary << toAdd << ':';
    std::cout << "Word added. Returning to main menu" << std::endl;
    dictionary.close();
    return;
}

int main()
{

    srand((unsigned)time(NULL));
    int choice = 0;

    while (true) {
        std::cout << "Main menu" << std::endl;
        std::cout << "1. Start a game" << std::endl;
        std::cout << "2. Options" << std::endl;
        std::cout << "3. Add a new word" << std::endl;
        std::cout << "4. Exit" << std::endl;
        std::cin >> choice;

        if (choice < 1 || choice > 4) {
            std::cout << "Invalid input. Please try again." << std::endl;
            continue;
        }

        if (choice == 1) {
            std::cout << std::endl;
            startGame();
        }

        if (choice == 2) {
            options();
            std::cout << std::endl;
            continue;
        }

        if (choice == 3) {
            addWord();
        }

        if (choice == 4) {
            break;
        }
    }

    delete letterCounter;
    delete roundCounter;

    return 0;
}
