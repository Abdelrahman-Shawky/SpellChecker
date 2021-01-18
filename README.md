# Spell Checker

A C application that implements a spell checking system based on a Binary Search Tree.

# What I Learned

* Utilization of Binary Search Trees.
* Arrangement of nodes in BST.

# User Manual

* On start application loads a file containing all language words with one word per line.
* The user is prompted to enter a sentence to check its spelling.
* For each word in the entered sentence, it is checked whether the word exists in the binary search tree.
* In case it exists then "correct" is displayed.
* In case it doesn not exist "incorrect" is displayed along with three suggestions for replacement.
* Suggestions are as follows: inorder predecessor, inorder successor, leaf node before declaring it does not exist.
