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
	UnionData getUnionData();
    int getIntData();
    float getFloatData();
    double getDoubleData();
    char* getStringData();
    bool getBoolData();
	sp::DataType getDataType();
};

inline Message::Message() {
	m_data.INTEGER = 0;
	m_dataType = sp::UNSUPPORTED_TYPE;
}

inline Message::UnionData Message::getUnionData() {
	return m_data;
}

inline int Message::getIntData() {
    return m_data.INTEGER;
}

inline float Message::getFloatData() {
    return m_data.FLOAT;
}

inline double Message::getDoubleData() {
    return m_data.DOUBLE;
}

inline char* Message::getStringData() {
    return m_data.CHAR_PTR;
}

inline bool Message::getBoolData() {
    return m_data.BOOL;
}

inline sp::DataType Message::getDataType() {
	return m_dataType;
}

#endif /* MESSAGE_H_ */
