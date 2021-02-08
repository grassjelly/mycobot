Consolidated ROS packages for [myCobot](https://www.elephantrobotics.com/en/myCobot-en/) 6DOF manipulator. The driver has been rewritten to support closed-loop operation when using MoveIt. Most of the functions are based on the original driver found [here](https://github.com/elephantrobotics/myCobotROS).

## 1. Installation:

### 1.1 Install ROS Dependencies

    sudo apt install -y python-rosdep
    cd <your_ws>/src
    git clone https://github.com/grassjelly/mycobot
    cd ..
    rosdep install --from-paths src --ignore-src -r -y

### 1.2 Firmware Installation
Download the latest software release [here](https://github.com/elephantrobotics/myCobot/releases/tag/0) and run the following commands to upload the firmware using [esptool](https://github.com/espressif/esptool):

First install esptool:

    pip install esptool

Atom Board Firmware:

    cd <latest_release_ino_folder>
    esptool.py -b 1500000 --port /dev/ttyUSB0 write_flash --flash_freq 80m 0x0000e000 boot_app0.bin 0x00001000 bootloader_qio_80m.bin 0x00010000 AtomMain2.5.ino.bin 0x00008000 AtomMain2.5.ino.partitions.bin

Base Board Firmware:

    cd <latest_release_ino_folder>
    esptool.py -b 1500000 --port /dev/ttyUSB0 write_flash --flash_freq 80m 0x0000e000 boot_app0.bin 0x00001000 bootloader_qio_80m.bin 0x00010000 Transponder.ino.bin 0x00008000 Transponder.ino.partitions.bin

Calibration Firmware:

    cd <latest_release_ino_folder>
    esptool.py -b 1500000 --port /dev/ttyUSB0 write_flash --flash_freq 80m 0x0000e000 boot_app0.bin 0x00001000 bootloader_qio_80m.bin 0x00010000 Calibration.ino.bin 0x00008000 Calibration.ino.partitions.bin

## 2. Running the driver:

    roslaunch mycobot_bring bringup.launch

Available Arguments:
- rviz - Launch the driver together with RViz
- joints_gui - Launch the driver together with a GUI to control the robot's joints