#include "anagram.h"
#include <iostream>
#include <fstream>

// worked with aryana9, sanjayb3, sureban2

/***
An AnagramDict constructor. This Constructor takes in a filepath
and then creates a binary tree out of all the words inside the 
binary tree. 

Input: 
std::string filename - the path to the file

Output:
N/A
***/
AnagramDict::AnagramDict(std::string filename) {
    filename_ = filename;
    std::string path = "dictionaries/" + filename_;
    std::ifstream file;
    file.open(path.c_str());
    /**
        Your code goes below here
    **/
    std::string word;
    while(file >> word) {
        addWord(word);
    }
    file.close();
}

/***
An AnagramDict member function. This function sorts the given word in 
lexicographical order

Input: 
std::string word - the word that needs to be sorted

Output:
std::string - the sorted version of the input
***/

std::string AnagramDict::sortWord(std::string word) {
    /**
        Your code goes below here
    **/
   std::string sorted_word = word;
    std::sort(sorted_word.begin(), sorted_word.end());
    return sorted_word;
}


/***
An AnagramDict member function. This function adds a word to the tree.
If the words sorted version already exists in the tree add it to the linked
list of that node. If the sorted word does not exist in the tree create a new
node and insert it into the tree
Duplicated words should not be added to the tree.
Input: 
std::string word - the word that needs to inserted

Output:
N/A
***/
void AnagramDict::addWord(std::string word) {
    std::string sorted_word = sortWord(word);
    Node<std::string, std::list<std::string> >* node = tree.find_node(sorted_word);

    if (node != NULL) { 
        std::list<std::string> anagrams = node->getData();
        
        for (std::list<std::string>::iterator it = anagrams.begin(); it != anagrams.end(); ++it){
            if (*it == word) {
                return;
            }
        }

        anagrams.push_back(word);
        node->setData(anagrams); 
        
    }       
    else {
        std::list<std::string> newList;
        newList.push_back(word);

        Node<std::string, std::list<std::string> >* newNode = new Node<std::string, std::list<std::string> >(sorted_word, newList);
        tree.insert_node(tree.getRoot(), newNode);
    }
}

/***
An AnagramDict member function. Does a preorder, postorder, or inorder traversal
and then prints out all the anagrams and words.

The output file should be the traversal order of the tree, but only the data on each line. 
View on wiki for more information. 

Input: 
std::string order - The type of order you want to traverse. Can be "pre", "post", "in"

Output:
N/A
***/
void AnagramDict::saveAnagrams(std::string order) {
    std::string path = "output/" + order + "_" + filename_;
    std::ofstream file;
    file.open(path.c_str());
    if(!file.is_open()) {
        file.open(path.c_str(),std::ios::out);
    }

    std::list<Node<std::string, std::list<std::string> > > nodes;

    if(order == "pre"){
        tree.pre_order(tree.getRoot(), nodes);
    } else if(order == "post"){
        tree.post_order(tree.getRoot(), nodes);
    } else if(order == "in"){
        tree.in_order(tree.getRoot(), nodes);
    }

    for (std::list<Node<std::string, std::list<std::string> > >::iterator it = nodes.begin(); it != nodes.end(); ++it){ 
        std::list<std::string> temp_list = it->getData();
        for (std::list<std::string>::iterator it2 = temp_list.begin(); it2 != temp_list.end(); ++it2){ 
            file << *it2 << " ";
        }
        file << std::endl;
    }

    return;
}
