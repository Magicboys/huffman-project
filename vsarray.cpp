/*
 Filename: vsarray.cpp
 Description: Contains the implementation to the vsarray class
 Author: Tyler Watson
 Date: 06/1/2020
 Course: Data Structures II
*/

#include "vsarray.h"
#include <sstream>
#include <iostream>
#include <string>
using std::stringstream;
using std::iostream;

/**
 * Method & Description: This is the variable size array constructor which takes in a delta which is the % it increases
 * the array when it resizes.
 * @param takes in a double parameter delta which is the percent the array is resized when needed
 * @return it returns nothing since it is a constructor
 */
VSArray::VSArray(double delta) : _size(0), _capacity(5), _delta(delta){
    _data = new Object*[_capacity];
    for(size_t i = 0; i < _capacity; i++){
        _data[i] = nullptr;
    }
}

/**
 * Method & Description: This is a deconstructor which deletes the array, but leaves the objects in the array to be deallocated by the client
 * @param no parameter
 * @return returns nothing
 */
VSArray::~VSArray(){
    delete [] _data;
}

/**
 * Method & Description: This method inserts an element at the end of the array
 * @param it takes in an Object* element which is what is being inserted into the array
 * @return it returns a bool which is true if the insertion was successful and false if it wasn't
 */
bool VSArray::Insert(Object* element){
    if(_size == _capacity){
        Resize();
    }
    _data[_size] = element;
    _size++;
    return true;
}

/**
 * Method & Description: This sorts the variable size array by highest frequency to lowest and then by ascii code for each frequency level
 * @param takes in no parameters
 * @return a bool which is true if the sort was successful and false if it was not
 */
bool VSArray::SortByFrequency(){
    if(_size == 0){
        return false;
    }
    //Sorts by frequency
    for(size_t i = 0; i < _size-1; i++){
        Object* objectHere =  _data[i];
        int max =  objectHere->GetFrequency();
        size_t position = i;
        //finds max in unsorted part of the list
        for(size_t j = i+1; j < _size; j++){
            if(max < _data[j]->GetFrequency()){
                max = _data[j]->GetFrequency();
                position = j;
            }
        }
        //swaps the elements if there is a higher frequency element to the right of position
        if(position != -1){
            Object* temp = _data[position];
            _data[position] = _data[i];
            _data[i] = temp;
        }
    }

    //Now sorts by ascii for each frequency level
    for(size_t i = 0; i < _size; i++){
        //if frequency is the same between at least two numbers

        if(_data[i]->GetFrequency() == _data[i+1]->GetFrequency()){
            //find range of same frequency numbers
            int localFrequency = _data[i]->GetFrequency();
            size_t endBound = i;
            while(endBound < _size){
                if(_data[endBound]->GetFrequency() == localFrequency){
                    endBound++;
                } else {
                    break;
                }
            }
            //Now sort by ascii character
            if((endBound-i) > 1){
                for(size_t z = i; z < endBound-1; z++){
                    for(size_t j = i; j < endBound-1; j++){
                        Object* temp = _data[j];
                        string firstVal = _data[j]->GetElement();
                        string secondVal = _data[j+1]->GetElement();

                        //checks if there is a special character in preparation for the character comparison
                        if(_data[j+1]->GetElement() == "CR" || _data[j]->GetElement() == "CR"){
                            if(_data[j]->GetElement() == "CR"){
                                firstVal = "\n";
                            } else {
                                secondVal = "\n";
                            }
                        }
                        if(_data[j+1]->GetElement() == "LF" || _data[j]->GetElement() == "LF"){
                            if(_data[j]->GetElement() == "LF"){
                                firstVal = "\r";
                            } else {
                                secondVal = "\r";
                            }
                        }

                        if(firstVal.compare(secondVal) < 0){
                            _data[j] = _data[j+1];
                            _data[j+1] = temp;
                        }
                    }
                }
            }
            i = endBound-1;
        }
    }
    return true;
}

/**
 * Method & Description: This sorts the elements in the vsarray by its encoded message from shortest to longest
 * @param no parameters
 * @returns true if successful and false if it was not
 */
