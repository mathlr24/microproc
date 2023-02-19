#include <stdio.h>

# define NUM_REGS 32
# define temps_horloge 1
int regs[ NUM_REGS ];

// Attention, il faut faire mettre un temps d execution pour les différntes instruction (1 cycle pour add, 1 pour mult, 100 pour load, ...)
// Avec la façon actuelle de faire le code, il va suffir que rajouter un delay dans chaque fonction. 
// Ou bien avec la fonction sleep. 
// On peut définir un temps d'horloge avec le # define du début et faire en fonction. 



int prog[] = { 0x9c00043, 0x9c00043, 0x9c00043, 0x0000000 };//Lire les instructions qui arrivent en entrée (Les mettres en 32bits pour tester)
int data[] = {15, 74, 56, 1, 0, 3, 4, 4, 5, 5};
int pc = 0;
int clock_rate = 0;

int fetch(){
    return prog[ pc++ ];
}


void set_regs(){
    for (int i=0; i<31; i++){
        regs[i] = i;
    }
    return 0;
}

void view_regs(){
    for (int i=0; i<31; i++){
        printf("R%d : %d  ", i, regs[i]);
    }
    return 0;
}


int codeop = 0;
int Ralpha = 0;
int immo = 0;
int o=0;
int Rbeta = 0;

void decode(int mot) {

     codeop = (mot & 0xF8000000) >> 27;
     Ralpha = (mot & 0x07C00000) >> 22;
     immo = (mot & 0x00200000) >> 21;
     o=0;
    if (immo == 1)
    {
         o = (mot & 0x001FFFE0) >> 5;
    }
    else {
         o = (mot & 0x000003E0) >> 5;
    }
    Rbeta = mot & 0x0000001F;
    printf("La valeur de mon codeop est : %d\n", codeop);
    printf("La valeur de mon Ralpha est :%d \n", Ralpha);
    printf("La valeur de mon immo est : %d\n", immo);
    printf("La valeur de mon o est : %d\n", o);
    printf("La valeur de mon Rbeta est :%d \n", Rbeta);
}

int running = 1;

