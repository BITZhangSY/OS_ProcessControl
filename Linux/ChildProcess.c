#include<stdio.h>
#include<unistd.h>

int main(int argc, char * argv[]){
	printf("Enter son process---------------------\n\n");	
	printf("%s\n\n",argv[0]);
	sleep(3);
	printf("Quit now------------------------------\n");
	return 0;
}
