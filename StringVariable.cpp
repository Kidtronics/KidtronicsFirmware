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

//convert int to c string
void StringVariable::IntToString(int input, char* buffer)
{
	snprintf(buffer, sizeof(buffer), "%d", input);
}

//convert boolean to c string
void StringVariable::BoolToString(bool input, char* buffer)
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



