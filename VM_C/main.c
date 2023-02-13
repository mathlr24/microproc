#include <stdio.h>

# define NUM_REGS 32
int regs[ NUM_REGS ];

// Attention, il faut faire mettre un temps d execution pour les différntes instruction (1 cycle pour add, 1 pour mult, 100 pour load, ...)
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
    printf("La valeur de mon codeop est : ", codeop);
    printf("La valeur de mon Ralpha est : ", Ralpha);
    printf("La valeur de mon immo est : ", immo);
    printf("La valeur de mon o est : ", o);
    printf("La valeur de mon Rbeta est : ", Rbeta);
}

int running = 1;

void evaluate(){
    switch (codeop) {
        case 0:
            printf("halt\n");
            running = 0;
            break;
        case 1:
            printf("ADD\n");



    }

}

int main() {
    for (int i=0; i<31; i++){
        printf("%d\n", regs[i]);
    }
    return 0;
}
