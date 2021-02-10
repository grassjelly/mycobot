from mycobot.mycobot import MyCobot
import time
import random
robot = MyCobot('/dev/ttyUSB0')

color_code = ['ff0000', '00ff00', '0000ff', '7f0000', '007f00', '00007f']
i = random.randint(0, len(color_code) - 1)
robot.set_led_color(color_code[i])

channel = 0
robot.set_pwm_mode(22, channel)

robot.power_on()

while True:
    robot.send_radians([0,0,0,0,0,0], 80)
    robot.set_pwm_output(channel,0)
    time.sleep(3)
    robot.set_pwm_output(channel, 125)
    time.sleep(3)

