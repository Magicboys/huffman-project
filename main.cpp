/*
 Filename: main.cpp
 Description: Contains the implementation main and tree building / processing methods as well as read / write.
              This file is the frame work for the program that encodes and decodes a file.
 Author: Tyler Watson
 Date: 06/1/2020
 Course: Data Structures II
*/

#include "object.h"
#include "vsarray.h"
#include "treenode.h"
#include <iostream>
#include <fstream>
#include <sstream>
using std::cout;
using std::endl;
using std::cerr;
using std::stringstream;
using std::ifstream;
using std::ofstream;
using std::noskipws;

//Method declarations
bool ReadFile(VSArray* data, string fileName);
bool ReadDecodeFile(VSArray* data, string fileName, string& encodedMessage);
TreeNode* BuildTree(TreeNode** data, size_t size);
void ClearTree(TreeNode* head);
void EncodeTreeElements(TreeNode* head, VSArray* encodingTable, string message);
void WriteToFile(string newFileName, string oldFileName, VSArray* encodingTable);

/**
 * Method & Description: Main method - handles the framework of the program
 * @param argc which is the amount of parameters passed in and argv are the arguement values
 * @returns an int which is the exit code
 */
int main(int argc, char* argv[]){
    if(argc > 3){
        string huffman = "./huffman";
        string encode = "-encode";
        string decode = "-decode";
        if(huffman.compare(argv[0]) == 0) {
            if(encode == argv[1]){
                string inputFile = argv[2];
                string outputFile = argv[3];
                //Create a read method that passes in the file and a VSArray to get the input all into the VSArray Frequency table
                VSArray* frequencyTable = new VSArray(1.5);

                bool goodRead = ReadFile(frequencyTable, inputFile);
                if(goodRead == false) {
                    cerr << "Invalid file name!" << endl;
                    delete frequencyTable;
                    return -1;
                }

                //Sorts the frequency table
                frequencyTable->SortByFrequency();
                for(int i = 0; i < frequencyTable->Size(); i++){
                    cout << frequencyTable->Get(i)->GetElement() << " " << frequencyTable->Get(i)->GetFrequency() << endl;
                }

                //Make the table of TreeNodes in an array in order since the frequency table has already been sorted
                size_t treeBuilderSize = frequencyTable->Size();
                TreeNode** treeBuilder = new TreeNode*[treeBuilderSize];
                for(size_t i = 0; i < frequencyTable->Size(); i++){
                    TreeNode* temp = new TreeNode(frequencyTable->Get(i));
                    treeBuilder[i] = temp;
                }

                //Run build tree method the head node should now be the first element in the tree
                //headNode contains the tree
                TreeNode* headNode;
                headNode = BuildTree(treeBuilder,treeBuilderSize);

                //Encoding table
                VSArray* encodingTable = new VSArray(1.5);
                //Sends encoded message to encodingTable
                string message = "";
                EncodeTreeElements(headNode,encodingTable,message);

                encodingTable->SortByFrequency();
                cout << encodingTable->EncodingToString() << endl;

                //Writes encoded message to new file
                WriteToFile(outputFile,inputFile,encodingTable);

                //Deallocates used data at the end of the program
                ClearTree(headNode);
                delete [] treeBuilder;
                delete frequencyTable;
                delete encodingTable;
                return 0;
            } else if(decode == argv[1]){
                //option for decoding
                string inputFile = argv[2];
                string outputFile = argv[3];

                //creates a frequency table and reads the file for the input
                string encodedMessage = "";
                VSArray* frequencyTable = new VSArray(1.5);
                bool fileRead = true;
                fileRead = ReadDecodeFile(frequencyTable,inputFile,encodedMessage);
                if(fileRead == false) {
                    cout << "File read failed!" << endl;
                    delete frequencyTable;
                    return 0;
                }

                //Make the table of TreeNodes in an array in order since the frequency table has already been sorted
                size_t treeBuilderSize = frequencyTable->Size();
                TreeNode** treeBuilder = new TreeNode*[treeBuilderSize];
                for(size_t i = 0; i < frequencyTable->Size(); i++){
                    TreeNode* temp = new TreeNode(frequencyTable->Get(i));
                    treeBuilder[i] = temp;
                }

                //builds the tree
                TreeNode* headNode;
                headNode = BuildTree(treeBuilder,treeBuilderSize);

                //Process time to decrypt the encoded message
                stringstream output("");
                size_t position = 0;

                //finds the value in the code
                while(position <= encodedMessage.size()-1){
                    string value = "E ";
                    TreeNode* temp = headNode;
                    while(temp->GetLeftChild() != nullptr && temp->GetRightChild() != nullptr){
                        if(encodedMessage.at(position) == '1'){
                            temp = temp->GetLeftChild();
                        } else {
                            temp = temp->GetRightChild();
                        }
                        if(temp->GetRightChild() == nullptr && temp->GetLeftChild() == nullptr){
                            value = temp->GetData()->GetElement();
                            break;
                        }
                        position++;
                    }
                    position++;
                    if(value == "CR"){
                        value = "\n";
                    }
                    if(value == "LF"){
                        value = '\r';
                    }
                    output << value;
                }
                //writes to file new message
                ofstream file(outputFile);
                if(file.good()){
                    file << output.str();
                }
                file.close();

                //deallocates used dynamically created memory segments
                ClearTree(headNode);
                delete [] treeBuilder;
                delete frequencyTable;

                return 0;
            } else {
                cout << "Incorrect option!" << endl;
                cout << "try ./huffman -encode <inputfilename> <outputfilename>" << endl;
                return -1;
            }
        }
    } else {
        cout << "Incorrect parameters entered!" << endl;
        return -1;
    }
    return -1;
}

