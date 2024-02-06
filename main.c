#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<conio.h>
#include<stdbool.h>
#include<string.h>
#include <unistd.h>
#include "game.h"
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
#define clear  "\e[1;1H\e[2J"// "\e[2J\e[H"//"\e[1;1H\e[2J"//"\033[2J\033[0;0H"   //"\033[2J\033[0;0H" //"clear" //"\e[1;1H\e[2J" //"\e[2J\e[0;0H"//"\033[2J\033[0;0H" // "\033[2J\033[1;1H", end='' //"\e[2J\e[H"//"\e[1;1H\e[2J"// "\033[2J\033[H" //'\033c' //"\033\033[1;1H"
#define happy "\U0001F389"
#define ghost2 "\U0001F47B"
#define pacman2 "\U0001F600"
#define pill   "\U0001F48A"
#define controller "\U0001F3AE"
#define  Dice      "\U0001F3B2"
#define caver       "U+25CD"
#define tab(n) for (int j=0; j<n; ++j) { printf("\t"); }

int main()
{
    printf(clear);
    welcome();
    sleep (4);
    printf(clear);
    link* phead = NULL;
    phead = read_file();
    int ch , count = write_file(phead); //count filename(last game)
    help();
    printf("\n");
    tab(5);
    printf(BOLD_RED"CLICK:"BOLD_BLACK);
    scanf(" %d", &ch);
    printf(clear);
    while (ch)
    {
        switch (ch)
        {
        case 1 :
            count++;
            creat_acount(&phead , count);
            break;
        case 2 :
            login(phead);
            break;
        case 3 :
            delete_account(&phead);
            break;
        case 4:
            score_board(phead);
            break;
        default:
            break;
        }
        help();
        printf("\n");
        tab(5);
        printf(BOLD_RED"CLICK:"BOLD_BLACK);
        scanf(" %d", &ch);
        printf(clear);
    }
    write_file(phead);
    release(phead);
}