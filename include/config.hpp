#pragma once

#include <cstdint>

namespace canControllerConfig {

constexpr bool canMonitorEnabled = true;

constexpr uint32_t CAN_BAUD_RATE = 500000u;
constexpr uint8_t CAN_MAX_MB = 64u;

}  // namespace canControllerConfig

namespace wheelControllerConfig {

constexpr uint32_t WHEEL_CONTROLLER_CANID = 0x0A0u;

constexpr uint32_t MSGID_TX_COMMAND_OFFSET = 0x20u;
constexpr uint32_t MSGID_RT_STATES_OFFSET = 0x0Au;
constexpr uint32_t MSGID_RT_FAULTS_OFFSET = 0x0Bu;

constexpr uint16_t MSG_TIMEOUT = 10;

}  // namespace wheelControllerConfig