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
        Tree<IndexCard> tree;   //Creates empty tree to return
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
    std::cout << "\nFile read succesfully, new deck was created!\n";
    return tree;
}

void writeToFile(Tree<IndexCard> tree)
{
    ofstream fileOut;
    fileOut.open("../../../indexCardOutput.txt");
    fileOut.close();
    tree.inorder(f3);

    std::cout << "Deck succesfully saved to indexCardOutput.txt\n\n";
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

Tree<IndexCard> manuallyCreateTree()
{
    //Used to create inital deck if opted for
    int index;
    std::string keyword;
    std::cout << "First card index: ";
    std::cin >> index;
    std::cout << "First card keyword: ";
    std::cin >> keyword;

    IndexCard first(index, keyword);

    Tree<IndexCard> treeReturn({first});

    return treeReturn;
}

void deleteCardFromDeck(Tree<IndexCard>& TreeDel)
{
    std::cout << "The card with matching information will be deleted.\n";
    IndexCard deleteCard = createCard();
    TreeDel.remove(deleteCard, TreeDel.rootNode());
}
void searchForCard(Tree<IndexCard>& tree)
{
    std::cout << "This info will be used to search the deck.\n";
    IndexCard search = createCard();
    IndexCard found;
    if (tree.find(search, found))
    {
        std::cout << "The card was found in the deck with this information:\n";
        found.printCard();
    }
    else
    {
        search.printCard();
        std::cout << "A card with the given info was not found in deck.\n";
    }
}

 

int main(int argc, const char * argv[]) 
{
    Tree<IndexCard> deck;

    int choice = 4;
    
    do
    {
        std::cout << "=========================================\n\n";
        std::cout << "To create a deck of index cards, one card is required.\nWould you like to manually create one or read from a file?\n"
            << "1. Manual\n"
            << "2. Read from file\n";
        std::cin >> choice;

        if (choice == 1)
        {
            deck = manuallyCreateTree();
            break;
        }
        else if (choice == 2)
        {
            deck = readToTree();
            break;
        }
        else
            std::cerr << "Invalid input, try again.\n\n";
    } while (true);
        

    do
    {
        std::cout << "=========================================\n\n"; //Closes section, used just to organize display
        std::cout << "*****************************************"      //Opens menu section, same as above
            <<"\n1.Create Index Card\n"
            << "2. Create Deck of Index Cards from File (overwrites current deck)\n"
            << "3. Write Deck of Index Cards to File\n"
            << "4. Print Deck of Cards to Screen\n"
            << "5. Remove Index Card\n"
            << "6. Search for Index Card\n"
            << "0. Exit\n"
            << "Enter your selection: ";
        std::cin >> choice;
        std::cout << "*****************************************\n\n";   //close menu section
        std::cout << "=========================================\n";     //open selected operation section

        switch (choice)
        {
        case 0:
            std::cout << "Closing program...\n";
            std::cout << "=========================================\n\n";
            return 0;
            break;

        case 1:
            //make new tree with a new card
            deck = deck.insert({ createCard() });   
            std::cout << "\nCard inserted!\n";
            break;
        case 2:
            //Tree from card info in file
            deck = readToTree(); 
            break;
        case 3:
            //Tree to file
            writeToFile(deck);
            break;
        case 4:
            //View in console
            deck.inorder(f2);
            break;
        case 5:
            //Remove card
           deleteCardFromDeck(deck);
           break;
        case 6:
            searchForCard(deck);
            break;
        default:
            //Invalid
            std::cout << "\mInvalid choice, try again.\n\n";
            break;
        }
        
    } while (true);

    //Something has gone very wrong if this executes.
    //Code shouldn't exit loop.
    return -1;

}
