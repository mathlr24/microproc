#include <stdio.h>
#include <stdlib.h>

#define MAX_LIST_SIZE 1000

# define NUM_REGS 32
# define temps_horloge 1
# define STOP 0
# define ADD 1
# define SUB 2
# define MUL 3
# define DIV 4
# define AND 5
# define OR 6 
# define XOR 7
# define SHL 8
# define SHR 9
# define SLT 10 
# define SLE 11
# define SEQ 12
# define LOAD 13
# define STORE 14
# define JMP 15 
# define BRAZ 16
# define BRANZ 17
# define SCALL 18

# define nb_max 2147483647
# define nb_max -2147483648



int regs[ NUM_REGS ];
int prog[MAX_LIST_SIZE];
int nodeCount1 = 0;
int data[MAX_LIST_SIZE];
int nodeCount2 = 0;

void insertMemoireInstr(int elementProg) {
    prog[nodeCount1] = elementProg;
    nodeCount1++;
}

void insertMemoireData(int elementData) {
    data[nodeCount2] = elementData;
    nodeCount2++;
}

void affichageListeInstr() {
    for (int i = 0; i < nodeCount1; i++) {
        printf("0x%08x 0x%08x\n", i, prog[i]);
    }
}

void affichageListeData() {
    for (int i = 0; i < nodeCount2; i++) {
        printf("0x%08x 0x%08x\n", i, data[i]);
    }
}

void error_number(result){
    if (result > nb_max || result < nb_min){
        printf("The number is out of range\n");
    }
}

int pc = 0;
long int clock_rate = 0;
int running = 1;

int fetch(){
    return prog[ pc++ ];
}


void set_regs(){
    for (int i=0; i<32; i++){
        regs[i] = data[i];
    }
}

void view_regs(){
    for (int i=0; i<32; i++){
        printf("R%d : %d ", i, regs[i]);
    }
    printf("\n");
}


