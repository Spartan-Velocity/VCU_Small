#include "can/canController.hpp"

#include "FlexCAN_T4.h"
#include "config.hpp"

namespace canController {

namespace {

FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> canBus;

uint8_t usedMailboxes = 0;

void sniffMessage(const CAN_message_t& msg);

void sniffMessage(const CAN_message_t& msg) {
  Serial.print("MB=");
  Serial.print(msg.mb);

  Serial.print(" | ID=0x");
  if (msg.id < 0x1000) {
    Serial.print("0");
  }
  Serial.print(msg.id, HEX);

  Serial.print(msg.flags.extended ? " | EXT" : " | STD");

  Serial.print(" | LEN=");
  Serial.print(msg.len);

  Serial.print(" | TS=");
  Serial.print(msg.timestamp);

  Serial.print(" | DATA=");
  const uint8_t length = min(msg.len, static_cast<uint8_t>(8));

  for (uint8_t index = 0; index < length; ++index) {
    if (msg.buf[index] < 0x10) {
      Serial.print("0");
    }

    Serial.print(msg.buf[index], HEX);

    if (index + 1 < length) {
      Serial.print(" ");
    }
  }

  if (msg.flags.overrun) {
    Serial.print(" | OVERRUN");
  }

  Serial.println();
}

}  // namespace

void requestMessages(uint32_t id, _MB_ptr handler, bool extendedID) {
  if (usedMailboxes >= 63) {
    return;
  }
  auto mailbox = FLEXCAN_MAILBOX(usedMailboxes);

  canBus.setMB(mailbox, RX, extendedID ? EXT : STD);
  canBus.setMBFilter(mailbox, id);
  canBus.onReceive(mailbox, handler);
  canBus.enableMBInterrupt(mailbox);

  usedMailboxes++;
}

void transmitMessage(const CAN_message_t& msg) {
  canBus.write(msg);
}

void initCANBus() {
  // TODO: swordpartee - find a better home for serial begin
  Serial.begin(115200);

  canBus.begin();

  canBus.setBaudRate(canControllerConfig::CAN_BAUD_RATE);
  canBus.setMBFilter(REJECT_ALL);  // disable all mailboxes

  canBus.setMB(MB0, TX);  // set mailbox 0 to transmit
  usedMailboxes++;

  // enable fifo mailbox for message sniffing
  canBus.enableFIFO();
  canBus.setFIFOFilter(ACCEPT_ALL);
  canBus.onReceive(FIFO, sniffMessage);
  canBus.enableFIFOInterrupt();

  // pass dedicated mailbox messages to fifo for debugging
  canBus.distribute(canControllerConfig::canMonitorEnabled);
}

void pollCANBus() {
  canBus.events();
}

}  // namespace canController

// TODO: swordpartee - write messages to a ring buffer and write to serial in poll
// TODO: swordpartee - report failures when configuring mailboxes