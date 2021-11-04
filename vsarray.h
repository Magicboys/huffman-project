/*
 Filename: vsarray.h
 Description: Declaration of the vsarray object which contains a virtual size array ADT
 Author: Tyler Watson
 Date: 06/1/2020
 Course: Data Structures II
*/

#ifndef HUFFMAN_VSARRAY_H
#define HUFFMAN_VSARRAY_H

#include "object.h"
#include <string>
using std::string;

class VSArray {
    Object** _data;
    size_t _size;
    size_t _capacity;
    double _delta;

public:
    VSArray(double delta);
    ~VSArray();
    bool Insert(Object* element);
    bool SortByFrequency();
    bool SortByEncoding();
    bool Remove(size_t position);
    int IndexOf(string element);
    Object* Get(size_t position);
    string FrequencyToString();
    string EncodingToString();
    size_t Size();
    void Clear();
    bool ContainsElement(string element);
    bool IsEmpty();
    void Resize();
};


#endif //HUFFMAN_VSARRAY_H
