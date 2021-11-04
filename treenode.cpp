/*
 Filename: treenode.cpp
 Description: Contains the implementation to the treenode class
 Author: Tyler Watson
 Date: 06/1/2020
 Course: Data Structures II
*/

#include "treenode.h"
#include "object.h"

/**
 * Method & Description: This is the treenode constructor which instantiates the object
 * @param takes in a parameter Object* data which is the object data that is being stored in the treenode
 * @returns nothing
 */
TreeNode::TreeNode(Object* data) : _data(data), _leftChild(nullptr), _rightChild(nullptr){
}

/**
 * Method & Description: This is the treenode deconstructor
 * @param no parameters
 * @returns nothing
 */
TreeNode::~TreeNode() {
    _leftChild = nullptr;
    _rightChild = nullptr;
    ClearData();
}

/**
 * Method & Description: This deleted the object data stored in the tree node
 * @param takes in no parameters
 * @returns nothing
 */
void TreeNode::ClearData() {
    delete _data;
}

/**
 * Method & Description: This gets the object data
 * @param takes in no parameters
 * @returns returns the object* that is stored in the tree node
 */
Object* TreeNode::GetData(){
    return _data;
}

/**
 * Method & Description: This sets the leftchild treenode member to another treenode object
 * @param takes in a TreeNode* parameter of the leftchild
 * @returns nothing
 */
void TreeNode::SetLeftChild(TreeNode* leftChild){
    _leftChild = leftChild;
}

/**
 * Method & Description: This sets the rightchild treenode member to another treenode object
 * @param takes in a TreeNode* parameter of the rightchild
 * @returns nothing
 */
void TreeNode::SetRightChild(TreeNode* rightChild){
    _rightChild = rightChild;
}

/**
 * Method & Description: This returns the leftchild treenode member
 * @param no parameters
 * @returns returns the leftchild TreeNode* object
 */
TreeNode* TreeNode::GetLeftChild(){
    return _leftChild;
}

/**
 * Method & Description: This returns the rightchild treenode member
 * @param no parameters
 * @returns returns the rightchild TreeNode* object
 */
TreeNode* TreeNode::GetRightChild(){
    return _rightChild;
}