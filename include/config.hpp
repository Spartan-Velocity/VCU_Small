#pragma once

#include <cstdint>

namespace canControllerConfig {

constexpr bool canMonitorEnabled = true;

constexpr uint32_t CAN_BAUD_RATE = 500000u;
constexpr uint32_t CAN_MAX_MB = 16u;

constexpr uint32_t MSGID_RECIEVE_DISPLAY_DATA = 0x019u;
constexpr uint32_t MSG_ID_PACK_DATA = 0x019u;
constexpr uint32_t MSG_ID_PACK_STATUS = 0x020u;
constexpr uint32_t MSG_ID_VSM_STATE = 0x0AAu;
constexpr uint32_t MSG_ID_FAULT_FLAGS = 0x024u;

}  // namespace canControllerConfig