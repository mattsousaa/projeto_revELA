# Import libraries
from numpy import *
from pyqtgraph.Qt import QtGui, QtCore
import pyqtgraph as pg
import serial
import time
import csv

start_time = time.time()

# Create object serial port
portName = "COM6"                      # replace this port name by yours!
baudrate = 115200
ser = serial.Serial(portName,baudrate)

### START QtApp #####
app = QtGui.QApplication([])            # you MUST do this once (initialize things)
####################

################################################### Plot PACIENTE 1 ####################################################
win = pg.GraphicsWindow(title="Signal from serial port")            # creates a window
p1 = win.addPlot(title="Paciente 1")                                # creates empty space for the plot 1 in the window
curve1 = p1.plot(pen=(255,0,0), name="Red X curve")                 # create an empty "plot 1" (a curve to plot)
p1.setRange(yRange=[0,150])

################################################### Plot PACIENTE 2 ####################################################
win.nextRow()                                                       # each graph below each other
p2 = win.addPlot(title="Paciente 2")                                # creates empty space for the plot 2 in the window
curve2 = p2.plot(pen=(0,255,0), name="Green Y curve")               # create an empty "plot 2" (a curve to plot)
p2.setRange(yRange=[0,120])

################################################### Plot PACIENTE 3 ####################################################
win.nextRow()                                                       # each graph below each other
p3 = win.addPlot(title="Paciente 3")                                # creates empty space for the plot 3 in the window
curve3 = p3.plot(pen=(0,0,255), name="Yellow Z curve")              # create an empty "plot 3" (a curve to plot)
p3.setRange(yRange=[0,120])

################################################### Plot PACIENTE 4 ####################################################
win.nextRow()                                                       # each graph below each other
p4 = win.addPlot(title="Paciente 4")                                # creates empty space for the plot 3 in the window
curve4 = p4.plot(pen=(255,255,0), name="Yellow W curve")            # create an empty "plot 3" (a curve to plot)
p4.setRange(yRange=[0,120])

windowWidth = 500                       # width of the window displaying the curve
Xm = linspace(0,0,windowWidth)          # create array that will contain the relevant time series for EMG1
Ym = linspace(0,0,windowWidth)          # create array that will contain the relevant time series for EMG2
Zm = linspace(0,0,windowWidth)          # create array that will contain the relevant time series for EMG3
Wm = linspace(0,0,windowWidth)          # create array that will contain the relevant time series for EMG4
ptr = -windowWidth                      # set first x position

# Realtime data plot. Each time this function is called, the data display is updated
def update():
    global curve1, curve2, curve3, curve4, ptr, Xm, Ym, Zm, Wm    
    Xm[:-1] = Xm[1:]                          # shift data from EMG1 in the temporal mean 1 sample left
    Ym[:-1] = Ym[1:]                          # shift data from EMG2 in the temporal mean 1 sample left
    Zm[:-1] = Zm[1:]                          # shift data from EMG3 in the temporal mean 1 sample left
    Wm[:-1] = Wm[1:]                          # shift data from EMG4 in the temporal mean 1 sample left

    value = ser.readline().decode("utf-8")    # read line (single value) from the serial port
    output = value.split(',')                 # split values between commas
    
    Xm[-1] = float(output[0])                 # vector containing the instantaneous values of EMG1 
    Ym[-1] = float(output[1])                 # vector containing the instantaneous values of EMG2 
    Zm[-1] = float(output[2])                 # vector containing the instantaneous values of EMG3 
    Wm[-1] = float(output[3])                 # vector containing the instantaneous values of EMG4 

    ptr += 1                                  # update x position for displaying the curve
    curve1.setData(Xm)                        # set the curve 1 with this data
    curve1.setPos(ptr,0)                      # set x position in the graph to 0

    curve2.setData(Ym)                        # set the curve 2 with this data
    curve2.setPos(ptr,0)                      # set x position in the graph to 0

    curve3.setData(Zm)                        # set the curve 3 with this data
    curve3.setPos(ptr,0)                      # set x position in the graph to 0

    curve4.setData(Wm)                        # set the curve 4 with this data
    curve4.setPos(ptr,0)                      # set x position in the graph to 0

    QtGui.QApplication.processEvents()        # you MUST process the plot now

    csv_1 = str(Xm[-1])                       # variable to store inside CSV1
    csv_2 = str(Ym[-1])                       # variable to store inside CSV2
    csv_3 = str(Zm[-1])                       # variable to store inside CSV3
    csv_4 = str(Wm[-1])                       # variable to store inside CSV4

    # save the serial data in real-time to a .csv file (Datalogger)
    decoded_bytes1 = float(csv_1[0:len(csv_1)-2])       # EMG1 data
    decoded_bytes2 = float(csv_2[0:len(csv_2)-2])       # EMG2 data
    decoded_bytes3 = float(csv_3[0:len(csv_3)-2])       # EMG3 data
    decoded_bytes4 = float(csv_4[0:len(csv_4)-2])       # EMG4 data

    # save data from EMG1 in dataPlayer1.csv
    with open("dataPlayer1.csv","a") as f1:
        writer1 = csv.writer(f1,delimiter=",")
        writer1.writerow([decoded_bytes1, (time.time() - start_time)])

    # save data from EMG2 in dataPlayer2.csv
    with open("dataPlayer2.csv","a") as f2:
        writer2 = csv.writer(f2,delimiter=",")
        writer2.writerow([decoded_bytes2, (time.time() - start_time)])

    # save data from EMG3 in dataPlayer3.csv
    with open("dataPlayer3.csv","a") as f3:
        writer3 = csv.writer(f3,delimiter=",")
        writer3.writerow([decoded_bytes3, (time.time() - start_time)])

    # save data from EMG4 in dataPlayer4.csv
    with open("dataPlayer4.csv","a") as f4:
        writer4 = csv.writer(f4,delimiter=",")
        writer4.writerow([decoded_bytes4, (time.time() - start_time)])

### MAIN PROGRAM #####    
# this is a brutal infinite loop calling your realtime data plot
while True: update()

### END QtApp ####
pg.QtGui.QApplication.exec_() # you MUST put this at the end
##################
