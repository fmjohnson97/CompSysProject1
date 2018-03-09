#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]){

    char* fileName = argv[1];
    char buffer[1000];
    int max;
    int min;
    int tmp;
    int sum;
    
    printf("The file name is %s\n", fileName);
    
    FILE* fp;
    fp=fopen(fileName, "r");
    fgets(buffer, 1000, fp);
    tmp = atoi(buffer);
    max = tmp;
    min = tmp;
    sum = tmp;
    bzero(buffer,1000);
    while(fgets(buffer, 1000, fp)!= NULL){
    tmp = atoi(buffer);
    //printf("%d\n",tmp);
      if (tmp > max){
        max = tmp;
      }
      if (tmp < min) {
        min = tmp;
      }
      sum += tmp;
      bzero(buffer, 1000);
    }
    printf("The max number is %d\nThe minimum number is %d\nThe Sum of the numbers is %d\n",max,min,sum);
    
    
}
