#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAMELEN 64
#define PLAYCOUNT 0
#define ARTISTID 1

struct artist {
    int artist_id;
    //char artist_name[NAMELEN];
    char artist_name;
    int playcount;
    int alt_id;
    struct artist *next;

};

struct play
{
  int user_id;
  int artist_id; 
  int playcount;
  struct play *next;
};

struct artist *read_artists(char *fname);
struct artist *add_artist(struct artist *head, struct artist *newp);
void print_artist(struct artist *p);
void print_artists(struct artist *head);
struct play *find_middle(struct play *p);
struct play *merge(struct play *a, struct play *b);
struct play *sort_plays(struct play *head);
struct artist* sort_artists(struct artist *p , int criterion);
struct artist *update_counts(struct artist *a, struct play *p);
int count_plays(struct play *head);
struct play *create_play(int id, int artist_id, int playcount);
struct play *filter_user(int user_id, struct play *head);
struct play *read_plays(char *file_name);
struct play *add_play(struct play *head, struct play *newp);
void free_artist(struct artist *p);
void free_artists(struct artist *p);
void free_plays(struct play *p);
void free_play(struct play *p);
void exit_usage();




struct artist *create_artist(int artist_id, char artist_name, int playcount)
{
  //printf("creatplay\n");
  playcount = 0;
  struct artist *a = (struct artist *)malloc(sizeof(struct artist));
  if (a != NULL){
  a->artist_id = artist_id;
  a->artist_name = artist_name;
  a->playcount = playcount;
  a->next = NULL;
  }
  return a;
}

struct artist *add_artist(struct artist *head, struct artist *newp)
{ 
  //printf("addplay\n");
  struct artist *tmp;
  if(head != NULL){
    if(newp == NULL){
      newp = head;
    }else{
      newp->next = head;
      }
    }
  return newp;
}

struct artist *read_artists(char *fname){
 //printf("read artist\n");
  FILE *fp;
  struct artist *creatStruct, *readPlays;
  readPlays = NULL;
  fp = fopen(fname, "r");
  if(!fp){
  fprintf(stderr, "error: unable to open %s\n", fname);
  return NULL;
  }
    int artist_id; 
    char artist_name;
    fscanf(fp, "%d\t%65[^\t\n]\n",&artist_id, &artist_name);
  while(feof(fp) == 0){
 
    creatStruct = create_artist(artist_id, artist_name);
    readPlays = add_artist(readPlays, creatStruct);
    fscanf(fp, "%d\t%65[^\t\n]\n",&artist_id, &artist_name);
  }  
//feof() -- return non-zero value if the end of file is reached

      if(fclose(fp)){
  fprintf(stderr, "error: unable to close %s\n", fname);
  return NULL;
      }
      free_artist(creatStruct);
      return readPlays;
}

void print_artist(struct artist *p)
{
  if(p == NULL){
    printf("NULL\n");
  }else{
    printf("%s (%d) [%d]\n", p->artist_name, p->artist_id, p->playcount);
  }
}

void print_artists(struct artist *head)
{
  //printf("print play\n");
  struct artist *tmp;
  tmp = head;
  if(tmp == NULL){
    printf("NULL\n");
  }else{
    while(tmp != NULL){
      print_artist(tmp);
      tmp = tmp ->next;
      }
    }
}

struct play *find_middle(struct play *p){
  struct play *slow = p;
  struct play *fast = p;
  while(fast->next != NULL && fast->next->next != NULL){
    slow = slow->next;
    fast = fast->next->next;
  }
  return slow;
}
struct play *merge(struct play *a, struct play *b){
  struct play *tmp = NULL;
  struct play *head = NULL;
  struct play *curr = NULL;

  if(b == NULL){
    return b;
  }else if(b == NULL){
    return a;
  }

  while(a != NULL && b != NULL){
    if(a->artist_id > b->artist_id){
      tmp = b;
      b = a;
      a = tmp;
    }

    if(head == NULL){
      head = a;
      curr = a;
    }else{
      curr->next = a;
      curr = curr->next;
    }
    a = a->next;
  }
  if(a == NULL){
    curr->next = b;
  }else{
    curr->next = a;
  }
  return head;
}

