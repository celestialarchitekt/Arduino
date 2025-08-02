# Arduino PWM

Pulse width modulation: keeping the frequency of signal the same, change the duty cycle. 
Duty cycle: for how much duration is the signal on during one cycle.

In Arduino, there are hardware timers that create the PWM signal, the CPU does not toggle the pin.
8 bit timers are used to generate the PWM, value address-> 2^8=256, so 0 to 255.

When the command analogWrite(pin, value) is given, the value sets the compare register.
Duty Cycle = value/255

1. If value == 0
Duty Cycle = 0, signal is low all the time

2. If value == 1
Duty Cycle = 1, signal is high all the time

3. If value == 127
Duty Cycle = 50% high, 50% low in one cycle



##PWM Frequency

- By default the R4 uses a default PWM of 490Hz.
- AnalogWrite(pin, value), value decides the duty cycle 









