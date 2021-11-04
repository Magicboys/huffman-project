/*
 Filename: treenode.h
 Description: Declaration of the treenode object which contains an individual tree node
 Author: Tyler Watson
 Date: 06/1/2020
 Course: Data Structures II
*/

#ifndef HUFFMAN_TREENODE_H
#define HUFFMAN_TREENODE_H
#include "object.h"

class TreeNode {
    Object* _data;
    TreeNode* _leftChild;
    TreeNode* _rightChild;
public:
    TreeNode(Object* data);
    ~TreeNode();
    Object* GetData();
    void SetLeftChild(TreeNode* leftChild);
    void SetRightChild(TreeNode* rightChild);
    void ClearData();
    TreeNode* GetLeftChild();
    TreeNode* GetRightChild();
};


#endif //HUFFMAN_TREENODE_H
