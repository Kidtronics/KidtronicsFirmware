/*
 * StringVariable.h
 *
 *  Created on: Jun 20, 2018
 *      Author: baiyuhuang
 */

#ifndef STRINGVARIABLE_H_
#define STRINGVARIABLE_H_
#include "StringVariable.h"
#include "MessageConstants.h"
#include <cstdlib>
#include "stdio.h"
#include "string.h"
#include <typeinfo>

const int DATA_STRING_SIZE = 11;

class StringVariable {
public:
	StringVariable();
    template <typename T>
    void Serialize(T &input, char* buffer);
    
    void IntToString(int input, char* buffer);
    void BoolToString(bool input, char* buffer);
    template<typename T>
    void FloatAndDoubleToString(T& input, char* buffer);
private:
    
};

//serialize float or double to string
template <typename T>
void StringVariable::FloatAndDoubleToString(T& input, char* buffer)
{
    if(typeid(input) == typeid(double) || typeid(input) == typeid(float)){
        snprintf(buffer, sizeof(buffer), "%f", input);
    }
}

//input a variable and it will serialize it
template <typename T>
void StringVariable::Serialize(T &input, char* buffer)
{
    *buffer = '\0';
    strncat(buffer, &sp::START_CHAR,1);
    char dataString[DATA_STRING_SIZE];
    if(typeid(input) == typeid(int))
    {
        strcat(buffer, sp::DATA_TYPE_STRINGS[sp::DataType::INTEGER]);
        strncat(buffer, &sp::HEADER_SEPARATOR,1);
        IntToString(input, dataString);
    }
    else if(typeid(input) == typeid(bool))
    {
        strcat(buffer, sp::DATA_TYPE_STRINGS[sp::DataType::BOOL]);
        strncat(buffer, &sp::HEADER_SEPARATOR,1);
        BoolToString(input, dataString);
    }
    else if(typeid(input) == typeid(double))
    {
        strcat(buffer, sp::DATA_TYPE_STRINGS[sp::DataType::DOUBLE]);
        strncat(buffer, &sp::HEADER_SEPARATOR,1);
        FloatAndDoubleToString(input, dataString);
    }
    else if(typeid(input) == typeid(float))
    {
        strcat(buffer, sp::DATA_TYPE_STRINGS[sp::DataType::FLOAT]);
        strncat(buffer, &sp::HEADER_SEPARATOR,1);
        FloatAndDoubleToString(input, dataString);
    }
    
    strcat(buffer, dataString);
    strncat(buffer, &sp::ESCAPE_CHAR,1);
}

#endif /* STRINGVARIABLE_H_ */
