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

StringVariable::StringVariable() {
    //empty constructor
}

void StringVariable::IntToString(char* buffer, int input)
{
	snprintf(buffer, sizeof(buffer), "%d", input);
}

void StringVariable::BoolToString(char* buffer, bool input)
{
	if(input)
	{
		buffer[0] = '1';
	}
	else
	{
		buffer[0] = '0';
	}
	buffer[1] = '\0';
}

template <typename T>
void StringVariable::FloatAndDoubleToString(char* buffer, T& input)
{
    if(typeid(input) == typeid(double) || typeid(input) == typeid(float)){
        snprintf(buffer, sizeof(buffer), "%f", input);
    }
}
template <typename T>
void StringVariable::DataToString(char* buffer, T &input, DataType dataType)
{
    switch(dataType)
    {
        case DataType::INTEGER:
            IntToString(buffer, input);
            break;
        case DataType::BOOL:
            BoolToString(buffer, input);
            break;
        case DataType::FLOAT:
            FloatAndDoubleToString(buffer, input);
            break;
        case DataType::DOUBLE:
            FloatAndDoubleToString(buffer, input);
            break;
        case DataType::STRING:
            snprintf(buffer, sizeof(buffer), "%s", input);
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
    buffer[0] = sp::START_CHAR;
    buffer[1] = '\0';
    DataType dataType = getDataType<T>(input);
    
    strcat(buffer, sp::DATA_TYPE_STRINGS[dataType]);
    strncat(buffer, &sp::HEADER_SEPARATOR,1);
    char dataString[DATA_STRING_SIZE];
    DataToString(dataString, input, dataType);
    
    strcat(buffer, dataString);
    strncat(buffer, &sp::ESCAPE_CHAR,1);
    char checkSum = calculateCheckSum(buffer);
    strncat(buffer, &checkSum, 1);
    strncat(buffer, &END_CHAR, 1);
}

void StringVariable::SerializeString(char* buffer, char* input)
{
    buffer[0] = sp::START_CHAR;
    buffer[1] = '\0';
    strcat(buffer, sp::DATA_TYPE_STRINGS[DataType::STRING]);
    strncat(buffer, &sp::HEADER_SEPARATOR,1);
    strcat(buffer, input);
    strncat(buffer, &sp::ESCAPE_CHAR,1);
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

template void StringVariable::FloatAndDoubleToString<float>(char* buffer, float&input);
template void StringVariable::FloatAndDoubleToString<double>(char* buffer, double&input);

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
