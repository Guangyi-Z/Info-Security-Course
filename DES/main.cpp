#include"header.h"
#include<stdio.h>
#include<math.h>
#include<string.h>
using namespace std;

// Uncomment this macro to output the debug info to screen
//#define DEBUG 1

/* data src */
//const char *s_data_src= "0000""0001""0010""0011""0100""0101""0110""0111""1000""1001""1010""1011""1100""1101""1110""1111";
const char *s_data_src= "01101000""10000101""00101111""01111010""00010011""01110110""11101011""10100100";
const int LEN_SRC= 64;
const int LEN_HALF_SRC= LEN_SRC/2;

/* key */
//const char* s_key_src= "00010011""00110100""01010111""01111001""10011011""10111100""11011111""11110001";
//const char* s_key_src= "11100010""11110110""11011110""00110000""00111010""00001000""01100010""11011100";
const char* s_key_src= "01100010""11110110""11011110""00110000""00111010""00001000""01100010""11011100";
const int LEN_KEY= 64;
const int NUM_SUB_KEY= 16;
const int LEN_KEY_FINAL= 48;

/* table */
const int LEN_TABLE_IP= LEN_SRC;
const int LEN_TABLE_PC1= 56;
const int LEN_TABLE_PC2= LEN_KEY_FINAL;
const int LEN_TABLE_E= 48;
const int NUM_TABLE_S= 8;
const int LEN_TABLE_S_ROW= 4, LEN_TABLE_S_COL= 16;
const int LEN_TABLE_P= 32;

const int TABLE_IP[]= {58, 50, 42, 34, 26, 18, 10 ,2,
				 60, 52, 44, 36, 28, 20, 12, 4,
			     62, 54, 46, 38, 30, 22, 14, 6,
			     64, 56, 48, 40, 32, 24, 16, 8,
				 57, 49, 41, 33, 25, 17,  9, 1,
		         59, 51, 43, 35, 27, 19, 11, 3,
	             61, 53, 45, 37, 29, 21, 13, 5,
	             63, 55, 47, 39, 31, 23, 15, 7};
const int TABLE_PC1[]= {57, 49, 41, 33, 25, 17, 9,
                   1, 58, 50, 42, 34, 26, 18,
			      10,  2, 59, 51, 43, 35, 27,
	              19, 11,  3, 60, 52, 44, 36,
	              63, 55, 47, 39, 31, 23, 15,
	               7, 62, 54, 46, 38, 30, 22,
	              14,  6, 61, 53, 45, 37, 29,
	              21, 13,  5, 28, 20, 12,  4};
const int TABLE_PC2[]= {14, 17, 11, 24,  1,  5,
				     3, 28, 15,  6, 21, 10,
	                23, 19, 12,  4, 26,  8,
                    16,  7, 27, 20, 13,  2,
				    41, 52, 31, 37, 47, 55,
			        30, 40, 51, 45, 33, 48,
		            44, 49, 39, 56, 34, 53,
	                46, 42, 50, 36, 29, 32};				  
const int TABLE_E[]= {32,  1,  2,  3,  4,  5,
				   4,  5,  6,  7,  8,  9,
				   8,  9, 10, 11, 12, 13,
				  12, 13, 14, 15, 16, 17,
                  16, 17, 18, 19, 20, 21,
		          20, 21, 22, 23, 24, 25,
				  24, 25, 26, 27, 28, 29,
			      28, 29, 30, 31, 32,  1};
