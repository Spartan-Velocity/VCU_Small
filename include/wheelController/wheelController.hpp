#pragma once

#include <cstdint>

namespace wheelController {

void setEnabled(bool enabled);
void setTorque(int16_t torque);

void init();
void poll();

}  // namespace wheelController