int codeop = 0;
int Ralpha = 0;
int immo = 0;
int o=0;
int Rbeta = 0;
int a =0;

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
                printf("Addition : R%d and %d in R%d\n", Ralpha, o, Rbeta);
            }

            else {
                regs[Rbeta] = regs[Ralpha] + regs[o];
                printf("Addition : R%d and R%d in R%d\n", Ralpha, o, Rbeta);
            }
            clock_rate++;
            break;
            
        case SUB:                 // Sub      We do a subtraction 
            if (immo == 1){
                regs[Rbeta] = regs[Ralpha] - o;
                printf("Subtraction : R%d and %d in R%d\n", Ralpha, o, Rbeta);
            }
            else {
                regs[Rbeta] = regs[Ralpha] - regs[o];
                printf("Subtraction : R%d and R%d in R%d\n", Ralpha, o, Rbeta);
            }
            clock_rate++;
            break;

        case MUL:                // Mul      We do a multiplication
            if (immo == 1){
                regs[Rbeta] = regs[Ralpha] * o;
                printf("Multiplication : R%d and %d in R%d\n", Ralpha, o, Rbeta);
            }
            else {
                regs[Rbeta] = regs[Ralpha] * regs[o];
                printf("Multiplication : R%d and R%d in R%d\n", Ralpha, o, Rbeta);
            }
            clock_rate+=2;
            break;

        case DIV:                // Div      We do a division
            if (immo == 1){
                regs[Rbeta] = regs[Ralpha] / o;
                printf("Division : R%d by %d in R%d\n", Ralpha, o, Rbeta);
            }
            else {
                regs[Rbeta] = regs[Ralpha] / regs[o];
                printf("Division : R%d by R%d in R%d\n", Ralpha, o, Rbeta);
            }
            clock_rate+=2;
            break;

        case AND:                // And      We do the AND gate
            if (immo == 1){
                regs[Rbeta] = regs[Ralpha] & o;
                printf("And gate : R%d and %d in R%d\n", Ralpha, o, Rbeta);
            }
            else {
                regs[Rbeta] = regs[Ralpha] & regs[o];
                printf("And gate : R%d and R%d in R%d\n", Ralpha, o, Rbeta);
            }
            clock_rate++;
            break;

        case OR:                // Or      We do the OR gate
            if (immo == 1){
                regs[Rbeta] = regs[Ralpha] | o;
                printf("Or gate : R%d and %d in R%d\n", Ralpha, o, Rbeta);
            }
            else {
                regs[Rbeta] = regs[Ralpha] | regs[o];
                printf("Or gate : R%d and R%d in R%d\n", regs[Ralpha], o, Rbeta);
            }
            clock_rate++;
            break;

        case XOR:                // exclusive OR      We do an exclusive OR gate
            if (immo == 1){
                regs[Rbeta] = regs[Ralpha] ^ o;
                printf("Exclusive Or (XOR): R%d and %d in R%d\n", Ralpha, o, Rbeta);
            }
            else {
                regs[Rbeta] = regs[Ralpha] ^ regs[o];
                printf("Exclusive Or : R%d and R%d in R%d\n", Ralpha, o, Rbeta);
            }
            clock_rate++;
            break;

        case SHL:                // shl      We do a left shift
            if (immo == 1){
                regs[Rbeta] = regs[Ralpha] << o;
                printf("Left shift : R%d and %d in R%d\n", Ralpha, o, Rbeta);
            }
            else {
                regs[Rbeta] = regs[Ralpha] << regs[o];
                printf("Left shift : R%d and R%d in R%d\n", Ralpha, o, Rbeta);
            }
            clock_rate++;
            break;

        case SHR:                // shr      We do a right shift
            if (immo == 1){
                regs[Rbeta] = regs[Ralpha] >> o;
                printf("Right shift : R%d and %d in R%d\n", Ralpha, o, Rbeta);
            }
            else {
                regs[Rbeta] = regs[Ralpha] >> regs[o];
                printf("Right shift : R%d and R%d in R%d\n", Ralpha, o, Rbeta);
            }
            clock_rate++;
            break;
                    //-------------------------------------------------------//
                    //----------------                        ---------------//
                    //--------------- LOWER / EQUAL FONCTIONS ---------------//
                    //----------------                        ---------------//
                    //-------------------------------------------------------//
                    

        case SLT:                // slt      We look for 'set lower than'
            if (immo == 1){
                regs[Rbeta] = (regs[Ralpha] < o) ? 1 : 0;
                printf("Set lower than : R%d and %d in R%d\n", Ralpha, o, Rbeta);
            }
            else {
                regs[Rbeta] = (regs[Ralpha] < regs[o]) ? 1 : 0;
                printf("Set lower than : R%d and R%d in R%d\n", Ralpha, o, Rbeta);
            }
            clock_rate++;
            break;
        
        case SLE:                // sle      We look for 'set lower equal'
            if (immo == 1){
                regs[Rbeta] = (regs[Ralpha] <= o) ? 1 : 0;
                printf("Set lower equal : R%d and %d in R%d\n", Ralpha, o, Rbeta);
            }
            else {
                regs[Rbeta] = (regs[Ralpha] <= regs[o]) ? 1 : 0;
                printf("Set lower equal : R%d and R%d in R%d\n", Ralpha, o, Rbeta);
            }
            clock_rate++;
            break;

        case SEQ:                // seq      We look for 'set equal'
            if (immo == 1){
                regs[Rbeta] = (regs[Ralpha] == o) ? 1 : 0;
                printf("Set equal : R%d and %d in R%d\n", Ralpha, o, Rbeta);
            }
            else {
                regs[Rbeta] = (regs[Ralpha] == regs[o]) ? 1 : 0;
                printf("Set equal : R%d and R%d in R%d\n", Ralpha, o, Rbeta);
            }
            clock_rate++;
            break;


                    //--------------------------------------------------------//
                    //----------------                         ---------------//
                    //--------------- LOAD and STORE FONCTIONS ---------------//
                    //----------------                         ---------------//
                    //--------------------------------------------------------//
        
        case LOAD:                // load
            if (immo == 1){
                regs[Rbeta] = data[ o + regs[Ralpha]];
                printf("LOAD : load of value %d in R%d\n", data[ o + regs[Ralpha]], Rbeta);

            }
            else{
                regs[Rbeta] = data[regs[o] + regs[Ralpha]];
                printf("LOAD : load of value %d in R%d\n", data[ regs[o] + regs[Ralpha]], Rbeta);
            }
            clock_rate+=100;
            break;
        case STORE:                // store
            if (immo == 1){
                data[o + regs[Ralpha]] = regs[Rbeta];
                printf("STORE : Store of value of R%d in memory case : %d\n",Rbeta, o + regs[Ralpha]);
            }
            else{
                data[regs[o] + regs[Ralpha]] = regs[Rbeta];
                printf("STORE : Store of value of R%d in memory case : %d\n",Rbeta, regs[o] + regs[Ralpha]);

            }
            clock_rate +=100;
            break;
            
        case JMP:                // jmp
            if (immo == 0){
                regs[Rbeta] = pc;
                pc = regs[o];
                printf("JMP : jump from %d to %d\n", pc, regs[o]);
            }
            else{
                regs[Rbeta] = pc;
                pc = o;
                printf("JMP : jump from %d to %d\n", pc, o);
            }
            break;

        case BRAZ:                // braz
            if (regs[Ralpha] == 0){
                pc = a;
                printf("BRAZ : braz to %d\n", a);
            }
            break;
        case BRANZ:                // branz
            if (regs[Ralpha] != 0){
                pc = a;
                printf("BRANZ : braz to %d\n", a);
            }
            break; 
        case SCALL:                // scall
            if (a==1){

            }
            if (a==0){
                printf("La veleur comprises dans R1 est : %d", regs[1]);
            }
            break;   
       

    }

}

void run(){
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
    view_regs();
    printf("Number of clock_rate : %ld", clock_rate);
}


void insertionMemoire(FILE *fp1, FILE *fp2){
    int instr;
    int count = 0;
    while (fscanf(fp1, "%*s %x", &instr) == 1 && count < MAX_LIST_SIZE) {
        insertMemoireInstr(instr);
        count++;
    }
    
    int data;
    count = 0;
    while (fscanf(fp2, "%*s %x", &data) == 1 && count < MAX_LIST_SIZE) {
        insertMemoireData(data);
        count++;
    }

}

void affichageMemoireStockee(){

    printf("Les instructions placées dans la mémoire de code sont:\n");
    affichageListeInstr();
    printf("Les datas placées dans la mémoire de données sont :\n");
    affichageListeData();

}






int main(int argc, char *argv[]) {

   
    if (argc != 3) {
        printf("Usage: %s <filename1> <filename2>\n", argv[0]);
        return 1;
    }

    char *filename1 = argv[1];
    FILE *fp1 = fopen(filename1, "r");
    if (fp1 == NULL) {
        printf("Error opening file %s\n", filename1);
        return 1;
    }

    char *filename2 = argv[2];
    FILE *fp2 = fopen(filename2, "r");
    if (fp2 == NULL) {
        printf("Error opening file %s\n", filename2);
        fclose(fp1);
        return 1;
    }
    
    insertionMemoire(fp1,fp2);
    affichageMemoireStockee();
    run();

    fclose(fp1);
    fclose(fp2);
    return 0;
}

