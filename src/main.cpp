#include <Arduino.h>
#include "can/canController.hpp"
#include "pump/pumpController.hpp"
#include "wheelController/wheelController.hpp"

void setup() {
  Serial.begin(115200);

  canController::init();
  // wheelController::init();
  // pumpController::init();
}

void loop() {
  canController::poll();
  // wheelController::poll();
}