const int TABLE_S[NUM_TABLE_S][LEN_TABLE_S_ROW][LEN_TABLE_S_COL]= {
					{14, 4,13, 1, 2,15,11, 8, 3,10, 6,12, 5, 9, 0, 7,
  				 	  0,15, 7, 4,14, 2,13, 1,10, 6,12,11, 9, 5, 3, 8,
      			  	  4, 1,14, 8,13, 6, 2,11,15,12, 9, 7, 3,10, 5, 0,
	  		     	 15,12, 8, 2, 4, 9, 1, 7, 5,11, 3,14,10, 0, 6,13},
					{15, 1, 8,14, 6,11, 3, 4, 9, 7, 2,13,12, 0, 5,10,
    				  3,13, 4, 7,15, 2, 8,14,12, 0, 1,10, 6, 9,11, 5,
		 	          0,14, 7,11,10, 4,13, 1, 5, 8,12, 6, 9, 3, 2,15,
				     13, 8,10, 1, 3,15, 4, 2,11, 6, 7,12, 0, 5,14, 9},
					{10, 0, 9,14, 6, 3,15, 5, 1,13,12, 7,11, 4, 2, 8,
				     13, 7, 0, 9, 3, 4, 6,10, 2, 8, 5,14,12,11,15, 1,
				     13, 6, 4, 9, 8,15, 3, 0,11, 1, 2,12, 5,10,14, 7,
			          1,10,13, 0, 6, 9, 8, 7, 4,15,14, 3,11, 5, 2,12},
					{ 7,13,14, 3, 0, 6, 9,10, 1, 2, 8, 5,11,12, 4,15,
    				 13, 8,11, 5, 6,15, 0, 3, 4, 7, 2,12, 1,10,14, 9,
				     10, 6, 9, 0,12,11, 7,13,15, 1, 3,14, 5, 2, 8, 4,
				      3,15, 0, 6,10, 1,13, 8, 9, 4, 5,11,12, 7, 2,14},
					{ 2,12, 4, 1, 7,10,11, 6, 8, 5, 3,15,13, 0,14, 9,
				     14,11, 2,12, 4, 7,13, 1, 5, 0,15,10, 3, 9, 8, 6,
				      4, 2, 1,11,10,13, 7, 8,15, 9,12, 5, 6, 3, 0,14,
				     11, 8,12, 7, 1,14, 2,13, 6,15, 0, 9,10, 4, 5, 3},
					{12, 1,10,15, 9, 2, 6, 8, 0,13, 3, 4,14, 7, 5,11,
				     10,15, 4, 2, 7,12, 9, 5, 6, 1,13,14, 0,11, 3, 8,
				      9,14,15, 5, 2, 8,12, 3, 7, 0, 4,10, 1,13,11, 6,
			          4, 3, 2,12, 9, 5,15,10,11,14, 1, 7, 6, 0, 8,13},
					{ 4,11, 2,14,15, 0, 8,13, 3,12, 9, 7, 5,10, 6, 1,
				     13, 0,11, 7, 4, 9, 1,10,14, 3, 5,12, 2,15, 8, 6,
				      1, 4,11,13,12, 3, 7,14,10,15, 6, 8, 0, 5, 9, 2,
			          6,11,13, 8, 1, 4,10, 7, 9, 5, 0,15,14, 2, 3,12},
					{13, 2, 8, 4, 6,15,11, 1,10, 9, 3,14, 5, 0,12, 7,
				      1,15,13, 8,10, 3, 7, 4,12, 5, 6,11, 0,14, 9, 2,
		   	          7,11, 4, 1, 9,12,14, 2, 0, 6,10,13,15, 3, 5, 8,
				      2, 1,14, 7, 4,10, 8,13,15,12, 9, 0, 3, 5, 6,11}
};
const int TABLE_P[]={16, 7,20,21,
                     29,12,28,17,
				      1,15,23,26,
				      5,18,31,10,
				      2, 8,24,14,
				     32,27, 3, 9,
				     19,13,30, 6,
				     22,11, 4,25};
const int TABLE_IP_CONVERSE[]=
	{40,  8,  48,  16,  56,  24,  64,  32,
     39,  7,  47,  15,  55,  23,  63,  31,
     38,  6,  46,  14,  54,  22,  62,  30,
     37,  5,  45,  13,  53,  21,  61,  29,
     36,  4,  44,  12,  52,  20,  60,  28,
     35,  3,  43,  11,  51,  19,  59,  27,
     34,  2,  42,  10,  50,  18,  58,  26,
     33,  1,  41,   9,  49,  17,  57,  25};

/* left shift array */
int num_left_shift[NUM_SUB_KEY]= {1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1};

