// Wordlist.h

#pragma once

/////////////////////////////////////////////////////////////////////////
//
// Student Info
// ------------
//
// Name : <Paramroop Parmar>
// St.# : <301555338>
// Email: <psp10@sfu.ca>
//
//
// Statement of Originality
// ------------------------
//
// All the code and comments below are my own original work. For any non-
// original work, I have provided citations in the comments with enough
// detail so that someone can see the exact source and extent of the
// borrowed work.
//
// In addition, I have not shared this work with anyone else, and I have
// not seen solutions from other students, tutors, websites, books,
// etc.
//
/////////////////////////////////////////////////////////////////////////

//
// Do not use any other #includes
//
#include "Wordlist_base.h"
#include <cassert>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;



class Wordlist : public Wordlist_base 
{
     // struct that contains the characteristic of the AVL Tree
    struct Node
    {
        string word;
        int count;
        Node *left;
        Node *right;
        int height;
    };

    Node *root = nullptr; // poniter to the root of the tree
   

    int get_height(Node *current) // returns height
    {
        if (current == nullptr)
            return 0;

        return current->height;
    }

    int get_balance(Node *current) // gets the balance
    {
        if (current == nullptr)
        {
            return 0;
        }
        else
            return get_height(current->left) - get_height(current->right);
    }

    int max(int a, int b) // returns the higest number between the two ints
    {
        if (a > b)
            return a;
        else
            return b;
    }

    // Helper function for add word: switches then returns the node to the nearest counterclock-wise node
    Node *right_rotate(Node *&current) 
    {
        Node *temp1 = current->left;
        Node *Temp2 = temp1->right;

        // rotates the node
        temp1->right = current;
        current->left = Temp2;

        // updates the heights of the nodes after the rotate
        current->height = max(get_height(current->left), get_height(current->right)) + 1;
        temp1->height = max(get_height(temp1->left), get_height(temp1->right)) + 1;

        // Return new root
        return temp1;
    }
    // Helper function for add word: switches then returns the node to the nearest clock-wise node
    Node *left_rotate(Node *current)
    {
        Node *temp = current->right;
        Node *temp2 = temp->left;

        // rotates the node
        temp->left = current;
        current->right = temp2;

        // updates the heights of the nodes after the rotate
        current->height = max(get_height(current->left),get_height(current->right)) + 1;
        temp->height = max(get_height(temp->left), get_height(temp->right)) +  1;
                       
                  

        // Return new root
        return temp;
    }

    //helper function to add word
    Node* add_word_helper(Node *current, const string &w) 
    {
        //add the word
        if (current == nullptr)
        {
            return  new Node{w, 1, nullptr, nullptr, 1};
        }
        else if (w == current->word)
        {

            current->count++;
        }
        else if (w < current->word)
        {

            current->left = add_word_helper(current->left, w);
        }
        else 
        {
            current->right = add_word_helper(current->right, w);
        }

        current->height = 1 + max(get_height(current->left),get_height(current->right));     

        // retrun the balance of the node
        int balance = get_balance(current);

        //case 1: if balance > 1 and word is greater than w
        if (balance > 1 && w < current->left->word)
        return right_rotate(current);

        //Case 2: if balance < -1 and word less than w
        if (balance < -1 && w > current->right->word)
            return left_rotate(current);

        //Case 3: if balance > 1 and word less then w
        if (balance > 1 && w > current->left->word)
        {
        current->left = left_rotate(current->left);
        return right_rotate(current);
        }

        //Case 4: if balance < -1 and w less than word
        if (balance < -1 && w < current->right->word)
        {
            current->right = right_rotate(current->right);
            return left_rotate(current);
        }
        return current;
    }

    // helper function for printing all the nodes in inorder
    void print_helper(Node *current,int &count) const
    {
        if (current == nullptr)
        {

            return;
        }
        print_helper(current->left,count);
        count++;
        cout <<count <<". {\"" << current->word << "\", " << current->count << "}" << endl;
        print_helper(current->right,count);
    }

    // helper function that returns the count of the word
    int get_count_helper(Node *current, const string &w) const
    {
        if (current == nullptr)
        {
            return 0;
        }
        else if (w == current->word)
        {
            return current->count;
        }
        else if (w < current->word)
        {
            return 0 + get_count_helper(current->left, w);
        }
        else
        {
            return 0 + get_count_helper(current->right, w);
        }
        return 0;
    }

