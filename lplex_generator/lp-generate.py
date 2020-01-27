#Modifiable
N = 5                               #Nb de tâche    
P = [1, 2, 3, 2, 3]       #Duree de chaque tâche
D = [2, 3, 4, 4, 5]       #Data limite de chaque tâche
T = [4, 3, 5, 5, 5, 6]        #Indisponibilité sur les 3 machines (indice 0, 1 et 2 début de l'indisponibilité)

#PAS TOUCHER
M = 1000                            #Constance pour l'inégalité
t = [0, 0, 0, T[3], T[4], T[5]]     #Variables utilisé dans l'écriture des contraintes

#Nom du fichier ou est sotcké le fichier
filename = "problem2.lp"
myfile = open(filename, 'w')

#Type du problème
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