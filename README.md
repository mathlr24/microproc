
# Digital architectures 

You will find in this folder our code for the digital architectures course.


## 🚀 About the devs
We are 2 students from ENSTA_Bretagne an engineering school in France. We are doing our studies in the field of embedded systems. 
We are currently in the second year of our engineering school. 
As part of the digital architecture course we had to develop 2 differents programs.

## The purpose of the project 
As you can see on this diagram our project is about making 2 differents codes. 

# Digital architectures 
![purpose_of_the_project](https://user-images.githubusercontent.com/125263698/224510912-955659fb-e3f1-49f3-8d70-8ab5641d3888.png)

You will find in this folder our code for the digital architectures course.

The First one is called "Assembler". The aim of this code is to transform an input file written in assembler in a binary file where you will have all instructions written in hexadecimal. In this this code you will find different parts which aims to read the assembler code and to decode it. We have codded 20 different instructions. You can find them bellow. 

Here are the basics functions : 
![image2](https://user-images.githubusercontent.com/125263698/224511276-c6e9362f-ebcf-460d-aef0-777b938ee5a9.png)

Here are 3 instructions for making loops : 

![image3](https://user-images.githubusercontent.com/125263698/224511277-c4565f5f-0223-4925-bbc7-4ff685495ed0.png)

Here are the scall function which is used to interact with the user and the stop function to end the program : 

![image4](https://user-images.githubusercontent.com/125263698/224511278-8f476641-614d-4951-bb2b-aa30ca3d9cf7.png)

We will more describe this program in a following part. 

The second code is called "VM". Indeed, this code simulates a virtual machine. The purpose of this code is to take the binary code and execute all the different instructions until the end. The project must also provide information about the instructions. Of course, it must give back all the results of the instructions, but it must also give back the performance of the code.

The first part of this code is to decode all the instructions. They are given on 32 bits but, on them, there is a lot of information that we have to decode. Here is the decoding scheme of these instructions.

![image7](https://user-images.githubusercontent.com/125263698/224511662-dc1c5421-9f48-4ad4-999d-f803331d4e90.png)

This virtual machine is programmed on 32 bits. So we have 32 registers. But depending on what we want to do, this may not be enough.

That is why we introduced a file named data. This file is used to stock all the datas that we don't need at the moment. 

Here is a diagram of what we wanted to simulate. 

![assembler code (1)](https://user-images.githubusercontent.com/125263698/224512144-3921d6fa-396e-4319-bb85-e9abe96faeae.png)


In the middle is the processor. This is the centerpiece of your machine. Here you will find 32 registers to store the data. Next to it, on the right side, you have the data, this part is called the data memory. In reality, this is a hard drive or SSD. That's why it takes a long time to store and load the data. Physically, this part is a few centimeters away from the process. Finally, on the left side we have the instructions. These are located in the memory of the program. This model is called the Harvard model.

Just like the assembly program, we will detail this program in a next part.







## Tests
As any program, our code needed to be tested. That is why we decides to do 4 differents tests. The are all availables in the folder "Tests". 

To write our tests we wanted to do 6 different things. 

<img width="791" alt="Capture d’écran 2023-03-19 à 22 22 22" src="https://user-images.githubusercontent.com/125263698/226210479-19efd7df-923b-40ca-9b09-812e083cec00.png">


First, we wanted to show that all the instructions were well coded. To do this, we wrote an assembly code in which all the basic functions are used with positive and negative numbers. We also wanted to show on this test that we make sure that the maximum and minimum limits are not exceeded. Indeed, as we have a 32 bits processor, we have limits concerning the maximum and minimum numbers. The numbers are signed, so the maximum is 2^31 - 1 = 2.147.483.647 and -2^31 = 2.147.483.648. The most significant bit is used to give the sign. This code uses launch_all.sh. 

The second : launch_current.sh is the program that takes care of launching the assembler file. It can allow you to put the code of your choice. Be careful, you must write your comments with a # and write your instructions in lower case. 

The third : launch_fibo.sh is a program that launches the fibonacci sequence. It can be used until the 46th iteration. After that, the values are not representable on 32 bits in signed. F(0) and F(1) are stored in the file data_suite.bin.

The fourth : launch_MIPS.sh is a program that launches the MIPS calculation. (Million operations per second). To get the most accurate result you can comment out the begin function at line 913 of the .c code. 

The fifth one: launch_number.sh is a game where you have to guess a randomly generated number between 0 and 75. 

The sixth: launch_petits_chevaux is a game of small horses. We don't have time to finalize it completely but it is still functional. Indeed, we programmed the game for only 1 player and we did not optimize the display of the game (the position of the pawn is indicated by 1 instead of X).

The seventh: launch_syracuse.sh is a program from the syracuse suite.




## How to use our code 🛠️

We have chosen to organize our files by family and by language. That is why you will find 5 folders. 

The first folder is where the python assembler program is. The second is the folder where the VM called ISS is located. The third one is the storage. There you will find the binary files. The fourth folder is where the test codes are. Finally, the last folder will be the executive files.

Here is a picture of the folder you will have. 

<img width="547" alt="Capture d’écran 2023-03-19 à 22 15 32" src="https://user-images.githubusercontent.com/125263698/226210152-8d72b4a3-e6d7-4088-909d-7f872706ffe3.png">

Here is the folder with all the executives codes.

<img width="798" alt="Capture d’écran 2023-03-19 à 22 16 05" src="https://user-images.githubusercontent.com/125263698/226210165-0bfd156f-0829-4ccf-9617-4726574ab4a1.png">


HOW TO USE one LAUNCH_[..].SH FILE ? 

There is what you could have in one of those files : 


```console
#!/bin/bash
cd ..
python3 assembler_code/translator.py tests_codes/number.txt storage/traduced_file.bin
gcc -o VM_in_c/ISS VM_in_c/ISS.c
./VM_in_c/ISS storage/traduced_file.bin storage/data.bin

#Script pour lancer l'ensemble du programme.

```

First you have the line to compile and execute the python file. After that you have the line to compile the C program and to finish you have the line to execute the C file. 

You can modify the assembler code called "tests_codes/number.txt" to change the test code.

You can also change the input data by changing the file storage/data.bin.
However, the advantage of having several .sh files is to be able to launch each program with the corresponding memory independently. 


## How to change the input data? 👨🏽‍🎨

If you want to, you can change the input data. On the folder "storage", you have the file data.bin. This file, has 2 parts. As you can see on this image : 

<img width="162" alt="Capture d’écran 2023-03-19 à 22 13 58" src="https://user-images.githubusercontent.com/125263698/226210084-2ab6d0de-b75e-49e7-b8f6-da7e9fd2efdb.png">



The left part has all the adresses. Here can write in hexadecimal the number of the register where you want to put the register. Then, the data that you want to put on your register is one the right side. You can write them in hexadecimal. 



## Assembler program description 📝

Based on the code provided, the goal of the program seems to be to read an assembly language code from a file, parse it, convert each instruction into its corresponding hexadecimal code, and then output the hexadecimal code into another file. The program also  handle the conversion of different types of operands  into their binary representations before converting them into hexadecimal codes.

The first part of the code reads the command line arguments to get the input and output file names. The output_hex_instructions function writes the machine code to the output file.

```python
def output_hex_instructions(hexaIDlist, hexInstructions, fileName):
    outputFile = open(fileName, 'w')
    for i in range(len(hexInstructions)):
        outputFile.write(hexaIDlist[i] + ' ' + hexInstructions[i] + '\n')
```

The decToBin function converts a decimal value to a binary string with the specified number of bits.
```python
#Decimal -> binary conversion function
def decToBin(decVal,nbBit): return (lambda x : ''.join(reversed([str((x >> i) & 1) for i in range(nbBit)])))(decVal)
```

The operandList dictionary maps each keyword in the assembly language to a unique integer opcode.

```python
#List of possible instructions
operandList={"add":1,"sub":2,"mul":3,"div":4,
             "and":5,"or":6,"xor":7,
             "shl":8,"shr":9,"slt":10,"sle":11,"seq":12,
             "load":13,"store":14,"jmp":15,
             "braz":16,"branz":17,"scall":18,
             "stop":0}
```

The code then reads the input file line by line, removes comments and detects labels. It stores the label names and their positions in separate lists.

```python
#Reading the ASM code
with open(inputFileName,'r') as instruFile: instruData=instruFile.read().split("\n")
```

It then iterates over each instruction in the assembly code and converts it to machine code using different conversion logic for each instruction type. The resulting machine code is appended to a list hexaList.

```python
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

    if len(data)==0: continue 

    #DETECTION OF INSTRUCTION
    while data[0]==" ": #Deletion of each space before the first character
        data=data[1:]
        if len(data)==0: break
    instruData[i]=data
    if len(data)<=1: continue #If no word found: we go to the next one
    if data.split(' ')[0] in operandList: position+=1 #Instruction found: one line is counted

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
```        


Finally, the resulting machine code is written to the output file using the output_hex_instructions function. The format of the machine code seems to be a fixed-length binary string with a 5-bit opcode followed by a variable number of arguments encoded in binary.

``` python
#Display of final values (contained in hexaList) :
decVal=0
listHexaID=[]
for hexa in hexaList:
    hexaID=hex(decVal)
    while len(hexaID)<10: hexaID="0x"+"0"+hexaID[2:]
    listHexaID.append(hexaID)
    print(hexaID,hexa)
    decVal+=1
    
    
output_hex_instructions(listHexaID, hexaList, outputFileName)
```

## VM in C program description 🔖
This is the part where we will describe the C code. 

All the code has been commented out, so we won't describe every line. The goal here is to take the main functions and explain what they do.

First of all, as we said before, the first thing to do is read the file "traduced_file". It is in this file, that we have all the binary instructions. 


JE TE LAISSE EXPLIQUER CETTE PARTIE JE NE LA COMPREND PAS BIEN. 
L'intérêt à mon sens c'est simplement de dire ce que tu fais grossièrement pour lire les instructions et les mettre dans le tableau prog[]. 


Once the instructions are arranged in the table, we must now decode them. To do that, we have used the diagram proposed by the teacher. 

Not all the instrcutions have the same way be decoded. That is why we divided them. The only one thing that is always the same is the codeop. Indeed, this 5 bits are used to give the function that we should use after (add, sub, load, ...). 

To retrieve this data, the first thing to do is to put all the bits not considering by codeop at 0. To do that we use a logical and with 0 for them. By doing it, no matter the value of the bit, x & 0 will always be equal to 0 in our case. For the bites of codeop we also do an logical and but with and. Like we can this on this table. 

![FOJNhRnXwAk9lei](https://user-images.githubusercontent.com/125263698/224515248-10de4c9b-daf4-430b-b37f-0b7e0d62bb31.png)

Now we have all the bite at 0 except the bite of the opcode. We can do a shift of 27 to the right to recover only the 5 bits of opcode. In the case of codeop we don't really need to put de 27 lasts bits to 0 but it is better to understand what we've done. 

Here is the code of the "decoding" function. We do the same reasoning as codeop for all other information with adaptations. 

```c
void decode(int mot) {

    codeop = (mot & 0xF8000000) >> 27;


                    //-----------------------------------------------//
                    //----------------                ---------------//
                    //--------------- NORMAL DECODING ---------------//
                    //----------------                ---------------//
                    //-----------------------------------------------//
                    //ADD SUB MUL DIV AND OR XOR SHL SHR SLT SLE SEQ //
                    //------------------ LOAD STORE -----------------//
                    //-----------------------------------------------//

    //We have to decode differently dipending on the opcode, we are testing the opcode to know the way to decode after

    if (codeop == 1 || codeop == 2 || codeop == 3 || codeop == 4 || codeop == 5 || codeop == 6 || codeop == 7 || codeop == 8 || codeop == 9 || codeop == 10 || codeop == 11 || codeop == 12 || codeop == 13 || codeop == 14){
        Ralpha = (mot & 0x07C00000) >> 22;
        immo = (mot & 0x00200000) >> 21;
        if (immo == 1)
        {
            o = (mot & 0x001FFFE0) >> 5;
        }
        else {
            o = (mot & 0x000003E0) >> 5;
        }
        Rbeta = mot & 0x0000001F;
    }
                        
                    //--------------------------------------------//
                    //---------------              ---------------//
                    //--------------- JMP DECODING ---------------//
                    //---------------              ---------------//
                    //--------------------------------------------//
    else if (codeop == 15)
    {
        Ralpha = (mot & 0x07C00000) >> 22;
        immo = (mot & 0x04000000) >> 26;
        o = (mot & 0x03FFFFE0) >> 5;
        Rbeta = mot & 0x0000001F;
    }
                    //-------------------------------------------------------//
                    //---------------                         ---------------//
                    //--------------- BRAZ AND BRANZ DECODING ---------------//
                    //---------------                         ---------------//
                    //-------------------------------------------------------//
    else if (codeop == 16 || codeop == 17){
        Ralpha = (mot & 0x07C00000) >> 22;
        a = (mot & 0x00aFFFFF);
    }
    
}
```

Now we have put all the instruction on a table. We have also decoded the first instruction. We can now apply it.
All the instructions have approximatly the same execution. That is why we wanted only to explain the function add. 

In the function add, in addtion to the codeop, we have the register alpha (the first data we want to add), the register beta (the register where we an to put the final result) and depending on whether we have an immediate number or a second register, we perform the appropriate addition.  
Here is the code : 


```c 
void evaluate(){
    switch (codeop) {
        case STOP:                 // HALT     We stop the program
            printf("HALT, end of the program\n");
            running = 0;
            break;

                    //------------------------------------------------//
                    //----------------                 ---------------//
                    //--------------- BASICS FONCTIONS ---------------//
                    //----------------                 ---------------//
                    //------------------------------------------------//


        case ADD:                 // ADD      We do an addition
            if (immo == 1){
                regs[Rbeta] = regs[Ralpha] + o;
                if (error_number(regs[Rbeta])){
                    regs[Rbeta] = regs[Ralpha] - o;
                    
                }
                else {
                    printf("Addition : R%d and %d in R%d\n", Ralpha, o, Rbeta);
                }
                clock_rate++;
            }

            else {
                regs[Rbeta] = regs[Ralpha] + o;
                if (error_number(regs[Rbeta])){
                    regs[Rbeta] = regs[Ralpha] - o;
                    
                }
                else {
                    printf("Addition : R%d and R%d in R%d\n", Ralpha, o, Rbeta);
                }
                clock_rate++;
            }
            
            break;
            }
```
In this code, you could have seen that we call a function named error_number. The purpose of this function is to always test if the value we calculated is always lower than the maximum or higher than the minimum we have set before. If the result of the fonction is not out of range we put the result on the register. However, if it is, we don't put it on and we show and error message to say that the numer is out of range. 

You may also have noticed that we have introduced a 'clock_rate' number. This number will be used at the end of the program to calculate the efficiency of our machine. 

Once the addtion is done, we can go to the next instruction and do this again and again until we are done. 

When we are done, we can now calculate de number of million operations per seconde. 

To do this, we have created at the begining a long int named clock_rate. At every instruction we increment it depending on the size of the task. Here is what we do : 

'add', 'sub', 'and', 'or', 'xor' count for one. 

'mul', 'div', 'shl', 'shr', 'slt', 'sle, 'seq' count for two. 

'jmp', 'braz', 'branz', 'scall' count for 10. 

'load', 'store' count for 100. 

When we are in the function 'run' that is the function to run the program, we use a counter of time to know how long it takes to do all the instructions. Here is the code of the function : 

```c
void run(){
    clock_t debut, fin;             // Variables pour compter le nombres de millions d'execution par seconde. 
    double duree;
    debut = clock();
    view_regs();
    set_regs();
    view_regs();
    while (running)
    {
        int instr = fetch();
        decode(instr);
        evaluate();
        view_regs();
    }
    fin = clock();
    duree = (double)(fin - debut) / CLOCKS_PER_SEC;
    double ops_par_sec = (double)clock_rate / duree; // Calcule les opérations par seconde
    printf("Le programme a pris %.2f secondes et a effectue %ld operations.\n", duree, clock_rate);
    printf("Number of clock_rate : %.2f\n", ops_par_sec);
}
```
At the end we just have to divide the nomber of operations by the time to know the number of operations per secondes. 

At the end, we show the registers and we end the program. 

This marks the end of the explanations of our programs. As mentioned earlier, our programs are commented and therefore you will find more information in this last one in order to understand even better the tasks we perform. 


## What can we learn from this project? 💼

This is the first time we had an as huge project of programming. Since the class hours were not enough, we had to learn to work efficiently on our project at home. In order to achieve our maximum on this project we tried to apply the agile method. We organized 20 minutes meetings 2 to 3 times a week in order to set objectives and to help each other on certain points. It was therefore a good exercise for us to prepare ourselves even better for the professional world that awaits us. 

Moreover, doing a collaborative project was a good excuse for us to learn how to use github. We had rarely had the opportunity to use this site before. It was therefore the opportunity to learn about this site and its use on the order line. 
We also tried to comment our changes on our codes in order to be able to prepare a new one to the world of work. 
We did not become experts of the platform, however we are now able to generate a git project, to add files, to delete them or even to modify them with the command lines in an easy way. 

Concerning the English language, we have chosen to write the whole readme in English. We are both French and our preferred language is not English. However, in addition to being able to collaborate on this project, the interest for us to realize this project on git was that it could be used as a showcase for a potential new job later. 

Therefore, we thought that using English could be a real plus for our project. Since we are both not completely bilingual, this also forced us to think in English about how to best explain our program and what we do in it. 

Now that we have covered everything, this is the end of our project. We hope you have enjoyed our work. We hope to be able to start projects of this scope again soon. 