    //helper function that returns the total number of different words
    int total_diffword_helper(const Node *current) const
    {
        if (current == nullptr)
        {
            return 0;
        }

        int right = total_diffword_helper(current->right);
        int left = total_diffword_helper(current->left);
        return 1 + right + left;
    }

    // helper function that returns the total number of words entered to the dictionary
    int total_word_helper(const Node *current) const
    {
        if (current == nullptr)
        {
            return 0;
        }
        //cout << current->count << " ";
        return current->count + total_word_helper(current->right) + total_word_helper(current->left);
    }

    // helper function that returns the string with the first node with the highest count
    string frequent_helper(const Node *current, const int num, string &word) const
    {
        if (current == nullptr)
        {
        }
        else if (current->count == num)
        {
            word = current->word;
            return current->word;
        }
        else
        {
            frequent_helper(current->left, num, word);
            frequent_helper(current->right, num, word);
        }
        return word;
    }

    // helper function that returns the highest count from the nodes
    int count_Largest(const Node *current, int &larger) const
    {
        if (current == nullptr)
        {
        }
        else
        {

            if (larger < current->count)
            {
                larger = current->count;
            }
            count_Largest(current->left, larger);
            count_Largest(current->right, larger);
        }
        return larger;
    }

    // helper function that returns the number of nodes with count 1
    int singleton_helper(const Node *current) const
    {
        if (current == nullptr)
        {
            return 0;
        }
        else if (current->count == 1)
        {
            return 1 + singleton_helper(current->left) + singleton_helper(current->right);
        }
        else
        {
            return 0 + singleton_helper(current->left) + singleton_helper(current->right);
        }
    }

    // helper function that checks if the tree is sorted
    int sorted_helper(const Node *current, string &previous) const
    {
        if (current == nullptr)
        {
            return 0;
        }
        sorted_helper(current->left, previous);
        if (!(previous <= current->word))
        {
            return 1;
        }
        else
            previous = current->word;

        return 0 + sorted_helper(current->right, previous);
    }

    // helper function that returns the smallest string
    string find_smallest(const Node *current, string &smallest) const
    {
        if (current == nullptr)
        {
        }
        else
        {
            if (current->word < smallest)
                smallest = current->word;
            find_smallest(current->left, smallest);
        }
        return smallest;
    }

    // helper function that deallocates the tree
    void free_mem(Node* current)
    {
        if (current == nullptr)
        {
            return;
        }
        free_mem(current->left);
        free_mem(current->right);
        delete current;
        current = nullptr;
    }

public:
    Wordlist() // constuctor
    {
        root = nullptr;
    }

    ~Wordlist() //deconstuctor 
    {
        free_mem(root);
    }
  
    //returns the count of the word
    int get_count(const string &w) const
    {

        return get_count_helper(root, w);
    }
   
   // returns true if word found
    bool contains(const string &w) const
    {
        return get_count(w) > 0;
    }
    
    // returns number of different words
    int num_different_words() const
    {
        return total_diffword_helper(root);
    }

   // returns the sum of count from every node
    int total_words() const
    {
        return total_word_helper(root);
    }
  
    // return true if tree sorted
    bool is_sorted() const // need two helpers
    {
        if (root == nullptr)
            return true;
        string small = root->word;
        string smallest = find_smallest(root, small);

        return !sorted_helper(root, smallest);
    }
  
    // find's the word with highest count
    string most_frequent() const
    {

        string large = root->word;
        int count = root->count;
        int foundbig = count_Largest(root, count);
        string num = to_string(foundbig);
        string most =frequent_helper(root, foundbig, large);
        return most + " " + num;
    }
    
    // Returns the number of nodes with count 1.
    int num_singletons() const
    {
        return singleton_helper(root);
    }
 
    //Adds the word according to the rules of a AVL tree
    // Cite: https://www.geeksforgeeks.org/insertion-in-an-avl-tree/
    void add_word(const string &w)
    {
        root = add_word_helper(root, w);

    }

    // Prints the words in the word list in alphabetical order by word, along
    void print_words() const
    {
        if (root == nullptr)
        {
            printf("L");
        }
        int count = 0;
        print_helper(root,count);
    }


}; // class Wordlist


