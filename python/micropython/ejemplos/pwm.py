from machine import Pin, PWM

pwm = PWM(Pin(0), freq=10000)

pwm.duty(512)