//
//  main.cpp
//  TreeTest
//
//  Created by Adam Lewis on 10/3/16.
//  Copyright © 2016 Adam Lewis. All rights reserved.
//

#include <iostream>
#include "Tree.hpp"


auto f2 = [](int thing)->void {std::cout << thing << " "; };

int main(int argc, const char * argv[]) {

    std::cout << "Tree test program\n";
    Tree<int> aTree({45,74,28,32,45,44,100});

    std::cout << "Preorder: ";
    aTree.preorder(f2);
    std::cout << "\nIn-order: ";
    aTree.inorder(f2);
    std::cout << "\nPostorder: ";
    aTree.postorder(f2);
    std::cout << std::endl;

    aTree.remove(45, aTree.rootNode());
    std::cout << "\n\nDelete 45\n";
    std::cout << "===================================\n";
    std::cout << "Preorder: ";
    aTree.preorder(f2);
    std::cout << "\nIn-order: ";
    aTree.inorder(f2);
    std::cout << "\nPostorder: ";
    aTree.postorder(f2);
    std::cout << std::endl;
    std::cout << "===================================\n";

    aTree.remove(28, aTree.rootNode());
    std::cout << "\n\nDelete 28\n";
    std::cout << "===================================\n";
    std::cout << "Preorder: ";
    aTree.preorder(f2);
    std::cout << "\nIn-order: ";
    aTree.inorder(f2);
    std::cout << "\nPostorder: ";
    aTree.postorder(f2);
    std::cout << std::endl;
    std::cout << "===================================\n";

    aTree.remove(100, aTree.rootNode());
    std::cout << "\n\nDelete 100\n";
    std::cout << "===================================\n";
    std::cout << "Preorder: ";
    aTree.preorder(f2);
    std::cout << "\nIn-order: ";
    aTree.inorder(f2);
    std::cout << "\nPostorder: ";
    aTree.postorder(f2);
    std::cout << std::endl;
    std::cout << "===================================\n";

    aTree.remove(28, aTree.rootNode());
    std::cout << "\n\nDelete 28 (Not in tree)\n";
    std::cout << "===================================\n";
    std::cout << "Preorder: ";
    aTree.preorder(f2);
    std::cout << "\nIn-order: ";
    aTree.inorder(f2);
    std::cout << "\nPostorder: ";
    aTree.postorder(f2);
    std::cout << std::endl;
    std::cout << "===================================\n";


    return 0;
}
