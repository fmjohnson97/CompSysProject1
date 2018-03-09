#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include "2.h"

tree_node* createTree(tree_node *thestruct, char* ident) // when node has 0 children what should ident BE?
{
    
    FILE* fp = thestruct->fp;
    FILE* getRoot = thestruct->fp;
    char buffer[100];
    char* nextChild;
    node newNode;
    node firstBorn = createNode();
    pid_t pid;
    
    if(strcmp(ident,"")==0)// for initial condition if empty string was put into buffer means first line
    {
        fgets(buffer, 100, fp);
        
    }
    else //this is to fine the line where we find the information to create the ident
    {
        char yayo[100];
        while(fgets(buffer,100,fp))
        {
            sprintf(yayo,"%s",buffer);
            char *chk = strtok(yayo," ");
            unsigned char hello = ident[0];
            unsigned char goodbye = chk[0];
            if(hello==goodbye)
            {
                break;
            }
            
        }
        
    }
    printf("%s",buffer);
    fflush(stdout);
    char *rootNode = strtok(buffer," ");
    char *strNumChild = strtok(NULL," ");
    int numKids = atoi(strNumChild);
    thestruct->rootNode = rootNode;
    thestruct->numChildren = numKids;
    
    if(numKids==0){
        kill -sigcont getppid();
        return thestruct;
    }
    
    else if(numKids ==1)
    {
        char *stream = strtok(NULL,"\r\n");
        firstBorn->data = stream;
        pid = fork();
        if (pid==0)
        {
            createTree(thestruct, stream);
            raise(SIGSTOP);//CHANGE THIS LINE; pause(raise(SIGSTOP)?) then child must send sigcont to parent
            kill -sigcont getppid();
            return thestruct;
        }
    }
    
    else //if number of children > 1
    {
        char *stream = strtok(NULL," ");
        firstBorn->data = stream;
        int i;
        for(i=0;i<numKids-2;i++)
        {
            nextChild = strtok(NULL," ");
            newNode = addNode(firstBorn,nextChild);
        }
        nextChild = strtok(NULL,"\n");
        newNode = addNode(firstBorn,nextChild);
        while(firstBorn != NULL)
        {
            pid = fork();
            if (pid == 0)
            {
                break;
            }
            else
            {
                firstBorn = firstBorn->next;
            }
        }
        
        
        if (pid == 0)
        {
            createTree(thestruct, firstBorn->data);
        }
        raise(SIGSTOP);//REPLACE THIS LINE; pause then child must send sigcont to parent
        kill -sigcont getppid();
        return thestruct;
    }
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
    raise(SIGSTOP);
    
    fclose(fo);
}


