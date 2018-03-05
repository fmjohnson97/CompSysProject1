#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include "2.h"

int main(int argc, char *argv[])
{
    char* fileName = argv[1];
    char buffer[100];
    
    FILE* fp;
    fp = fopen(fileName,"r");
  
    tree_node *initNode = malloc(sizeof(tree_node));
    initNode->fp = fp;  
}

void createTree(tree_node *node)
{
    FILE* fp = node->fp;
    char buffer[100];
    char *rootNode = strtok(buffer," "); //local variables must return to main also must store into struct treeNode
    char *strNumChild = strtok(NULL," ");
    int numKids = atoi(strNumChild); 
    
    while(fgets(buffer,100,fp)!=NULL)
    {
        if(numKids>0)
        {
            int pid;
            int procNum;
            
            for(procNum = 0; procNum < numKids; procNum++)
            {
                pid = fork();
                if (pid == 0) 
                {
                    break; // break the loop if you are child process so processes dont grow by 2^n
                }
            }
            
            if (pid == 0) 
            {
                // child specific stuff. procNum is set to the "child number"
                
            }else{
             
                // parent stuff
            }
        
        }else{
        
        
        
        }
        
        
        
        
    
    }
}