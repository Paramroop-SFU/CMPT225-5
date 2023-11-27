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

//
// IMPORTANT: no global variables are permitted in this file!
//
// It is okay to define helper functions defined outside the class.
//

class Wordlist : public Wordlist_base
{
    //
    // Use this Node to implement an AVL tree for the word list. You can *add*
    // extra variables/methods/features to this struct if you like, but you must
    // keep its name the same, and also keep the word, count, left, and right
    // variables as defined.
    //
    struct Node
    {
        string word;
        int count;
        Node *left;
        Node *right;
        int height;
    };

    Node *root = nullptr;
    //
    // IMPORTANT: root is the only variable that can be defined in this class.
    // It should point to the top node of your AVL tree. When root == nullptr,
    // the tree is empty.
    //
    // No variables other than root are permitted!
    //

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

    int max(int a, int b)
    {
        if (a > b)
            return a;
        else
            return b;
    }

    Node *right_rotate(Node *&current)
    {
        Node *temp1 = current->left;
        Node *Temp2 = temp1->right;

        temp1->right = current;
        current->left = Temp2;

        // Update heights
        current->height = max(get_height(current->left), get_height(current->right)) + 1;
        temp1->height = max(get_height(temp1->left), get_height(temp1->right)) + 1;

        // Return new root
        return temp1;
    }

    Node *left_rotate(Node *current)
    {
        Node *temp = current->right;
        Node *temp2 = temp->left;

        // Perform rotation
        temp->left = current;
        current->right = temp2;

        // Update heights
        current->height = max(get_height(current->left),get_height(current->right)) + 1;
        temp->height = max(get_height(temp->left), get_height(temp->right)) +  1;
                       
                  

        // Return new root
        return temp;
    }

    Node* add_word_helper(Node *current, const string &w) // main body for the add function
    {
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

        int balance = get_balance(current);


        if (balance > 1 && w < current->left->word)
        return right_rotate(current);

        if (balance < -1 && w > current->right->word)
            return left_rotate(current);

        if (balance > 1 && w > current->left->word)
        {
        current->left = left_rotate(current->left);
        return right_rotate(current);
        }

        if (balance < -1 && w < current->right->word)
        {
            current->right = right_rotate(current->right);
            return left_rotate(current);
        }
        return current;
    }

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

    int total_word_helper(const Node *current) const
    {
        if (current == nullptr)
        {
            return 0;
        }
        //cout << current->count << " ";
        return current->count + total_word_helper(current->right) + total_word_helper(current->left);
    }

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
    //
    // Returns the number of times w occurs as a word in the word list.
    //
    int get_count(const string &w) const
    {

        return get_count_helper(root, w);
    }
    //
    // Returns true if w is in the word list, false otherwise.
    //
    bool contains(const string &w) const
    {
        return get_count(w) > 0;
    }
    //
    // Returns the number of nodes in the word list.
    //
    int num_different_words() const
    {
        return total_diffword_helper(root);
    }

    //
    // Returns the total number of words in the word list, i.e. the sum of the
    // word counts.
    //
    int total_words() const
    {
        return total_word_helper(root);
    }
    //
    // Returns true if the words in the word list are in ascending sorted order,
    // false otherwise.
    //
    // For an AVL implementation, this should return true if the AVL tree is a
    // BST, and false otherwise.
    //
    bool is_sorted() const // need two helpers
    {
        if (root == nullptr)
            return true;
        string small = root->word;
        string smallest = find_smallest(root, small);

        return sorted_helper(root, smallest);
    }
    //
    // Returns a string of the most frequent word in the format "word freq".
    // E.g. if the most frequent word is "the" with count 5437, then "the 5437"
    // is returned.
    //
    // If there is a tie, the first word in the list is returned. For an AVL
    // implementation, this means return the word that occurs first
    // alphabetically.
    //
    // Assumes the list is not empty.
    //
    string most_frequent() const
    {

        string large = root->word;
        int count = root->count;
        int foundbig = count_Largest(root, count);
        string num = to_string(foundbig);
        string most =frequent_helper(root, foundbig, large);
        return most + " " + num;
    }
    //
    // Returns the number of nodes with count 1.
    //
    int num_singletons() const
    {
        return singleton_helper(root);
    }
    //
    // Adds w to the word list. If w is already in the word list, then increment
    // its count. Otherwise add a new Node (with count 1) at the alphabetically
    // correct location for the word.
    //
    // Cite: https://www.geeksforgeeks.org/insertion-in-an-avl-tree/
    void add_word(const string &w)
    {
        root = add_word_helper(root, w);

    }
    //
    // Prints the words in the word list in alphabetical order by word, along
    // with their counts. The first word is 1, the second 2, and so on, e.g.:
    //
    //   ❯ ./a5_main < small.txt
    //   1. {"This", 1}
    //   2. {"a", 2}
    //   3. {"is", 2}
    //   4. {"or", 1}
    //   5. {"test", 1}
    //   6. {"test?", 1}
    //   7. {"this", 1}
    //
    void print_words() const
    {
        if (root == nullptr)
        {
            printf("L");
        }
        int count = 0;
        print_helper(root,count);
    }

    int getroot()
    {
        return root->count;
    }

}; // class Wordlist

//
// Make sure to thoroughly test your code as you go!
//
