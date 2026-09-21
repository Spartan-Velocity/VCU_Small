#include "can/canController.hpp"

#include "config.hpp"
#include "display/display.hpp"

namespace canController {

namespace {

FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> canBus;

}  // namespace

void initCANBus() {
  canBus.begin();

  canBus.setBaudRate(canControllerConfig::CAN_BAUD_RATE);
  canBus.setMaxMB(canControllerConfig::CAN_MAX_MB);
  canBus.enableFIFO();
  canBus.enableFIFOInterrupt();

  canBus.onReceive(onCanMessage);
}

void pollCANBus() {
  canBus.events();
}

void onCanMessage(const CAN_message_t& msg) {
  switch (msg.id) {
    case canControllerConfig::MSGID_RECIEVE_DISPLAY_DATA: {
      vcu->pack->voltage = msg.buf[1] / 10;
      vcu->pack->avgTemp = msg.buf[0];
      vcu->pack->soc = msg.buf[2] / 2;
      vcu->pack->maxTemp = msg.buf[3];
      vcu->pack->minTemp = msg.buf[4];

      Display::writeDisplay({.voltage = msg.buf[1] / 10,
                             .avgTemp = msg.buf[0],
                             .soc = msg.buf[2] / 2,
                             .maxTemp = msg.buf[3],
                             .minTemp = msg.buf[4]});
      state = pumpModuleUpdate;

      break;
    }

    case 0x0A3: {
      uint32_t raw = msg.buf[0];
      uint32_t raw2 = msg.buf[1];
      Serial.println(raw);
      Serial.println(raw2);

      break;
    }

    case MSG_ID_PACK_STATUS: {
      uint8_t byte0 = msg.buf[0];
      uint8_t byte1 = msg.buf[1];

      if ((byte0 & STATUS_VOLT_TOO_HIGH_MASK) != 0U) {
        displayWrite("t4", "VOLT TOO HIGH", 0, "X");
      }
      if ((byte1 & STATUS_REDUN_SUPPLY_MASK) != 0U) {
        displayWrite("t4", "REDUN SUPPLY", 0, "X");
      }

      break;
    }

    default: {
      displayWrite("t0", "CAN_DC", 1, "C");
      displayWrite("t3", "X", 1, "V");
      displayWrite("t2", "X", 1, "%");
      displayWrite("t10", "X ", 1, "C");
      displayWrite("t8", "X ", 1, "C");

      break;
    }
  }
}

}  // namespace canController