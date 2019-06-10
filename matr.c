#include <stdio.h>
#include <stdlib.h>
#include "group.c"


typedef struct matr
{
    char color;
    group *pGroup;
    struct matr *up;
    struct matr *left;
    struct matr *down;
    struct matr *right;
}matr;

matr* createMatr(long n,long m){
     matr *head=null;
     head=malloc(sizeof(matr));
     head->color='0';
     head->right=null;
     head->down=null;
     head->pGroup=null;
     head->up=null;
     head->left=null;
     matr *currF=head;
     //printf("\n");
     for(int i=0;i<n;i++){
         matr *curr=currF;
       //  printf("\n");
         for(int j=0;j<m-1;j++){
         //    printf("\n");
             if(curr->right==null){
                 curr->right=malloc(sizeof(matr));
                 curr->right->left=curr;
                 curr->right->right=null;
                 curr->right->down=null;
                 curr->right->pGroup=null;
                 curr->right->color='0';
                 if(curr->up!=null){
                     curr->right->up=curr->up->right;
                     curr->up->right->down=curr->right;
                 }else{
                     curr->right->up=null;
                 }
             }
             curr=curr->right;
         }
         if(currF->down==null&&i<n-1){
             currF->down=malloc(sizeof(matr));
             currF->down->up=currF;
             currF->down->down=null;
             currF->down->left=null;
             currF->down->right=null;
             currF=currF->down;
         }
     }
     return head;
}


void free_row(matr *rowHead){
    matr *curr=rowHead;
    while(curr!=null){
        if(curr->right==null){
            if(curr->left!=null) {
                curr = curr->left;
                free(curr->right);
                curr->right = null;
            }else{
                return ;
            }
        }else{
            curr=curr->right;
        }
    }
}

void free_matr(matr **head) {
    matr *current = *head;
    while(current!=null){
        if(current->down==null){
            if(current->up!=null){
                current=current->up;
                free_row(current->down);
                free(current->down);
                current->down=null;
            }else{
                free_row(current);
                free(current);
                current=null;
                break;
            }
        }else{
            current=current->down;
        }
    }
    *head=null;
    //printf("\n");
}
