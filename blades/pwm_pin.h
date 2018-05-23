#ifndef BLADES_PWM_PIN_H
#define BLADES_PWM_PIN_H

#include "led_interface.h"

#ifdef TEENSYDUINO
void LSanalogWriteSetup(uint32_t pin) {
  analogWriteResolution(16);
  analogWriteFrequency(pin, 1000);
}
void LSanalogWrite(uint32_t pin, int value) {
  analogWrite(pin, value);
}
#else
#include <stm32l4_timer.h>

namespace {
static stm32l4_timer_t stm32l4_pwm[PWM_INSTANCE_COUNT];

void SetupTimer(uint32_t instance) {
  if (stm32l4_pwm[instance].state == TIMER_STATE_NONE) {
    stm32l4_timer_create(&stm32l4_pwm[instance], g_PWMInstances[instance], 15, 0);
    
    // 813 Hz, 32768 steps
    uint32_t carrier = 26666666;
    uint32_t modulus = 32768;
    uint32_t divider = stm32l4_timer_clock(&stm32l4_pwm[instance]) / carrier;
    
    if (divider == 0) divider = 1;
    
    stm32l4_timer_enable(&stm32l4_pwm[instance], divider -1, modulus -1, TIMER_OPTION_COUNT_PRELOAD, NULL, NULL, 0);
    stm32l4_timer_start(&stm32l4_pwm[instance], false);
    if (instance)  {
      SetupTimer(0);
      // TIM16 cannot be synchronized in hardware, so let's do the best we can.
      volatile uint32_t* from = &stm32l4_pwm[0].TIM->CNT;
      volatile uint32_t* to = &stm32l4_pwm[instance].TIM->CNT;
      noInterrupts();
      *to = *from + 10;
      interrupts();
    }
  }
}

void LSanalogWriteSetup(uint32_t pin) {
  // Handle the case the pin isn't usable as PIO
  if (pin >= NUM_TOTAL_PINS || g_APinDescription[pin].GPIO == NULL) {
    Serial.println("Analog Setup: NOT A PIN: ");
    Serial.println(pin);
    return;
  }
  
  if (!(g_APinDescription[pin].attr & PIN_ATTR_PWM)) {
    Serial.println("Analog Setup: Pin is not configured for PWM: ");
    Serial.println(pin);
    return;
  }
  SetupTimer(g_APinDescription[pin].pwm_instance);
  stm32l4_gpio_pin_configure(g_APinDescription[pin].pin, (GPIO_PUPD_NONE | GPIO_OSPEED_HIGH | GPIO_OTYPE_PUSHPULL | GPIO_MODE_ALTERNATE));
}
// TODO: Shut down timer when we don't need it anymore.

void LSanalogWrite(uint32_t pin, int value) {
  uint32_t instance = g_APinDescription[pin].pwm_instance;
  value >>= 1;
  if (value < 0) value = 0;
  if (value > 32768) value = 32768;
  
  stm32l4_timer_channel(&stm32l4_pwm[instance], g_APinDescription[pin].pwm_channel, value, TIMER_CONTROL_PWM);
}


};
#endif

class PWMPin {
public:
  void Init(int pin, LEDInterface*c) {
    pin_ = pin;
    c_ = c;
  }
  void Activate() {
    if (pin_ == -1) return;
    LSanalogWriteSetup(pin_);
    LSanalogWrite(pin_, 0);  // make it black
  }
  void set(const Color16& c) {
    if (pin_ == -1) return;
    LSanalogWrite(pin_, c_->PWM(c));
  }
  void set_overdrive(const Color16& c) {
    if (pin_ == -1) return;
    LSanalogWrite(pin_, c_->PWM_overdrive(c));
  }

  int pin_;
  LEDInterface* c_;
};

#endif