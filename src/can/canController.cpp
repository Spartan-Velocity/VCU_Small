#include "can/canController.hpp"

#include "FlexCAN_T4.h"
#include "config.hpp"

namespace canController {

namespace {

FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> canBus;

uint8_t usedMailboxes = 0;

void sniffMessage(const CAN_message_t& msg);

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
  canBus.begin();

  canBus.setBaudRate(canControllerConfig::CAN_BAUD_RATE);

  canBus.distribute(true);  // pass messages to every accepting mailbox

  canBus.setMBFilter(REJECT_ALL);  // disable all mailboxes
                                   //
  canBus.setMB(MB0, TX);           // set mailbox 0 to transmit
  usedMailboxes++;

  // set mailbox 1 to sniff all standard id messages
  canBus.setMB(MB1, RX, STD);
  canBus.setMBFilter(MB1, ACCEPT_ALL);
  canBus.onReceive(MB1, sniffMessage);
  canBus.enableMBInterrupt(MB1);
  usedMailboxes++;

  // set mailbox 2 to sniff all extended id messages
  canBus.setMB(MB2, RX, EXT);
  canBus.setMBFilter(MB2, ACCEPT_ALL);
  canBus.onReceive(MB2, sniffMessage);
  canBus.enableMBInterrupt(MB2);
  usedMailboxes++;
}

void pollCANBus() {
  canBus.events();
}

}  // namespace canController

// TODO: report failures when configuring mailboxes