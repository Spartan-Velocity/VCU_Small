#pragma once

#include <cstdint>

namespace canControllerConfig {

constexpr bool canMonitorEnabled = true;

constexpr uint32_t CAN_BAUD_RATE = 500000u;
constexpr uint8_t CAN_MAX_MB = 64u;

}  // namespace canControllerConfig

namespace wheelControllerConfig {

constexpr uint32_t WHEEL_CONTROLLER_CANID_OFFSET = 0x0A0u;

constexpr uint32_t MSGID_W_COMMAND = WHEEL_CONTROLLER_CANID_OFFSET + 0x20u;
constexpr uint32_t MSGID_R_STATES  = WHEEL_CONTROLLER_CANID_OFFSET + 0x0Au;
constexpr uint32_t MSGID_R_FAULTS = WHEEL_CONTROLLER_CANID_OFFSET + 0x0Bu;

constexpr uint16_t MSG_TIMEOUT = 10;


}  // namespace wheelControllerConfig