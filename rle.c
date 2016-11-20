#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

int * partitionInput(int numPartitions, int length);


struct arg_struct {
    int arg1;
    int arg2;
    char * string;
};



void *encode(void  *arg){

	struct arg_struct *args = arg;

	char *src = (char*)args->string;
	
	int rlen; 
	char count[256];
	int len = strlen(src);

	char *dest = (char *)malloc(sizeof(char)*(len*2+1));

	int i;
	int k;
	int j = 0;
	
	printf("%d\n", args->arg1);
	printf("%d\n", args->arg2);	

	for (i = args->arg1; i < args->arg2; i++){

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
	printf("%s\n", dest);
	return NULL;
}


int main(){

	char str[] = "heeppppopopeeeelllloooo";

	int * values = partitionInput(5, strlen(str));
	
	printf("%d\n", values[0]);
	printf("%d\n", values[1]);
	printf("%d\n", values[2]);
	printf("%d\n", values[3]);
	printf("%d\n", values[4]);

	printf("%lu\n", strlen(str));	
	
	pthread_t pth;
	int i = 0;

	struct arg_struct args; 
	
	for (i = 0; i < 4; i++){
	
    		args.arg1 = values[i];
    		args.arg2 = values[i]-1;
		args.string = str;
		pthread_create(&pth, NULL, encode, (void*)&args);
		
	}

	pthread_join(pth, NULL);
	return 0;
	
		
}

int * partitionInput(int numPartitions, int length) {

        int partitionSize = length/numPartitions;
        int remainder = length % numPartitions;

        int * partitionIndices = (int *)malloc(sizeof(int)*numPartitions);
        partitionIndices[0] = 0;

        int i;

        for (i = 0; i < numPartitions - 1; i++) {

                if (i == 0) {

                        partitionIndices[1] = partitionSize + remainder;

                }

                else {

                        partitionIndices[i + 1] = partitionIndices[i] + partitionSize;

                }

        }

        return partitionIndices;

}

