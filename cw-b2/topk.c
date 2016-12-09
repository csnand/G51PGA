#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAMELEN 64
#define PLAYCOUNT 0
#define ARTISTID 1

struct artist {
    int artist_id;
    //char artist_name[NAMELEN];

    char *artist_name;
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
struct artist *create_artist(int artist_id, char *artist_name);

void print_artist(struct artist *p);
void print_artists(struct artist *head);
struct play *find_middle(struct play *p);
struct play *merge(struct play *a, struct play *b);
struct play *sort_plays(struct play *head);

struct artist *afind_middle(struct artist *p);
struct artist *amerge(struct artist *a, struct artist *b);
struct artist *asort_artisrid(struct artist *head);
struct artist *asort_playcount(struct artist *head);

struct artist* sort_artists(struct artist *p , int criterion);
struct artist *update_counts(struct artist *a, struct play *p);
struct play *create_play(int id, int artist_id, int playcount);
struct play *read_plays(char *file_name);
struct play *add_play(struct play *head, struct play *newp);
void free_artist(struct artist *p);
void free_artists(struct artist *p);
void free_plays(struct play *p);
void free_play(struct play *p);
void exit_usage();



struct artist *create_artist(int artist_id, char *artist_name)
{
  //printf("creatplay\n");
  struct artist *a = (struct artist *)malloc(sizeof(struct artist));
  if (a != NULL){
  a->artist_id = artist_id;
//<<<<<<< HEAD
  a->artist_name = artist_name;
//=======
//  strcpy(a->artist_name, artist_name);
//  a->playcount = playcount;
//>>>>>>> 11305d2ac81728aee0d11637709acdeb274ce2bb
  a->next = NULL;
  }
  return a;
}

struct artist *add_artist(struct artist *head, struct artist *newp)
{
  //printf("addplay\n");
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
  struct artist  *readArtist;
  readArtist = NULL;
  fp = fopen(fname, "r");
  if(!fp){
  fprintf(stderr, "error: unable to open %s\n", fname);
  return NULL;
  }
//<<<<<<< HEAD
    int artist_id;
    char artist_name[NAMELEN];
    char testline[64];
    while(fgets(testline, NAMELEN, fp) != NULL){
      if(sscanf(testline, "%d\t%65[^\t\n]\n", &artist_id, artist_name) == 2){
        struct artist *creatStruct = (struct artist *)malloc(sizeof(struct artist));
        creatStruct = create_artist(artist_id, artist_name);
        readArtist = add_artist(readArtist, creatStruct);
      }
    }
//=======
//
//  while(feof(fp) == 0){
//    fscanf(fp, "%d %[^\n]s", &tmp1->artist_id, tmp1->artist_name);
//    if(strlen(tmp1->artist_name) < 65 && strlen(tmp1->artist_name) > 0){
//            tmp2 = (struct artist *)calloc(1, sizeof(struct artist));
//            tmp2->artist_id = tmp1->artist_id;
//            strcpy(tmp2->artist_name, tmp1->artist_name);
//            tmp2->playcount = 0;
//            tmp2->next = readArtist;
//            readArtist = tmp1;
//  }
//  }
////feof() -- return non-zero value if the end of file is reached
//>>>>>>> 11305d2ac81728aee0d11637709acdeb274ce2bb

      if(fclose(fp)){
  fprintf(stderr, "error: unable to close %s\n", fname);
  return NULL;
      }
      //free_artist(creatStruct);
      return readArtist;
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

struct artist *afind_middle(struct artist *p){
  struct artist *slow = p;
  struct artist *fast = p;
  while(fast->next != NULL && fast->next->next != NULL){
    slow = slow->next;
    fast = fast->next->next;
  }
  return slow;
}
struct artist *amerge(struct artist *a, struct artist *b){
  struct artist *tmp = NULL;
  struct artist *head = NULL;
  struct artist *curr = NULL;

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

struct artist *asort_artisrid(struct artist *head){
  struct artist *m = NULL;
  struct artist *x = NULL;
  struct artist *y = NULL;

  if(head == NULL || head->next == NULL){
    return head;
  }
  x = head;
  m = afind_middle(head);
  y = m->next;
  m->next = NULL;
  return amerge(asort_artisrid(x), asort_artisrid(y));
}


struct artist *asort_playcount(struct artist *head){
  struct artist *m = NULL;
  struct artist *x = NULL;
  struct artist *y = NULL;

  if(head == NULL || head->next == NULL){
    return head;
  }
  x = head;
  m = afind_middle(head);
  y = m->next;
  m->next = NULL;
  return amerge(asort_playcount(x), asort_playcount(y));
}


struct artist* sort_artists(struct artist *p , int criterion){

  while(criterion == PLAYCOUNT || criterion == ARTISTID ){
    while(criterion == PLAYCOUNT){
      return (asort_playcount(p));
      break;
    }
    while(criterion == ARTISTID){
      return (asort_artisrid(p));
      break;
    }
    break;
  }
    while(criterion != PLAYCOUNT || criterion != ARTISTID){
    printf("error: list unsorted");
    return p;
    break;
}

}

struct artist *update_counts(struct artist *a, struct play *p){
  struct play *p_tmp;
  struct artist *a_tmp;
  a_tmp = a;
  p_tmp = p;
  while(a_tmp){
      while(p_tmp){
        if(a_tmp->artist_id == p_tmp->artist_id){
          a_tmp->playcount += p_tmp->playcount;
        }
      p_tmp = p_tmp->next;
      }
    a_tmp = a_tmp->next;
  }
  return a_tmp;
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

  struct play *p_tmp;
  struct artist *a_tmp;
  struct artist *mostp;

  int count;
  count = atoi(argv[1]);

  if(argc == 4 &&  count > 0){
    //p_tmp = read_plays(argv[3]);
    //a_tmp = read_artists(argv[2]);
    a_tmp = read_artists(argv[2]);
    p_tmp = read_plays(argv[3]);

    p_tmp = sort_plays(p_tmp);
    a_tmp = update_counts(a_tmp, p_tmp);
    mostp = sort_artists(a_tmp, PLAYCOUNT);


    while(count > 0){
                print_artist(mostp);
                mostp = mostp->next;
                count -= 1;
    }
//free_plays(p_tmp);
//free_artists(a_tmp);
//free_artists(mostp);
  }else{
    exit_usage();
    }

  return 0;
}
