/*
 Filename: object.cpp
 Description: Contains the implementation to the object class
 Author: Tyler Watson
 Date: 06/1/2020
 Course: Data Structures II
*/

#include "object.h"
#include <string>
#include <sstream>

using std::stringstream;

/**
 * Method & Description: This is the object class constructor
 * @param takes in a parameter of string element which is the label and int frequency which is the frequency of the label
 * @returns nothing
 */
Object::Object(string element, int frequency) : _element(element), _frequency(frequency), _encoding("NULL"){
}

/**
 * Method & Description: This is the object deconstructor
 * @param no parameters
 * @returns nothing
 */
Object::~Object(){
    _element = "NULL";
    _frequency = -1;
    _encoding = "NULL";
}

/**
 * Method & Description: This method returns a string in JSON format of the frequency tostring message of the object
 * @param no parameters
 * @returns returns a string of the JSON representation of the objects label and frequency
 */
string Object::FrequencyMessage(){
    stringstream result("");
    if(_element == "LF" || _element == "CR"){
        result << "{key: " << _element << ", frequency: " << _frequency << "}";
    } else {
        result << "{key:  " << _element << ", frequency: " << _frequency << "}";
    }
    return result.str();
}

/**
 * Method & Description: This method returns a string in JSON format of the encoding tostring message of the object
 * @param no parameters
 * @returns returns a string of the JSON representation of the objects label and encoding message
 */
string Object::EncodingMessage(){
    stringstream result("");
    if(_element == "LF" || _element == "CR"){
        result << "{key: " << _element << ", code: " << _encoding << "}";
    } else {
        result << "{key:  " << _element << ", code: " << _encoding << "}";
    }
    return result.str();
}

/**
 * Method & Description: This method gets the frequency of the object
 * @param no parameters
 * @returns an int frequency of the object frequency
 */
int Object::GetFrequency(){
    return _frequency;
}

/**
 * Method & Description: This method gets the label of the object
 * @param no parameters
 * @returns a string representation of the label
 */
string Object::GetElement(){
    return _element;
}

/**
 * Method & Description: This method gets the encoding message of the object
 * @param no parameters
 * @returns a string representation of the encoding message
 */
string Object::GetEncoding(){
    return _encoding;
}

/**
 * Method & Description: This method increases the frequency of the object
 * @param int amount which is the amount being added to the frequency
 * @returns nothing
 */
void Object::IncreaseFrequency(int amount){
    _frequency +=  amount;
}

/**
 * Method & Description: This method changes the encoding message of the object
 * @param takes in a parameter of the newEncoding message
 * @returns nothing
 */
void Object::ChangeEncoding(string newEncoding){
    _encoding = newEncoding;
}

