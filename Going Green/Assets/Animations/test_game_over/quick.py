import subprocess as sp
for i in range(3, 15):
    sp.run(["mv", "frame" + str(i), "frame" + str(i) + ".png"])

