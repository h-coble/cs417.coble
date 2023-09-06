
#pragma once

#include<string>
#include <memory>
#include <functional>
#include <cassert>
using namespace std;


class Rope
{
    // The inner struct Node represents one node of the tree.  This defines the
    // underlying structure implied by the mathematical definition of the Tree
    // ADT
    //
    struct Node
    {
        Node(std::shared_ptr<Node> const & lft, int wght, std::string str, std::shared_ptr<Node> const & rgt)
        : _lft(lft), weight(wght), _rgt(rgt), substr(str)
        {}

        std::shared_ptr<Node> _lft;
        int weight;
        std::string substr;
        std::shared_ptr<Node> _rgt;
    };

    //
    // And this private constructor defines how we keep track of the root of the
    // tree while not exposing that information to clients of this class.
    //
    explicit Rope(std::shared_ptr<Node> const & node)
      : _root(node) {}

  
public:
  
    Rope() {}

    /*
    Tree(Tree const & lft, T val, Tree const & rgt)
    : _root(std::make_shared<Node>(lft._root, val, rgt._root))
    {
        assert(lft.isEmpty() || lft.root() < val);
        assert(rgt.isEmpty() || val < rgt.root());
    }*/

    
    Rope(std::string whole) {
        Tree t;
        for (T v: init) {
            t = t.insert(v);
        }
        _root = t._root;
    }

    //
    // The next portion of the protocol allows the client to query the state
    // of the Tree.   Again, note how we avoid exposing the state to the client.
    //
    bool isEmpty() const { return !_root; }

    size_t size() { return numberOfNodes; }

    T root() const {
        assert(!isEmpty());
        return _root->_val;
    }
    std::shared_ptr<Node> rootNode()
    {
        return _root;
    }

    Tree left() const {
        assert(!isEmpty());
        return Tree(_root->_lft);
    }

    Tree right() const {
        assert(!isEmpty());
        return Tree(_root->_rgt);
    }

    //
    // Now we manipulate the tree.
    // Note insert operates... we don't try to "fix" an existing treee.
    // Rather we build a new tree, inserting the new value at the correct point.
    //
    // Note also the implicit assumption about the template class... it must
    // support the comparison operator, or mathematically, must be partially
    // ordered.
    //
    Tree insert(T x) {
      numberOfNodes++;
        if (isEmpty())
            return Tree(Tree(), x, Tree());
        T y = root();
        if (x < y)
            return Tree(left().insert(x), y, right());
        else if (y < x)
            return Tree(left(), y, right().insert(x));
        else
        {
            numberOfNodes--;
            return *this; // no duplicates
        }
    }

    bool member(T x) const {
        if (isEmpty())
            return false;
        T y = root();
        if (x < y)
            return left().member(x);
        else if (y < x)
            return right().member(x);
        else
            return true;
    }

  bool find(T x, T &foundValue) const {
        if (isEmpty())
            return false;
        T y = root();
        if (x < y)
            return left().find(x,foundValue);
        else if (y < x)
            return right().find(x,foundValue);
        else 
        {
            if (x == y)
            {
                foundValue = y;
                return true;
            }
            else
            {
                std::cerr << "Index belongs to another card's keyword.\n";
                return false;
            }
          
        }
    }

    //
    // For each of traversal functions, we assume that the parameter is a
    // function pointer, object, or lambda expression that returns void and is
    // passed an object of type T.
    //
    void preorder(std::function<void(T)> visit) const {
        if (isEmpty())
            return;
        T contents = root();
        visit(contents);
        left().preorder(visit);
        right().preorder(visit);
    }

    void inorder(std::function<void(T)> visit) const {
        if (isEmpty()) return;
        left().inorder(visit);
        T contents = root();
        visit(contents);
        right().inorder(visit);
    }

    void postorder(std::function<void(T)> visit) const {
        if (isEmpty()) return;
        left().postorder(visit);
        right().postorder(visit);
        T contents = root();
        visit(contents);
    }

    std::shared_ptr<Node>findMin(std::shared_ptr<Node> root)                
    {
        if (root != nullptr)
        {
            while (root->_lft != nullptr)   //while root isn't set to left-most leaf
            {
                root = root->_lft;          //set root = to its left child
            }
        }
        return root; //return left-most leaf
    }

    void remove( T deletionVal, std::shared_ptr<Node>& subRoot)             
    {
        if (subRoot == nullptr)
            return;
        if (deletionVal < subRoot->_val)                                                                        //CURRENT CONDITION: value is less than this node, continue down left side of tree to find it
            
            remove(deletionVal, subRoot->_lft);

        else if (subRoot->_val < deletionVal)                                                                   //CURRENT CONDITION: value is greater, continue down right side to find node with value
            remove(deletionVal, subRoot->_rgt);

        else if (subRoot->_lft != nullptr && subRoot->_rgt != nullptr)                                          //CURRENT CONDITION: subRoot has 2 children and deleteValue == subRoot value
        {
            subRoot->_val = findMin(subRoot->_rgt)->_val;   
            remove(subRoot->_val, subRoot->_rgt);

            
            /*^ HOW THIS WORKS ^
            //Restructures this (sub)tree:
            //minValue found replaces value to be deleted; 
            //essentially, this is the deletion we asked for as it no longer exists in tree.
            //
            //Then, it deletes the copied minValue from its original position.
            */
        }
        else
        {
            std::shared_ptr<Node> oldNode = subRoot;

            if (subRoot == _root) // Check if the node to be removed is the root node
            {
                if (subRoot->_lft != nullptr)
                    _root = subRoot->_lft;
                else
                    _root = subRoot->_rgt;
            }
            else
            {
                subRoot = (subRoot->_lft != nullptr) ? subRoot->_lft : subRoot->_rgt;
            }

            oldNode.reset();
        }
        
    }
private:
    std::shared_ptr<Node> _root;
    unsigned int numberOfNodes = 0;
};