void evaluate(){
    switch (codeop) {
        case 0:                 // HALT     We stop the program
            printf("HALT \n");
            running = 0;
            break;

                    //------------------------------------------------//
                    //----------------                 ---------------//
                    //--------------- BASICS FONCTIONS ---------------//
                    //----------------                 ---------------//
                    //------------------------------------------------//


        case 1:                 // ADD      We do an addition 
            if (immo == 1){
                regs[Rbeta] = regs[Ralpha] + o;
                printf("Addition : R%d and %d\n", regs[Ralpha], o);
            }

            else {
                regs[Rbeta] = regs[Ralpha] + regs[o];
                printf("Addition : R%d and R%d\n", regs[Ralpha], o);
            }
            clock_rate++;
            break;
            
        case 2:                 // Sub      We do a subtraction 
            if (immo == 1){
                regs[Rbeta] = regs[Ralpha] - o;
                printf("Subtraction : R%d and %d\n", regs[Ralpha], o);
            }
            else {
                regs[Rbeta] = regs[Ralpha] - regs[o];
                printf("Subtraction : R%d and R%d\n", regs[Ralpha], o);
            }
            clock_rate++;
            break;

        case 3:                // Mul      We do a multiplication
            if (immo == 1){
                regs[Rbeta] = regs[Ralpha] * o;
                printf("Multiplication : R%d and %d\n", regs[Ralpha], o);
            }
            else {
                regs[Rbeta] = regs[Ralpha] * regs[o];
                printf("Multiplication : R%d and R%d\n", regs[Ralpha], o);
            }
            clock_rate+=2;
            break;

        case 4:                // Div      We do a division
            if (immo == 1){
                regs[Rbeta] = regs[Ralpha] / o;
                printf("Division : R%d and %d\n", regs[Ralpha], o);
            }
            else {
                regs[Rbeta] = regs[Ralpha] / regs[o];
                printf("Division : R%d and R%d\n", regs[Ralpha], o);
            }
            clock_rate+=2;
            break;

        case 5:                // And      We do the AND gate
            if (immo == 1){
                regs[Rbeta] = regs[Ralpha] & o;
                printf("And gate : R%d and %d\n", regs[Ralpha], o);
            }
            else {
                regs[Rbeta] = regs[Ralpha] & regs[o];
                printf("And gate : R%d and R%d\n", regs[Ralpha], o);
            }
            clock_rate++;
            break;

        case 6:                // Or      We do the OR gate
            if (immo == 1){
                regs[Rbeta] = regs[Ralpha] | o;
                printf("Or gate : R%d and %d\n", regs[Ralpha], o);
            }
            else {
                regs[Rbeta] = regs[Ralpha] | regs[o];
                printf("Or gate : R%d and R%d\n", regs[Ralpha], o);
            }
            clock_rate++;
            break;

        case 7:                // exclusive OR      We do an exclusive OR gate
            if (immo == 1){
                regs[Rbeta] = regs[Ralpha] ^ o;
                printf("Exclusive Or : R%d and %d\n", regs[Ralpha], o);
            }
            else {
                regs[Rbeta] = regs[Ralpha] ^ regs[o];
                printf("Exclusive Or : R%d and R%d\n", regs[Ralpha], o);
            }
            clock_rate++;
            break;

        case 8:                // shl      We do a left shift
            if (immo == 1){
                regs[Rbeta] = regs[Ralpha] << o;
                printf("Left shift : R%d and %d\n", regs[Ralpha], o);
            }
            else {
                regs[Rbeta] = regs[Ralpha] << regs[o];
                printf("Left shift : R%d and R%d\n", regs[Ralpha], o);
            }
            clock_rate++;
            break;

        case 9:                // shr      We do a right shift
            if (immo == 1){
                regs[Rbeta] = regs[Ralpha] >> o;
                printf("Right shift : R%d and %d\n", regs[Ralpha], o);
            }
            else {
                regs[Rbeta] = regs[Ralpha] >> regs[o];
                printf("Right shift : R%d and R%d\n", regs[Ralpha], o);
            }
            clock_rate++;
            break;
                    //-------------------------------------------------------//
                    //----------------                        ---------------//
                    //--------------- LOWER / EQUAL FONCTIONS ---------------//
                    //----------------                        ---------------//
                    //-------------------------------------------------------//
                    

        case 10:                // slt      We look for 'set lower than'
            if (immo == 1){
                regs[Rbeta] = (regs[Ralpha] < o) ? 1 : 0;
                printf("Set lower than : R%d and %d\n", regs[Ralpha], o);
            }
            else {
                regs[Rbeta] = (regs[Ralpha] < regs[o]) ? 1 : 0;
                printf("Set lower than : R%d and R%d\n", regs[Ralpha], o);
            }
            clock_rate++;
            break;
        
        case 11:                // sle      We look for 'set lower equal'
            if (immo == 1){
                regs[Rbeta] = (regs[Ralpha] <= o) ? 1 : 0;
                printf("Set lower equal : R%d and %d\n", regs[Ralpha], o);
            }
            else {
                regs[Rbeta] = (regs[Ralpha] <= regs[o]) ? 1 : 0;
                printf("Set lower equal : R%d and R%d\n", regs[Ralpha], o);
            }
            clock_rate++;
            break;

        case 11:                // seq      We look for 'set equal'
            if (immo == 1){
                regs[Rbeta] = (regs[Ralpha] == o) ? 1 : 0;
                printf("Set equal : R%d and %d\n", regs[Ralpha], o);
            }
            else {
                regs[Rbeta] = (regs[Ralpha] == regs[o]) ? 1 : 0;
                printf("Set equal : R%d and R%d\n", regs[Ralpha], o);
            }
            clock_rate++;
            break;


                    //--------------------------------------------------------//
                    //----------------                         ---------------//
                    //--------------- LOAD and STORE FONCTIONS ---------------//
                    //----------------                         ---------------//
                    //--------------------------------------------------------//
        

        case 117 :                //LOAD      We load the data in the reg    
            printf("LOAD : \n");
            //regs[]
            break;
        


    }

}

void run(){
    view_regs();
    while (running)
    {
        int instr = fetch();
        decode(instr);
        evaluate();
    }
    view_regs();
    return 0;
}

int main() {
    run();
    return 0;
}
