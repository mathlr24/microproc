
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

To write our tests we wanted to do 4 different things. 

First, we wanted to show that all the instructions were well coded. To do this, we wrote an assembly code in which all the basic functions are used with positive and negative numbers. We also wanted to show on this test that we make sure that the maximum and minimum limits are not exceeded. Indeed, as we have a 32 bits processor, we have limits concerning the maximum and minimum numbers. The numbers are signed, so the maximum is 2^31 - 1 = 2.147.483.647 and -2^31 = 2.147.483.648. The most significant bit is used to give the sign.


## How to use our code 🛠️

We have chosen to organize our files by family and by language. That is why you will find 4 folders and 1 .txt file. 

The first folder is where the python assembler program is. The second is the folder where the VM called ISS is located. The third one is the storage. There you will find the binary files. The fourth folder is where the test codes are. Finally, the last folder will be the executive file.

Here is a picture of the folder you will have. 

<img width="538" alt="Capture d’écran 2023-03-11 à 23 18 29" src="https://user-images.githubusercontent.com/125263698/224513872-ebe09ca5-37d7-4fc7-b8e1-ee1a46ea1f84.png">

HOW TO USE THE LAUNCH_APP.SH FILE ? 

There is what you have in this file : 


```console
#!/bin/bash

#Compilation of the python code. The first parameter is the name of the python code, 
#then the name of the assembly code to be tested and finally the .bin file where to write the instructions. 
python3 assembler_code/translator.py tests_codes/assembleur.txt storage/fichier_traduit.bin

#Compilation of the VM in C 
gcc -o VM_in_c/ISS VM_in_c/ISS.c

#Execution of the VM. The first parameter is the name of the VM executable. The second is the name 
#of the .bin file with instructions and the last is the .bin file with data.
./VM_in_c/ISS storage/fichier_traduit.bin storage/data.bin
```

First you have the line to compile and execute the python file. After that you have the line to compile the C program and to finish you have the line to execute the C file. 

You can modify the assembler code called "tests_codes/assembleur.txt" to change the test code. 



