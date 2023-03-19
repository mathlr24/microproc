#Translator from assmbler to bin 

import sys

if len(sys.argv) > 1:
    inputFileName = sys.argv[1]
    outputFileName = sys.argv[2]
    
def output_hex_instructions(hexaIDlist, hexInstructions, fileName):
    outputFile = open(fileName, 'w')
    for i in range(len(hexInstructions)):
        outputFile.write(hexaIDlist[i] + ' ' + hexInstructions[i] + '\n')
    
    
#Decimal -> binary conversion function
def decToBin(decVal,nbBit): return (lambda x : ''.join(reversed([str((x >> i) & 1) for i in range(nbBit)])))(decVal)

#List of possible instructions
operandList={"add":1,"sub":2,"mul":3,"div":4,
             "and":5,"or":6,"xor":7,
             "shl":8,"shr":9,"slt":10,"sle":11,"seq":12,
             "load":13,"store":14,"jmp":15,
             "braz":16,"branz":17,"scall":18,
             "stop":0}

#Reading the ASM code
with open(inputFileName,'r') as instruFile: instruData=instruFile.read().split("\n")


position=0
labelList,posList=[],[]
for i in range(len(instruData)):
    data=instruData[i]

    if "#" in data: data=data.split("#")[0] #Si commentaire : on prend tout avant le marqueur
    instruData[i] = data

    #DETECTION OF LABEL
    if ':' in data: #label detected
        currentLabel=data.split(':')[0].replace(' ','') #Removal of all spaces before the marker
        if '#' in currentLabel: break #Remove of the labels
        labelList.append(currentLabel)
        posList.append(position)
        data=data.split(":")[1] #Take the instruction after the label if it exists
        instruData[i]=data

    if len(data)==0: continue #Take the instruction after the label if it exists

    #DETECTION OF INSTRUCTION
    while data[0]==" ": #Deletion of each space before the first character
        data=data[1:]
        if len(data)==0: break
    instruData[i]=data
    if len(data)<=1: continue #If no word found: we go to the next one
    if data.split(' ')[0] in operandList: position+=1 #Instruction found: one line is counted

#for i in range(len(labelList)): print(labelList[i],"-",posList[i])     # It is a helper that displays the labels 

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
        n=decToBin(b1,27)
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
        b3 = int(values[1][1:])
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
        if len(values)<=2:
            valeur = 0
        else :
            valeur = int(values[2][1:])
        b4=valeur #Third argument always a register

        Ralpha,imm,o,Rbeta=decToBin(b1,5),decToBin(b2,1),decToBin(b3,16),decToBin(b4,5)
        fullCode=codeop+Ralpha+imm+o+Rbeta

    hexaCode = hex(int(fullCode,2))
    while len(hexaCode)<10: hexaCode="0x"+"0"+hexaCode[2:]


    hexaList.append(hexaCode)

#Display of final values (contained in hexaList) :
decVal=0
listHexaID=[]
for hexa in hexaList:
    hexaID=hex(decVal)
    while len(hexaID)<10: hexaID="0x"+"0"+hexaID[2:]
    listHexaID.append(hexaID)
    # print(hexaID,hexa)            #This line is a help. It allows to know the hexadecimal writing of the instructions 
    decVal+=1
    
    
output_hex_instructions(listHexaID, hexaList, outputFileName)

