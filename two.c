#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>


struct LinkedList
{
    char* data;
    struct LinkedList *next;
    
};
typedef struct LinkedList *node;

node createNode()
{
    node temp;
    temp = (node)malloc(sizeof(struct LinkedList)); 
    temp->next = NULL;
    return temp;
}

node addNode(node head, char* value)
{
    node temp,p;
    temp = createNode();
    temp->data = value; 
    if(head == NULL){
        head = temp;    
    }
    else{
        p  = head;
        while(p->next != NULL){
            p = p->next;
        }
        p->next = temp;
    }
    return head;
}

typedef struct tree_node
{
    FILE* fp;
    char* rootNode;
    int numChildren;
    node headNode;//**head child node**

}tree_node;

tree_node *lineHandle(tree_node *thestruct)
{
 
    FILE* fp = thestruct->fp;
    char buffer[100];
    char * temp;
    node newNode;
    fgets(buffer, 100, fp);
    char *rootNode = strtok(buffer," ");
    char *strNumChild = strtok(NULL," ");
    int numChild = atoi(strNumChild); 
    node head;
    
        if(numChild>1)
        {
            head = createNode();    
            head->data = strtok(NULL," "); // the last process name may be \n delimated 
            int i;
             
            for(i=0;i<numChild-2;i++){     
                  temp = strtok(NULL," ");      
                  newNode = addNode(head,temp);
            } 
                  temp = strtok(NULL,"\n");
                  newNode = addNode(head,temp);
                   
              thestruct->rootNode = rootNode;
              thestruct->numChildren = numChild; 
              thestruct->headNode = head;
              thestruct->fp = fp;
              
              printf("%s\n",rootNode);
              //createTree(thestruct); 
            
        }
        else if(numChild==1)
        {
              head = createNode(); 
              head->data = strtok(NULL,"\n");
              
              thestruct->rootNode = rootNode;
              thestruct->numChildren = numChild; 
              thestruct->headNode = head;
              thestruct->fp = fp;
              printf("%s\n",rootNode);
        }else{
              thestruct->rootNode = rootNode;
              thestruct->numChildren = numChild; 
             head = NULL;// if number of children is = 0 do something
              thestruct->fp = fp;
              printf("%s\n",rootNode);
        }
    
    return thestruct;
}
void createTree(tree_node *thestruct)
{
    pid_t pid;
    FILE* fp = thestruct->fp;
    FILE* gp = thestruct->fp;
    int numKids = thestruct->numChildren;
    //node p = thestruct->headNode;
    int procNum;
    char buffer[100];   
       
    
    for(procNum = 0; procNum < numKids; procNum++)
     {
    
          pid = fork();
          if (pid == 0)
          {
          break;   
          }
      }
      //danger zone both parent and child operate here
//      count++;
//      int j;
//      for(j=0;j<count;j++){
//      fgets(buffer, 100, fp);
//      }
      
    if (pid == 0) // after for loop if you are a child process 
    {// child specific stuff
       // printf("I am child process %d\n",procNum+1);
        int i; 
        for(i=0;i<procNum+1 ;i++){
            bzero(buffer,100);
            fgets(buffer, 100, fp);
        }
        //fgets(buffer, 100, fp);
        char *rootNode = strtok(buffer," ");      
        char *compare = thestruct->headNode->data;
        
        if(strcmp(rootNode,compare)==0)
        {   
            tree_node *nextNode = malloc(sizeof(tree_node));
            nextNode->fp = gp;
            nextNode = lineHandle(nextNode);
            createTree(nextNode);
           //printf("hello\n");
        }else{
            //loop head nodes
            while(strcmp(thestruct->headNode->data,rootNode)!=0){
            thestruct->headNode = thestruct->headNode->next;
            }
            thestruct->rootNode = rootNode;
            thestruct->numChildren = numKids; 
            
            
        
        }
        
       
    }else {
    
    if(numKids==0)//means ur a leaf
    {
        fgets(buffer, 100, fp);
        char *rootNode = strtok(buffer," "); 
        printf("%s\n",rootNode);
    }
    //printf("I am the parent process\n");
    // parent stuff
    // if leaf then wait
    
    }
}




int main(int argc, char *argv[])
{
    char* fileName = argv[1];
    char buffer[100];
    FILE* fp;
    fp = fopen(fileName,"r");
    tree_node *initial = malloc(sizeof(tree_node));
    initial->fp = fp;
   
    tree_node *thestruct = lineHandle(initial);
    createTree(thestruct);

}






