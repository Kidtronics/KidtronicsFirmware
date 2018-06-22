/*
 * ParsedMessage.h
 *
 *  Created on: Jun 21, 2018
 *      Author: baixiao
 */

#ifndef MESSAGE_H_
#define MESSAGE_H_

#include "MessageConstants.h"

class Message {
private:
	void* m_data;
	sp::DataType m_dataType;
public:
	Message(void* data, sp::DataType dataType);
	Message();
	void* getData();
	sp::DataType getDataType();
};

inline Message::Message(void* data, sp::DataType dataType) :
		m_data(data), m_dataType(dataType)
{}

inline Message::Message() {
	m_data = nullptr;
	m_dataType = sp::UNSUPPORTED_TYPE;
}

inline void* Message::getData() {
	return m_data;
}

inline sp::DataType Message::getDataType() {
	return m_dataType;
}

#endif /* MESSAGE_H_ */
