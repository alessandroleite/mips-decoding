#include <stdio.h>
#include <stdlib.h>


/**
 * Estrutura que representa uma palavra e suas partes de uma instru��o MIPS.
 */
typedef struct mips_word
{
    unsigned int opcode;
    unsigned int rd;
    unsigned int rs;
    unsigned int rt;
    unsigned int sa;    
	char *name;
}MipsWord;

/**
 * Estrutura que representa uma instru��o.
 */
typedef struct instruction
{
  unsigned int ri;
  unsigned int funct;
}Instruction;

/**
 * Opcodes de uma instru��o MIPS
 */
enum OPCODES
{
    LW=0x23,  LB=0x20,  LH=0x21,
    LHU=0x25, SW=0x2B,  SB=0x28,
    LUI=0x0F, BEQ=0x04, BNE=0x05,
    J=0x02,   JAL=0x08, FUN=0x00
};

/**
 * Fun��es do MIPS. Utilizada durante o ciclo de execu��o de uma instru��o MIPS.
 */
enum FUNCT
{
    ADD=0x20, ADDU=0x21, SUB=0x22,
    MUL=0x18, DIV=0x1A,  AND=0x24,
    OR=0x25,  XOR=0x26,  SLT=0x2A,
    JR=0x08,  SLL=0,     SRL=0x02,
    SRA=0x03
};


/**
 * @param ri Registrador de instru��o (RI) que possui a instru��o a ser decodificada
 * @param A instru��o MIPS decodificada com os valores das suas partes encapsulados em uma MipsWord.
 */
MipsWord* decode (Instruction* inst)
{
    int ri = (inst->ri);	
    MipsWord* word_ = (MipsWord*) malloc(sizeof(MipsWord));

    word_->opcode = (ri >> 26) & 0x3F;	
	
	switch(word_->opcode)
	{
	  case LW:	   	
		word_->name = "LW - Load Word";
		word_->rs = (ri >> 21) & 0x1F;
		word_->rt = (ri >> 16) & 0x1F;
		word_->rd = ri & 0xFFFF;	    		
		break;
		
	  case SW:	
		word_->name = "SW - Store Word";
		word_->rs 	= (ri >> 21) & 0x1F;
		word_->rt 	= (ri >> 16) & 0x1F;
		word_->rd 	= ri & 0xFFFF;			
	    break;
		
	  case FUN:
	    word_->name = "ADD";
		
		if (inst->funct == ADD)
		{
			word_->rs 	= (ri >> 21) & 0x1F;
			word_->rt 	= (ri >> 16) & 0x1F;
			word_->rd 	= (ri >> 11) & 0x1F;
			word_->sa 	= (ri >> 6 ) & 0x1F;
		}				
	    break;
		
	  case BEQ:
		word_->name = "BEQ - Salto Condicional";
		word_->rs 	= (ri >> 21) & 0x1F;
		word_->rt 	= (ri >> 16) & 0x1F;
		word_->rd 	= ri & 0xFFFF;			
	    break;
		
	  case J:
		word_->name = "J - Salto Incondicional";		
		word_->rs 	= ri  & 0x03FFFFFF;
		break;	  		
		
	  default:
	    return NULL;
	}	
	
    return word_;
}

/**
 * Apresenta no terminal o valor dos atributos da estrutura.
 * @param word_ Estrutura a ter os seus atributos apresentados no terminal. N�o pode ser NULL.
 */
void dump (MipsWord* word_)
{
    if (word_ == NULL)
    {
        printf("Error! Instruction not decoded!");
        exit(1);
    }

    printf("name   = %s\n", word_->name);
    printf("rd     = %x\n",word_->rd);
    printf("rs     = %x\n",word_->rs);
    printf("rt     = %x\n",word_->rt);      
}

/**
 * Apresenta as op��es para que o usu�rio escolha uma e retorna a op��o escolhida. 
 * Caso a op��o escolhida n�o esteja dentre as determinadas, apresenta novamente as op��es novamente.
 * @return A op��o escolhida pelo usu�rio.
 */
int read()
{
  int op;
  do
  {
	printf("\n === Escolha uma instrucao MIPS a ser decodificada === \n");
	printf("0 - sair\n");
	printf("1 - Load Word\n");
	printf("2 - Store Word\n");
	printf("3 - ADD\n");
	printf("4 - BEQ\n");
	printf("5 - J\n");
	printf("Op: ");
	scanf("%d", &op);
  }while (!(op >= 0 && op <= 5));
  
  return op;
}

/**
 * Carrega a instru��o de acordo com a op��o escolhida.
 * @return Uma instru��o segundo uma data op��o.
 */
Instruction* load(int op)
{	
    Instruction* inst = malloc(sizeof(Instruction)); 
	switch(op)
	{
		case 1:		    
			inst->ri = 0x8D100002;
			break;
		case 2:
			inst->ri = 0xAD100002;
			break;
		case 3:
			inst->ri = 0x002A5820; 			
			inst->funct = inst->ri & 0x3F;
			break;
		case 4:
			inst->ri = 0x11100002;
			break;	
		case 5:
			inst->ri = 0X09100002;  
			break;
	}	
	return inst;
}


int main()
{
	int op;
	do 
	{
	  op = read();	  
	  if (op != 0) 
	  {	  
		Instruction* inst = load(op);	
		MipsWord* word_ = decode(inst);			
		dump(word_);      	  
		printf("\n ================================================== \n");	  
	  }
	}while (op != 0);
	
	getchar();
	
    return 0;
}