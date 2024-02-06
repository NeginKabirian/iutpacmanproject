#include<stdio.h>
#include "game.h"
void welcome()
{
    for(int i=0 ; i<30;++i)
    {
        tab(4);
        printf(ghost2 MAGENTA" welcome "controller GREEN" to "pacman2 RED" pacman "controller BLUE" game "ghost2"\n");
    }
     printf("\n");
}

void creat_acount(link** phead , int count) //flag=0 for check correct //creat and initilize and check ID(uniqe)(8 char) and test again ...
{
    char name[20] , ID[9] , str[10];
    int flag=1 , cmd;
    while(flag)
    {
    link* temp = *phead;
    printf(BOLD_BLUE"\n\n\t\tCREAT ACCOUNT");
    printf(YELLOW"\n\n\n\n\t\t\t\t\tname: "BOLD_BLACK);
    scanf(" %s", name);
    printf(YELLOW"\n\t\t\t\t\tID(8 char):"BOLD_BLACK);
    scanf(" %s",ID);
    while(strlen(ID)!=8)
    {
        printf(BOLD_RED"\n\t\t\t\t\tYou entered an 8-letter word!\n"RESET);
        printf(YELLOW"\n\t\t\t\t\tID(8 char): "RESET);
        scanf(" %s",ID);
    }
     while(temp)
    {
        if(strcmp(temp->data.ID,ID)==0)
        {
            
            printf(BOLD_RED"\n\t\t\t\tEror!This ID has already been used\n\n"RESET);
            tab(5);
            printf(GREEN "1.try again:\n");
            tab(5);
            printf(GREEN"0.Back Home:\n\n");
            tab(5);
            printf(BOLD_RED"CLICK:"BOLD_BLACK);
            scanf("%d",&cmd);
            if (cmd == 0)
            {
                printf(clear);
                return;
            }
            break;
        }
        temp = temp->pnext;
    }
    if(temp==NULL) //check the id is uniqe?
    {
        flag = 0;
    }
    printf(clear);
    }

    link* pnew = (link*)malloc(sizeof(link));
    pnew->pnext = NULL;
    if (*phead == NULL) 
    {
        *phead = pnew;
    } 
    else 
    {
        link* temp = *phead;
        while (temp->pnext) 
        {
            temp = temp->pnext;
        }
        temp->pnext = pnew;
    }
    strcpy(pnew->data.name , name);
    strcpy(pnew->data.ID , ID);
    pnew->data.level = 0;
    strcpy(pnew->data.state , "inactive");
    sprintf(str , "%d" , count);  //int ->str
    strcpy(pnew->data.filename , str);
    printf(clear);
}

int write_file(link* phead) //save linked list in file info.bin
{
    FILE *fp = fopen("info.bin","wb");
    link *temp = phead;
    int count = 128;  //count = number of node  //filename(lastgame)
    if(fp == NULL)
    {
        printf(RED"Unable to opening the file\n"RESET);
        return count;
    }
    while(temp)
    {
        fwrite(&temp->data , sizeof(info) , 1 ,fp);
        temp = temp -> pnext;
        count++;
    }
    fclose(fp);
    return count;
}
link* read_file() //read file info.bin and craat linked list
{
    FILE *fp = fopen("info.bin","rb");
    info data;
    link* temp = NULL , *phead = NULL;
    if(fp == NULL)
    {
        printf(RED"Unable to opening the file\n"RESET);
        return phead;
    }
    while(fread(&data , sizeof(info) , 1 ,fp)>0)
    {
        link* pnew = (link*)malloc(sizeof(link));
        pnew->pnext = NULL;
        pnew->data = data;
        if(temp == NULL)
        {
            temp = phead = pnew;
        }
        else
        {
            while(temp->pnext)
            {
                temp = temp->pnext;
            }
            temp->pnext = pnew;
        }
    }
    return phead;
    fclose(fp);
}
void sort(link *phead)
{
    link *temp = phead ,*pi , *pj , T;
    for ( pi = temp ; pi ; pi = pi->pnext)
    {
        for( pj = pi->pnext ; pj ;pj= pj->pnext)
        {
            if (pi->data.level < pj->data.level)
            {
                T.data = pi->data ;
                pi->data = pj->data;
                pj->data = T.data;
            }
        }
    }
}
void score_board(link* phead ) 
{
    
    link* temp=phead;
    tab(2);
    printf(MAGENTA"Scoreboard\n\n\n");
    sort(phead);
    while(temp)
    {
        printf(YELLOW"\t\t\t\tname:%s",temp->data.name);
        //printf(GREEN"\n\n\t\t\t\tID:%s",temp->data.ID);
        printf(MAGENTA"\n\n\t\t\t\tstate:%s",temp->data.state);
        printf(BOLD_BLUE"\n\n\t\t\t\tlevel:%d",temp->data.level);
        printf("\n\n\n");
        temp=temp->pnext;
    }
    sleep(5);
    printf(clear);
}

