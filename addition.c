#include "variables.h"


Matrix addition(Matrix A,Matrix B)
{
	Matrix C;
	int ai,bi,ci;
	int aj,bj,cj;
	int ak,bk,ck;
	ak = bk = ck = 0;
	if(A.row_num != B.row_num || A.col_num != B.col_num){
		printf("MATRIX SIZE IS DIFFERENT\n");
		exit(EXIT_FAILURE);
    }
	C.row_num = A.row_num;
	C.col_num = A.col_num;
	while(ak <= A.value_num && bk <= B.value_num){
        	ai = A.data[ak].row;
        	bi = B.data[bk].row;
        	if(ai > bi){
            		ci = bi;
            		while(ci == B.data[bk].row){
                		C.data[ck].row = ci;
               			C.data[ck].col = B.data[bk].col;
                		C.data[ck].value = B.data[bk].value; 
                		++bk;
                		++ck;
            		}            
        	}else if(ai < bi){
          		ci = ai;
           		while(ci == A.data[ak].row){
                		C.data[ck].row = ci;
                		C.data[ck].col = A.data[ak].col;
                		C.data[ck].value = A.data[ak].value;
                		++ak;
                		++ck;
            		}            
        	}else if(ai == bi){
            		ci = ai;            
            		aj = A.data[ak].col;
            		bj = B.data[bk].col;
            		if(aj > bj){          
                		C.data[ck].row = ci;
                		C.data[ck].col = bj;
                		C.data[ck].value = B.data[bk].value;
                		++ck;
                		++bk;
            		}else if(aj < bj){ 
                		C.data[ck].row = ci;
                		C.data[ck].col = aj;
                		C.data[ck].value = A.data[ak].value;
                		++ck;
               			++ak;
           	 	}else if(aj == bj){                
                		if(A.data[ak].value + B.data[bk].value != 0){
                    			C.data[ck].row = ci;
                    			C.data[ck].col = aj;
                    			C.data[ck].value = A.data[ak].value + B.data[bk].value;
                    			++ck;
               			 }
                	++ak;
                	++bk;
            }            
        }
    }
 
	while(ak <= A.value_num){
        	C.data[ck].row = A.data[ak].row;
        	C.data[ck].col = A.data[ak].col;
        	C.data[ck].value = A.data[ak].value;
        	++ck;
        	++ak;
    	}
	while(bk <= B.value_num){
        	C.data[ck].row = B.data[bk].row;
        	C.data[ck].row = B.data[bk].row;
        	C.data[ck].value = B.data[bk].value;
        	++ck;
        	++bk;
    	}
	C.value_num = ck + 1;
	return C;
}
