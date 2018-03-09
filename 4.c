#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include "4.h"
#include <ctype.h>
int ap=0;

int initArray(char* expr){
  int sz = 0;
  int sp=0;
  
  int len = strlen(expr);
  //printf("length: %d\n",len);
  while(sp<len){
  char tmp= expr[sp];
  //printf("%c\n",tmp);
  if(tmp == '(' || tmp==')'||tmp==' '){
  //skip
  sp++;
  }
  else if(tmp=='+' || tmp=='*'){
  sz++;
  sp++;
  }
  else if(isdigit(tmp)){
    while(isdigit(tmp)){
      sp++;
      tmp= expr[sp];
    }
    sz++;
  }
  
  
  } 
  return sz;
}
int skipParen(char* expr,int sp){
char tmp= expr[sp];
//printf("%s\n",expr);
  while(tmp !=')'){
        sp++;
        tmp= expr[sp];
        
              printf("%c\n",tmp);
              if(tmp == '(' ){
              //skip
                sp = skipParen(expr,sp);
                
              }
        
  }
  return sp;    
}
int number(char* expr){
int sp=0;
int len  = strlen(expr);
char tmp= expr[sp];
    while(sp<len){
      if(!isdigit(tmp)){
        return 0;      
      }
    
      sp++;
      tmp= expr[sp];
    }
  return 1;
}
void setArray(char* expr,char* arr[]){
  //printf("test: %s\n",arr[1]);
  char tmp;
  int len  = strlen(expr);
  int sp=0;
  //printf("init: %s\n",expr);
  if(expr[0] == '('){
    //printf("cut\n");
    if(expr[len-1] == ')'){
      //printf("cut\n");
      char * cut=malloc(sizeof(char) * 100);
      strncpy(cut,expr+1, len-2);
      strcpy(expr,cut);
      //free(cut);
      //printf("cutted: %s\n",expr);
    }
  }
  if(number(expr)){
    arr[ap]= expr;
    ap++;
    return;
  }
  //printf("%s\n",expr);
    while(sp<len){
    tmp= expr[sp];
    //printf("%c\n",tmp);
    if(tmp == '(' ){
    //skip
    //printf("paren\n");
      sp = skipParen(expr,sp);
    }
    else if(tmp=='+' || tmp=='*'){
    //printf("operator: %c %d\n",tmp,sp);
    //char* op;
      if(tmp == '+'){
        arr[ap]="+";
      }
      else{
        arr[ap]="*";
      }
       
       ap++;
       //p1
       char * str1=malloc(sizeof(char) * 100);
       strncpy(str1,expr,(sp));
       //printf("str1: %s\n",str1);
         
       //p2
       char * str2=malloc(sizeof(char) * 100); 
       strncpy(str2,expr+sp+1,((len)-(sp)));
       //printf("str2: %s\n",str2);
         
         if(number(str2)){
           setArray(str2, arr);
         setArray(str1, arr);
         
         }
         else{
           setArray(str1, arr);
         setArray(str2, arr);
         
         }
         //free(str2);
         //free(str1);
         
         
       return;
    }

    sp++;
    }
  

  

}
void uniqueOP(char* init[],int len){
  int idp=0;
  int idm=0;
  int chk=0;
  //char* tmp=malloc(sizeof(char) * 100);
  while(chk<len){
  //printf("%s\n",init[chk]);
    if(strcmp(init[chk],"+")==0){
      //printf("plus\n");
      char* tp=malloc(sizeof(char)*100);
      sprintf(tp,"+%d",idp);
      //printf("%s\n",tp);
      init[chk]=tp;
      //printf("%s\n",init[chk]);
      idp++;
    }
    else if(strcmp(init[chk],"*")==0){
      //printf("mult\n");
      char* tm=malloc(sizeof(char)*100);
      sprintf(tm,"*%d",idm);
      //printf("%s\n",tm);
      init[chk]=tm;
      //printf("%s\n",init[chk]);
      idm++;
    }
    
    
    
    chk++;
    }

  return;
}
FILE* treeSchema(char * arr[],int sz){
  FILE* sc =fopen("schema.txt","w");
  int p=0;
  while(p<sz){
    char* tmp1 = arr[p];
    char* tmp2 = arr[p+1];
    char* tmp3 = arr[p+2];
    if(number(tmp1)){
    fprintf(sc,"%s 0\n",tmp1);
      p++;
    }
    else{
      if(number(tmp2) && number(tmp3)){
        fprintf(sc,"%s 1 %s %s\n",tmp1,tmp2,tmp3);
      }
      else if(!number(tmp2)&& number(tmp3)){
        fprintf(sc,"%s 2 %s %s\n",tmp1,tmp2,tmp3);
      }
      else if(number(tmp2)&& !number(tmp3)){
        fprintf(sc,"%s 3 %s %s\n",tmp1,tmp2,tmp3);
      }
      else if(!number(tmp2) && !number(tmp3)){
        fprintf(sc,"%s 4 %s %s\n",tmp1,tmp2,tmp3);
      }
      p++;
    }
  
  }
  fclose(sc);
  FILE* fp = fopen("schema.txt","r");
  return fp;

}

