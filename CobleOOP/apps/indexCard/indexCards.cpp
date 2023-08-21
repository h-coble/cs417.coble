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
    fileOut.open("indexCardOutput.txt", std::ios::app);
    fileOut << thing.getIndex() << " " << thing.getKeyword() << std::endl;
    fileOut.close();
};


Tree<IndexCard> readToTree()
{
    ifstream fileIn;
    int tempIndex = -1;
    string tempStr = "";
    IndexCard tempCard;
    fileIn.open("indexCards.txt");
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
    fileOut.open("indexCardOutput.txt");
    fileOut.close();
    tree.inorder(f3);
}

int main(int argc, const char * argv[]) {

    
    IndexCard aCard(1, "first"), anotherCard(2,"second");       //Create two index cards
    Tree<IndexCard> aTree({aCard,anotherCard});                 //Create a tree with this list of cards.
    
    //Verify Tree
    std::cout << "Verify that tree was built\n";
    std::cout << "Preorder: \n";
    aTree.preorder(f2);
    std::cout << "\nIn-order: \n";
    aTree.inorder(f2);
    std::cout << "\nPostorder: \n";
    aTree.postorder(f2);
    std::cout << std::endl;

    //Card setters and tree insertion tests
    aCard.setIndex(4);
    aCard.setKeyword("four");
    aTree = aTree.insert(aCard);

    aCard.setIndex(5);
    aCard.setKeyword("five");
    aTree = aTree.insert(aCard);

    aCard.setIndex(3);
    aCard.setKeyword("three");
    aTree = aTree.insert(aCard);

    //Check that tree is properly formed
    std::cout << "Verify that insertions worked\n";
    std::cout << "Preorder: \n";
    aTree.preorder(f2);
    std::cout << "\nIn-order: \n";
    aTree.inorder(f2);
    std::cout << "\nPostorder: \n";
    aTree.postorder(f2);
    std::cout << std::endl;

    //Delete a card from Tree and verify it's gone
    std::cout << "Deleting this card -->\t"; anotherCard.printCard();
    aTree.remove(anotherCard,aTree.rootNode());

    std::cout << "Preorder: \n";
    aTree.preorder(f2);
    std::cout << "\nIn-order: \n";
    aTree.inorder(f2);
    std::cout << "\nPostorder: \n";
    aTree.postorder(f2);
    std::cout << std::endl;

    //Delete again
    aTree.remove(anotherCard, aTree.rootNode());
    std::cout << "Verify that an invalid deletion doesn't affect tree; attempted to delete the same card.\n";
    aTree.preorder(f2);
    std::cout << "\nIn-order: \n";
    aTree.inorder(f2);
    std::cout << "\nPostorder: \n";
    aTree.postorder(f2);
    std::cout << std::endl;

    std::cout << "Bool return from .find: " << aTree.find(anotherCard, aCard) <<std::endl;

    //File In
    Tree<IndexCard>anotherTree;
    anotherTree = readToTree();

    //Check for new insertions.
    std::cout << "\n Tree From File In-order: \n";
    anotherTree.inorder(f2);
  
    writeToFile(anotherTree);

    return 0;
}
