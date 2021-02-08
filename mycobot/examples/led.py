from mycobot.mycobot import MyCobot
import time
import random
robot = MyCobot('/dev/ttyUSB1')

color_code = ['ff0000', '00ff00', '0000ff', '7f0000', '007f00', '00007f']
i = random.randint(0, len(color_code) - 1)

robot.set_color(color_code[i])
robot.set_color('00ff00')

robot.power_on()
robot.set_pwm_mode(22, 0)

while True:
    robot.send_radians([0,0,0,0,0,0], 80)
    robot.set_pwm_output(0, 240)
    robot.set_gripper_value(0, 80)
    robot.set_gripper_value(1, 80)
    time.sleep(1)
    break


