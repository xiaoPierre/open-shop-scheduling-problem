import sys
from tkinter import *


class Job(object):
    def __init__(self, identifiant, weight, processTime, startTime, endTime):
        self.identifiant = identifiant
        self.weight = weight
        self.processTime = processTime
        self.startTime = startTime
        self.endTime = endTime

def calculateWCT(jobs):
    count = 0
    for job in jobs:
        count += job.weight * max(job.endTime)
    return count


if len(sys.argv) != 2:
    print("Usage: python vis.py [DataFile]")
    exit()

jobs = []
maxEndDate = 0
with open(sys.argv[1], 'r') as jobsFile:
    for line in jobsFile.readlines():
        jobString = list(map(int, line.rstrip().split(' ')))
        identifiant = jobString[0]
        weight = jobString[1]
        processTime = jobString[2:6]
        startTime = jobString[6:10]
        endTime = list(map(lambda x: x[0]+x[1], zip(processTime, startTime)))
        if max(endTime) > maxEndDate:
            maxEndDate = max(endTime)
        jobs.append(Job(identifiant, weight, processTime, startTime, endTime))

if len(jobs) > 10:
    print("Too many jobs for visualisation! (maximum 10)")
    exit()

racine = Tk()

width = 1000
height = 500
margeVertical = height / 5
margeHorizontal = width / 10
lengthOfMainLine = width - 2 * margeHorizontal
ecart = (height - 2 * margeVertical) / 4
zone_dessin = Canvas(racine, width=width, height=height) #Définit les dimensions du canevas
zone_dessin.pack() #Affiche le canevas

for i in range(4):
    zone_dessin.create_line(margeHorizontal, margeVertical + i * ecart, width - margeHorizontal,
                            margeVertical + i * ecart)

lenthOfUnityTime = lengthOfMainLine / maxEndDate



colors = ["red", "yellow", "blue", "green", "black", "purple", "white", 'gray', 'navy', 'magenta']
for machine in range(4):
    for idxJob in range(len(jobs)):
        zone_dessin.create_rectangle(margeHorizontal + jobs[idxJob].startTime[machine] * lenthOfUnityTime,
                                     margeVertical + machine * ecart,
                                     margeHorizontal + (jobs[idxJob].startTime[machine] + jobs[idxJob].processTime[machine]) * lenthOfUnityTime,
                                     margeVertical + machine * ecart - 20,
                                     fill=colors[idxJob])

bouton_sortir = Button(racine,text="Sortir",command=racine.destroy)
bouton_sortir.pack()

print(calculateWCT(jobs))

racine.mainloop()
