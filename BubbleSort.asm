# Função que ordena os elementos de um vetor (v) de tamanho n alocados nos registradores $a0 e $a1 em ordem
# crescente utilizando o algoritmo de ordenação BubbleSort. Corresponde ao seguinte código em C.
#    void bubbleSort(int v[], int n)
#    {
#       int i, j;
#       for(i = 0; i < n; i++)
#         for(j = i -1; j >=0 && v[j] > v[j + 1]; j--)
#            swap(v,j)
#    }
#
bubbleSort: addi $sp,$sp,-20      
      Sw   $ra, 16($sp)     	  
      Sw   $s3, 12($sp)
      Sw   $s2, 8($sp)
      Sw   $s1, 4($sp)
      Sw   $s0, 0($sp)
      
      	 move $s2, $a0
      	 move $s3, $a1
      
      	 move $s0, $zero 
forE:    slt  $t0, $s0, $s3
	 beq  $t0, $zero, exit1
	 
	 addi $s1, $s0, -1
forI:    slti $t0, $s1, 0
	 bne  $t0, $zero, exit2
	 sll  $t1, $s1, 2
	 add  $t2, $s2, $t1
	 lw   $t3, 0($t2)
	 lw   $t4, 4($t2)
	 slt  $t0, $t4, $t3
	 beq  $t0, $zero, exit2
	 
	 move $a0, $s2
	 move $a1, $s1
	 jal  swap
	 
	 addi $s1, $s1, -1
	 j    forI

exit2:   addi $s0, $s0, 1
	 j    forE
	 
exit1:	 lw   $s0, 0($sp)
	 lw   $s1, 4($sp)
	 lw   $s2, 8($sp)
	 lw   $s3, 12($sp)
	 lw   $ra, 16($sp)
	 addi $sp, $sp, 20
	 
	 jr   $ra

# Função que troca o conteúdo de duas posições (variáveis) de memória na posição k com a k + 1. 
# Corresponde ao seguinte código em C:
#   void swap(int v[], int k){
#      int temp = v[k];
#      v[k] = v[k + 1];
#      v[k + 1] = temp;	 
swap: 	sll $t1, $a1, 2
	add $t1, $a0, $t1
	
	lw  $t0, 0($t1)
	lw  $t2, 4($t1)
	
        sw  $t2, 0($t1)
        sw  $t0, 4($t1)
        
        jr  $ra   	    	  	        