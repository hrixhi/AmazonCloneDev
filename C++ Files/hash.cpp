#include "hash.h"


unsigned long long hash_str(const char* s)
{
	int size_=0, j=0;

	while(s[j]!='\0') {
		size_++; j++;
	}
	unsigned long long x = 0;

	for(int i = 0; i<size_; i++) {
		x += ((unsigned long long)pow(128, i)) * (int) s[j-1];
		j--;
	}

	unsigned int h[4];
	j = 4;

	while(j>=0) {
		h[4-j] = x % 65521;
		x = x/65521; j--;
	}

	unsigned long long toReturn = (45912 * h[3] + 35511 * h[2] + 65169 * h[1] + h[0] * 4625) % 65521;

   	return toReturn;
}