void delete_account(link ** phead) //delete node 
{
    char ID[9];
    link* temp  , *prev=NULL;
    int cmd;
    while(1) 
    {
    tab(2);
    printf(MAGENTA"DELETE ACCOUNT\n\n");
    printf(GREEN"\n\t\t\t\tID(8 char):"BOLD_BLACK);
    scanf("%s",ID);
    if(strcmp((*phead)->data.ID , ID)== 0) //first node
    {
        link* temp = *phead;
        *phead = (*phead)->pnext;
        free(temp);
        return ;
    }
    temp = *phead;
    while(temp) //other node
    {
        if (strcmp(temp->data.ID , ID)==0)
        {
            prev->pnext = temp->pnext;
            free(temp);
            printf(clear);
            return;
        }
        prev = temp;
        temp = temp->pnext;
    }
    printf(BOLD_RED"\n\t\t\tThe ID was not found !!!\n\n");
    tab(4);
    printf(GREEN "1.try again:\n");
    tab(4);
    printf(GREEN"0.Back Home:\n\n");
    tab(4);
    printf(BOLD_RED"CLICK:"BOLD_BLACK);
    scanf("%d",&cmd);
    if (cmd == 0)
    {
        printf(clear);
        return;

    }
    printf(clear);
    } 
}
void show (link curr)
{  
    tab(2);
    printf(MAGENTA"information\n");
    tab(4);
    printf(MAGENTA"name: %s\n\n\n",curr.data.name);
    tab(4);
    printf(YELLOW"ID: %s\n\n\n",curr.data.ID);
    tab(4);
    printf(GREEN"level: %d\n\n\n",curr.data.level);
    tab(4);
    printf(BLUE"state: %s\n\n\n",curr.data.state);
}
void initialize_ghost (Map* map) //initialize and creat _ghost-x[] and ghost_y[]
{
    int k = 0;
    map->ghost.ghost_x = (int*)malloc(map->ghost.num_G * sizeof(int));
    map->ghost.ghost_y = (int*)malloc(map->ghost.num_G * sizeof(int));
    for(int i = 0 ; i < map->row ; ++i)
    {
        for(int j = 0 ; j < map->column ; ++j)
        {
            
            if (map->mat[i][j]== G)
            {
                    map->ghost.ghost_x[k] = i;
                    map->ghost.ghost_y[k] = j;
                    k++;
            }
               
            }
        }
}  
void creat_Map (Map *map ,char filename[20] , int flag) // read file, creat map and initialize  it //flag 1 = first map 0 = changed map
{
    FILE *fp = fopen(filename,"r+");
    map->ghost.num_G = 0 ,  map->num_food = 0 , map->pac.pacman_x = 0, map->pac.pacman_y = 0 ;//, map->score = 0;
    if (fp==NULL)
    {
        printf(RED"Unable to opening the file\n"RESET);
        return;
    }
    fscanf(fp, "%d %d" ,&map->row , &map->column);
    fgetc(fp);
    map->mat = (char**)malloc(map->row * sizeof(char*));
    for(int i = 0 ; i < map->row ; ++i)
    {
        map->mat[i] = (char*)malloc(map->column * sizeof(char));
        for(int j=0 ; j < map->column ; ++j)
        {
            fscanf(fp ,"%c",&map->mat[i][j]);
            if (map->mat[i][j]== pacman)
            {
                map->pac.pacman_x = i;
                map->pac.pacman_y = j;
            }
            if (map->mat[i][j]== G)
            {
                map->ghost.num_G ++;
            }
            if(map->mat[i][j] == P)
            {
                map->num_food++;
            }
        }
        fgetc(fp); //get new line 
    }
   if(flag == 1)
   {
    map->score = 0;
   }
   else
   {
    fscanf(fp , "%d" , &map->score);
   }
    fclose(fp);
    initialize_ghost(map);
    return;
}
void draw_map (Map *map) //show_map name score...
{
    for(int i=0 ; i < map->row ; ++i)
    {
        printf("\t\t\t\t");
        for (int j=0 ; j < map->column ; ++j)
        {
           
            switch(map->mat[i][j])
            {
                case V_W :
                    printf(BLUE "%c"RESET , map->mat[i][j]);
                    printf(BLUE "%c"RESET , map->mat[i][j]);
                    break;
                case H_W :
                    printf(BLUE "%c"RESET , map->mat[i][j]);
                    printf(BLUE "%c"RESET , map->mat[i][j]);
                    break;
                case E :
                    printf(YELLOW "%c"RESET , map->mat[i][j]);
                    printf(YELLOW"%c"RESET , map->mat[i][j]);
                    break;
                case P:
                    printf(pill);
                    break;
                case pacman:
                    printf(pacman2);
                    break;
                case G:
                    printf(ghost2);
                    break;
            }  
        }
        printf("\n");
    }
    printf(MAGENTA " food: %d\n"RESET,map->num_food);
    printf(MAGENTA " score: %d\n" RESET,map->score);
    printf(MAGENTA " name : %s\n\n"RESET,map->name);
    
}
int input(Map *map) //return 0 for finish or 1 for continue 
 {
    int exit_flag=1;
    char cmd , ch;
    char filename;
    map->pac.move_y = 0 , map->pac.move_x = 0;
    cmd = _getch();
    switch (cmd)
    {
    case 'w':  //up
    case 'W':
        map->pac.move_y = -1;
        break;
    case 'a' : //left
    case 'A' :
        map->pac.move_x = -1;
        break;
    case 's' :
    case 'S' :
        map->pac.move_y = 1; //down
        break;
    case 'd' : //right
    case 'D' :
        map->pac.move_x = 1; 
        break;
    case 'q': //quit
    case 'Q':
        exit_flag=0;//finish game
        break;
        }
    return exit_flag;
 }
 void store_game(Map *map ,char filename [9])  //save lastgame in text file
 {
    FILE *fp = fopen(filename , "w");
    if (fp==NULL)
    {
        printf(RED"Unable to open the file\n"RESET);
        return;
    }
    fprintf(fp, "%d %d\n" ,map->row , map->column);
    for(int i = 0 ; i < map->row ; ++i)
    {
        for(int j=0 ; j < map->column ; ++j)
        {
            fprintf(fp ,"%c",map->mat[i][j]);
        }
        fprintf(fp,"\n");
    }
    fprintf(fp , "%d" , map->score);
    fclose(fp);
    return;
 }
 
