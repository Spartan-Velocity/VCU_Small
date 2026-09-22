#pragma once

#include <FlexCAN_T4.h>

namespace canController {

void requestMessages(uint32_t id, _MB_ptr handler, bool extendedID = false);
void transmitMessage(const CAN_message_t& msg);

void initCANBus();
void pollCANBus();

}  // namespace canController