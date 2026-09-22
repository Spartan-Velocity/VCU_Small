#include "pump/pumpController.hpp"

#include "config.hpp"
#include "core_pins.h"

namespace pumpController {

namespace {}  // namespace

void init() {
  pinMode(pumpConfig::PUMP_PWM_PIN, OUTPUT);

  analogWriteResolution(8);
  analogWriteFrequency(pumpConfig::PUMP_PWM_PIN, pumpConfig::PUMP_PWM_FREQUENCY);

  analogWrite(pumpConfig::PUMP_PWM_PIN, pumpConfig::PUMP_PWM_DUTYCYCLE);
}

}  // namespace pumpController