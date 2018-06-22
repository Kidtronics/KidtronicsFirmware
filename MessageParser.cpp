/*
 * MessageParser.cpp
 *
 *  Created on: Jun 20, 2018
 *      Author: baixiao
 */

#include "MessageParser.h"
#include "MessageConstants.h"
#include "Message.h"
#include "stdlib.h"
#include "string.h"

using namespace sp;
using namespace std;

const unsigned int CHECKSUM_END_CHAR_SIZE = 3;

MessageParser::MessageParser() {
	m_message = nullptr;
	m_parsedMessage = Message();
}

bool MessageParser::parse(char* message) {
	m_message = message;

	if (isCorrupted()) {
		return false;
	}
	int headerEndIdx = getHeaderEndIdx();
	if (headerEndIdx == -1) {
		return false;
	}

	DataType dataType = getDataTypeFromHeader(this->m_message + headerEndIdx);
	if (dataType == UNSUPPORTED_TYPE) {
		return false;
	}

	void* parsedData = getParsedDataFromMessageBody(m_message + headerEndIdx + 1, dataType);
	if (parsedData == nullptr) {
		return false;
	}
	m_parsedMessage = Message(parsedData, dataType);
	return true;
}

Message MessageParser::getParsedMessage() {
	return m_parsedMessage;
}

bool MessageParser::isCorrupted() {
	char* ptr = m_message;
	char checksum = *ptr;
	ptr++;
	while (*ptr != '\0') {
		checksum ^= *ptr;
		ptr++;
	}
	return *ptr != 0x00;
}


////////////////Private Functions/////////////////

/**
 * returns: return the index to the end of message header, pointing at HEADER_SEPARATOR.
 * If HEADER_SEPARATOR cannot be found, return -1.
 */
int MessageParser::getHeaderEndIdx() {
	char* ptr = m_message;
	int i = 0;
	while (ptr[i] != '\0') {
		if (ptr[i] == HEADER_SEPARATOR) {
			if (i > 0 && ptr[i - 1] == ESCAPE_CHAR) {
				continue;
			}
			break;
		}
		i++;
	}
	return ptr[i] == '\0' ? -1 : i;
}

/**
 * headerEndPtr: pointer to the end of header.
 * returns: return DataType that header specify,
 * return UNSUPPORTED_TYPE when DataType is not supported.
 */
DataType MessageParser::getDataTypeFromHeader(char* headerEndPtr) {
	const char* ptr;
	if (*m_message == START_CHAR) {
		ptr = m_message + 1;
	}
	else {
		ptr = m_message;
	}
	char header[MAX_HEADER_SIZE];
	unsigned int headerSize = headerEndPtr - ptr;

	// If we use tokenization, memory copy is required.
	memcpy(header, ptr, headerSize);
	header[headerSize] = '\0';

	// TODO: implement tokenization in the future.
	// for now, we don't need to tokenize.

	return str2DataType(header);
}

/**
 *  bodyStartPtr: pinter pointing at the start of the message body.
 *  dataType: dataType that we parse the data into.
 *  return: return the pointer to parsed data value.
 */
void* MessageParser::getParsedDataFromMessageBody(char* bodyStartPtr, DataType dataType) {
	unsigned int bodyLength = strlen(bodyStartPtr) - CHECKSUM_END_CHAR_SIZE;
	char messageBody[MAX_MESSAGE_BODY_SIZE];

	memcpy(messageBody, bodyStartPtr, bodyLength);
	messageBody[bodyLength] = '\0';

	char* str = (char*) malloc(bodyLength + 1);

	switch (dataType) {
	case INTEGER:
		return new int(atoi(messageBody));
	case FLOAT:
		return new float(atof(messageBody));
	case DOUBLE:
		return new double(atof(messageBody));
	case BOOL:
		return new bool(atoi(messageBody) == 1);
	case STRING:
		strcpy(str, messageBody);
		return str;
	default:
		break;
	}
	return nullptr;
}

/**
 * str: input string that represents data type.
 * returns: return the data type.
 */
DataType MessageParser::str2DataType(char* str) {
	for (int i=0; i<NUM_SUPPORTED_DATA_TYPE; i++) {
			if (strcmp(DATA_TYPE_STRINGS[i], str) == 0) {
				return (DataType) i;
			}
		}
	return sp::UNSUPPORTED_TYPE;
}
