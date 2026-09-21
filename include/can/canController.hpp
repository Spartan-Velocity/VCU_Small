#pragma once

#include <FlexCAN_T4.h>

namespace canController {

void initCANBus();
void pollCANBus();

void onCanMessage(const CAN_message_t& msg);

}  // namespace canController