/**
 * Method & Description: This method reads a file that contains the encoded message and the frequency table
 * @param takes in a virtual size array called data, a string for the file name and a pass by reference string for the encoded message
 * @return returns a bool for whether the file read was successful
 */
bool ReadDecodeFile(VSArray* data, string fileName, string& encodedMessage){
    ifstream file;
    file.open(fileName);
    if(file.good()){
        string input;
        while(getline(file,input)){
            if(input[0] == 'E'){
                stringstream temp(input);
                char val;
                temp >> val;
                int frequency = 0;
                string label = "";
                //frequency table file read
                if(input.at(2) == ' '){
                    label = " ";
                    temp >> frequency;
                } else {
                    temp >> label;
                    temp >> frequency;
                }
                int indexOfVal = data->IndexOf(label);
                if(indexOfVal == -1){
                    //cout << "INSERTING " << label << endl;
                    Object* localElement = new Object(label,frequency);
                    data->Insert(localElement);
                } else {
                    data->Get(indexOfVal)->IncreaseFrequency(1);
                }
            } else {
                encodedMessage = input;
            }
        }
        file.close();
        return true;
    } else {
        file.close();
        return false;
    }
}

/**
 * Method & Description: This method writes the new encoded message to a the specified output file
 * @param takes in a string newFileName and oldFileName to be able to use both files and the encoding table
 * @return returns nothing since it is void
 */
void WriteToFile(string newFileName, string oldFileName, VSArray* encodingTable){
    stringstream originalInput("");
    //reads the file and gets the string of the original
    ifstream file;
    file.open(oldFileName);

    if(file.good()){
        char word;
        while(file >> noskipws >> word){
            originalInput << word;
        }
    }
    string original =  originalInput.str();

    stringstream newMessage("");
    //Writes the frequency table to the file
    size_t encodingTableSize = encodingTable->Size();
    for(size_t i = 0; i < encodingTableSize;i++){
        newMessage << "E " << encodingTable->Get(i)->GetElement() << " " << encodingTable->Get(i)->GetFrequency() << "\n";
    }

    //builds a the encoded message.
    for(int i = 0; i < original.size(); i++){
        stringstream localCharacter("");
        if(original.at(i) == '\n'){
            localCharacter << "CR";
        } else if (original.at(i) == '\r'){
            localCharacter << "LF";
        } else {
            localCharacter << original.at(i);
        }
        int index =  encodingTable->IndexOf(localCharacter.str());
        string localEncodingMessage = encodingTable->Get(index)->GetEncoding();
        newMessage << localEncodingMessage;
    }
    file.close();
    ofstream newFile;
    newFile.open(newFileName);
    if(newFile.is_open()){
        newFile << newMessage.str();
    }
    newFile.close();
}

/**
 * Method & Description: This method works is called EncodeTreeElements and it traverses the tree and when
 * it reachs a leaf node it puts the encoded message of 1's and 0's in the object of the treenode.
 * @param Takes in a treenode* which is the head node of the huffman tree, a VSArray which contains the encoding table and
 * a string message which is where the encoded message is built as it recursively tracks through the tree
 * @return returns nothing since it is void
 */
void EncodeTreeElements(TreeNode* head, VSArray* encodingTable, string message){
    if(head->GetLeftChild() == nullptr && head->GetRightChild() == nullptr){
        string val = message;
        head->GetData()->ChangeEncoding(message);
        encodingTable->Insert(head->GetData());
        return;
    }
    if(head->GetLeftChild() != nullptr){
        string val = message + "1";
        EncodeTreeElements(head->GetLeftChild(),encodingTable,val);
    }
    if(head->GetRightChild() != nullptr){
        string val = message + "0";
        EncodeTreeElements(head->GetRightChild(),encodingTable,val);
    }
    return;
}

/**
 * Method & Description: This method builds the tree based off a sorted array that contains the data
 * @param takes in an array of treenodes that are sorted and the size of the array
 * @return it returns the head node of the huffman tree once the tree is build.
 */
