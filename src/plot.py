import matplotlib.pyplot as plt
import numpy as np


file = open("./data/data.txt","r")
positions_sol = []
positions_top = []
time = []

lines = file.readlines()
n = len(lines)
stiffness,damping,B_H,k_1 = [float(i) for i in lines[0].split(" ")]

for line in lines[1:]:
    t, pos_s,pos_t = [float(i) for i in line.split(" ")]
    positions_sol.append(pos_s)
    positions_top.append(pos_t)
    time.append(t)

max_x = max(max(positions_sol),max(positions_top))
min_x = min(min(positions_sol),min(positions_top))

plt.title(f"Tuned Mass Damper system oscillations.")
fig,ax = plt.subplots()

plt.xlabel("Time (ms)")
plt.ylabel("X axis (pixels)")
ax.plot(time,positions_sol,linewidth=1.0)
ax.plot(time,positions_top,linewidth=1.0)
string = f"Hauteur du bâtiment : {B_H}\nk_1 : {k_1}"
ax.legend("")
props = dict(boxstyle='round', facecolor='wheat', alpha=0.5)
ax.text(0.7, 0.95, string, transform=ax.transAxes, fontsize=9,verticalalignment='top', bbox=props)
plt.yticks(np.arange(int(min_x/10) * 10, max_x,50))

plt.gca().legend(('Position au sol.','Position en haut du bâtiment.'),loc='lower right')
plt.show()