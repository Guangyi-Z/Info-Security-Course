
/* func */
void permutation(bool *src, bool* des, const int* TABLE, int len);
void permutation_converse(bool *src, bool* des, const int* TABLE, int len);
void bitscpy(bool* src, bool* des, int start, int len);
void get_bits_from_bitstr(const char* str, bool* des, int len);
void bitscat(bool* des, bool* src, int n, int len_src);
void leftshift(bool* src, bool* des, int len, int n);
void print_bits(bool* bits, int len);


void f_func(bool* r, bool* key);
int s_box(bool* src, int s_num, int index);
void iteration(bool* l, bool* r, bool* k);
