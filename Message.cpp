//
//  Message.cpp
//  SerialProtocol
//
//  Created by Baixiao Huang on 6/22/18.
//  Copyright © 2018 Baixiao Huang. All rights reserved.
//

#include "Message.h"
#include "stdlib.h"
#include "string.h"

using namespace sp;

Message::Message(UnionData data, sp::DataType dataType) :
	m_dataType(dataType)
{
    m_data = data;
    if (m_dataType == STRING) {
        int strLength = strlen(data.CHAR_PTR);
        m_data.CHAR_PTR = (char*) malloc(strLength + 1);
        strcpy(m_data.CHAR_PTR, data.CHAR_PTR);
        free(m_data.CHAR_PTR);
    }
}
