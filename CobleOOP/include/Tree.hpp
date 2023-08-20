//
// File:    Tree.h
// Author:  Adam.Lewis@athens.edu
// Purpose:
// Use C++ templates, STL classes and functions, and smart pointers to
// implement a binary search tree.
//
// A binary search tree is defined as being either empty, or a 3-tuple
// (left.subtree, value, right.subtree) where left.subtree is a binary search
// tree that only contains values less than our value and right.subtree is a
// binary search tree that only contains values larger than our value.
//
#pragma once

#include <memory>
#include <functional>
#include <cassert>
using namespace std;

template<class T>
class Tree
{
    // The inner struct Node represents one node of the tree.  This defines the
    // underlying structure implied by the mathematical definition of the Tree
    // ADT
    //
    struct Node
    {
        Node(std::shared_ptr<Node> const & lft
             , T val
             , std::shared_ptr<Node> const & rgt)
        : _lft(lft), _val(val), _rgt(rgt)
        {}

        std::shared_ptr<Node> _lft;
        T _val;
        std::shared_ptr<Node> _rgt;
    };

    //
    // And this private constructor defines how we keep track of the root of the
    // tree while not exposing that information to clients of this class.
    //
    explicit Tree(std::shared_ptr<Node> const & node)
      : _root(node) {}

  unsigned int numberOfNodes = 0;
public:
    //
    // The first two public constructors provide the protocol for creating a
    // Tree per the mathematical definition of the Tree ADT.
    //
    Tree() {}

    Tree(Tree const & lft, T val, Tree const & rgt)
    : _root(std::make_shared<Node>(lft._root, val, rgt._root))
    {
        assert(lft.isEmpty() || lft.root() < val);
        assert(rgt.isEmpty() || val < rgt.root());
    }

    //
    // We add an additional constructor that we use to construct a Tree from
    // an initializer list.
    //
    Tree(std::initializer_list<T> init) {
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
            return *this; // no duplicates
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
            return left().find(x);
        else if (y < x)
            return right().find(x);
        else {
          foundValue = y;
          return true;
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

    void remove(const T deletionVal, std::shared_ptr<Node>& subRoot)             
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

        else                                                                                                    //CURRENT CONDITION: subRoot is leaf or has only 1 child AND val == deleteValue
        {
            std::shared_ptr<Node> oldNode = subRoot;
            subRoot = (subRoot->_lft != nullptr) ? subRoot->_lft : subRoot->_rgt;  
            oldNode.reset();

            /*^ HOW THIS WORKS ^
            // 
            //subRoot passed by reference, so it now points to its only child or is nullptr:
            // 
            //if _lft child exists, point to left child; moves L child to subroot's place in tree
            //else, point subroot to right child (which may also be nullptr); moves R child to subroot's place in tree
            // 
            //Subsequently, if it exists, the child's subtree (which it is the root of) is moved up a tier in tree 
            // 
            //if subRoot was a leaf, this doesn't matter; it is nullified and the shared pointer is deleted*/
        }
    }
private:
    std::shared_ptr<Node> _root;
};


