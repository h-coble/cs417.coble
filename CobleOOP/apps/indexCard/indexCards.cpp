//
//  main.cpp
//  TreeTest
//
//  Created by Adam Lewis on 10/3/16.
//  Copyright © 2016 Adam Lewis. All rights reserved.
//

#include <iostream>
#include <fstream>
#include "Tree.hpp"
#include "Card.hpp"

auto f2 = [](IndexCard thing)->void {thing.printCard();};
auto f3 = [](IndexCard thing)->void 
{
    ofstream fileOut;
    fileOut.open("../../../indexCardOutput.txt", std::ios::app);
    fileOut << thing.getIndex() << " " << thing.getKeyword() << std::endl;
    fileOut.close();
};
//E:\Git Client\ExampleGit\cs417.coble\CobleOOP\docs

Tree<IndexCard> readToTree()
{
    ifstream fileIn;
    int tempIndex = -1;
    string tempStr = "";
    IndexCard tempCard;
    fileIn.open("../../../indexCards.txt");
    if (!fileIn.is_open())
    {
        std::cerr << "Error opening file.\n";
        Tree<IndexCard> tree;   //Does nothing
    }

    //Create tree from first card
    fileIn >> tempIndex >> tempStr;
    tempCard.setIndex(tempIndex);
    tempCard.setKeyword(tempStr);
    Tree<IndexCard> tree({tempCard});

    //Fill tree by inserting remaining
    while (fileIn >> tempIndex >> tempStr)
    {
        tempCard.setIndex(tempIndex);
        tempCard.setKeyword(tempStr);
        tree = tree.insert(tempCard);
    }
    fileIn.close();
    return tree;
}

void writeToFile(Tree<IndexCard> tree)
{
    ofstream fileOut;
    fileOut.open("../../../indexCardOutput.txt");
    fileOut.close();
    tree.inorder(f3);
}

IndexCard createCard()
{
    int index=0;
    std::string keyword = "";
    
    std::cout << "Enter your desired index: ";
    std::cin >> index;
    std::cout << "Enter your keyword: ";
    std::cin >> keyword;
    
    IndexCard outCard(index, keyword);

    return outCard;
}

int main(int argc, const char * argv[]) 
{
    IndexCard initialCard(-1,"initial");
    Tree<IndexCard> deck({ initialCard });
    bool firstInsert = true;

    int choice = 4;
    do
    {
        std::cout << "1. Create Index Card\n"
            << "2. Create Deck of Index Cards from File\n"
            << "3. Write Deck of Index Cards to File\n"
            << "4. Print Deck of Cards to Screen\n"
            << "0. Exit\n"
            << "Enter your selection: ";
        std::cin >> choice;

        std::cout << endl;

        switch (choice)
        {
        case 0:
            return 0;
            break;

        case 1:
            deck = deck.insert({ createCard() });
            if (firstInsert)
            {
                deck.remove(initialCard, deck.rootNode());//Doesn't work, needs to change how/when Tree is created
                firstInsert = false;
            }
            break;
        case 2:
            deck = readToTree();
            break;
        case 3:
            writeToFile(deck);
            break;
        case 4:
            deck.inorder(f2);
            break;
        default:
            cout << "Invalid choice, try again.\n\n";
            break;
        }
    } while (true);

        return -1;
 
}
