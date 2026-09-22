#pragma once

#include <FlexCAN_T4.h>

namespace canController {

using Message = CAN_message_t;

void requestMessages(uint32_t id, _MB_ptr handler, bool extendedID = false);
void writeMessage(const Message& msg);

void initCANBus();
void pollCANBus();

}  // namespace canController