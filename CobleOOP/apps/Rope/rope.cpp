#include <iostream>
#include <string>
#include <memory>

class RopeNode {
public:
    std::string data;
    int weight = data.length();
    std::shared_ptr<RopeNode> left;
    std::shared_ptr<RopeNode> right;

    RopeNode(const std::string& str) : data(str), weight(str.length()), left(nullptr), right(nullptr) {}
};

class Rope {
private:


    // Helper function to insert a node recursively
    std::shared_ptr<RopeNode> insert(std::shared_ptr<RopeNode> current, const std::string& str) {
        if (current == nullptr) {
            return std::make_shared<RopeNode>(str);
        }

        if (str < current->data) {
            current->left = insert(current->left, str);
        }
        else if (str > current->data) {
            current->right = insert(current->right, str);
        }

        return current;
    }


public:
    Rope() : root(nullptr) {}
    std::shared_ptr<RopeNode> root;
    // Public function to insert a string into the  Rope
    void insert(const std::string& str) {
        root = insert(root, str);
        root->weight = root->data.length();
    }

    // Public function to perform an in-order traversal and print the nodes
    void inOrderTraversal(std::shared_ptr<RopeNode> current) {
        if (current != nullptr) {
            inOrderTraversal(current->left);
            std::cout << "String: " << current->data << ", Weight: " << current->weight << std::endl;
            inOrderTraversal(current->right);
        }
    }

    // Public function to print the entire Rope
    void printRope() {
        inOrderTraversal(root);
    }

    char index(int i)
    {
        if (i > root->left->weight)
        {
            //Go to right
            return index(root->right, i - root->left->weight);
        }
        else if (i <= root->left->weight)
        {
            //Go to left
            return index(root->left, i);
        }
    }
    //Note: Canvas says to use Rope& node
    char index(std::shared_ptr<RopeNode> node, int i)
    {
        if (node->data != "")
            return node->data[i];
        else if (i > node->left->weight)
        {
            //Go to right child
            return index(node->right, i - node->left->weight);
        }
        else if (i <= node->left->weight)
        {
            //Go to left child
            return index(node->left, i);
        }
        else
            std::cerr << "Error navigating to char at given index.\n";
    }

    //Returns pointer to an internal node with two children
    //Children have half the string of the original node
    //Returned node has no string, but has weight = two children's sum

    std::shared_ptr<RopeNode> split(int i)
    {
        //Root only, no children
        if (root->left == root->right && root->right == nullptr)
        {
            if (i < root->data.length())
            {
                std::shared_ptr<RopeNode> newL;
                newL->data = root->data;
                newL->weight = root->weight;

                root->left = newL;
                std::shared_ptr<RopeNode> newR;
                newR->data = "";
                newR->weight = 1;

                root->right = newR;
                return root;
            }

        }
        else
        {
            if (i > root->left->weight)
            {
                //Go to right
                return split(root->right, i - root->left->weight);
            }
            else if (i <= root->left->weight)
            {
                //Go to left
                return split(root->left, i);
            }
        }
    }
    std::shared_ptr<RopeNode> split(std::shared_ptr<RopeNode> node, int i)
    {
        //if node is a leaf
        if (node->left == nullptr && node->right == nullptr)
        {
            if (i == node->data.length())
            {
                //Left Leaf
                std::shared_ptr<RopeNode> newL;
                newL->data = node->data;
                newL->weight = node->weight;

                node->left = newL;

                //Right Leaf
                std::shared_ptr<RopeNode> newR;
                newR->data = "";
                newR->weight = 1;

                node->data = "";
                node->right = newR;
                return root;
            }
            else if (i < node->data.length())
            {
                std::string lftStr, rgtStr;
                lftStr = rgtStr = "";

                for (int j = 0; j < i; j++)
                {
                    lftStr[j] = node->data[j];
                }
                for (int j = i; j < node->data.length(); j++)
                {
                    rgtStr[j] = node->data[j];
                }
                //Left Leaf Creation
                std::shared_ptr<RopeNode> newL;
                newL->data = lftStr;
                newL->weight = lftStr.length();

                node->left = newL;
                //Right Leaf Creation
                std::shared_ptr<RopeNode> newR;
                newR->data = rgtStr;
                newR->weight = rgtStr.length();

                node->right = newR;

                node->data = "";
                return node;
            }
        }
        //else if internal node, continue to find appropriate leaf
        else if (i > root->left->weight)
        {
            //Go to right
            return split(root->right, i - root->left->weight);
        }
        else if (i <= root->left->weight)
        {
            //Go to left
            return split(root->left, i);
        }
    }

    std::shared_ptr<RopeNode>concat(RopeNode rope2)
    {
        std::shared_ptr<RopeNode> newRoot;

        newRoot->left = newRoot;
        newRoot->weight = newRoot->left->weight;
        newRoot->right = std::make_shared<RopeNode>(rope2);

        root = newRoot;
        return root;
    }

    //Couldn't get these functions to work for the rope.
    //Couldn't find any online resources to get more information on ropes aside from information about the boost library and STL ropes

};

int main() {
    Rope rope;

    rope.insert("apple");
    rope.root = rope.split(3);

    std::cout << "Rope Contents:" << std::endl;
    rope.printRope();

    return 0;
}
