/*
 Filename: object.h
 Description: Declaration of the class object which contains the data an element
 Author: Tyler Watson
 Date: 06/1/2020
 Course: Data Structures II
*/

#ifndef HUFFMAN_OBJECT_H
#define HUFFMAN_OBJECT_H

#include <string>
using std::string;

class Object {
    int _frequency;
    string _element;
    string _encoding;
public:
    Object(string element, int frequency);
    ~Object();
    string FrequencyMessage();
    string EncodingMessage();
    int GetFrequency();
    string GetElement();
    string GetEncoding();
    void IncreaseFrequency(int amount);
    void ChangeEncoding(string newEncoding);
};


#endif //HUFFMAN_OBJECT_H