struct play *sort_plays(struct play *head){
  struct play *m = NULL;
  struct play *x = NULL;
  struct play *y = NULL;

  if(head == NULL || head->next == NULL){
    return head;
  }
  x = head;
  m = find_middle(head);
  y = m->next;
  m->next = NULL;
  return merge(sort_plays(x), sort_plays(y));
}

struct artist* sort_artists(struct artist *p , int criterion){
  struct list {
    void *val;
    struct list *next;
  };
  if(criterion == PLAYCOUNT || criterion == ARTISTID ){  
    
  }else{
    printf("error: list unsorted");
    return p;
}

}

struct artist *update_counts(struct artist *a, struct play *p){
  
}

int count_plays(struct play *head)
{
  //printf("countplay\n");
  struct play *p = head;
  int i = 0;
  while(p != NULL){
    i = i + p->playcount;
    p = p->next;
  }
  return i;
}


struct play *create_play(int id, int artist_id, int playcount)
{
  //printf("creatplay\n");
  struct play *a = (struct play *)malloc(sizeof(struct play));
  if (a != NULL){
  a->user_id = id;
  a->artist_id = artist_id;
  a->playcount = playcount;
  a->next = NULL;
  }
  return a;
}


struct play *filter_user(int user_id, struct play *head)
{
  struct play *tmp, *tmp2, *filtUserLinked = NULL;
  tmp = head;
  //printf("filter\n"); 
  while(tmp != NULL){
    //printf("filter loop\n");
    if(user_id == tmp->user_id){
      tmp2 = create_play(tmp->user_id, tmp->artist_id, tmp->playcount);
      filtUserLinked = add_play(filtUserLinked, tmp2);
      tmp = tmp->next;
        }else{
          tmp = tmp->next;
        }
    }
  return filtUserLinked;
  
}


struct play *read_plays(char *file_name){
 //printf("readplay\n");
  FILE *fp;
  struct play *creatStruct, *readPlays;
  readPlays = NULL;
  fp = fopen(file_name, "r");
  if(!fp){
  fprintf(stderr, "error: unable to open %s\n", file_name);
  return NULL;
  }
    int user_id, artist_id, playcount; 
    fscanf(fp, "%d %d %d", &user_id, &artist_id, &playcount);
  while(feof(fp) == 0){
 
    creatStruct = create_play(user_id, artist_id, playcount);
    readPlays = add_play(readPlays, creatStruct);
    fscanf(fp, "%d %d %d", &user_id, &artist_id, &playcount);
  }  
//feof() -- return non-zero value if the end of file is reached

      if(fclose(fp)){
  fprintf(stderr, "error: unable to close %s\n", file_name);
  return NULL;
      }
      free_play(creatStruct);
      return readPlays;
}

struct play *add_play(struct play *head, struct play *newp)
{ 
  //printf("addplay\n");
  struct play *tmp;
  if(head != NULL){
    if(newp == NULL){
      newp = head;
    }else{
      newp->next = head;
      }
    }
  return newp;
}


void free_artist(struct artist *p)
{
  free(p);
}

void free_artists(struct artist *p)
{
  struct artist *tmp;
  while(p != NULL){
    tmp = p;
    p = p->next;
    free(tmp);
    }
}

void free_play(struct play *p)
{
  free(p);
}

void free_plays(struct play *p)
{
  struct play *tmp;
  while(p != NULL){
    tmp = p;
    p = p->next;
    free(tmp);
    }
}

void exit_usage() {
  printf("USAGE: topk number file1 file2\n"
         "\n"
         "where command is\n"
         "\n"
         "   number is the number of artist to play.\n"
         "   file1 is the name of the artist data file.\n"
         "   file2 is the name of the play data file.\n"
         "\n");
   exit(1);
}

int main(int argc, char **argv){
  exit_usage();
  return 0;
}