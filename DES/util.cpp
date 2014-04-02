#include<stdio.h>

/* 
 * len: len of the table
 */
void permutation(bool *src, bool* des, const int* table, int len){
	for(int i= 0; i< len; i++){
		des[i]= src[table[i]-1];
	}
}

/* 
 * len: len of the table
 */
void permutation_converse(bool *src, bool* des, const int* table, int len){
	for(int i= 0; i< len; i++){
		des[table[i]-1]= src[i];
	}
}

void bitscpy(bool* src, bool* des, int start, int len){
	for(int i= start, j= 0; j< len; i++, j++){
		des[j]= src[i];
	}
}

/* 
 * str: a char array where each char is either 1 or 0
 */
void get_bits_from_bitstr(const char* str, bool* des, int len){
	for(int i= 0; i<len; i++){
		des[i]= str[i] - '0';
	}
}

/* 
 * n: the number of items in des before
 */
void bitscat(bool* des, bool* src, int n, int len_src){
	for( int i= 0; i< len_src; i++){
		des[n++]= src[i];
	}
}

/* 
 * n: number of shifting
 */
void leftshift(bool* src, bool* des, int len, int n){
	for(int i= 0; i<len; i++){
		des[i]= src[i];
	}
	for(int i= 0; i<n; i++){ // swap item in max and 0
		bool tmp= des[0];
		for(int j= 0; j< len; j++){
			des[j]= des[j+1];
		}
		des[len-1]= tmp;
	}
}

void print_bits(bool* bits, int len){
	for(int i= 0 ; i< len; i++){
		if( i%8 == 0 && i != len-1)
			printf(" ");
		printf("%d", bits[i]);
	}
	printf("\n");
}
