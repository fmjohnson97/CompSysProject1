#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include "2.h"

tree_node* createTree(tree_node *thestruct, char* ident)
{    
    //
    FILE* fp = thestruct->fp;
    char buffer[100];
    char * temp;
    if(strcmp(ident,"")==0){
    //printf("init\n");
    fgets(buffer, 100, fp);
    
    }
    else{
    char yayo[100];
      while(fgets(buffer,100,fp)){

      //you want to compare ident with first letter of buffer
      
        sprintf(yayo,"%s",buffer);
        
       char *chk = strtok(yayo," ");
       
       int foo = strcmp(ident,chk);
//       printf("\n--chk--\n");
//       printf("%s%s",ident,chk);
//       printf("%d",foo);
//       printf("\n--chk--\n");
        if(strcmp(ident,chk)==0){
           //printf("break\n");
                   break;       
        }
        
      }
       
    }
  printf("%s",buffer);
  fflush(stdout);
    char *rootNode = strtok(buffer," ");
    //printf("%s",buffer);
    char *strNumChild = strtok(NULL," ");
   //printf("%s\n",strNumChild);
    int numKids = atoi(strNumChild); 
    if(numKids==0){
     sleep(1);
     return thestruct;
    }
    node newNode;
// printf("%s\n%d\n",rootNode,numKids);
    
    
    thestruct->rootNode = rootNode; 
    thestruct->numChildren = numKids;
     //printf("%s %d \n",rootNode, numKids);
    node firstBorn = createNode();     
    //printf("%s\n",buffer);
    if(numKids ==1){
    char *stream = strtok(NULL,"\r\n ");
    firstBorn->data = stream; // the last process name may be \n delimated 
    }
    else{
    char *stream = strtok(NULL," ");
    firstBorn->data = stream; // the last process name may be \n delimated 
    }
    
    
    if(numKids > 1){
    int i;
    for(i=0;i<numKids-2;i++){     
    temp = strtok(NULL," ");      
    newNode = addNode(firstBorn,temp);
    } 
    temp = strtok(NULL,"\n");
    newNode = addNode(firstBorn,temp);
    }
    //
     
    node tmp;
    tmp = firstBorn;
    //printf("%d\n",numKids);
    int pid;
    if(numKids == 1){
      pid = fork();
      if (pid==0){
      //printf("work\n");
        createTree(thestruct, tmp->data);
      }
          wait(NULL);
    return thestruct;
    
    }
    else{//
              //printf("%s\n",tmp->next);
      while(tmp != NULL){
       // B =tmp->data 
        //printf("%s\n",tmp->data);
              // printf("work\n");
              // int procNum;
               
              
         pid = fork();
         
                          if (pid == 0) 
                 {
                     break; // break the loop if you are child process so processes dont grow by 2^n
                 }
               if (pid>0){
                 wait(NULL);
               
               }
          
        tmp = tmp->next;
      }  
      
      
          if (pid == 0) 
               {
                   // child specific stuff. procNum is set to the "child number"
                   //recall the function createTree(theStruct)
                //printf("activated \n");
                   createTree(thestruct, tmp->data);   
               } 
               
               
               
       wait(NULL);
    return thestruct;
    }
    

    wait(NULL);
    return thestruct;

}
int main(int argc, char *argv[])
{
    FILE *fo = freopen("output2.txt","w",stdout);
    char* fileName = argv[1];
    char buffer[100];
    char* init="";
    FILE* fp;
    fp = fopen(fileName,"r");

    tree_node *initNode = malloc(sizeof(tree_node));
    initNode->fp = fp;  
    
    initNode = createTree(initNode, init);
    
    fclose(fo);
}

