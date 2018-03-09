#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>


int main(int argc, char *argv[]){
FILE* fo = freopen("outputB.txt","w",stdout);

char* fileName = argv[1];
    char buffer[1000];
    int max;
    int min;
    int tmp;
    int sum=0;
    int count=0;
    int mypipefd[2];
    int mypipefd2[2];
    
    int ret;
    char buf[20];
    
    ret=pipe(mypipefd);
    if(ret==-1){
    perror("ERROR PIPE ERROR\n");
    exit(1);
    }
    FILE* fpcount;
    fpcount=fopen(fileName,"r");
   while(NULL!=fgets(buffer,1000,fpcount)){
   bzero(buffer, 1000);
   count++;
   };
    int array[count];
    
    
    FILE* fp;
    fp=fopen(fileName, "r");

    int ac=0;
     while(fgets(buffer, 1000, fp)!= NULL){
     
     if(ac==0){
           max = tmp;
           min = tmp;
     }
     
     
     
    tmp = atoi(buffer);
    array[ac]=tmp;
    //printf("%d\n",array[ac]); 
    ac++;
    }
    min=array[0];
       //freopen("output.txt", "w", stdout); 
    
    pid_t pid = fork();

    if (pid == 0){
    
      pid_t pid1 = fork();
      if (pid1 == 0){
      
      
      
      pid_t pid2 = fork();
      if (pid2 == 0){
        printf("Hi, I'm process %d and my parent is %d\n",getpid(),getppid());
        int k;
         for(k=0; k<count; k++){
           sum += array[k];
       }
       
       pid1 = wait(NULL);
       printf("Sum = %d\n", sum,array[0]);
        return; 
      }
      
      
      max=array[0];
        printf("Hi, I'm process %d and my parent is %d\n",getpid(),getppid());
         int j;
         for(j=1; j<count-1; j++){
           if (array[j]>max){
             max=array[j];
         }
       }
       //bzero(buffer, 1000);
       //sprintf(buffer,"The maximum value is %d\n", max);
       //printf(buffer);
      //close(mypipefd2[0]);
      // write(mypipefd2[1], buffer, 1000);//wat if i wrote to a different buffer??? //wat if write from grandchild to child to parent???
       //printf("Located inside the buffer is %s\n",buffer);
       //close(mypipefd2[1]);
        
        pid2 = wait(NULL);
        printf("Max = %d\n",max);
        return;
        
      }
      
       printf("Hi, I'm process %d and my parent is %d\n",getpid(),getppid());
       int i;
      // printf("the 000000count is %d\n", count);
       for(i=0; i<count-1; i++){
         //printf("what is contained in array is %d\n",array[i]);
         if (array[i]<min){
           min=array[i];
           
          // printf("The NEW minimum number is %d\n",min);
           //return;
       }
        //printf("The minimum number is %d\n",min);
       //return;
     }
     //printf("The minimum number is %d\n",min);
//    bzero(buffer, 1000);
//     sprintf(buffer,"The minimum number is %d\n",min);
//    close(mypipefd[0]);
//     write(mypipefd[1], buffer, 1000);
//     close(mypipefd[1]);
     pid1 = wait(NULL);
     printf("Min = %d\n",min);
   return;
     
   }

   
     printf("Hi, I'm process %d and my parent is %d\n",getpid(),getppid());  
      pid = wait(NULL);
      	fclose(fo);
//      
//       bzero(buffer, 1000);
//      read(mypipefd2[0],buffer,1000); // mypipefd[0] is input mypipefd[1] is output
//      close(mypipefd2[0]);
//      printf(buffer); 
//      
//      close(mypipefd[1]);
//      close(mypipefd2[1]);
//      printf("before\n");
//      
//      bzero(buffer, 1000);
//      read(mypipefd[0],buffer,1000);
//     // printf("MAXXXXX %s\n",buffer);
//      close(mypipefd[0]);
      
     // bzero(buffer, 1000);
      //read(mypipefd2[0],buffer,1000);
      //printf(buffer);
      //close(mypipefd2[0]);
//      printf("after\n");
//      printf(buffer);
     
     // printf("hello my friend\n");
     //the order of the reads is important  sum max min should be order!!!
    
     
  // 
    return;
      

}
