#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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
# define nb_min -2147483648



int regs[ NUM_REGS ];
int prog[MAX_LIST_SIZE];
int nodeCount1 = 0;
int data[MAX_LIST_SIZE];
int iDdata[NUM_REGS];
int nodeCount2 = 0;
int view_registers = 1;
int random_number=0;

void insertMemoireInstr(int elementProg) {
    prog[nodeCount1] = elementProg;
    nodeCount1++;
}

void insertMemoireData(unsigned int elementIDdata, unsigned int elementData) {
    iDdata[nodeCount2] = elementIDdata;
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
        printf("0x%08x 0x%08x\n", iDdata[i], data[i]);
    }
}

int error_number(long long int result){
    if (result > nb_max || result < nb_min){
        printf("The number is out of range\n");
        return 1;
    }
    else {
        return 0;
    }
}

int pc = 0;
long int clock_rate = 0;
int running = 1;
int nb_scall = 0;

int fetch(){
    return prog[ pc++ ];
}


void set_regs(){
	for (int i=0; i<32; i++){
        for(int j=0;j<32;j++){
	        if (i == iDdata[j]){
	            regs[i]=data[j];
	        }
        }
   }
}

void view_regs(int view_registers){
    if (view_registers == 1){
        for (int i=0; i<32; i++){
            printf("R%d : %d ", i, regs[i]);
        }
        printf("\n");
    }
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
                    //---------------          SCALL          ---------------//
                    //-------------------------------------------------------//
    else if (codeop == 16 || codeop == 17){
        Ralpha = (mot & 0x07C00000) >> 22;
        a = (mot & 0x003FFFFF);
    }
    else if (codeop == 18){
        a = (mot & 0x07FFFFFF);
    }
    
}


