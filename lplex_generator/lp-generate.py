N = 10                              #Nb de tâche    
M = 100                             #Constance pour l'inégalité
P = [i + 1 for i in range(N)]       #Duree
D = [i + 3 for i in range(N)]       #Data limite
nb_machine = 3
T = [10, 10, 10, 12, 12, 12]        #Indisponibilité
t = [0, 0, 0, T[3], T[4], T[5]]

filename = "problem.lp"
myfile = open(filename, 'w')

myfile.write('Min\n\t')

for i in range(N):
    if(i == N-1):
        myfile.write("x_" + str(i) + "_7\n")
    else:
        myfile.write("x_" + str(i) +"_7 + ")

myfile.write("\nSubject to\n\t")
for i in range(N):
    for j in range(1,8):
        if(j == 7):
            myfile.write("x_" + str(i) + "_" + str(j) + " = 1\n\t")
        else:
            myfile.write("x_" + str(i) +"_" + str(j) + " + ")

for j in range(1, 4):
    for i in range(N):
        if (i == N-1):
            myfile.write(str(P[i]) + " x_" + str(i) + "_" + str(j) + " <= " + str(T[1]) + "\n\t")
        else:
            myfile.write(str(P[i]) + " x_" + str(i) + "_" + str(j) + " + ")

for j in range(1, 7):
    for i in range(N):
        for k in range(i + 1):
            if (k == i):
                myfile.write(str(P[i] + M) + " x_" + str(k) + "_" + str(j) + " <= " + str(D[i] + M - t[j - 1]) + "\n\t")
            else:
                myfile.write(str(P[i]) + " x_" + str(k) + "_" + str(j) + " + ")

myfile.write("\nBinary\n\t")
for i in range(N):
    for j in range(1, 8):
        myfile.write("x_" + str(i) + "_" + str(j) + "\n\t")

myfile.write("\nEnd")

myfile.close()