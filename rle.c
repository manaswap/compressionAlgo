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

	printf("+++++++++++++++++\n");
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


int main(int argc, char ** argv){

	char str[] = "aaaaaaaabbbbbbbbbbccccccccccdddddddddeeeeeeeefffffffff";; 

	int partitions = atoi(argv[1]);
	printf("%d\n", partitions);
	int * values = partitionInput(partitions, strlen(str));
	
	
	pthread_t thread[partitions];
	int i = 0;

	struct arg_struct args; 
	
	for (i = 0; i < partitions; i++){
	
    		args.arg1 = values[i];
		if (i == partitions-1) {
    		    args.arg2 = strlen(str);
		} else {
    		    args.arg2 = values[i+1] - 1;
		}
		args.string = str;
		pthread_create(&thread[i], NULL, encode, (void*)&args);
		pthread_join(thread[i], NULL);
	}

	return 0;
	
		
}

int * partitionInput(int numPartitions, int length) {

        int partitionSize = length/numPartitions;
        int remainder = length % numPartitions;

        int * partitionIndices = (int *)malloc(sizeof(int)*numPartitions);
        partitionIndices[0] = 0;

        int i = 1;
        for (i = 1; i < numPartitions; i++) {

                if (i == 1) {

                        partitionIndices[1] = partitionSize + remainder;

                }

                else {

                        partitionIndices[i] = partitionIndices[i - 1] + partitionSize;

                }

        }

        return partitionIndices;

}

