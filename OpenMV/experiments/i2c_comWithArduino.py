# https://forums.openmv.io/viewtopic.php?t=194
import sensor, image, time
from pyb import I2C

def Com123():
    print("Command 123")

def Com124():
    print("Command 124")

def Com125():
    print("Command 125")

def Com126():
    print("Command 126")

kernel_size = 1 # kernel width = (size*2)+1, kernel height = (size*2)+1
kernel = [-1, -1, -1,\
          -1, +8, -1,\
          -1, -1, -1]
thresholds = [(150, 255)] # grayscale thresholds
TestData = 123
SlaveAddress = 0x12

bus = I2C(2, I2C.MASTER, baudrate=100000, gencall=False) # P4=SCL, P5=SDA, set the slave address to whatever...

sensor.reset() # Initialize the camera sensor.
sensor.set_pixformat(sensor.GRAYSCALE) # or sensor.RGB565
sensor.set_framesize(sensor.QVGA) # or sensor.QVGA (or others)
sensor.skip_frames(10) # Let new settings take affect.
clock = time.clock() # Tracks FPS.

if (sensor.get_id() == sensor.OV7725):
    sensor.__write_reg(0xAC, 0xDF)
    sensor.__write_reg(0x8F, 0xFF)

#----------------
#Look for Arduino
#----------------
OnLine = bus.scan()
if(OnLine == []):
    print("Arduino not found")
    MainLoop = False
else:
    if(OnLine[0] == SlaveAddress):
        print("Arduino Online")
        MainLoop = True
    else:
        print("Arduino not found")
        print(OnLine)
        MainLoop = False

#---------------
#start main loop
#---------------
while(MainLoop):  #Start Main loop
    clock.tick()  #Track elapsed milliseconds between snapshots().

    #---------------
    #Talk to Arduino
    #---------------
    ArduionWait = True
    TestData = 100
    while(ArduionWait):
        # Get a test byte from Arduino
        try:
            TestData = ord(bus.recv(1, SlaveAddress, timeout=1000))
        except OSError:
            pass
        # Confirm test byte received
        try:
            bus.send(TestData, SlaveAddress, timeout=1000)
        except OSError:
            pass
        if(TestData != 111):
            ArduionWait = False

    #----------------------
    #What did Arduino say?
    #----------------------
    if (TestData == 123):
        Com123()
    elif (TestData == 124):
        Com124()
    elif (TestData == 125):
        Com125()
    elif (TestData == 126):
        Com126()
    else:
        print(TestData)
    img = sensor.snapshot() # Take a picture and return the image.
    print(clock.fps())