void evaluate(){
    long long int result_instr = 0;
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
                
                result_instr = (long long int)regs[Ralpha] + o;
                if (error_number(result_instr)){
                    printf("We can not do the addition\n");
                }
                else {
                    regs[Rbeta] = result_instr;
                    printf("Addition : R%d and %d in R%d\n", Ralpha, o, Rbeta);
                }
            }

            else {
                result_instr = (long long int)regs[Ralpha] + regs[o];
                if (error_number(result_instr)){
                    printf("We can not do the addition\n");
                    
                }
                else {
                    regs[Rbeta] = result_instr;
                    printf("Addition : R%d and R%d in R%d\n", Ralpha, o, Rbeta);
                }
            }
            clock_rate++;
            break;
            
        case SUB:                 // Sub      We do a subtraction
            if (immo == 1){
                result_instr = (long long int)regs[Ralpha] - o;
                if (error_number(result_instr)){
                    printf("We can not do the substraction\n");
                }
                else {
                    regs[Rbeta] = result_instr;
                    printf("Subtraction : R%d and %d in R%d\n", Ralpha, o, Rbeta);
                }
            }
            else {
                result_instr = (long long int)regs[Ralpha] - regs[o];
                if (error_number(result_instr)){
                    printf("We can not do the substraction\n");
                }
                else {
                    regs[Rbeta] = result_instr;
                    printf("Subtraction : R%d and R%d in R%d\n", Ralpha, o, Rbeta);
                }
            }
            clock_rate++;
            break;

        case MUL:                // Mul      We do a multiplication
            if (immo == 1){
                result_instr = (long long int)regs[Ralpha] * o;
                if (error_number(result_instr)){
                    printf("We can not do the multiplication.\n");
                }
                else {
                    regs[Rbeta] = result_instr;
                    printf("Multiplication : R%d and %d in R%d\n", Ralpha, o, Rbeta);
                }
                
            }
            else {
                result_instr = (long long int)regs[Ralpha] * regs[o];
                if (error_number(result_instr)){
                    printf("We can not do the multiplication.\n");
                }
                else {
                    regs[Rbeta] = result_instr;
                    printf("Multiplication : R%d and R%d in R%d\n", Ralpha, o, Rbeta);
                }            
            }
            clock_rate+=2;
            break;

        case DIV:                // Div      We do a division
            if (immo == 1){
                result_instr = (long long int)regs[Ralpha] / o;
                if (error_number(result_instr)){
                    printf("We can not do the division.\n");
                }
                else {
                    regs[Rbeta] = result_instr;
                    printf("Division : R%d by %d in R%d\n", Ralpha, o, Rbeta);
                }
            }
            else {
                result_instr = (long long int)regs[Ralpha] / regs[o];
                if (error_number(result_instr)){
                    printf("We can not do the division.\n");
                }
                else {
                    regs[Rbeta] = result_instr;
                    printf("Division : R%d by R%d in R%d\n", Ralpha, o, Rbeta);
                }
                
            }
            clock_rate+=2;
            break;

        case AND:                // And      We do the AND gate
            if (immo == 1){
                result_instr = (long long int)regs[Ralpha] & o;
                if (error_number(result_instr)){
                    printf("We can not do the and.\n");
                }
                else {
                    regs[Rbeta] = result_instr;
                    printf("And gate : R%d and %d in R%d\n", Ralpha, o, Rbeta);
                } 
            }
            else {
                result_instr = (long long int)regs[Ralpha] & regs[o];
                if (error_number(result_instr)){
                    printf("We can not do the and.\n");
                }
                else{
                    regs[Rbeta] = result_instr;
                    printf("And gate : R%d and R%d in R%d\n", Ralpha, o, Rbeta);
                }
                
            }
            clock_rate++;
            break;

        case OR:                // Or      We do the OR gate
            if (immo == 1){
                result_instr = (long long int)regs[Ralpha] | o;
                if (error_number(result_instr)){
                    printf("We can not do the or.\n");
                }
                else {
                    regs[Rbeta] = result_instr;
                    printf("Or gate : R%d and %d in R%d\n", Ralpha, o, Rbeta);
                }
                
            }
            else {
                result_instr = (long long int)regs[Ralpha] | regs[o];
                if (error_number(result_instr)){
                    printf("We can not do the or.\n");
                }
                else {
                    regs[Rbeta] = result_instr;
                    printf("Or gate : R%d and R%d in R%d\n", regs[Ralpha], o, Rbeta);
                }
                
            }
            clock_rate++;
            break;

        case XOR:                // exclusive OR      We do an exclusive OR gate
            if (immo == 1){
                result_instr = (long long int)regs[Ralpha] ^ o;
                if (error_number(result_instr)){
                    printf("We can not do the or.\n");
                }
                else{
                    regs[Rbeta] = result_instr;
                    printf("Exclusive Or (XOR): R%d and %d in R%d\n", Ralpha, o, Rbeta);
                }
                
            }
            else {
                result_instr = (long long int)regs[Ralpha] ^ regs[o];
                if (error_number(result_instr)){
                    printf("We can not do the or.\n");
                }
                else{
                    regs[Rbeta] = result_instr;
                    printf("Exclusive Or : R%d and R%d in R%d\n", Ralpha, o, Rbeta);
                }
                
            }
            clock_rate++;
            break;

        case SHL:                // shl      We do a left shift
            if (immo == 1){
                result_instr = (long long int )regs[Ralpha] << o;
                if (error_number(result_instr)){
                    printf("We can not do a shl.\n");
                }
                else{
                    regs[Rbeta] = result_instr;
                    printf("Left shift : R%d and %d in R%d\n", Ralpha, o, Rbeta);   
                }
                
            }
            else {
                result_instr = (long long int)regs[Ralpha] << regs[o];
                if (error_number(result_instr)){
                    printf("We can not do a shl.\n");
                }
                else {
                    regs[Rbeta] = result_instr;
                    printf("Left shift : R%d and R%d in R%d\n", Ralpha, o, Rbeta);
                }
                
            }
            clock_rate++;
            break;

        case SHR:                // shr      We do a right shift
            if (immo == 1){
                result_instr = (long long int)regs[Ralpha] >> o;
                if (error_number(result_instr)){
                    printf("We can not do a shr.\n");
                }
                else {
                    regs[Rbeta] = result_instr;
                    printf("Right shift : R%d and %d in R%d\n", Ralpha, o, Rbeta);
                }
                
            }
            else {
                result_instr = (long long int)regs[Ralpha] >> regs[o]; 
                if (error_number(result_instr)){
                    printf("We can not do a shl.\n");
                }
                else {
                    regs[Rbeta] = result_instr;
                printf("Right shift : R%d and R%d in R%d\n", Ralpha, o, Rbeta);
                }
                
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
                result_instr = ((long long int)regs[Ralpha] < o) ? 1 : 0;
                if (error_number(result_instr)){
                    printf("We can not do a slt.\n");
                }
                else {
                    regs[Rbeta] = result_instr;
                    printf("Set lower than : R%d and %d in R%d\n", Ralpha, o, Rbeta);
                }
                
            }
            else {
                result_instr = ((long long int)regs[Ralpha] < regs[o]) ? 1 : 0;
                if (error_number(result_instr)){
                    printf("We can not do a slt.\n");
                }
                else{
                    regs[Rbeta] = result_instr;
                printf("Set lower than : R%d and R%d in R%d\n", Ralpha, o, Rbeta);
                }
                
            }
            clock_rate+=2;
            break;
        
        case SLE:                // sle      We look for 'set lower equal'
            if (immo == 1){
                result_instr = ((long long int)regs[Ralpha] <= o) ? 1 : 0;
                if (error_number(result_instr)){
                    printf("We can not do a sle.\n");
                }
                else{
                    regs[Rbeta] = result_instr;
                    printf("Set lower equal : R%d and %d in R%d\n", Ralpha, o, Rbeta);
                }
                
            }
            else {
                result_instr = ((long long int)regs[Ralpha] <= regs[o]) ? 1 : 0;
                if (error_number(result_instr)){
                    printf("We can not do a sle.\n");
                }
                else{
                    regs[Rbeta] = result_instr;
                printf("Set lower equal : R%d and R%d in R%d\n", Ralpha, o, Rbeta);
                }
            
            }
            clock_rate+=2;
            break;

        case SEQ:                // seq      We look for 'set equal'
            if (immo == 1){
                result_instr = ((long long int)regs[Ralpha] == o) ? 1 : 0;
                if (error_number(result_instr)){
                    printf("We can not do a seq.\n");
                }
                else{
                    regs[Rbeta] = result_instr;
                    printf("Set equal : R%d and %d in R%d\n", Ralpha, o, Rbeta);
                }
                
            }
            else {
                result_instr = ((long long int)regs[Ralpha] == regs[o]) ? 1 : 0;
                if (error_number(result_instr)){
                    printf("We can not do a seq.\n");
                }
                else{
                    regs[Rbeta] = result_instr;
                printf("Set equal : R%d and R%d in R%d\n", Ralpha, o, Rbeta);
                }
                
            }
            clock_rate+=2;
            break;


                    //--------------------------------------------------------//
                    //----------------                         ---------------//
                    //--------------- LOAD and STORE FONCTIONS ---------------//
                    //----------------                         ---------------//
                    //--------------------------------------------------------//
        
        case LOAD:                // load
            if (immo == 1){
                result_instr = data[ o + regs[Ralpha]];
                if (result_instr > 31 || result_instr < 0){
                    printf("R%lld does not exist.\n", result_instr);
                }
                else {
                    regs[Rbeta] = data[ o + regs[Ralpha]];
                printf("LOAD : load of value %d in R%d\n", data[ o + regs[Ralpha]], Rbeta);
                }
                

            }
            else{
                result_instr = data[regs[o] + regs[Ralpha]];
                if (result_instr > 31 || result_instr < 0){
                    printf("R%lld does not exist.\n", result_instr);
                }
                else {
                    regs[Rbeta] = data[regs[o] + regs[Ralpha]];
                    printf("LOAD : load of value %d in R%d\n", data[ regs[o] + regs[Ralpha]], Rbeta);
                }
                
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
                if (regs[o] < 0 || regs[o] > MAX_LIST_SIZE){
                    printf("We can not jump on to this position because it is out of range.\n");
                }
                else{
                    pc = regs[o];
                    printf("JMP : jump from %d to %d\n", pc, regs[o]);
                }
                
            }
            else{
                regs[Rbeta] = pc;
                if (o < 0 || o > MAX_LIST_SIZE){
                    printf("We can not jump on to this position because it is out of range.\n");
                }
                else{
                    pc = o;
                    printf("JMP : jump from %d to %d\n", pc, o);
                }
            }
            clock_rate+=2;
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
            clock_rate+=2;
            break;
        case SCALL:                // scall
            if (a==0){
                printf("Give a number : ");
                scanf("%d", &nb_scall);
                printf("Your value is : %d. \n", nb_scall);
                regs[1] = nb_scall;
                break;
            }
            if (a == 1){
                printf("SCALL 1, The value in R1 is : %d\n", regs[1]);
                break;
            }
            if (a == 15){
                printf("You have selected to show registers.\n");
                view_registers = 0;
            }
            if (a == 30){
                printf("You have selected to do not show registers.\n");
                view_registers = 0;
            }
            if (a==75){
                // view_registers = 0;
                srand(time(NULL));
                printf("Welcome on the game give a number.\n");
                printf("The goal of the game is to find a random number between 0 and 75. Simple no? \n");
                printf("Let's go.\n");
                random_number = rand() % 76;;
                regs[2] = random_number;
            }
            if (a==76){
                printf("Bravo you found the right number.\n");
            }
            else{
                printf("This value : %d is not recognized. \n", a);
                break;
            }
            clock_rate+=2;
            break;
       

    }

}
void begging(){
    printf("/------------------------------/\n");
    printf("/------------------------------/\n");
    printf("/------Launch of the vm -------/\n");
    printf("/------------------------------/\n");
    printf("/------------------------------/\n");
    }

