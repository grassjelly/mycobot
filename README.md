Consolidated ROS packages for [myCobot](https://www.elephantrobotics.com/en/myCobot-en/) 6DOF manipulator. The driver has been rewritten to support closed-loop operation when using MoveIt. Most of the functions are based on the original driver found [here](https://github.com/elephantrobotics/myCobotROS).

## 1. Installation:

### 1.1 Install ROS Dependencies

    sudo apt install -y python-rosdep
    cd <your_ws>/src
    git clone https://github.com/grassjelly/mycobot
    cd ..
    rosdep install --from-paths src --ignore-src -r -y

### 1.2 Firmware Installation
You need to upload version 2.1 Alpha firmware to the Atom Board for the ROS driver to work. You can find the released binaries [here](https://github.com/elephantrobotics/myCobot/releases/tag/0).

The main board must also be uploaded with Transponder firmware found in the link above.

Here's a CLI sample on how to burn the Atom firmware in Linux using [esptool](https://github.com/espressif/esptool):

    python esptool.py -b 1500000 --port /dev/ttyUSB0 write_flash --flash_freq 80m 0x0000e000 boot_app0.bin 0x00001000 bootloader_qio_80m.bin 0x00010000 Atom2.1alpha.ino.bin 

There's also a copy of the Transponder's source code in mycobot/firmware/base which you can use to upload using [PlatformIO](https://platformio.org/)

## 2. Running the driver:

    roslaunch mycobot_bring bringup.launch

Available Arguments:
- rviz - Launch the driver together with RViz
- joints_gui - Launch the driver together with a GUI to control the robot's joints