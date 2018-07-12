//============================================================================
// Name        : SerialProtocol.cpp
// Author      : baixiao
// Version     :
// Copyright   : Proprietary software
// Description : Serial protocol
//============================================================================

#include <iostream>
#include <string>
#include "MessageConstants.h"
#include "MessageParser.h"
#include "Message.h"
#include "StringVariable.h"

using namespace std;
using namespace sp;

char calculateCheckSum(char* str);
void appendChecksumAndEndingCharacter(char* message);
void printMessage(Message msg);
void variableToStringTest();

int main() {
	char intMsg[30] = "<INT\r2934\\";
    char floatMsg[30] = "<FLOAT\r34.284\\";
    char doubleMsg[30] = "<DOUBLE\r76.84937283\\";
    char strMsg[30] = "<STR\rThis is a test\\";
    char boolMsg[30] = "<BOOL\r1\\";
    char unsupported[30] = "<\r100\\";
    char unsupported2[30] = "<\\";
    char unsupported3[30] = "<ARR\r132\\";
    
    const int size = 8;
    char* arr[size] = {intMsg, floatMsg, doubleMsg, strMsg, boolMsg, unsupported, unsupported2, unsupported3};
    
    for (int i=0; i<size; i++) {
        appendChecksumAndEndingCharacter(arr[i]);
    }
    
    MessageParser parser = MessageParser();
    
    for (int j=0; j<100; j++) {
    for (int i=0; i<size; i++) {
        if(parser.parse(arr[i])) {
            Message message = parser.getParsedMessage();
            printMessage(message);
        }
        else {
            cout << "unsupported" << endl;
        }
    }
      
    variableToStringTest();
}

void printMessage(Message msg) {
    cout << "DataType: " << DATA_TYPE_STRINGS[msg.getDataType()] << endl;
    cout << "Value: ";
    switch (msg.getDataType()) {
        case INTEGER:
            cout << msg.getIntData()<< endl;
            break;
        case DOUBLE:
            cout << msg.getDoubleData() << endl;
            break;
        case FLOAT:
            cout << msg.getFloatData() << endl;
            break;
        case STRING:
            cout << msg.getStringData() << endl;
            break;
        case BOOL:
            cout << msg.getBoolData() << endl;
            break;
        default:
            break;
    }
}

void appendChecksumAndEndingCharacter(char* message) {
	char checksum = calculateCheckSum(message);
    checksum ^= END_CHAR;
	char* ptr = message + strlen(message);
	*ptr = checksum;
	ptr++;
	*ptr = END_CHAR;
	ptr++;
	*ptr = '\0';
}

char calculateCheckSum(char* str) {
	char checksum = *str;
	str++;
	while(*str != '\0') {
		checksum ^= *str;
		str++;
	}
	return checksum;
}

void variableToStringTest()
{
    StringVariable strVar;
    int input = 1234567890;
    float floatInput = 1.23324f;
    double doubleInput = 1.23234f;
    bool boolInput = false;
    char strInput[15];
    snprintf(strInput, sizeof(strInput),"hello world");
    char* intBuffer = (char*) malloc(30);
    char* boolBuffer = (char*) malloc(30);
    char* floatBuffer = (char*) malloc(30);
    char* doubleBuffer = (char*) malloc(30);
    char* stringBuffer = (char*) malloc(30);
    strVar.Serialize(intBuffer,input);
    strVar.Serialize(boolBuffer,boolInput);
    strVar.Serialize(floatBuffer,floatInput);
    strVar.Serialize(doubleBuffer,doubleInput);
    strVar.SerializeString(stringBuffer, strInput);
    
    printf("%s\n", intBuffer);
    printf("%s\n", boolBuffer);
    printf("%s\n", floatBuffer);
    printf("%s\n", doubleBuffer);
    printf("%s\n", stringBuffer);
    free(intBuffer);
    free(boolBuffer);
    free(floatBuffer);
    free(doubleBuffer);
    free(stringBuffer);
}