//pacman move
 int move_pacman(Map *map) //flag=win?lose    win=1 : lose=0  in progress=2
 {

    int flag=2;     
    int new_x = map->pac.pacman_x + map->pac.move_y;
    int new_y = map->pac.pacman_y + map->pac.move_x;
    if( map->mat[new_x][new_y] != V_W && map->mat[new_x][new_y] != H_W && new_x < map->row && new_x > 0 && new_y < map->column && new_y > 0)
    {
        switch (map->mat[new_x][new_y])
        {
        case P :
            map->score++;
            map->mat[map->pac.pacman_x][map->pac.pacman_y] = E;
            map->mat[new_x][new_y] = pacman;
            map->pac.pacman_x = new_x;
            map->pac.pacman_y = new_y;
            map->num_food-- ;
            break;

        case G :
            flag = 0;
            return flag;

        case E :
            map->mat[map->pac.pacman_x][map->pac.pacman_y] = E;
            map->mat[new_x][new_y] = pacman;
            map->pac.pacman_x = new_x;
            map->pac.pacman_y = new_y;
            break;
        }
        if( map->num_food == 0 )
        {
            flag = 1;
            return flag;
        }
    }
    return flag;
 }
int move_ghost (Map *map) //flag = 0 lose  flag = 2 active
{
    int new_x , new_y , flag = 2;
    for (int i=0 ; i < map->ghost.num_G ; ++i)
    {
        int move_x = 0 , move_y = 0;
        int random_move = rand() % 4; //0 until 3
        switch (random_move)
        {
            case 0 :
                move_y = -1; //up
                break;
            case 1 :
                move_y = 1; //down
                break;
            case 2 :
                move_x = -1; //left
                break;
            case 3 :
                move_x = 1;//right
                break;
        }
        new_x = map->ghost.ghost_x[i] + move_y ;
        new_y = map->ghost.ghost_y[i] + move_x ;
        if (new_x < map->row && new_x >= 0 && new_y < map->column && new_y >= 0 && map->mat[new_x][new_y] == E)
        {
            map->mat[map->ghost.ghost_x[i]][map->ghost.ghost_y[i]] = E;
            map->ghost.ghost_x[i] = new_x;
            map->ghost.ghost_y[i] = new_y;
            map->mat[new_x][new_y] = G;
        }
        if( map->mat[new_x][new_y] == pacman )
        {
            flag = 0;
            return flag;
        }
    }
    return flag;
}
void release_map(Map* map)
{
    for(int i=0 ; i < map->row ; ++i)
    {
        free(map->mat[i]);
    }
    free(map->mat);
    free(map->ghost.ghost_x);
    free(map->ghost.ghost_y);
}
void game(link *curr , char filename[30] , int temp)
{
    int exit_flag=1 , flag = 2 , flag_g = 2 ; //flag=win?lose    win=1 : lose=0 //exit_flag = 'q' // in progress=2 
    char Filename[30 ] , ch; //ch choose for save last game or not
    Map map;
    map.score = 0;
    strcpy(map.name,curr->data.name);
    creat_Map(&map , filename , temp);
    draw_map(&map);
    while (exit_flag && flag == 2 && flag_g == 2) 
    { 
        while(kbhit()==0)
        {
            flag_g = move_ghost(&map);
            if(flag_g != 2)
            {
                break;
            }
            sleep(1);
            printf(clear);
            draw_map(&map);
        }
        if(flag_g != 2)
        {
            break;
        }
        exit_flag = input(&map);
        flag = move_pacman(&map);
        flag_g = move_ghost(&map);
        printf(clear);
        draw_map(&map);
    }
    
   if(flag==1)
    {
        curr->data.level += 3;
        if(strcmp(curr->data.state,"inactive")!=0)
        {
        strcpy(curr->data.state ,"inactive");
        }     
        for(int i=0 ; i<40 ; ++i)
        {
            printf(happy);
        }
        printf(BOLD_YELLOW"\n\n\t\t\tCongratulations! You've won!\n"RESET);
        release_map(&map);
        return;
    }
    else
        if(flag == 0 || flag_g == 0)
    {
         if(strcmp(curr->data.state,"inactive")!=0)
        {
        strcpy(curr->data.state ,"inactive");
        }     
        curr->data.level --;
        for(int i=0 ; i<40 ; ++i)
        {
            printf(ghost2);
        }
        puts(BOLD_RED"\n\n\t\t\tOh no! Pacman encountered a ghost!"RESET);
        release_map(&map);
        return;
    }
    else
        if (exit_flag == 0)
        {   
            printf(YELLOW"Do you want to save the current state of the game and continue it in the future or not?\n");
            printf("choose y (yes) or n (no)\n");
            scanf(" %c",&ch);
            if(ch == 'y'|| ch == 'Y')
            {
                strcpy(curr->data.state ,"active");
                strcpy(Filename , curr->data.filename); 
                store_game(&map , Filename);
            }
            else
            {
                strcpy(curr->data.state ,"inactive");
            }
            release_map(&map);
            return;
        }
}
void Menu()
{
    tab(2);
    printf(BOLD_RED"GUIDE");
    printf("\n\n");
    tab(4);
    printf("\n");
    tab(4);
    printf(YELLOW"1.Easy level\n\n");
    tab(4);
    printf(GREEN"2. Medium level\n\n");
    tab(4);
    printf(BLUE"3.Hard level\n\n");
    tab(4);
    printf(WHITE"4.Review account information\n\n"); 
    tab(4);
    printf(MAGENTA"5.Play last game\n\n");
    tab(4);
    printf(CYAN"0.Log out\n"RESET);
    tab(4);
}
void game_menu(link * curr)
{
    char filename[30];
    int ch , flag;
    while(1)
    {
        Menu();
        printf("\n");
        tab(5);
        printf(BOLD_RED"CLICK:"BOLD_BLACK);
        scanf("%d",&ch);
        printf(clear);
    switch(ch)
    {
        case 1: //easy level
            flag = 1;
            //strcpy(filename , "mapC.txt");
            strcpy(filename,"mapC2.txt");
            game(curr, filename , flag);
            sleep(1);
            printf(clear);
            break;  
        case 2: //Medium level
            flag = 1;
            //strcpy(filename , "r.txt");
            strcpy(filename,"ne.txt");
            game(curr, filename , flag);
            sleep(1);
            printf(clear);
            break;
        case 3://hard level
            flag = 1;//
            strcpy(filename,"neg.txt");
            game(curr, filename ,flag);
            sleep(2);
            printf(clear);
            break;
        case 4: //show review
            show(*curr);
            sleep(3);
            printf(clear);
            break;
        case 5: //play last game
            flag = 0;
            if(strcmp(curr->data.state , "active")==0)
            {
                strcpy(filename , curr->data.filename);
                game(curr, filename , flag);
            }
            else
                printf(RED"\n\n\n\n\n\t\tsorry! your last game must be active"RESET);
            sleep(1);
            printf(clear);
            break;
        case 0://logout
            return;
        default:
            break;  
    }
    sleep(1);
    printf(clear);
    Menu();
    printf("\n");
    tab(5);
    printf(BOLD_RED"CLICK:"BOLD_BLACK);
    sleep(1);
    printf(clear);
    }
    return;
}
void login(link *phead) //log in game 
{
    char name[20] , ID[9];
    link* temp;
    int flag=1; //flag=0 for find node
    while(flag)
    {
    printf(BOLD_GREEN"\n\t\t LOG in"RESET);
    printf(BLUE"\n\n\n\t\t\t\t\tname:"BOLD_BLACK);
    scanf(" %s",name);
    printf(BLUE"\n\t\t\t\t\tID(8 char):"BOLD_BLACK);
    scanf(" %s",ID);
    while(strlen(ID)!=8)
    {
        printf(BOLD_RED"\n\t\t\t\tYou entered an 8-letter word!"RESET);
        printf(BLUE"\n\n\t\t\t\t\tID(8 char): "BOLD_BLACK);
        scanf("%s",ID);
    }
    temp = phead;
    while(temp)
    {
        if(strcmp(temp->data.name , name)==0 && strcmp(temp->data.ID,ID)==0)
        {
            flag = 0;
            break;
        }
        temp = temp->pnext;
    }
    if(temp==NULL)
    {
        int cmd;
        printf(BOLD_RED"\n\n\t\t\t\tAuthentication Failed\n\n"RESET);
        tab(5);
        printf(GREEN "1.try again:\n");
        tab(5);
        printf(GREEN"0.Back Home:\n\n"BOLD_BLACK);
        tab(5);
        printf(BOLD_RED"CLICK:"BOLD_BLACK);
        scanf("%d",&cmd);
        if (cmd == 0)
        {
            printf(clear);
            return;
        }
    }
    else
    {    printf(clear);
         game_menu(temp);
    }
    printf(clear);
    }
    printf(clear);
    return;
}
void release(link* phead )
{
    while(phead->pnext)
    {
        link *next_std=phead->pnext;
        free(phead);
        phead=next_std;
    }
}
void help()
{
    tab(2);
    printf(BOLD_RED"GUIDE");
    printf("\n\n");
    tab(4);
    printf("\n");
    tab(4);
    printf(YELLOW"1. Create Account: Create a new account\n");
    printf("\n");
    tab(4);
    printf(GREEN"2. Login: Log into an existing account\n");
    printf("\n");
    tab(4);
    printf(BLUE"3. Delete Account: Delete an existing account\n");
    printf("\n");
    tab(4);
    printf(WHITE"4. Review: Review account information\n"); 
    printf("\n");
    tab(4);
    printf(MAGENTA"0. Exit: Exit the program\n"RESET);
    tab(4);
}