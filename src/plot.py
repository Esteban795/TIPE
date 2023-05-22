import matplotlib.pyplot as plt

file = open("./data/data.txt","r")
positions_sol = []
positions_top = []
time = []

lines = file.readlines()
n = len(lines)
stiffness,damping,B_H = [float(i) for i in lines[0].split(" ")]

for line in lines[1:]:
    t, pos_s,pos_t = [float(i) for i in line.split(" ")]
    positions_sol.append(pos_s)
    positions_top.append(pos_t)
    time.append(t)


plt.title(f"Tuned Mass Damper system oscillations.")
fig,ax = plt.subplots()

plt.xlabel("Time (ms)")
plt.ylabel("X axis (pixels)")
ax.plot(time,positions_sol,linewidth=1.0)
ax.plot(time,positions_top,linewidth=1.0)
string = f"Rigidité : {stiffness}\n Coefficient d'amortissement : {damping}\n Hauteur du bâtiment : {B_H}"

props = dict(boxstyle='round', facecolor='wheat', alpha=0.5)
ax.text(0.6, 0.95, string, transform=ax.transAxes, fontsize=9,verticalalignment='top', bbox=props)
ax.set(xlim=(0,time[-1]))

plt.show()