#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *encode(char *src){
	
	int rlen; 
	char count[256];
	int len = strlen(src);

	char *dest = (char *)malloc(sizeof(char)*(len*2+1));

	int i;
	int k;
	int j = 0;

	for (i = 0; i < len; i++){

		dest[j++] = src[i];

		rlen = 1; 
	
		while (i+1<len && src[i] == src[i+1]) { 
	
			rlen++;
			i++;
		
		}
	
		sprintf(count,"%d", rlen);

		for (k = 0; *(count+k); k++, j++){
			dest[j] = count[k];
		}
	}

	dest[j] = '\0';
	return dest;
}


int main(){

	char str[] = "heeppppopopeeeelllloooo";
	char *res = encode(str);
	printf("%s", res);
	getchar();
}









