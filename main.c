#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <direct.h>
#include "matr.c"



long findMax(group* head){
    group* current=head;
    unsigned long maxCount=0;
    while(current!=NULL) {
        if(current->isChecked==false) {
            group *curr = current;
            unsigned long currMax = curr->count;
            curr=curr->next;
            while (curr != null) {
                if (curr->groupId == current->groupId) {
                    currMax += curr->count;
                    curr->isChecked = true;
                }
                curr = curr->next;
            }
            if(currMax>maxCount){
                maxCount=currMax;
            }
        }
        current=current->next;
    }
    return maxCount;
}
void getSubstr(char c[],char newChar[],int start,int end){
    int len=strlen(c);
    if(start>len||end>len||start>end){
        return ;
    }
    for(int i=start;i<end;i++){
        newChar[i-start]=c[i];
    }
}
int main(int argc,char *argv[]) {
    if(argc<=1){
        printf("No arguments");
    }
    int arg;
    for (arg=1;arg<argc;arg++){
        char thisPath[FILENAME_MAX];
        _getcwd(thisPath,FILENAME_MAX);
        char testPath[FILENAME_MAX]="";
        getSubstr(thisPath,testPath,0,strlen(thisPath)-strlen("cmake-build-debug"));
        strcat(testPath,"tests\\");
        strcat(testPath,argv[arg]);
        FILE *f=NULL;
        f=fopen(testPath,"rb");
        if(f==NULL){
            printf("%s\n",argv[arg]);
            continue;
        }
        long n,m;
        char col;
        fscanf(f,"%ld%ld",&n,&m);
        fscanf(f,"%c",&col);
        matr *mat=createMatr(1,m);
        group *head=malloc(sizeof(group));
        head->next=null;
        head->count=0;
        head->groupId=1;
        head->i=1;
        mat->pGroup=head;
        matr *curr=null;

        for(long i=0;i<n;i++){
            curr=mat;
            for(long j=0;j<m;j++){
                fscanf(f,"%c",&col);
               // printf("%c ",col);
                if(curr->pGroup==null){
                    if(curr->left==null) {
                        curr->pGroup = malloc(sizeof(group));
                        push_end(head, curr->pGroup);
                        curr->pGroup->count = 1;
                        curr->pGroup->next = null;
                        curr->color = col;
                    }else{
                        if(curr->left->color==col){
                            curr->pGroup=curr->left->pGroup;
                            curr->left->pGroup->count++;
                            curr->color=col;
                        }else{
                            curr->pGroup = malloc(sizeof(group));
                            push_end(head, curr->pGroup);
                            curr->pGroup->count = 1;
                            curr->pGroup->next = null;
                            curr->color = col;
                        }
                    }
                }else {
                    if (curr->color == col) {
                        curr->pGroup->count++;
                        if(curr->left!=null){
                            if(curr->left->color==col){
                                curr->left->pGroup->groupId=curr->pGroup->groupId;
                            }
                        }
                    }else if(curr->left!=null){
                        if(curr->left->color==col){
                            curr->left->pGroup->count++;
                            curr->pGroup=curr->left->pGroup;
                            curr->color=col;
                        }else{
                            curr->pGroup=malloc(sizeof(group));
                            push_end(head,curr->pGroup);
                            curr->pGroup->count=1;
                            curr->color=col;
                        }
                    }else{
                        curr->pGroup=malloc(sizeof(group));
                        push_end(head,curr->pGroup);
                        curr->pGroup->count=1;
                        curr->color=col;
                    }
                }
                curr = curr->right;
                fscanf(f,"%c",&col);
            }
            //printf(" %d\n",i);
        }
        unsigned long ma=findMax(head);
        printf("%ld\n",ma);


        free_list(&head);
        free_matr(&mat);
        printf("\n");
    }
    return 0;
}