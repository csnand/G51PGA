#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAMELEN 64
#define BUFSIZE 100

struct play
{
  int user_id;
  int artist_id; 
  int playcount;
  struct play *next;
};

void print_play(struct play *p);
void print_plays(struct play *p);
struct play *create_play(int id, int artist_id, int playcount);
struct play *parse_play(char *line);
struct play *read_plays(char *file_name);
struct play *add_play(struct play *head, struct play *newp);
struct play *filter_user(int user_id, struct play *head);
int count_plays(struct play *head);
void free_plays(struct play *p);
void free_play(struct play *p);

void print_play(struct play *p)
{
  if(p == NULL){
    printf("NULL\n");
  }else{
    printf("user: %d artist: %d count: %d\n", p->user_id, p->artist_id, p->playcount);
  }
}

struct play *create_play(int id, int artist_id, int playcount)
{
  //printf("creatplay\n");
  struct play *a = (struct play *)calloc(1, sizeof(struct play));
  if (a != NULL){
  a->user_id = id;
  a->artist_id = artist_id;
  a->playcount = playcount;
  a->next = NULL;
  }
  return a;
}

struct play *parse_play(char *line)
{  
  printf("Function play *parse_play is not yet defined.\n");
  return NULL;
}

void free_play(struct play *p)
{
  free(p);
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

void print_plays(struct play *head)
{
  //printf("print play\n");
  struct play *tmp;
  tmp = head;
  if(tmp == NULL){
    printf("NULL\n");
  }else{
    while(tmp != NULL){
      print_play(tmp);
      tmp = tmp ->next;
      }
    }
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
  printf("USAGE: query_plays file command\n"
         "\n"
         "where command is one of\n"
         "\n"
         "   p <userid>  prints plays, optionally limited to user.\n"
         "   c <userid>  counts plays, optionally limited to user.\n");
   exit(1);
}

void test_task1() {
  struct play *test_play = NULL;
  print_play(test_play);
  test_play = create_play(1,2,3);
  print_play(test_play);
  free_play(test_play);
}

void test_task2() {
  struct play *a = create_play(1,2,3);
  struct play *b = create_play(4,5,6);

  struct play *c = create_play(7,8,9);
  a = add_play(a, b);
  a = add_play(a, c);
  a = add_play(a, NULL);
  print_plays(a);
  printf("There are %d plays in a.\n", count_plays(a));
}

int main(int argc, char **argv) {

  //test_task1();
  //test_task2();


  //TASK 2 G starts here
  if(argc <= 4 && argc > 2){
    struct play *queryPlays, *filtered;
    queryPlays = read_plays(argv[1]);

    while((strcmp(argv[2], "c") == 0) && argv[3] != NULL){
          int userId = atoi(argv[3]);
          //convert string to long int strtol(string, pointer, base);
          filtered = filter_user(userId, queryPlays);
          printf("%d\n",count_plays(filtered));
          break;
      }
    while((strcmp(argv[2], "c") == 0) && argv[3] == NULL){
        printf("%d\n",count_plays(queryPlays));
        break;
      } 
      
    while((strcmp(argv[2], "p") == 0) && argv[3] != NULL){
        int userId = atoi(argv[3]);
        //printf("filter+print");
        //convert string to long int strtol(string, pointer, base);
       filtered = filter_user(userId, queryPlays);
       print_plays(filtered);
       break;
      }
    while((strcmp(argv[2], "p") == 0) && argv[3] == NULL){
        print_plays(queryPlays);
        break;
        }
  }else{
    exit_usage();
      }
  //TASK 2 G ends here
return 0;
}


