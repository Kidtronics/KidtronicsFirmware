/*
 * InputConnection.h
 *
 *  Created on: Jul 15, 2018
 *      Author: baixiao
 */

#ifndef SRC_INPUTCONNECTION_H_
#define SRC_INPUTCONNECTION_H_

#include "MessageConstants.h"
#include "HardwareSerial.h"
#include "Message.h"

class InputConnection {
private:
	char m_buffer[sp::MAX_MESSAGE_SIZE];
	unsigned int m_bufferIdx;
	bool m_startReadingMessage;
	bool m_newMessageAvailable;
	HardwareSerial* m_Serial;
	Message m_message;
public:
	InputConnection();
	InputConnection(HardwareSerial* Serial, unsigned int baudRate);
	/**
	 * Check the Serial buffer for available data, then read into buffer
	 */
	void update();
	/**
	 * return whether new message is available for read.
	 */
	bool newMessageAvailable();
	/**
	 * Get message parsed from buffer.
	 */
	Message getMessage();
};


#endif /* SRC_INPUTCONNECTION_H_ */