bool VSArray::SortByEncoding(){
    SortByFrequency();
}

/**
 * Method & Description: This method removed an element from the variable size array
 * @param takes in a size_t position which is the position of the element being removed
 * @returns true if it was successful and false if it was not
 */
bool VSArray::Remove(size_t position){
    if(position >= _size){
        return false;
    }
    Object* deleteMe =  Get(position);
    delete deleteMe;
    _data[position] = nullptr;
    for(size_t i = position; i < _size-1; i++){
        _data[i] = _data[i+1];
    }
    _size--;
    return true;
}

/**
 * Method & Description: This is a get function which returns the element at a certain position
 * @param takes in the position of the element in the array
 * @returns the element is the position is valid. If the position is not valid it returns nullptr.
 */
Object* VSArray::Get(size_t position){
    if(position > _size){
        return nullptr;
    }
    return _data[position];
}

/**
 * Method & Description: This method returns the size of the variable size array
 * @param no parameters
 * @return returns the size as a size_t type
 */
size_t VSArray::Size(){
    return _size;
}

/**
 * Method & Description: This clears the array and deallocates all the elements within the array
 * @param no parameters
 * @returns nothing
 */
void VSArray::Clear(){
    for(int i = 0; i < _size; i++){
        if(_data[i] != nullptr){
            delete _data[i];
            _data[i] = nullptr;
        }
    }
    _size = 0;
}

/**
 * Method & Description: This method checks is an element exists in the array
 * @param takes in a string element which is compared againist all the elements in the array
 * @returns true if the element exists and false if it doesn't
 */
bool VSArray::ContainsElement(string element){
    for(size_t i = 0; i < _size; i++){
        Object* temp = _data[i];
        if(temp->GetElement() == element){
            return true;
        }
    }
    return false;
}

/**
 * Method & Description: This method is an IndexOf method which returns the position of the element
 * @param it has a parameter string element which is the element of the index we are looking for
 * @returns an int with the position, if the position is not found it returns -1
 */
int VSArray::IndexOf(string element){
    for(size_t i = 0; i < _size; i++){
        Object* temp = _data[i];
        if(temp->GetElement() == element){
            return static_cast<int>(i);
        }
    }
    return -1;
}

/**
 * Method & Description: This an IsEmpty method which says if the method contains ellements
 * @param no parameters
 * @returns true if the size > 0 and false if size == 0
 */
bool VSArray::IsEmpty(){
    return _size == 0;
}

/**
 * Method & Description: This a resize method which enlargens the array if the capacity needs to be expanded
 * @param it takes in no parameters
 * @returns nothing
 */
void VSArray::Resize(){
    size_t newCapacity =  _capacity*_delta;
    Object** newArray = new Object*[newCapacity];
    //assigns over elements of the old array to the new one
    for(size_t i = 0; i < _capacity; i++){
        newArray[i] =  _data[i];
    }
    for(size_t j = _capacity; j < newCapacity; j++){
        newArray[j] = nullptr;
    }

    delete [] _data;
    _data = newArray;
    _capacity = newCapacity;
}

/**
 * Method & Description: This creates a string in JSON format for each element in the table with the frequency.
 * @param takes in no parameters
 * @returns a string which contains the JSON representation of the table
 */
string VSArray::FrequencyToString(){
    stringstream returnVal("");
    if(_size > 0){
        for(size_t i = 0; i < _size-1; i++){
            Object* temp = _data[i];
            returnVal << temp->FrequencyMessage() << std::endl;
        }
        Object* temp = Get(_size-1);
        returnVal << temp->FrequencyMessage();
    }
    return returnVal.str();
}

/**
 * Method & Description: This creates a string in JSON format for each element in the table with the encoding message.
 * @param takes in no parameters
 * @returns a string which contains the JSON representation of the table
 */
string VSArray::EncodingToString(){
    stringstream returnVal("");
    if(_size > 0){
        for(size_t i = 0; i < _size-1; i++){
            Object* temp = _data[i];
            returnVal << temp->EncodingMessage() << std::endl;
        }
        Object* temp = Get(_size-1);
        returnVal << temp->EncodingMessage();
    }
    return returnVal.str();
}