import sys

if len(sys.argv) > 1:
    inputFileName = sys.argv[1]
    outputFileName = sys.argv[2]
    
    
#Fonction de conversion décimal -> binaire
def decToBin(decVal,nbBit): return (lambda x : ''.join(reversed([str((x >> i) & 1) for i in range(nbBit)])))(decVal)

#Liste des keyword possibles
operandList={"add":1,"sub":2,"mul":3,"div":4,
             "and":5,"or":6,"xor":7,
             "shl":8,"shr":9,"slt":10,"sle":11,"seq":12,
             "load":13,"store":14,"jmp":15,
             "braz":16,"branz":17,"scall":18,
             "stop":0}

#Lecture du code ASM
with open(inputFileName,'r') as instruFile: instruData=instruFile.read().split("\n")

#Clean de chaque ligne et repérage de chaque label
position=0
labelList,posList=[],[]
for i in range(len(instruData)):
    data=instruData[i]

    if "#" in data: data=data.split("#")[0] #Si commentaire : on prend tout avant le marqueur
    instruData[i] = data

    #DETECTION DE LABEL
    if ':' in data: #label détecté
        currentLabel=data.split(':')[0].replace(' ','') #Suppression de tous les espaces avant le marqueur
        if '#' in currentLabel: break #Le label est un commentaire : on skip
        labelList.append(currentLabel)
        posList.append(position)
        data=data.split(":")[1] #On prend l'instruction après le label si existe
        instruData[i]=data

    if len(data)==0: continue #Si plus de donnée : tchao bye bye

    #DETECTION D'INSTRUCTION
    while data[0]==" ": #Suppression de chaque espace avant premier caractère
        data=data[1:]
        if len(data)==0: break
    instruData[i]=data
    if len(data)<=1: continue #Si aucun mot trouvé : on passe à la suivante
    if data.split(' ')[0] in operandList: position+=1 #Instruction trouvée : on compte une ligne

for i in range(len(labelList)): print(labelList[i],"-",posList[i])

instruData = [i for i in instruData if i!= ""] #Remove all empty lines remaining in the list

hexaList=[]
for data in instruData:

    operand = data.split(" ")[0]
    b0 = operandList.get(operand,0)
    codeop=decToBin(b0,5)

    args = data.replace(operand, "").replace(" ","")
    values=[]

    if operand != "stop": values = args.split(",")
    if operand == "stop": fullCode = decToBin(0,32)

    elif operand == "scall":
        #instr|            n
        #00000|000000000000000000000000000
        # b0  |            b1
        b1 = int(values[0])
        n=decToBin(b1,5),decToBin(b1,27)
        fullCode=codeop+n

    elif operand == "jmp":
        #instr|i|         o           | R
        #00000|0|000000000000000000000|00000
        # b0  |b1|        b2          | b3
        b1=1
        if values[0] in labelList: b2=posList[labelList.index(values[0])]
        elif values[0][0]!='r': b2=int(values[0])
        else:
            b2=int(values[0][1:])
            b1=0
        #b3 = int(values[1][1:])
        imm,o,R=decToBin(b1,1),decToBin(b2,21),decToBin(b3,5)
        fullCode=codeop+imm+o+R

    elif operand in ["braz","branz"]:
        #instr|  R  |        a
        #00000|00000|0000000000000000000000
        # b0  |  b1 |        b2
        b1 = int(values[0][1:])
        if values[1] in labelList: b2=posList[labelList.index(values[1])]
        else: b2=int(values[1])
        R,a=decToBin(b1,5),decToBin(b2,22)
        fullCode=codeop+R+a

    else:
        #instr|rAlph|i|       o        |rBeta
        #00000|00000|0|0000000000000000|00000
        # b0  | b1  |b2|      b3       | b4
        b1 = int(values[0][1:]) #First argument always a register
        if values[1][0].lower()=='r': #If second argument register : not immediate value
            b2=0
            b3=int(values[1][1:])
        else: #If second argument not register : immediate value
            b2=1
            b3=int(values[1])
        b4=int(values[2][1:]) #Third argument always a register

        Ralpha,imm,o,Rbeta=decToBin(b1,5),decToBin(b2,1),decToBin(b3,16),decToBin(b4,5)
        fullCode=codeop+Ralpha+imm+o+Rbeta

    hexaCode = hex(int(fullCode,2))
    while len(hexaCode)<10: hexaCode="0x"+"0"+hexaCode[2:]

    #Ligne ajoutée avec succès
    hexaList.append(hexaCode)

#Affichage des valeurs finales (contenues dans hexaList) :
decVal=0
for hexa in hexaList:
    hexaID=hex(decVal)
    while len(hexaID)<10: hexaID="0x"+"0"+hexaID[2:]
    print(hexaID,hexa)
    decVal+=1

with open(outputFileName,'w') as binaryFile:
    for i in range(len(hexaList)):
        binaryFile.write(hexaList[i])
        if i<len(hexaList)-1: binaryFile.write("\n")
