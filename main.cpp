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


using namespace std;
using namespace sp;

char calculateCheckSum(char* str);
void appendChecksumAndEndingCharacter(char* message);
void printMessage(Message msg);

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
    
    MessageParser parser = MessageParser();
    for (int i=0; i<size; i++) {
//    int i = 3;
        appendChecksumAndEndingCharacter(arr[i]);

        if(parser.parse(arr[i])) {
            Message message = parser.getParsedMessage();
            printMessage(message);
        }
        else {
            cout << "unsupported" << endl;
        }
    }
}

void printMessage(Message msg) {
    cout << "DataType: " << DATA_TYPE_STRINGS[msg.getDataType()] << endl;
    cout << "Value: ";
    switch (msg.getDataType()) {
        case INTEGER:
            cout << ((Message::UnionData) msg.getData()).INTEGER << endl;
            break;
        case DOUBLE:
            cout << ((Message::UnionData) msg.getData()).DOUBLE << endl;
            break;
        case FLOAT:
            cout << ((Message::UnionData) msg.getData()).FLOAT << endl;
            break;
        case STRING:
            cout << ((Message::UnionData) msg.getData()).CHAR_PTR << endl;
            break;
        case BOOL:
            cout << ((Message::UnionData) msg.getData()).BOOL << endl;
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
