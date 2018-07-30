/*
 * InputConnection.cpp
 *
 *  Created on: Jul 15, 2018
 *      Author: baixiao
 */

#include "InputConnection.h"
#include "MessageParser.h"
#include "HardwareSerial.h"

using namespace sp;

InputConnection::InputConnection()
	: m_startReadingMessage(false),
	  m_newMessageAvailable(false),
	  m_bufferIdx(0),
	  m_Serial(nullptr)
{}

InputConnection::InputConnection(HardwareSerial* Serial, unsigned int baudRate):
		m_startReadingMessage(false), m_newMessageAvailable(false), m_bufferIdx(0)
{
	this->m_Serial = Serial;
	this->m_Serial->begin(baudRate);
}

void InputConnection::update() {
	MessageParser parser;
	while (m_Serial->available()) {
		char data = m_Serial->read();

		if (m_startReadingMessage) {
			m_buffer[m_bufferIdx++] = data;
		}

		// buffer overflow, message is invalid.
		if (m_bufferIdx == MAX_MESSAGE_SIZE) {
			m_startReadingMessage = false;
			m_newMessageAvailable = false;
			m_bufferIdx = 0;
			continue;
		}

		// When data is not escaped.
		if (m_bufferIdx == 0 || m_buffer[m_bufferIdx - 1] != sp::ESCAPE_CHAR) {
			if (data == START_CHAR) {
				m_startReadingMessage = true;
				m_bufferIdx = 0;
			}
			else if(data == END_CHAR) {
				m_buffer[m_bufferIdx] = '\0';
				if(parser.parse(m_buffer)) {
					m_message = parser.getParsedMessage();
					m_newMessageAvailable = true;
				}
				m_startReadingMessage = false;
			}
		}

	}
}

bool InputConnection::newMessageAvailable() {
	return m_newMessageAvailable;
}

Message InputConnection::getMessage() {
	m_newMessageAvailable = false;
	return m_message;
}