/* main() */
int main(){
	/* data */
	bool b_data[LEN_SRC];
	get_bits_from_bitstr(s_data_src, b_data, LEN_SRC);
	
#ifdef DEBUG
printf("DATA:\n");
print_bits(b_data, LEN_SRC);
#endif

	//IP permutation
	bool b_data_ip[LEN_TABLE_IP];
	permutation(b_data, b_data_ip, TABLE_IP, LEN_SRC);

#ifdef DEBUG
printf("DATA AFTER TABLE IP:\n");
print_bits(b_data_ip, LEN_TABLE_IP);
#endif

	//split into L and R
	bool b_ldata[LEN_HALF_SRC], b_rdata[LEN_HALF_SRC];
	bitscpy(b_data_ip, b_ldata,  0, LEN_HALF_SRC);
	bitscpy(b_data_ip, b_rdata, LEN_HALF_SRC, LEN_HALF_SRC);

#ifdef DEBUG
printf("DATA L0 R0:\n");
print_bits(b_ldata, LEN_HALF_SRC);
print_bits(b_rdata, LEN_HALF_SRC);
#endif

	/* key */
	bool b_key[LEN_KEY];
	get_bits_from_bitstr(s_key_src, b_key, LEN_KEY);

#ifdef DEBUG
printf("KEY:\n");
print_bits(b_key, LEN_KEY);
#endif

	//PC-1 permutation, 64-bit to 56-bit
	bool b_key_pc1[LEN_TABLE_PC1];
	permutation(b_key, b_key_pc1, TABLE_PC1, LEN_TABLE_PC1);

#ifdef DEBUG
printf("KEY_PC1:\n");
print_bits(b_key_pc1, LEN_TABLE_PC1);
#endif

	//slipt into C0 and D0
	const int LEN_KEY_C_D= LEN_TABLE_PC1/2;
	bool b_lkey_pc1[LEN_KEY_C_D], b_rkey_pc1[LEN_KEY_C_D];
	bitscpy(b_key_pc1, b_lkey_pc1, 0, LEN_KEY_C_D);
	bitscpy(b_key_pc1, b_rkey_pc1, LEN_KEY_C_D, LEN_KEY_C_D);

#ifdef DEBUG
printf("SUBKEY C0 & D0:\n");
print_bits(b_lkey_pc1, LEN_KEY_C_D);
print_bits(b_rkey_pc1, LEN_KEY_C_D);
#endif

	// left shift
	bool b_subkeyc[NUM_SUB_KEY][LEN_KEY_C_D];
	bool b_subkeyd[NUM_SUB_KEY][LEN_KEY_C_D];
		leftshift(b_lkey_pc1, b_subkeyc[0], LEN_KEY_C_D, num_left_shift[0]);
		leftshift(b_rkey_pc1, b_subkeyd[0], LEN_KEY_C_D, num_left_shift[0]);
	for( int i= 1; i< NUM_SUB_KEY; i++){
		leftshift(b_subkeyc[i-1], b_subkeyc[i], LEN_KEY_C_D, num_left_shift[i]);
		leftshift(b_subkeyd[i-1], b_subkeyd[i], LEN_KEY_C_D, num_left_shift[i]);
	}

#ifdef DEBUG
printf("SUBKEYS C1~C16:\n");
for(int i= 0; i< NUM_SUB_KEY; i++){
	print_bits(b_subkeyc[i], LEN_KEY_C_D);
}
printf("SUBKEYS D1~D16:\n");
for(int i= 0; i< NUM_SUB_KEY; i++){
	print_bits(b_subkeyd[i], LEN_KEY_C_D);
}
#endif

	// merch CnDn into subkey, 2*28= 56 bits
	bool b_subkey_cd[NUM_SUB_KEY][LEN_KEY_C_D * 2];
	for( int i= 0; i< NUM_SUB_KEY; i++){
		bitscat(b_subkey_cd[i], b_subkeyc[i], 0, LEN_KEY_C_D);
		bitscat(b_subkey_cd[i], b_subkeyd[i], LEN_KEY_C_D, LEN_KEY_C_D);
	}

#ifdef DEBUG
printf("16 SUBKEYS C&D:\n");
for(int i= 0; i< NUM_SUB_KEY; i++){
	print_bits(b_subkey_cd[i], LEN_KEY_C_D*2);
}
#endif

	// PC-2 permutation of Cn and Dn, 56-bit to 48-bit
	bool b_subkey[NUM_SUB_KEY][LEN_KEY_C_D * 2];
	for( int i= 0; i<NUM_SUB_KEY; i++){
		permutation(b_subkey_cd[i], b_subkey[i], TABLE_PC2, LEN_KEY_FINAL);
	}

#ifdef DEBUG
printf("16 SUBKEYS:\n");
for(int i= 0; i< NUM_SUB_KEY; i++){
	print_bits(b_subkey[i], LEN_KEY_FINAL);
}
#endif

	/* encoding */ 
	// 16 iterations
	// Ln= Rn-1
	// Rn= Ln-1 + f(Rn-1, Kn)
	for( int i= 0; i< NUM_SUB_KEY; i++){
		iteration(b_ldata, b_rdata, b_subkey[i]);

#ifdef DEBUG
printf("LEFT & RIGHT DATA IN %d ITERATION\n", i+1);
print_bits(b_ldata, LEN_HALF_SRC);
print_bits(b_rdata, LEN_HALF_SRC);
#endif

	}

	//merge L and R in reverse order RnLn
	bool b_data_merge[LEN_SRC];
	bitscat(b_data_merge, b_rdata, 0, LEN_HALF_SRC);
	bitscat(b_data_merge, b_ldata, LEN_HALF_SRC, LEN_HALF_SRC);

#ifdef DEBUG
printf("R16L16:\n");
print_bits(b_data_merge, LEN_SRC);
#endif

	//converse IP-1 permutation
	bool b_data_cip[LEN_SRC];
	permutation(b_data_merge, b_data_cip, TABLE_IP_CONVERSE, LEN_SRC);

#ifdef DEBUG
printf("AFTER ENCODING:\n");
print_bits(b_data_cip, LEN_SRC);
#endif

	//print result to screen
	printf("RESULT:\n");
	printf("DATA:\n");
	print_bits(b_data, LEN_SRC);
	printf("KEY:\n");
	print_bits(b_key, LEN_KEY);
	printf("ENCODING RESULT:\n");
	print_bits(b_data_cip, LEN_SRC);
}

