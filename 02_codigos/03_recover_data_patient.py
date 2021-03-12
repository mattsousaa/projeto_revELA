import matplotlib.pyplot as plt
import numpy as np
import sys

def average_column (csv):

    list_num = []

    with open (csv, "rb") as annotate:
        for col in annotate:
            ann = col.decode().split(",")
            list_num.append(float(ann[0]))
    
    avg = sum(list_num) / len(list_num)

    return avg

if len(sys.argv) <= 1: 
    print('Insufficient arguments')
    sys.exit()

amp_avg = average_column('dataPlayer3.csv')

#print(f"The amplitude average is {amp_avg:.2f}")

y, x = np.loadtxt('dataPlayer3.csv', delimiter=',', unpack=True)

plt.plot(x, y, 'b-', linewidth=1.0, label='EMG filtered')

plt.title('Data from the CSV File: EMG values - Player1 (Nome: {}) - AVG = {:.2f}'.format(sys.argv[1], amp_avg))

plt.xlabel('Time')
plt.ylabel('Voltage')

plt.grid()
plt.show()


