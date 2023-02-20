#Fonction de conversion décimal -> binaire
def decToBin(decVal,nbBit): return (lambda x : ''.join(reversed([str((x >> i) & 1) for i in range(nbBit)])))(decVal)


def output_hex_instructions(hexaIDlist, hexInstructions, fileName):

	outputFile = open(fileName, 'w')
	for i in range(len(hexInstructions)):
		outputFile.write(hexaIDlist[i]+' '+hexInstructions[i] + '\n')

#Liste des keyword possibles
operandList={"add":1,"sub":2,"mul":3,"div":4,
             "and":5,"or":6,"xor":7,
             "shl":8,"shr":9,"slt":10,"sle":11,"seq":12,
             "load":13,"store":14,"jmp":15,
             "braz":16,"branz":17,"scall":18,
             "stop":0}

#Lecture du code ASM (voir schéma sur moodle)
with open("data.txt",'r') as instruFile: instruData=instruFile.read().split("\n")

labelList,posList,hexaList=[],[],[]

position=0
#Lecture de chaque ligne
for data in instruData:
    if ':' in data: #label détecté
        currentLabel=data.split(':')[0].replace(' ','')
        data=data[data.index(':')+1:]
        if '#' in currentLabel: continue #Le label est un commentaire : on skip
        labelList.append(currentLabel)
        posList.append(position)

    if len(data)==0: continue #Pas de donnée : on skip
    while data[0]==' ' and len(data)>1: data=data[1:]
    if not data.split(' ')[0] in operandList: continue #Pas de keyword : on skip

    operand=data.split(' ')[0]

    if operand=="stop": #Traitement cas particulier
        hexaList.append("0x00000000")
        position+=1
        continue

    data=data.split(operand)[1]
    data=data.replace(' ','') #On supprime les espaces de la donnée
    if '#' in data: data=data[:data.index('#')] #On supprime les commentaires de la donnée

    values=data.split(",")

    if len(values)==2: #Si deux paramètres trouvés

        if not values[1][0]=='r' or not values[1][1:].isdigit(): #Si l'un des deux paramètres est un label
            val0,val1,val2=values[0],"0",'r'+str(posList[labelList.index(values[1])])

        else: val0,val1,val2="r0",values[0],values[1] #Sinon, traité comme un registre

    else: val0,val1,val2=values[0],values[1],values[2] #Si trois paramètres trouvés

    b0 = operandList.get(operand,0) #5 premiers bits : opérande
    b1 = int(val0.split('r')[1]) #5 bits suivant : premier registre
    b2 = 0 #Bit suivant : par défaut à 0, mis à 1 si valeur immédiate

    if 'r' in val1: b3=int(val1.split('r')[1]) #5 bits suivants : traités comme deuxième registre
    else:
        if len(values)==3: b2=1
        b3=int(val1) #5 bits suivants : traités comme valeur immédiate

    b4 = int(val2.split('r')[1]) #5 bits suivants : troisième registre

    #Assemblage des différentes parties du code binaire
    codeop=decToBin(b0,5)
    Ralpha=decToBin(b1,5)
    imm=decToBin(b2,1)
    val=decToBin(b3,16)
    Rbeta=decToBin(b4,5)

    #Code complet final + conversion en hexa
    fullCode = codeop+Ralpha+imm+val+Rbeta
    hexaCode = hex(int(fullCode,2))
    while len(hexaCode)<10: hexaCode="0x"+"0"+hexaCode[2:]

    #Ligne ajoutée avec succès
    hexaList.append(hexaCode)
    position+=1



#Affichage des valeurs finales (contenues dans hexaList) :
decVal=0
hexaIDlist=[]
for hexa in hexaList:
    hexaID=hex(decVal)
    while len(hexaID)<10: hexaID="0x"+"0"+hexaID[2:]
    print(hexaID,hexa)
    hexaIDlist.append(hexaID)
    decVal+=1


outputFileName = 'hexInstructions.txt'
output_hex_instructions(hexaIDlist,hexaList, outputFileName)
