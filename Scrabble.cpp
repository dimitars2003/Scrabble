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

int * letterCounter = new int(10);
int * roundCounter = new int(10);
std::fstream dictionary;

int main() {

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
