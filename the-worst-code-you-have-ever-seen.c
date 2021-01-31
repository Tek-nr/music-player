#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
FILE* inputf, * outputf;

struct node
{
    char songName[51];
    struct node* next;
};

struct node* head = NULL; 
struct node* tail = NULL; 
struct node* last= &head; 

void InsertSong(char place, char SongName[51]) {

    if (head == NULL) { 
        head = (struct node*)malloc(sizeof(struct node));
        strcpy(head->songName, SongName);
        tail = head;
        head->next = NULL;
        
    }

    else {
        struct node* tmp = (struct node*)malloc(sizeof(struct node));
        if (place == 'H') {
            strcpy(tmp->songName, SongName);
            tmp->next = head;
            head = tmp;
        }
        else if (place == 'T') {
            strcpy(tmp->songName, SongName);
            tail->next = tmp;
            tail->next->next = NULL;
            tail = tmp;
        }
    }
}

void RemoveSong(char SongName[51]) {

    struct node* tmp = (struct node*)malloc(sizeof(struct node));
    struct node* prev = (struct node*)malloc(sizeof(struct node));
    struct node* new_head = (struct node*)malloc(sizeof(struct node));
    tmp = head;

    if (head == tail) { 
        head = NULL;
        return;
    }

    if (last != NULL && strcmp(last->songName, SongName) == 0) {
        fprintf(outputf, "Cannot Remove The Playing Song\n*****\n");
        return;
    }

    if (head != NULL && (strcmp(tmp->songName, SongName) == 0)) { 
        new_head = tmp->next;
        free(head);
        head = new_head;
        return;
    }
    else {
        while (tmp != NULL && (strcmp(tmp->songName, SongName) != 0)) {
            prev = tmp;
            tmp = tmp->next;
        }
        if (tmp == NULL) return;
        prev->next = tmp->next;
        free(tmp);
    }
}

void printPlaylist() 
{
    struct node* tmp = (struct node*)malloc(sizeof(struct node));
    tmp = head;

    if (tmp == NULL) {
        fprintf(outputf, "No Songs To Print\n*****\n");
        return;
    }

    else {

        if (head->next==NULL) {
            fprintf(outputf,"%s\n*****\n", tmp->songName);
            return;
        }

        while (tmp != NULL) {
            fprintf(outputf, "%s\n", (tmp->songName));
            tmp = tmp->next;
        }
        fprintf(outputf, "*****\n");  
    }
}

void reversePlaylist() {
    if (head == NULL || head->next == NULL) {
        return;
    }

    struct node* tmp = (struct node*)malloc(sizeof(struct node));
    struct node* next = (struct node*)malloc(sizeof(struct node));
    struct node* prev = NULL;
    tmp = head;
    while (tmp != NULL) {
        next = tmp->next;
        tmp->next = prev;
        prev = tmp;
        tmp = next;
    }
    head = prev;
}

void PrintReversedPlaylist() {
    reversePlaylist();
    printPlaylist();
    reversePlaylist();
}

void NextPlaySong() 
{
    if (head == NULL) {
        fprintf(outputf, "No Songs To Play\n*****\n");
        return;
    }

    else {

        if (last->next != NULL && head!=NULL)
            last = last->next;
            
        else
            last = head;

        fprintf(outputf, "Playing\t %s\n*****\n", (last->songName));       
    }
}

void PrevPlaySong() {
    reversePlaylist();
    NextPlaySong();
    reversePlaylist();
}


void MoveSong(char place,char eklenecek[51], char referans[51]) { 
    struct node* iter = (struct node*)malloc(sizeof(struct node));
    struct node* iter2 = (struct node*)malloc(sizeof(struct node));
    struct node* tmp = (struct node*)malloc(sizeof(struct node));
    struct node* tmp2 = (struct node*)malloc(sizeof(struct node)); 
    iter = head;
    iter2 = head;
    
    if (head == NULL && head->next==NULL) {
            return;
        }

    if (place == 'B') {
        if (strcmp(head->songName,referans)==0) {
            while ((iter2->next!= NULL) && (strcmp(iter2->next->songName, eklenecek) != 0)) {
                iter2 = iter2->next;
            } tmp2 = iter2->next;

            if (tmp2->next == NULL) {
                tmp2->next = head;
                iter2->next = NULL;
                head = tmp2;
                return;
            }

            else {
                iter2->next = tmp2->next;
                tmp2->next = head;
                head = tmp2;
                return;
            }
        }

        while ((iter->next != NULL) && strcmp(iter->next->songName, referans) != 0) {
            iter = iter->next;                         
        } tmp = iter->next;
        
        while ((iter2->next != NULL) && (strcmp(iter2->next->songName, eklenecek) != 0)) {
            iter2 = iter2->next;            
        } tmp2 = iter2->next;

        iter2->next = tmp2->next;
        tmp2->next = tmp;
        iter->next = tmp2;
    }

    else if (place == 'A') {
        if (strcmp(head->songName, eklenecek) == 0) {
            while ((iter2 != NULL) && (strcmp(iter2->songName, referans) != 0)) {
                iter2 = iter2->next;
            }tmp2 = iter2;
            head = iter->next;
            iter->next = iter2->next;
            iter2->next = iter;
            return;
        }

        while ((iter->next != NULL) && strcmp(iter->next->songName, eklenecek) != 0) {
            iter = iter->next;            
        }tmp = iter->next;

        while ((iter2!= NULL) && (strcmp(iter2->songName, referans) != 0)) {
            iter2 = iter2->next;
        }tmp2=iter2;

        iter->next = tmp->next;
        tmp->next = iter2->next;
        iter2->next = tmp;
    }
    
}


int main() {

    char command[31], SongName[51], place;
    inputf = fopen("input.txt", "r");
    outputf = fopen("output.txt", "w");

    if (inputf == NULL) {
        printf("ERROR! Input file was not opened!");
        return;
    }
    else if (outputf == NULL) {
        printf("\nERROR! Output file was not opened!");
        return;
    }
    else {
        while (fscanf(inputf, "%s", &command) != -1) {

            int conTab = fscanf(inputf, "%d", &conTab);

            if (strcmp(command, "InsertSong") == 0) {
                int getInfo = fscanf(inputf, "%c%s", &place, SongName);
                InsertSong(place, SongName);  
            }

            else if (strcmp(command, "RemoveSong") == 0) {
                int getInfo = fscanf(inputf, "%s", SongName);
                RemoveSong(SongName);
            }

            else if ((strcmp(command, "PrintPlaylist") == 0)) {
                int getInfo = fscanf(inputf, "%c", &place);
                if (place == 'F')
                    printPlaylist();
                else if (place == 'R')
                    PrintReversedPlaylist();
            }

            else if (strcmp(command, "ReversePlaylist") == 0) {
                reversePlaylist();
            }

            else if (strcmp(command, "MoveSong") == 0) {
                char *eklenecek[51], *referans[51];
                int getInfo = fscanf(inputf, "%c%s%s", &place, eklenecek, referans);
                    MoveSong(place,eklenecek, referans);
            }

            else if (strcmp(command, "PlaySong") == 0) {
                int getInfo = fscanf(inputf, "%c", &place);
                if (place == 'N') {
                    NextPlaySong();
                }
                else if (place == 'P') {
                    PrevPlaySong();
                }
            }
        }
    }
    fclose(inputf);
    fclose(outputf);
    return 0;
}
