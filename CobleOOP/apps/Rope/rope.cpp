#include <iostream>
#include <string>
#include <memory>

class RopeNode {
public:
    std::string data;
    std::shared_ptr<RopeNode> left;
    std::shared_ptr<RopeNode> right;

    RopeNode(const std::string& str)
        : data(str), left(nullptr), right(nullptr) {}
};

class Rope {
private:
    std::shared_ptr<RopeNode> root;

    // Helper function to concatenate two ropes
    std::shared_ptr<RopeNode> concat(std::shared_ptr<RopeNode> leftNode, std::shared_ptr<RopeNode> rightNode) {
        std::shared_ptr<RopeNode> newNode = std::make_shared<RopeNode>("");
        newNode->left = leftNode;
        newNode->right = rightNode;
        return newNode;
    }

    // Helper function to split a rope at a specific index
    std::pair<std::shared_ptr<RopeNode>, std::shared_ptr<RopeNode>> split(std::shared_ptr<RopeNode> node, int index) {
        if (!node) return { nullptr, nullptr };

        if (index == 0) return { nullptr, node };
        if (index >= static_cast<int>(node->data.length())) return { node, nullptr };

        std::shared_ptr<RopeNode> left = nullptr;
        std::shared_ptr<RopeNode> right = nullptr;

        if (index < static_cast<int>(node->data.length())) {
            left = std::make_shared<RopeNode>(node->data.substr(0, index));
            right = std::make_shared<RopeNode>(node->data.substr(index));
        }

        return { left, right };
    }

    // Helper function to get the string representation of a rope node
    std::string getRopeString(std::shared_ptr<RopeNode> node) {
        if (!node) return "";
        if (!node->left && !node->right) return node->data;
        return getRopeString(node->left) + getRopeString(node->right);
    }

public:
    Rope() : root(nullptr) {}

    // Insert a string at a specific index
    void insert(const std::string& str, int index) {
        auto splitNodes = split(root, index);
        auto newNode = std::make_shared<RopeNode>(str);
        root = concat(concat(splitNodes.first, newNode), splitNodes.second);
    }

    // Delete characters in the range [start, end)
    void remove(int start, int end) {
        auto split1 = split(root, start);
        auto split2 = split(split1.second, end - start);
        root = concat(split1.first, split2.second);
    }

    // Retrieve a substring in the range [start, end)
    std::string substring(int start, int end) {
        auto split1 = split(root, start);
        auto split2 = split(split1.second, end - start);
        std::string result = getRopeString(split2.first);
        root = concat(split1.first, concat(split2.first, split2.second));
        return result;
    }

    // Concatenate two ropes
    void concat(Rope& other) {
        root = concat(root, other.root);
        other.root = nullptr; // Clear the other rope
    }

    // Get the string representation of the rope
    std::string toString() {
        return getRopeString(root);
    }
};

int main() {
    Rope rope;
    rope.insert("Hello, ", 0);
    rope.insert("world!", 7);
    std::cout << rope.toString() << std::endl;

    rope.remove(5, 13);
    std::cout << rope.toString() << std::endl;

    Rope other;
    other.insert("This is another ", 0);
    other.insert("rope.", 16);
    rope.concat(other);
    std::cout << rope.toString() << std::endl;

    return 0;
}