//tree_node* createTree(tree_node *thestruct, char* ident)
//{    
//    //
//    FILE* fp = thestruct->fp;
//    char buffer[100];
//    char * temp;
//    if(strcmp(ident,"")==0){
//    //printf("init\n");
//    fgets(buffer, 100, fp);
//    
//    }
//    else{
//    char yayo[100];
//      while(fgets(buffer,100,fp)){
//
//      //you want to compare ident with first letter of buffer
//      
//        sprintf(yayo,"%s",buffer);
//        
//       char *chk = strtok(yayo," ");
//       
//       int foo = strcmp(ident,chk);
////       printf("\n--chk--\n");
////       printf("%s%s",ident,chk);
////       printf("%d",foo);
////       printf("\n--chk--\n");
//        if(strcmp(ident,chk)==0){
//           //printf("break\n");
//                   break;       
//        }
//        
//      }
//       
//    }
//  printf("%s",buffer);
//  fflush(stdout);
//    char *rootNode = strtok(buffer," ");
//    //printf("%s",buffer);
//    char *mode = strtok(NULL," ");
//   //printf("%s\n",strNumChild);
//    int md = atoi(strNumChild); 
//    if(md==0){
//     sleep(1);
//     return thestruct;
//    }
//    node newNode;
//// printf("%s\n%d\n",rootNode,numKids);
//    
//    
//    thestruct->rootNode = rootNode; 
//    thestruct->mode = md;
//     //printf("%s %d \n",rootNode, numKids);
//    node firstBorn = createNode();     
//    //printf("%s\n",buffer);
////    if(numKids ==1){
////    char *stream = strtok(NULL,"\r\n ");
////    firstBorn->data = stream; // the last process name may be \n delimated 
////    }
////    else{
//    char *stream = strtok(NULL," ");
//    firstBorn->data = stream; // the last process name may be \n delimated 
//    }
//    
//    
//    if(numKids > 1){
//    int i;
//    for(i=0;i<numKids-2;i++){     
//    temp = strtok(NULL," ");      
//    newNode = addNode(firstBorn,temp);
//    } 
//    temp = strtok(NULL,"\n");
//    newNode = addNode(firstBorn,temp);
//    }
//    //
//     
//    node tmp;
//    tmp = firstBorn;
//    //printf("%d\n",numKids);
//    int pid;
////    if(numKids == 1){
////      pid = fork();
////      if (pid==0){
////      //printf("work\n");
////        createTree(thestruct, tmp->data);
////      }
////          wait(NULL);
////    return thestruct;
////    
////    }
////    else{//
//              //printf("%s\n",tmp->next);
//      while(tmp != NULL){
//       // B =tmp->data 
//        //printf("%s\n",tmp->data);
//              // printf("work\n");
//              // int procNum;
//               
//              
//         pid = fork();
//         
//                          if (pid == 0) 
//                 {
//                     break; // break the loop if you are child process so processes dont grow by 2^n
//                 }
//               if (pid>0){
//                 wait(NULL);
//               
//               }
//          
//        tmp = tmp->next;
//      }  
//      
//      
//          if (pid == 0) 
//               {
//                   // child specific stuff. procNum is set to the "child number"
//                   //recall the function createTree(theStruct)
//                //printf("activated \n");
//                   createTree(thestruct, tmp->data);   
//               } 
//               
//               
////               
////       wait(NULL);
////    return thestruct;
////    }
//    
//
//    wait(NULL);
//    return thestruct;
//
//}
int main(int argc, char *argv[])
{
    //FILE *fo = freopen("output2.txt","w",stdout);
    char* fileName = argv[1];
    char buffer[100];
    FILE* fp;
    fp = fopen(fileName,"r");
    
  fgets(buffer,100,fp);
  char* expr = malloc(sizeof(char) * 100);
  sprintf(expr,"%s",buffer);
  
    int sz;
    sz = initArray(expr);
    
    char* init[sz];
    //init[0]=expr;
    setArray(expr,init);
    uniqueOP(init,sz);
    FILE* ts = treeSchema(init,sz);
//    int chk=0;
//   // printf("done\n");
//    while(chk<sz){
//    printf("%s\n",init[chk]);
//    chk++;
//    }
    
    //printf("%d\n",sz);
    //fclose(fi);
    //fclose(fp);

//    tree_node *initNode = malloc(sizeof(tree_node));
//    initNode->fp = ts;  
//    
//    initNode = createTree(initNode, "");
//    
//    fclose(fo);
}

