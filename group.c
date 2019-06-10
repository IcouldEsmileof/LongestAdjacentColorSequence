#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#define null NULL
typedef struct group
{
    //elementi
    long i;
    long count;
    long groupId;
    struct group *next;
    bool isChecked;
}group;

long getLength(group* head){
    group *current=head;
    int i=0;
    while(current!=NULL){
        i++;
        current=current->next;
    }
    return i;
}

group* push_end(group * head,group *newGroup) {
    group * current = head;
    while (current->next != NULL) {
        current = current->next;
    }

    current->next = newGroup;
    current->next->count = 1;
    current->next->next = NULL;
    current->next->i=(current->i)+1;
    current->next->groupId=current->next->i;
    current->next->isChecked=false;
    return current->next;
}

int pop_head(group ** head) {
    int v = -1;
    group *next_node = NULL;

    if ((*head )== NULL) {
        return v;
    }
    if((*head)->next!=NULL) {
        next_node = (*head)->next;
    }else{
        next_node=NULL;
    }
    v = (*head)->count;
    free(*head);
    *head = next_node;
    return v;
}
long pop(group ** head, long n) {
    long v = -1;
    group * current = *head;
    group * temp_node = NULL;

    if(current->groupId==n){
        pop_head(head);
    }

    while(current->next->groupId!=n) {
        if (current->next->next == NULL) {
            return v;
        }
        current = current->next;
    }

    temp_node = current->next;
    v = temp_node->count;
    current->next = temp_node->next;
    free(temp_node);
    return v;
}

void free_list(group **head)
{
    while(*head!=NULL){
        pop_head(head);
    }
}