void run(){
    begging();
    clock_t debut, fin;             // Variables pour compter le nombres de millions d'execution par seconde. 
    double duree;
    debut = clock();
    view_regs(view_registers);
    set_regs();
    view_regs(view_registers);
    while (running)
    {
        int instr = fetch();
        decode(instr);
        evaluate();
        view_regs(view_registers);
    }
    fin = clock();
    duree = (double)(fin - debut) / CLOCKS_PER_SEC;
    double ops_par_sec = (double)clock_rate / duree; // Calcule les opérations par seconde
    printf("Le programme a pris %.2f secondes et a effectue %ld operations.\n", duree, clock_rate);
    printf("Number of clock_rate : %.2f\n", ops_par_sec);
}


void insertionMemoire(FILE *fp1, FILE *fp2) {
    int instr;
    int count = 0;
     char line[100];
    while (fscanf(fp1, "%*s %x", &instr) == 1 && count < MAX_LIST_SIZE) {
        insertMemoireInstr(instr);
        count++;
    }
    
    while (fgets(line, sizeof(line), fp2) != NULL && count < MAX_LIST_SIZE) {
        int identifiantData;
        int valueData;
        if (sscanf(line, "0x%08x 0x%08x", &identifiantData, &valueData) == 2) { 
            insertMemoireData(identifiantData,valueData);
            count++;
        }
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
