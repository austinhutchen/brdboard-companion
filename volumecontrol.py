import os
import serial
import argparse

parser = argparse.ArgumentParser()
parser.add_argument('--force', dest='force', action='store_const', const=True)
args = parser.parse_args()
force = args.force
volume = 0
arduino = serial.Serial('/dev/cu.usbmodem1411', 115200, timeout=.1)
while True:
    data = arduino.readline()
    if data:
        new_volume = int(data)/30
        if force==True:
            os.system('osascript -e "set Volume {}"'.format(new_volume))
        else: 
            if new_volume==volume:
                pass
            else:
                os.system('osascript -e "set Volume {}"'.format(new_volume))
                volume = new_volume