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

int fetch(){
    return prog[ pc++ ];
}


int codeop = 0;
int Ralpha = 0;
int immo = 0;
int o=0;

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
    int Rbeta = mot & 0x0000001F;
    printf("La valeur de mon codeop est : %d", codeop);
    printf("La valeur de mon Ralpha est :%d ", Ralpha);
    printf("La valeur de mon immo est : %d", immo);
    printf("La valeur de mon o est : %d", o);
    printf("La valeur de mon Rbeta est :%d ", Rbeta);
}

int running = 1;

void evaluate(){
    switch (codeop) {
        case 0:                 // HALT     We stop the program
            printf("HALT \n");
            running = 0;
            break;
        case 1:                 // ADD      We do an addition 
            printf("ADD :\n");
            if (immo == 1){
                regs[Rbeta] = regs[Ralpha] + o;
            }
            else regs[Rbeta] = regs[Ralpha] + regs[o];
            break;
        case 2 :                //LOAD      We load the data in the reg    
            printf("LOAD : \n");
            regs[]


    }

}

int main() {
    for (int i=0; i<31; i++){
        printf("R%d : %d\n", i, regs[i]);
    }
    return 0;
}
