#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<conio.h>
#include<stdbool.h>
#include<string.h>
#include <unistd.h> //headerfile sleap()
//color
#define RESET "\033[0m"
#define BLACK "\033[0;30m"
#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define YELLOW "\033[0;33m"
#define BLUE "\033[0;34m"
#define MAGENTA "\033[0;35m"
#define CYAN "\033[0;36m"
#define WHITE "\033[0;37m"
#define BOLD_BLACK "\033[1;30m"
#define BOLD_RED "\033[1;31m"
#define BOLD_GREEN "\033[1;32m"
#define BOLD_YELLOW "\033[1;33m"
#define BOLD_BLUE "\033[1;34m"
#define BOLD_MAGENTA "\033[1;35m"
#define BOLD_CYAN "\033[1;36m"
#define BOLD_WHITE "\033[1;37m"
#define clear  "\e[1;1H\e[2J"
#define happy "\U0001F389"
#define ghost2 "\U0001F47B"
#define pacman2 "\U0001F600"
#define pill   "\U0001F48A"
#define controller "\U0001F3AE"
#define  Dice      "\U0001F3B2"
#define caver       "U+25CD"
#define tab(n) for (int j=0; j<n; ++j) { printf("\t"); }

//struct
typedef struct info
{
    char ID[9];
    char name[20];
    char state[15];
    int level;
    char filename[10];
}info;
typedef struct link
{
    info data;
    struct link *pnext;
}link;
//struct game
typedef struct Pacman
{
    int pacman_x;
    int pacman_y;
    int move_x;
    int move_y;
}Pacman;
typedef struct Ghost
{
    int* ghost_x;
    int* ghost_y;
    int num_G;
}Ghost;
typedef struct map
{
    char** mat;
    int row;
    int column;
    char name[20];
    int score;
    int num_food;
    Pacman pac;
    Ghost ghost;
}Map;

//characters
#define G 'G'   //GHOST_CHARACTER 
#define E '.'   //EMPTY_SPACE 
#define V_W '|'  //VERTICAL_WALL 
#define H_W '-'  //HORIZONTAL_WALL 
#define P 'P'     //PILL
#define pacman '@' //HERO  

/*
DEscription: 
Inputes: 
OutPut:
*/
void welcome(); //used in first of the program
//function related to game
void initialize_ghost (Map* map);//input:(pointer to struct map) //initialize and creat ghost_x [] and ghost_y[]

void creat_Map (Map *map ,char filename[20] , int flag);//input(pointer to struct map) (filename)(flag)
//ralated to file(game) // read file, creat map and initialize  it //flag 1 : play first time 0 : play last game(for initilize food and score)

void draw_map (Map *map);//input:(pointer to struct map) //print matrix, name ,score, num of food...

int input(Map *map); //input:(pointer to struct map)// Getting input from the user(w a s d q)//return 0 for finish or 1 for continue 

void store_game(Map *map ,char filename [9]);//input(pointer to struct map) (filename)//ralated to file(game)
//save last game in text file

int move_pacman(Map *map); //input(pointer to struct map)  //pacman_move //return flag=win?lose    win=1 : lose=0  in progress=2

int move_ghost (Map *map); //input(pointer to struct map) //move_ghost //return (flag  0 : lose )(flag  2 : active)

void game(link *curr , char filename[30] , int temp);  //input :(struct link)(filename(map))(temp)
 //temp (1 : play first time (0: play last game)(for initilize food and score)(Creat_map function input)

void Menu(); //guide related to game
void game_menu(link * curr);//input:(struct link) //Menu for game level and log out and show information and play last game

//function related to account
void creat_acount(link** phead , int count); //input(pointer to pointer phead)(count) //count:start from 128 (for filename(unique))
//creat and initialize and check id (unique)(8 char)and possible to test again

void sort(link *phead); //input:(pointer to phead) //sort linked list

void score_board(link* phead);//input:(pointer to phead) //show information in order of their level

void delete_account(link ** phead); //input(pointer to pointer phead) //delete node 

void login(link *phead); //input:(pointer to phead) //log in game 

void help();    //guide related to account 

//function ralated to file (account)
int write_file(link* phead); //input:(pointer to phead) //save linked list in file info.bin
//return count(need for filename(unique))

link* read_file(); //read file info.bin and craat linked list //return phead

//function related to free memory
void release(link* phead ); //input : phead of linked list //free memory (linked list)

void release_map(Map* map); //input : struct Map //free memory(matrix and ghost_x[] and ghost_y[])