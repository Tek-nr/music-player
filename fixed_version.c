#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
	char name[51];
	struct Node* prev;
	struct Node* next;
};

struct Node* head = NULL; 
struct Node* tail = NULL; 
struct Node* currentSong = &head;

struct Node* NewNode(char name[51]) {

	struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
	strcpy(new_node->name, name);
	new_node->next = NULL;
	new_node->prev = NULL;
	return new_node;
}

void InsertHead(char name[51]) {

	struct Node* new_node = NewNode(name);
	//for the first node
	if (head == NULL) {
		head = new_node;
		tail = head;
		return;
	}

	head->prev = new_node;
	new_node->next = head;
	head = new_node;	
}

void InsertTail(char name[51]) {  

	struct Node* new_node = NewNode(name);
	//for the first node
	if (head == NULL) {
		head = new_node;
		tail = head;
		return;
	}

	tail->next = new_node;
	new_node->prev = tail;
	tail = new_node;
}

void RemoveSong(char name[51]) {

	if (head == NULL)
		return;

	if (strcmp(currentSong->name, name) == 0) {
		printf("Cannot Remove The Playing Song\n*****\n");
		return;
	}
	
	struct Node* tmp = head;
	struct Node* tmp2 = tail;
	struct Node* new_head = NULL;
	struct Node* new_tail = NULL;

	if (strcmp(head->name, name) == 0) {
		new_head = tmp->next;
		free(head);
		head = new_head;
		head->prev = NULL;
		return;
	}
	
	else if (strcmp(tail->name, name) == 0) {
		new_tail = tmp2->prev;
		free(tail);
		tail = new_tail;
		tail->next = NULL;
		return;
	}

	//struct Node* tmp = head;
	while (tmp != NULL && strcmp(tmp->name, name) != 0) {
		tmp = tmp->next;
	}

	if (tmp == NULL) {
		return;
	}

	tmp->prev->next = tmp->next;
	tmp->next->prev = tmp->prev;
	free(tmp);

}


void PlayNextSong() {

	if (head == NULL) {
		printf( "No Songs To Play\n*****\n");
		return;
	}

	if (currentSong->next != NULL)
		currentSong = currentSong->next;
	else
		currentSong = head;
	printf("Playing\t%s\n*****\n", (currentSong->name));
}

void PlayPrevSong() {

	if (head == NULL) {
		printf("No Songs To Play\n*****\n");
		return;
	}

	if (currentSong->prev != NULL)
		currentSong = currentSong->prev;
	else
		currentSong = tail;
	printf("Playing\t%s\n*****\n", currentSong->name);	
}

void ReversePlaylist() { 
	struct Node* tmp = NULL;
	struct Node* curr = head;

	tail = head;
	while (curr != NULL) {
		tmp = curr->prev;
		curr->prev = curr->next;
		curr->next = tmp;
		curr = curr->prev;
	}

	if (tmp != NULL) {
		head = tmp->prev;
	}
}

void MoveSongBefore(char songToAdd[51], char refSong[51]) {
	struct Node* sa = head; //song to add
	struct Node* rs = head; //ref song

	while ((sa != NULL) && (strcmp(songToAdd, sa) != 0)) {
		sa = sa->next;
	}	
	
	while ((rs != NULL) && (strcmp(refSong, rs) != 0) ) {
		rs = rs->next;
	}

	if (rs == NULL || sa == NULL || sa == rs)
		return;

	if (strcmp(sa, tail) == 0 && strcmp(rs, head) == 0) {
		tail = tail->prev;
		sa->next = rs;
		rs->prev = sa;
		tail->next = NULL;
		head = head->prev;
	}

	else if (strcmp(sa, head) == 0) {
		head = head->next;
		sa->next = rs;
		rs->prev->next = sa;
		sa->prev = rs->prev;
		rs->prev = sa;
		head->prev = NULL;
	}	
	
	else if (strcmp(rs, head) == 0) {
		sa->prev->next = sa->next;
		sa->next->prev = sa->prev;
		sa->next = rs;
		rs->prev = sa;
		sa->prev = NULL;
		head = sa;
	}	
	
	else if (strcmp(sa, tail) == 0) {
		tail = tail->prev;
		sa->next = rs;
		sa->prev = rs->prev;
		rs->prev->next = sa;
		rs->prev = sa;
		tail->next = NULL;
	}

	else {
		sa->prev->next = sa->next;
		sa->next->prev = sa->prev;
		rs->prev->next = sa;
		sa->prev = rs->prev;
		rs->prev = sa;
		sa->next = rs;
	}
}

