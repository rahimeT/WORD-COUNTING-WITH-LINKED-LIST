#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*Dosyadan okunan metin, oncelikle node1 kullanilarak bagli listeye donusturulur.Sonrasýnda bu bagli listeden farkli kelimeler ile yeni bir
  bagli liste daha olusturulur ve bu bagli kullanilarak hangi kelimeden kac adet oldugu saptanýrken,saptanan kelimelerin adetine göre node2
  kullanilarak buyukten kucuge doðru siralanan  bagli liste olusturulur.*/
struct node1 {
    char word[20];
    struct node1 *next;
}*head1;

struct node2 {
	char word[20];
    int count;
    struct node2 *next;
}*head2;
/*addList1 fonksiyonu oluþturulurken https://www.tutorialspoint.com/learn_c_by_examples/simple_linked_list_program_in_c.htm sitesinden
 faydalýnýlmýþtýr.*/
void addList1(char* elm){
	if (head1==NULL){
		head1=(struct node1*) malloc(sizeof(struct node1));
		strcpy(head1->word,elm);
		head1->next=NULL;
		return;
	}
	struct node1* newNode=(struct node1*) malloc(sizeof(struct node1));
	strcpy(newNode->word,elm);
	newNode->next=NULL;
	struct node1 *temp=head1;
	while(temp->next!= NULL){
		temp=temp->next;
	}
	temp->next=newNode;
}
/* basa_ekle fonksiyonu oluþturulurken https://www.codesdope.com/blog/article/inserting-a-new-node-in-a-linked-list-in-c/ sitesinden
 yararlanýlmýþtýr. */
void basa_ekle(char *w,int adet){
	struct node2 *newNode=(struct node2*) malloc(sizeof(struct node2));
	strcpy(newNode->word,w);
	newNode->count=adet;
	newNode->next=head2;
	head2=newNode;
}
/* araya_ekle fonksiyonu oluþturulurken https://www.codesdope.com/blog/article/inserting-a-new-node-in-a-linked-list-in-c/ sitesinden
 yararlanýlmýþtýr. */
void araya_ekle(int pos,char *w,int adet){
	struct node2* newNode=(struct node2*) malloc(sizeof(struct node2));
	struct node2* curr=head2;
	strcpy(newNode->word,w);
	newNode->count=adet;
	newNode->next=NULL;
	int i;
	for(i=0;i<pos-1;i++){
		curr=curr->next;
	}
	newNode->next=curr->next;
	curr->next=newNode;
}
/*sona_ekle fonksiyonu oluþtutulurken https://codeforwin.org/2015/09/c-program-to-insert-node-at-end-of-singly-linked-list.html sitesinden
faydalýnýlmýþtýr. */
void sona_ekle(char *w,int adet){
	struct node2 *newNode=(struct node2*) malloc(sizeof(struct node2));
	struct node2* curr=head2;
	strcpy(newNode->word,w);
	newNode->count=adet;
	newNode->next=NULL;
	while(curr->next!=NULL){
		curr=curr->next;
	}
	curr->next=newNode;
}
void insert(char *w,int adet){
	if(head2==NULL){
		head2=(struct node2*) malloc(sizeof(struct node2));
		strcpy(head2->word,w);
		head2->count=adet;
		head2->next=NULL;
		return;
	}
	struct node2 *temp=head2;
	int pos=0;
	while(adet<=temp->count && temp->next!=NULL){
		temp=temp->next;
		pos++;
	}
	if(pos==0 && temp->next==NULL){
		if(adet<=temp->count){
			sona_ekle(w,adet);
		}
		else{
			basa_ekle(w,adet);
		}
	}
	else if(temp->next==NULL){
		sona_ekle(w,adet);
	}
	else if(pos==0){
		basa_ekle(w,adet);
	}
	else{
		araya_ekle(pos,w,adet);
	}
}
/*printList fonksiyonu oluþturulurken https://www.tutorialspoint.com/learn_c_by_examples/simple_linked_list_program_in_c.htm sitesinden
 faydalýnýlmýþtýr.*/
void printList() {

   struct node2 *temp = head2;
   int sayac=1;
   while(temp != NULL) {
      printf("%d. %s: %d\n",sayac,temp->word,temp->count);
      temp = temp->next;
      sayac++;
   }

}

int main(){
 	char str[20];
 	struct node1 *temp1,*temp2,*curr;
 	int count=0;
 	int size=0;
 	int tespit=0;
 	int i,j,k;
 	FILE* fp;
    fp=fopen("belge.txt","r");
 	if ( fp == NULL )
    {
        printf( "HATA" ) ;
		exit(1);
    }
    while(!feof(fp))
	{
    	fscanf(fp,"%s",str);
		addList1(&str[0]);
	}
	fclose(fp);
	temp1=head1;
	while(temp1!=NULL){
		count++;
		temp1=temp1->next;
	}
	temp1=head1;
	temp2=head1;
	curr=head1;
	for(i=0 ;i<count ;i++){
		for(j=0 ;j<i ;j++){
			if(strcmp(temp1->word,curr->word)==0){
				tespit=1;
				break;
			}
			temp1=temp1->next;
		}
		if(tespit!=1){
			for(k=0 ;k<count ;k++){
				if(strcmp(temp2->word,curr->word)==0){
					size++;
				}
				temp2=temp2->next;
			}
			insert(&curr->word[0],size);
		}
		tespit=0;
		curr=curr->next;
		size=0;
		temp1=head1;
		temp2=head1;
	}
	printList();
 }