TreeNode* BuildTree(TreeNode** data, size_t size){
    size_t sizeCounter = size;
    TreeNode* mergeNodeOne;
    TreeNode* mergeNodeTwo;

    while(sizeCounter > 1){
        //Take the bottom two and merge, then insert the node into the correct part of the list
        mergeNodeOne = data[sizeCounter-1];
        mergeNodeTwo = data[sizeCounter-2];
        stringstream combinedLabel("");

        //if mergeNodeOne is to the left of mergeNodeTwo gets the combined information
        if(mergeNodeOne->GetData()->GetFrequency() <= mergeNodeTwo->GetData()->GetFrequency()){
            combinedLabel << mergeNodeOne->GetData()->GetElement() << mergeNodeTwo->GetData()->GetElement();
        } else {
            combinedLabel << mergeNodeTwo->GetData()->GetElement() << mergeNodeOne->GetData()->GetElement();
        }
        int combinedFrequency = data[sizeCounter-1]->GetData()->GetFrequency() + data[sizeCounter-2]->GetData()->GetFrequency();
        //creates the combined node
        Object* combinedData = new Object(combinedLabel.str(),combinedFrequency);

        //Merged Node that now needs to be sorted back into the treeBuilder
        TreeNode* mergedVersion = new TreeNode(combinedData);
        if(mergeNodeOne->GetData()->GetFrequency() <= mergeNodeTwo->GetData()->GetFrequency()){
            mergedVersion->SetLeftChild(mergeNodeOne);
            mergedVersion->SetRightChild(mergeNodeTwo);
        } else {
            mergedVersion->SetLeftChild(mergeNodeTwo);
            mergedVersion->SetRightChild(mergeNodeOne);
        }
        size_t position = 0;

        //start at the bottom and look up the list and finds the insertion position
        for(size_t i = sizeCounter-1; i >= 0; i--){
            //if the current is larger then then the mergedVersion then the position is set before i
            if(data[i]->GetData()->GetFrequency() >= mergedVersion->GetData()->GetFrequency()){
                position = i+1;
                break;
            }
            //If the mergedVersion is larger then all elements
            if(i == 0){
                position = 0;
                break;
            }
        }

        //Sets old positions where the now merged data is to nullptr since it is now stored in mergedVersion
        data[sizeCounter-1] = nullptr;
        data[sizeCounter-2] = nullptr;
        sizeCounter--;

        //Shifts over elements so it can insert at the correct position
        if(sizeCounter > 0){
            if(position != sizeCounter-1){
                data[sizeCounter] =  data[sizeCounter-1];
                if (position > 0){
                    for(size_t i = sizeCounter; i > position; i--){
                        data[i] = data[i-1];
                    }
                    //now puts the mergedVersion of the two nodes in the correct place in the treebuilder
                    data[position] = mergedVersion;
                } else {
                    for(size_t i = sizeCounter; i > 0; i--){
                        data[i] = data[i-1];
                    }
                    data[position] = mergedVersion;
                }

            } else {
                data[position] = mergedVersion;
            }
        } else {
            data[0] = mergedVersion;
            data[1] = nullptr;
            break;
        }
    }

    //when the process is complete the treeNode at index one should be the head of the whole tree
    return data[0];
}

/**
 * Method & Description: This method reads a file character by character and builds the frequency table based off the input
 * @param takes in a variable size array called data which is the frequency table and a string fileName which is the name of the file
 * we are reading from
 * @return it returns true if the read was successful and false if it wasn't
 */
bool ReadFile(VSArray* data, string fileName){
    ifstream file;
    file.open(fileName);

    if(file.good()){
        char word;
        while(file >> noskipws >> word){
            stringstream character("");
            character << word;
            //If it is not a delimiter character then it goes through this if
            if(word != '\n' && word != '\r'){
                if(data->ContainsElement(character.str()) == false){
                    if(word == ' '){
                        Object* newElement = new Object(" ",1);
                        data->Insert(newElement);
                    } else {
                        Object* newElement = new Object(character.str(),1);
                        data->Insert(newElement);
                    }
                } else {
                    size_t index = data->IndexOf(character.str());
                    data->Get(index)->IncreaseFrequency(1);
                }
            }
            if(word == '\n'){
                if(data->ContainsElement("CR") == false){
                    Object* newElement = new Object("CR",1);
                    data->Insert(newElement);
                } else {
                    size_t index = data->IndexOf("CR");
                    data->Get(index)->IncreaseFrequency(1);
                }
            }
            if(word == '\r'){
                if(data->ContainsElement("LF") == false){
                    Object* newElement = new Object("LF",1);
                    data->Insert(newElement);
                } else {
                    size_t index = data->IndexOf("LF");
                    data->Get(index)->IncreaseFrequency(1);
                }
            }
        }
    } else {
        return false;
    }
    file.close();
    return true;
}

/**
 * Method & Description: This method deallocates all the treenodes in the tree
 * @param it takes in the head node to the huffman tree
 * @return it returns nothing since it is void
 */
void ClearTree(TreeNode* head){
    if(head == nullptr){
        head->ClearData();
        return;
    }
    if(head->GetLeftChild() != nullptr){
        ClearTree(head->GetLeftChild());
    }
    if(head->GetRightChild() != nullptr){
        ClearTree(head->GetRightChild());
    }
    delete head;
    head = nullptr;
    return;
}