void MoveSongAfter(char songToAdd[51], char refSong[51]) {
	struct Node* sa = head;
	struct Node* rs = head;

	while ((sa != NULL) && strcmp(songToAdd, sa) != 0) {
		sa = sa->next;
	}

	while ((rs != NULL) && strcmp(refSong, rs) != 0) {
		rs = rs->next;
	}

	if (rs == NULL || sa == NULL || sa == rs)
		return;

	if (strcmp(sa, head) == 0 && strcmp(rs, tail) == 0) {
		head = head->next;
		rs->next = sa;
		sa->prev = rs;
		sa->next = NULL;
		head->prev = NULL;
		tail = tail->next;
	}

	else if (strcmp(sa, head) == 0) {
		head = head->next;
		sa->prev = rs;
		sa->next = rs->next;
		rs->next->prev = sa;
		rs->next = sa;
		head->prev = NULL;
	}

	else if (strcmp(sa, tail) == 0) {
		tail = tail->prev;
		sa->prev = rs;
		rs->next->prev = sa;
		sa->next = rs->next;
		rs->next = sa;
		tail->next = NULL;
	}

	else if (strcmp(rs, tail) == 0) {
		sa->prev->next = sa->next;
		sa->next->prev = sa->prev;
		sa->prev = rs;
		rs->next = sa;
		sa->next = NULL;
		tail = sa;
	}

	else {
		sa->prev->next = sa->next;
		sa->next->prev = sa->prev;
		sa->prev = rs;
		rs->next->prev = sa;
		sa->next = rs->next;
		rs->next = sa;
	}


}

void DisplayForward() {

	if (head == NULL) {
		printf("No Songs To Print\n*****\n");
		return;
	}

	struct Node *temp = head;
	while (temp != NULL) {
		printf("%s\n", temp->name);
		temp = temp->next;
	}printf("*****\n");
}

void DisplayReversed() {

	if (head == NULL) {
		printf("No Songs To Print\n*****\n");
		return;
	}

	struct Node *temp = tail;
	while (temp != NULL) {
		printf("%s\n", temp->name);
		temp = temp->prev;
	}printf("*****\n");
}

int main() {
	PlayNextSong();
	DisplayForward();
	InsertHead("A");
	InsertHead("B"); 
	InsertHead("C");
	InsertTail("E");
	InsertTail("F");
	InsertTail("G");
	DisplayForward();
	PlayNextSong();
	PlayNextSong();
	MoveSongBefore("B", "F");
	DisplayForward();
	RemoveSong("C");
	DisplayForward();
	PlayPrevSong();
	PlayPrevSong();
	PlayPrevSong();
	PlayPrevSong();
	MoveSongBefore("F", "E");
	DisplayForward();	
	MoveSongBefore("B", "A");
	DisplayForward();		
	MoveSongAfter("A", "G");
	DisplayForward();
	ReversePlaylist();
	DisplayForward();



	printf("Head: %s\n",head->name);
	printf("Tail: %s\n",tail->name);
	printf("Current Prev: %s\n",currentSong->prev->name);
	printf("Current: %s\n",currentSong->name);
	printf("Current Next: %s\n",currentSong->next->name);

	return 0;
}
