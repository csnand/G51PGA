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
  
  struct play *a = (struct play *)malloc(sizeof(struct play));
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
  p = NULL;
}

struct play *add_play(struct play *head, struct play *newp)
{ 
  struct play *tmp;
  if(newp == NULL){
    newp = head;
  }else{
    newp->next = head;
  }
  return newp;
}

void print_plays(struct play *head)
{
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

  FILE *fp;
  struct play *creatStruct, *readPlays;
  readPlays = NULL;
  fp = fopen(file_name, "r");
  if(!fp){
  fprintf(stderr, "error: unable to open %s\n", file_name);
  return NULL;
  }

  while(feof(fp) == 0){
    int user_id, artist_id, playcount;
    fscanf(fp, "%d %d %d", &user_id, &artist_id, &playcount);
    creatStruct = create_play(user_id, artist_id, playcount);
    readPlays = add_play(creatStruct, readPlays);
  }  
//feof() -- return non-zero value if the end of file is reached
      return readPlays;
      free_plays(readPlays);
  if(fclose(fp)){
  fprintf(stderr, "error: unable to close %s\n", file_name);
  return NULL;
      }
}


int count_plays(struct play *head)
{
  int i = 0;
  struct play *p = head;
  while(p != NULL){
    i += p->playcount;
    p = p->next;
  }
  return i;
}

struct play *filter_user(int user_id, struct play *head)
{
  struct play *tmp, *tmp2, *filtUserLinked = NULL;
  tmp = head;
  while(tmp != NULL){
    if(user_id == head->user_id){
      tmp2 = create_play(head->user_id, head->artist_id, head->playcount);
      filtUserLinked = add_play(tmp2, filtUserLinked);
      tmp = tmp->next;
        }else{
          tmp = tmp->next;
        }
    }
  return filtUserLinked;
  free_plays(filtUserLinked);
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
  a = add_play(a, b);
  a = add_play(a, NULL);
  print_plays(a);
  printf("There are %d plays in a.\n", count_plays(a));
}

int main(int argc, char **argv) {

  //test_task1();
  //test_task2();

  //TASK 2 G starts here
  argv[1] = "e1.txt";
  argv[2] = "c";
  argv[3] = "0";
  
    struct play *queryPlays, *filtered;
    queryPlays = read_plays(argv[1]);
    printf("%d\n",count_plays(queryPlays)); 
      
          int userId = strtol(argv[3], NULL, 10);
          //convert string to long int strtol(string, pointer, base);
          filtered = filter_user(userId, queryPlays);
          printf("%d\n",count_plays(filtered));
         
        print_plays(queryPlays);
      
        int userID = strtol(argv[3], NULL, 10);
        //convert string to long int strtol(string, pointer, base);
       filtered = filter_user(userID, queryPlays);
       print_plays(filtered);
    //TASK 2 G ends here
return 0;
}

