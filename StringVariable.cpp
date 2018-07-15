/*
 * StringVariable.cpp
 *
 *  Created on: Jun 20, 2018
 *      Author: baiyuhuang
 */

#include "StringVariable.h"
#include "MessageConstants.h"
#include <cstdlib>
#include "stdio.h"
#include "string.h"
#include <typeinfo>

using namespace std;
using namespace sp;

template <typename T>
void StringVariable::DataToString(char* buffer, T &input, DataType dataType)
{
    switch(dataType)
    {
        case DataType::INTEGER:
            snprintf(buffer, sizeof(buffer), "%d", input);
            break;
        case DataType::BOOL:
            buffer[0] = input+'0';
            buffer[1] = '\0';
            break;
        case DataType::FLOAT:
        case DataType::DOUBLE:
            snprintf(buffer, sizeof(buffer), "%f", input);
            break;
        case DataType::UNSUPPORTED_TYPE:
            break;
        default:
            break;
    }
}

template <typename T>
void StringVariable::Serialize(char* buffer, T &input)
{
    buffer[0] = START_CHAR;
    buffer[1] = '\0';
    DataType dataType = getDataType<T>(input);
    
    strcat(buffer, DATA_TYPE_STRINGS[dataType]);
    strncat(buffer, &HEADER_SEPARATOR,1);
    char dataString[DATA_STRING_SIZE];
    DataToString(dataString, input, dataType);
    
    strncat(buffer, dataString, MAX_HEADER_SIZE);
    strncat(buffer, &ESCAPE_CHAR,1);
    char checkSum = calculateCheckSum(buffer);
    strncat(buffer, &checkSum, 1);
    strncat(buffer, &END_CHAR, 1);
}

void StringVariable::SerializeString(char* buffer, char* input)
{
    buffer[0] = START_CHAR;
    buffer[1] = '\0';
    strncat(buffer, DATA_TYPE_STRINGS[DataType::STRING], MAX_HEADER_SIZE);
    strncat(buffer, &HEADER_SEPARATOR,1);
    strncat(buffer, input, MAX_MESSAGE_BODY_SIZE);
    strncat(buffer, &ESCAPE_CHAR,1);
    char checkSum = calculateCheckSum(buffer);
    strncat(buffer, &checkSum, 1);
    strncat(buffer, &END_CHAR, 1);
}

char StringVariable::calculateCheckSum(char* str)
{
    char checksum = *str;
    str++;
    while(*str != '\0')
    {
        checksum ^= *str;
        str++;
    }
    return checksum;
}

template<typename T>
DataType StringVariable::getDataType(T &input)
{
    if(typeid(input) == typeid(int))
    {
        return DataType::INTEGER;
    }
    else if(typeid(input) == typeid(bool))
    {
        return DataType::BOOL;
    }
    else if(typeid(input) == typeid(float))
    {
        return DataType::FLOAT;
    }
    else if(typeid(input) == typeid(double))
    {
        return DataType::DOUBLE;
    }
    else
    {
        return DataType::UNSUPPORTED_TYPE;
    }
}


//template DataType StringVariable::getDataType<int>(int &input);
//template DataType StringVariable::getDataType<bool>(bool &input);
//template DataType StringVariable::getDataType<float>(float &input);
//template DataType StringVariable::getDataType<double>(double &input);
//template DataType StringVariable::getDataType<char*>(char* &input);
//
//template void StringVariable::DataToString<int>(char* buffer, int &input, DataType dataType);
//template void StringVariable::DataToString<bool>(char* buffer, bool &input, DataType dataType);
//template void StringVariable::DataToString<float>(char* buffer, float &input, DataType dataType);
//template void StringVariable::DataToString<double>(char* buffer, double &input, DataType dataType);
//template void StringVariable::DataToString<char*>(char* buffer, char* &input, DataType dataType);

template void StringVariable::Serialize<int>(char* buffer, int &input);
template void StringVariable::Serialize<bool>(char* buffer, bool &input);
template void StringVariable::Serialize<float>(char* buffer, float &input);
template void StringVariable::Serialize<double>(char* buffer, double &input);