/* iteration */
//Ln= Rn-1
//Rn= Ln-1 + f(Rn-1, Kn)
void iteration(bool* l, bool* r, bool* k){
	bool tmp[LEN_HALF_SRC];
	for(int i= 0; i< LEN_HALF_SRC; i++){
		tmp[i]= l[i];
		l[i]= r[i];
	}
	f_func(r, k);
	for(int i= 0; i< LEN_HALF_SRC; i++){
		r[i]^= tmp[i];
	}
}

/* 
 * index: src[index] as the first bit
 * s_num: indicate s_num th s-box to use
 * each call use 6 bits in src as addr of s-box
 */
int s_box(bool* src, int s_num, int index){
	// S boxes
	// i= B[0]B[5], j= B[1]B[2]B[3]B[4], Sn[i,j] as output
	int ii= src[index]*2 + src[index+5];
	int jj= src[index+1]*8 + src[index+2]*4 + src[index+3]*2 + src[index+4];
	return TABLE_S[s_num][ii][jj];
}

/* f function */
//r= f(Rn-1, Kn)
void f_func(bool* r, bool* key){
	//E table permutation of Rn-1, 32-bit to 48-bit
	bool r_E[LEN_TABLE_E];
	permutation(r, r_E, TABLE_E, LEN_TABLE_E);
#ifdef DEBUG
printf("E(R):\n");
print_bits(r_E, LEN_TABLE_E);
#endif
	//Kn XOR E(Rn-1) = B1B2B3B4B5B6B7B8, each B is a 6-bit block
	for(int i= 0; i<LEN_KEY_FINAL; i++){
		key[i]= r_E[i] ^ key[i];
	}
#ifdef DEBUG
printf("KEY xor E(R):\n");
print_bits(key, LEN_KEY_FINAL);
#endif
	//S1(B1)S2(B2)S3(B3)S4(B4)S5(B5)S6(B6)S7(B7)S8(B8), 48-bit to 32-bit
	//P table permutation, 32-bit to 32-bit
	int count= LEN_KEY_FINAL/6;
	for(int i= 0; i< count; i++){
		int tmp= s_box(key, i, i*6);
		for( int j= 0; j< 4; j++){
			r[i*4+j]= tmp / (int)pow(2, 3-j);
			tmp%= (int) pow(2, 3-j);
		}
	}
	bool r_dup[LEN_HALF_SRC];
	memcpy(r_dup, r, sizeof(r_dup));
	permutation(r_dup, r, TABLE_P, LEN_HALF_SRC);
}

