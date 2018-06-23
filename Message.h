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
public:
    union UnionData {
        int INTEGER;
        float FLOAT;
        double DOUBLE;
        char* CHAR_PTR;
        bool BOOL;
    };
private:
	UnionData m_data;
	sp::DataType m_dataType;
public:
	Message(UnionData data, sp::DataType dataType);
	Message();
	UnionData getData();
	sp::DataType getDataType();
};

inline Message::Message() {
	m_data.INTEGER = 0;
	m_dataType = sp::UNSUPPORTED_TYPE;
}

inline Message::UnionData Message::getData() {
	return m_data;
}

inline sp::DataType Message::getDataType() {
	return m_dataType;
}

#endif /* MESSAGE_H_ */
