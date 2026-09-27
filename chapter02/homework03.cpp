typedef struct node{
    int data;  struct node *next;
}linknode,*link;

link LinkListSort(link list){
    link sorted=list;
    link cur=list->next;
    sorted->next=nullptr;
    while(cur!=nullptr){
        link next=cur->next;
        if(cur->data<sorted->data){
            cur->next=sorted;
            sorted=cur;
        }else{
            link p=sorted;
            while(p->next!=nullptr && p->next->data<cur->data){
                p=p->next;
            }
            cur->next=p->next;
            p->next=cur;
        }
        cur=next;
    }
    return sorted;
}