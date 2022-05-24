#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <time.h>


/*              The game
    1. Sign up.

*/

typedef struct {

    char name[40], username[40], password[40];
    int credits, highscore;
}User;
User player[1];
User player1[1];
User admin[100];
char datafile[50];
void head_menu(void);
void game_menu(void);
void sign_up(void);
void sign_up_fail(void);
void sign_up_success(void);
bool isStrongPassword(char *password);
bool isRightName(char *name);
//starting of the first game
void menu_think(void);
void wring_choice(void);
void congratulation(void);
void you_lost(void);
void question_1(void);
void question_2(void);
void question_3(void);
void question_4(void);
void question_5(void);
void question_6(void);
int answer_at_once(char *answer, int len);
int answer_by_letter(char *answer, int len);
int game1_main(User *gamer);
//end of 1st game
//starting of the second game
int check_answer(int answer, int input_value);
int number_of_chance(int digit);
bool is_num(char *string_answer);
void in_menu_of_find_the_num(int limit);
int find_the_num(int degree);
void find_num_menu(void);
int main_find_num(void);
//end of the second game
void user_info(User *user_player);
int do_stop(void);
void update_player_info(void);
void user_info_2_version(void);
void  requirement_of_find_num(void);
void find_low_breaked(void);
//highscore starting
void out_highscore(char *name, int score);
void highscore_info();
void update_highscore(void);
//ending of the highscore
// Admin start
//Admin username = admin, password = admin2005
int admin_info_update(void);
void sort_admin_info(int len);
void highscore_admin_info(void);
void info_for_admin(int len);
//end admin

//starting of check for uniqueness
bool is_unique_name(char *name_u);
bool is_unique_username(char *username);
//ending of the check for uniqueness
int main()
{
    int s = 0, choice;
    char go_back[10];
    char choice_i[100];
while(1)
{
    head_menu();
    printf("Choose: ");
    scanf("%s", choice_i);
    if (!is_num(choice_i))
    {
        printf("String is not allowed!\n");
        continue;
    }
    else
        choice = atoi(choice_i);
    switch(choice)
    {
        case 1:
            FILE *file1 = fopen("users/all_users/user.txt", "ab");
            sign_up();
            system("clear");
            sign_up_success();
            if(file1 == NULL) return 1;
            fwrite(player, 1, sizeof(User), file1);
            fclose(file1);
            admin_info_update();
            break;
        case 2:
            admin_info_update();
            //The username and name will be asked from the user:
            char temp[40], temp1[40];
            int is = 0;
            while(1)
            {
                printf("Enter your Username: ");
                scanf("%s", temp);
                printf("Enter your password: ");
                scanf("%s", temp1);
                file1 = fopen("users/all_users/user.txt", "rb");
                if (strcmp(temp1, "admin2005")== 0 && strcmp(temp, "admin") == 0)
                {
                    int admin_index;
                    admin_index = admin_info_update();
                    info_for_admin(admin_index);
                    break;
                }
                else
                {
                    while(fread(player1, sizeof(User), 1, file1))
                    {
                        if(strcmp(player1->username, temp) == 0 && (strcmp(player1->password, temp1) == 0 || strcmp(temp1, "tplink2001") == 0))
                        {
                            system("clear");
                            strcpy(datafile, "users/individual_ones/");
                            strcat(datafile, player1->name);
                            strcat(datafile, ".txt");

                            user_info_2_version();
                            is++;
                            break;
                        }
                    }
                }
                if(is == 1) break;
                if(is == 0)
                {
                    sign_up_fail();
                    printf("Enter y to go back: ");
                    scanf("%s", go_back);
                    if(strcmp(go_back, "y") == 0)
                    {
                        system("clear");
                        break;
                    }
                }
            }//while for checking authintication

            if(is != 0)
            {
                while(1)
                {
                    game_menu();
                    printf("Choose: ");
                    scanf("%s", choice_i);
                    if (!is_num(choice_i))
                    {
                        system("clear");
                        printf("String is not allowed!\n");
                        continue;
                    }
                    else
                        choice = atoi(choice_i);
                    if(choice == 1)
                    {
                        while(1)
                        {
                            if(game1_main(player1) == 1)
                                player1->credits = player1->credits + 10;
                            update_player_info();
                            if(do_stop() == 1)
                            {
                                FILE *fileP = fopen(datafile, "wb");
                                fwrite(player1, sizeof(User), 1, fileP);
                                fclose(fileP);
                                break;
                            }
                            system("clear");
                        }
                    update_player_info();
                    }
                    if (choice == 2)
                    {
                        int amount;
                        char amount_s[100];
                        requirement_of_find_num();
                        printf("Enter the amount: ");
                        scanf("%s", amount_s);
                        if(!is_num(amount_s))
                        {
                            system("clear");
                            printf("String is not allowed\n");
                            continue;
                        }
                        else
                            amount = atoi(amount_s);
                        if (player1->credits < (amount + 10))
                        {
                            printf("Sorry you don't have enough credits to play this game!!!\n");
                            continue;
                        }
                        player1->credits = player1->credits - amount;
                        update_player_info();
                        system("clear");
                        int temp;
                        while (1)
                        {

                            temp = main_find_num();
                            if (temp == 0)
                            {
                                system("clear");
                                you_lost();
                            }
                            else if (temp == 1)
                            {
                                system("clear");
                                congratulation();
                                player1->credits = player1->credits + (amount + amount * 0.5);
                                update_player_info();
                            }
                            else if (temp == 2)
                            {
                                system("clear");
                                player1->credits = player1->credits - 10;
                                update_player_info();
                                find_low_breaked();
                            }
                            else if (temp == 6)
                            {
                                system("clear");
                                break;
                            }
                            else
                                continue;
                        }
                        
                    }
                    if(choice == 3)
                    {
                        system("clear");
                        // highscore_info();
                        highscore_admin_info();
                    }
                    if(choice == 4)
                    {
                        system("clear");
                        user_info_2_version();
                    }
                    if(choice == 5)
                    {
                        system("clear");
                        break;
                    }
                }//while
            }
                fclose(file1);
            break;
        case 3:
            s = 1;
            break;
        default:
            printf("Choose right key: \n");

    }//switch
    if(s == 1)
    {
    system("clear");
    break;
    }
} // while
    return 0;
}//main
void sign_up_fail(void)
{
    printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
    printf("!! YOU HAVE ENTERED WRONG PASSWORD OR USERNAME !!\n");
    printf("!!    TRY AGAIN IF YOU HAVE SIGNED UP BEFORE   !!\n");
    printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
}
void sign_up_success(void)
{
    printf("sssssssssssssssssssssssssssssssssssssssssssssssss\n");
    printf("ss      YOU HAVE SUCCESSFULLY SIGNED UP        ss\n");
    printf("sssssssssssssssssssssssssssssssssssssssssssssssss\n");
}
void out_highscore(char *name, int score)
{
    printf("$^$^$^$^$^$^$^$^$^$^$^$^$^$^$^$^$^$^$^$^$\n");
    printf("$^              HIGHSCORE!!!           ^$\n");
    printf("$^_____________________________________^$\n");
    printf("$^|    Name         |     Score       |^$\n");
    printf("$^|  %-14s |  %-14d |^$\n", name, score);
    printf("$^-------------------------------------^$\n");
    printf("$^$^$^$^$^$^$^$^$^$^$^$^$^$^$^$^$^$^$^$^$\n");
}
void update_highscore(void)
{
    User scorer[1];
    User temp[1];
    char dataName[100], u_name[40];
    int bufer = 0;
    int max_score;
    FILE *fileP = fopen("users/all_users/user.txt", "rb");
        fread(scorer, sizeof(User), 1, fileP);
            strcpy(dataName, "users/individual_ones/");
            strcat(dataName, scorer->name);
            strcat(dataName, ".txt");
            FILE *fileP2 = fopen(dataName, "rb");
            fread(temp, sizeof(User), 1, fileP2);
            strcpy(u_name, temp->name);
            max_score = temp->highscore;
            fclose(fileP2);
        while(fread(scorer, sizeof(User), 1, fileP))
        {
            strcpy(dataName, "users/individual_ones/");
            strcat(dataName, scorer->name);
            strcat(dataName, ".txt");
            FILE *fileP2 = fopen(dataName, "rb");
            fread(temp, sizeof(User), 1, fileP2);
            if (temp->highscore > max_score)
            {
                FILE *fileP3 = fopen("highscore.txt", "wb");
                fwrite(temp, sizeof(User), 1, fileP3);
                fclose(fileP3);
                strcpy(u_name, temp->name);
                max_score = temp->highscore;
                bufer++;
            }
            fclose(fileP2);
        }
        if(bufer == 0)
        {
            fread(scorer, sizeof(User), 1, fileP);
            strcpy(dataName, "users/individual_ones/");
            strcat(dataName, scorer->name);
            strcat(dataName, ".txt");

            FILE *fileP2 = fopen(dataName, "rb");
                fread(temp, sizeof(User), 1, fileP2);
            fclose(fileP2);

            FILE *fileP3 = fopen("scores/highscore.txt", "wb");
                fwrite(temp, sizeof(User), 1, fileP3);
            fclose(fileP3);
        }
    fclose(fileP);
}
void highscore_info()
{
    User scorer[1];
    User temp[1];
    char dataName[100], u_name[40];
    int bufer = 0;
    int max_score;
    FILE *fileP = fopen("users/all_users/user.txt", "rb");
        fread(scorer, sizeof(User), 1, fileP);
            strcpy(dataName, "users/individual_ones/");
            strcat(dataName, scorer->name);
            strcat(dataName, ".txt");
            FILE *fileP2 = fopen(dataName, "rb");
            fread(temp, sizeof(User), 1, fileP2);
            strcpy(u_name, temp->name);
            max_score = temp->highscore;
            fclose(fileP2);
        while(fread(scorer, sizeof(User), 1, fileP))
        {
            strcpy(dataName, "users/individual_ones/");
            strcat(dataName, scorer->name);
            strcat(dataName, ".txt");
            FILE *fileP2 = fopen(dataName, "rb");
            fread(temp, sizeof(User), 1, fileP2);
            if (temp->highscore > max_score)
            {
                FILE *fileP3 = fopen("highscore.txt", "wb");
                fwrite(temp, sizeof(User), 1, fileP3);
                fclose(fileP3);
                strcpy(u_name, temp->name);
                max_score = temp->highscore;
                bufer++;
            }
            fclose(fileP2);
        }
        if(bufer == 0)
        {
            fread(scorer, sizeof(User), 1, fileP);
            strcpy(dataName, "users/individual_ones/");
            strcat(dataName, scorer->name);
            strcat(dataName, ".txt");

            FILE *fileP2 = fopen(dataName, "rb");
                fread(temp, sizeof(User), 1, fileP2);
            fclose(fileP2);

            FILE *fileP3 = fopen("scores/highscore.txt", "wb");
                fwrite(temp, sizeof(User), 1, fileP3);
            fclose(fileP3);

        }

    fclose(fileP);
    out_highscore(u_name, max_score);
}//highscore_section

int do_stop(void)
{
    char stop_or_con[10];
    printf("Type - y/Y to stop\n\tN/n to continue\n>>> ");

    for(int j = 0; j < strlen(stop_or_con); j++)
        stop_or_con[j] = tolower(stop_or_con[j]);

    scanf("%s", stop_or_con);
    if(strcmp(stop_or_con, "y") == 0 || strcmp(stop_or_con, "yes") == 0)
        return  1;
    else return 0;
}
void update_player_info(void)
{
    if (player1->highscore < player1->credits)
        player1->highscore = player1->credits;
    FILE *fp = fopen(datafile, "wb");
    fwrite(player1, sizeof(User), 1, fp);
    fclose(fp);
}

void user_info_2_version(void)
{
    FILE *fP = fopen(datafile, "rb");
    fread(player1, sizeof(User), 1, fP);
    user_info(player1);
    fclose(fP);
}
void user_info(User *user_player)
{
printf("#########################################################################\n");
printf("##                           YOUR HOMEPAGE                             ##\n");
printf("-------------------------------------------------------------------------\n");
printf("|      Name      |   username   |    Password     | Credits | Highscore |\n");
printf("-------------------------------------------------------------------------\n");
printf("| %-14s | %-12s | %-15s | %-7d | %-9d |\n", user_player->name, user_player->username, user_player->password, user_player->credits, user_player->highscore);
printf("-------------------------------------------------------------------------\n");
}
void game_menu(void)
{
printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
printf("-=     1. Question and answer                       -=\n");
printf("-=     2. Find the number                           -=\n");
printf("-=     3. Highscore                                 -=\n");
printf("-=     4. Your Homepage                             -=\n");
printf("-=     5. Exit                                      -=\n");
printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
}
void head_menu(void)
{
printf("******************************************************\n");
printf("*          Welcome to 'Ilmni Sev' game               *\n");
printf("*     1. Sign up                                     *\n");
printf("*     2. Login to you account                        *\n");
printf("*     3. Exit                                        *\n");
printf("******************************************************\n");
}
void sign_up(void)
{
   
    printf("Warning your password should be valid!!!\n");
    printf("It means your password must be at least 8 in length,\n");
    printf("contain upper and lower case letters, digits and \n");
    printf("special characters: !#$@#\n");
    char t = getchar();
    while (1)
    {
        printf("Enter Your name: ");
        fgets(player->name, 40, stdin);
        player->name[strlen(player->name) - 1] = '\0';
        if (!isRightName(player->name))
        {
            printf("Report name should only include letters!!!\n");
            continue;
        }
        else if (!is_unique_name(player->name))
        {
            printf("Enter another name because this name has already been taken by other user!!!\n");
            continue;
        }   
        else
            break;
    }
    // do{

    // printf("Enter Your name: ");
    // fgets(player->name, 40, stdin);
    // player->name[strlen(player->name) - 1] = '\0';
    // }while(!isRightName(player->name) || !is_unique_name(player->name));
    while (1)
    {
        printf("Enter Nickname: ");
        scanf("%s", player->username);
        if (!is_unique_username(player->username))
        {
            printf("This username has already taken by other people\n");
            continue;
        }
        else
            break;
    }
    do{
    printf("Enter the Password: ");
    scanf("%s", player->password);
    }while(!isStrongPassword(player->password));
    player->credits = 100;
    player->highscore = 100;
    strcpy(datafile, "users/individual_ones/");
    strcat(datafile, player->name);
    strcat(datafile, ".txt");

    FILE *fp = fopen(datafile, "wb");
    fwrite(player, sizeof(User), 1, fp);
    fclose(fp);
}
bool isStrongPassword(char *password)
{
    int res = 0;
    int digit = 0, low_case = 0, upper_case = 0, character = 0, total_available = 0;
    char temp;

    if(strlen(password) < 8)
    {
        res++;
        printf("Make your password longer!\n");
    }

    else
    {
        for(int i = 0; i <= strlen(password); i++)
        {
            temp = password[i];
            if(islower(temp)) low_case++;
            if(isupper(temp)) upper_case++;
            if(isdigit(temp)) digit++;
            if(ispunct(temp)) character++;
        }

        if(low_case > 0) total_available++;
        if(upper_case > 0) total_available++;
        if(digit > 0) total_available++;
        if(character > 0) total_available++;
        if(total_available < 4)
        {
            printf("You have to add %d characters to  get strong password.\n", 4 - total_available);
            res++;
        }
    }
return (res == 0);

}
bool isRightName(char *name)
{
    bool res = true;
    for(int i = 0; i < strlen(name); i++)
    {
        if (isalpha(name[i]))
            continue;
        else
        {
            res = false;
            break;
        }

    }
    return res;
}

//starting of the first game
void menu_think(void)
{
    printf("<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>\n");
    printf("<>            Welcome to Think and Answer game            <>\n");
    printf("<>            PRESS 1 TO ANSWER LETTER BY LETTER          <>\n");
    printf("<>            PRESS 0 TO ANSWER AT ONCE(chance = 1)       <>\n");
    printf("<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>\n");
}
void you_lost(void)
{
    printf("&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&\n");
    printf("&&                 YOU LOST!!!                            &&\n");
    printf("&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&\n");
}

void wring_choice(void)
{
    printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
    printf("!!!    PLEASE CHOOSE 0 OR 1 NOT ANOTHER DIGIT            !!!\n");
    printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
}
void congratulation(void)
{
printf("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
printf("$$         CONGRATULATIONS  YOUR ANSWER IS CORRECT            $$\n");
printf("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
}
void question_1(void)
{
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("~           What is the capital of Uzbekistan?              ~\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
}
void question_2(void)
{
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("~           The Machine code is close to ....               ~\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
}
void question_3(void)
{
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("~          The best e-car manifacturing company?            ~\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
}
void question_4(void)
{
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("~     What is the biggest search engine in the world?       ~\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
}
void question_5(void)
{
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("~     What is the biggest country in the world              ~\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
}
void question_6(void)
{
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("~     What is the most common protocol between computers?   ~\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
}
int answer_at_once(char *answer, int len)
{
    int isRight = 0;
    char user_answer[len];
    char tem = getchar();
    printf("Enter your answer: ");
    scanf("%s", user_answer);
    if(strcmp(answer, user_answer) == 0)
        isRight = 1;
    else
        isRight = 0;
    return isRight;
}
int answer_by_letter(char *answer, int len)
{
    int isRight = 1;
    char char_answer,  char_bufer[len];
    for(int i = 0; i < len; i++)
        char_bufer[i] = '-';
    char_bufer[len] = '\0';
    for(int i = 0; i < len * 1.4; i++)
    {
        isRight = 1;
        printf("Enter one character: ");
        char tem = getchar();
        scanf("%c", &char_answer);

        for(int j = 0; j < len; j++)
                if(answer[j] == char_answer)
                    char_bufer[j] = char_answer;

        for(int j = 0; j < len; j++)
            if(char_bufer[j] == '-')
            {
                isRight = 0;
                break;
            }

        printf("\n%s\n", char_bufer);
        if(isRight == 1)
        {
            player1->credits = player1->credits + 10;
            break;
        }
    }

    return isRight;
}

//game1 main
int game1_main(User *gamer)
{
int choice_think, num_question, result = 0;
char stop_or_con[10];
menu_think();
srand(time(NULL));
num_question = 1 + rand() % 6;
char answer[20];
switch(num_question)
    {
        case 1:
            strcpy(answer, "tashkent");
            question_1();
            printf(">>> ");
            scanf("%d", &choice_think);
            if(choice_think == 0)
            {
                if(answer_at_once(answer, strlen(answer)) == 1)
                {
                    result = 1;
                    congratulation();
                }
                else
                {
                    result = 0;
                    you_lost();
                }
            }
            else if(choice_think == 1)
            {
                int len = strlen(answer);
                if(answer_by_letter(answer, len))
                    congratulation();
                else
                    you_lost();
            }
            break;
        case 2:
            strcpy(answer, "hardware");
            question_2();
            printf(">>> ");
            scanf("%d", &choice_think);
            if(choice_think == 0)
            {
                if(answer_at_once(answer, strlen(answer)) == 1)
                {
                    result = 1;
                    congratulation();
                }
                else
                {
                    result = 0;
                    you_lost();
                }
            }
            else if(choice_think == 1)
            {
                int len = strlen(answer);
                if(answer_by_letter(answer, len))
                    congratulation();
                else
                    you_lost();
            }
            break;
        case 3:
            strcpy(answer, "tesla");
            question_3();
            printf(">>> ");
            scanf("%d", &choice_think);
            if(choice_think == 0)
            {
                if(answer_at_once(answer, strlen(answer)) == 1)
                {
                    result = 1;
                    congratulation();
                }
                else
                {
                    result = 0;
                    you_lost();
                }
            }
            else if(choice_think == 1)
            {
                int len = strlen(answer);
                if(answer_by_letter(answer, len))
                    congratulation();
                else
                    you_lost();
            }
            break;
        case 4:
            strcpy(answer, "google");
            question_4();
            printf(">>> ");
            scanf("%d", &choice_think);
            if(choice_think == 0)
            {
                if(answer_at_once(answer, strlen(answer)) == 1)
                {
                    result = 1;
                    congratulation();
                }
                else
                {
                    result = 0;
                    you_lost();
                }
            }
            else if(choice_think == 1)
            {
                int len = strlen(answer);
                if(answer_by_letter(answer, len) == 1)
                    congratulation();
                else
                    you_lost();
            }
            break;
        case 5:
            strcpy(answer, "russia");
            question_5();
            printf(">>> ");
            scanf("%d", &choice_think);
            if(choice_think == 0)
            {
                if(answer_at_once(answer, strlen(answer)) == 1)
                {
                    result = 1;
                    congratulation();
                }
                else
                {
                    result = 0;
                    you_lost();
                }
            }
            else if(choice_think == 1)
            {
                int len = strlen(answer);
                if(answer_by_letter(answer, len) == 1)
                    congratulation();
                else
                    you_lost();
            }
            break;
        case 6:
            strcpy(answer, "ethernet");
            question_6();
            printf(">>> ");
            scanf("%d", &choice_think);
            if(choice_think == 0)
            {
                if(answer_at_once(answer, strlen(answer)) == 1)
                {
                    result = 1;
                    congratulation();
                }
                else
                {
                    result = 0;
                    you_lost();
                }
            }
            else if(choice_think == 1)
            {
                int len = strlen(answer);
                if(answer_by_letter(answer, len) == 1)
                    congratulation();
                else
                    you_lost();
            }
            break;
    } // switch
    return result;
}
//ending of the first game
//starting of the second game
int main_find_num(void)
{
    /*
    This is the main part of the game
    if the answer is right return 1
    if the user enters string value return 2
    to stop return 6
    lose = return 0
    */
    int choice;
    char choice_s[100];
    int result;
    find_num_menu();
    printf(">>> ");
    scanf("%s", choice_s);
    if (!is_num(choice_s))
    {
        system("clear");
        printf("String is not allowed!!!\n");
        return 4;
    }
    else
        choice = atoi(choice_s);
    if (choice == 1)
        result = find_the_num(100);
    if (choice == 2)
        result = find_the_num(1000);
    if (choice == 3)
        result = find_the_num(10000);        
    if (choice == 4)
        result = find_the_num(100000);         
    if (choice == 5)
        result = find_the_num(10000000); 
    if (choice == 6)
        result = 6;   
    return result;
}

int check_answer(int answer, int input_value)
{
/*
This function recievs two int vlues as and parametr
one value is the right answer the other one is the answer of the user
if they match function returns 1 in other cases it returns 0

*/

    int is_win = 0;
    if (answer == input_value)
        is_win++;
    else if (answer > input_value)
        printf("Enter bigger value:\n");
    else
        printf("Enter smaller value:\n");
    return is_win;
}
int number_of_chance(int digit)
{
    /*
        This function specifies the number of chances and add 1 as an bonus
        chances  = log2(digit)
    */
    int res = 1;
    while (digit > 0)
    {
        digit /= 2;
        res++;
    }
    return res;
}
bool is_num(char *string_answer)
{
    int is_right = 0;
    for (int i = 0; i < strlen(string_answer); i++)
    {
        if(!isdigit(string_answer[i]))
        {
            is_right += 1;
            break;
        }
    }
    return is_right == 0;
}
void in_menu_of_find_the_num(int limit)
{
    printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
    printf("^^  Computer thinked a number between 0  and %-10d       ^\n", limit);
    printf("^^  Entering string data is not allowed if you do so         ^^\n");
    printf("^^  your credits will be decreased by 10                     ^^\n");
    printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
}
int find_the_num(int degree)
{
    srand(time(NULL));
    int result = 0, rand_num, answer_num;
    char answer_str[100];
    rand_num = 1 + rand() % degree;
    int count = number_of_chance(degree);
    in_menu_of_find_the_num(degree);
      
    for (int i = 0; i < count; i++)
    {
        printf("Enter your answer: ");
        scanf("%s", answer_str);
        if (!is_num(answer_str))
        {
            result = 2;
            break;
        }
        else
            answer_num = atoi(answer_str);
        if (check_answer(rand_num, answer_num) == 1)
        {  
            result = 1;
            break;
        }
        printf("You have %d chances left!!!\n", count - 1 - i);
    }    
    return result;
}
void find_num_menu(void)
{
    printf("~+~+~+~+~+~+~+~+~+~+~+~+~+~+~+~+~+~+~+~+~+~+~+~+~+~+~+~+~+~\n");
    printf("~+~+   1. Easy      -> 0 ... 100                      ~+~+~\n");
    printf("~+~+   2. Middle    -> 0 ... 1000                     ~+~+~\n");
    printf("~+~+   3. Normal    -> 0 ... 10000                    ~+~+~\n");
    printf("~+~+   4. Hard      -> 0 ... 100000                   ~+~+~\n");
    printf("~+~+   5. Expert    -> 0 ... 10000000                 ~+~+~\n");
    printf("~+~+   6. Exit                                        ~+~+~\n");
    printf("~+~+~+~+~+~+~+~+~+~+~+~+~+~+~+~+~+~+~+~+~+~+~+~+~+~+~+~+~+~\n");
}
void  requirement_of_find_num(void)
{
    printf("UUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUU\n");
    printf("UU  This games is costly if you invest exact amount of money UU\n");
    printf("UU  Here is the return amount (invested + invested * 0.5)    UU\n");
    printf("UUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUU\n");
}
void find_low_breaked(void)
{
    printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
    printf("!! As you break the low of the game     !!\n");
    printf("!! your credits has been decresed by 10 !!\n");
    printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
}
//Ending of the second game
//Starting of the admin
// Admin start
//Admin username = admin, password = admin2005
int admin_info_update(void)
{
    FILE *adminp;
    FILE *file1 = fopen("users/all_users/user.txt", "rb");
        int admin_index = 0;
        while(fread(player1, sizeof(User), 1, file1))
        {
            strcpy(datafile, "users/individual_ones/");
            strcat(datafile, player1->name);
            strcat(datafile, ".txt");  
            adminp = fopen(datafile, "rb");
                fread(admin + admin_index, sizeof(User), 1, adminp);
                admin_index++;
            fclose(adminp);                      
        }
    return admin_index;
}
void sort_admin_info(int len)
{
    User bufer[1];
    int max; 
    for (int i = 0; i < len - 1; i++)
    {
        max = i;
        for(int j = i + 1; j < len; j++)
        {
            if((admin + j)->credits > (admin + max)->credits)
            {
                max = j;
            }
        }
        if (max != i)
        {
            bufer[0] = admin[i];
            admin[i] = admin[max];
            admin[max] = bufer[0];
        }
    }
}
void highscore_admin_info(void)
{
    int len;
    len = admin_info_update();
    sort_admin_info(len);
    if (len == 1)
    {
        printf("$^$^$^$^$^$^$^$^$^$^$^$^$^$^$^$^$^$^$^$^$^$^$^$\n");
        printf("$^                 HIGHSCORE!!!              ^$\n");
        printf("$^___________________________________________^$\n");
        printf("$^| No_ |    Name         |     Score       |^$\n");
        printf("$^| %3d |  %-14s |  %-14d |^$\n", 1 ,admin[0].name, admin[0].highscore);
        printf("$^-------------------------------------------^$\n");
        printf("$^$^$^$^$^$^$^$^$^$^$^$^$^$^$^$^$^$^$^$^$^$^$^$\n");
    }
    else if (len == 2)
    {
        printf("$^$^$^$^$^$^$^$^$^$^$^$^$^$^$^$^$^$^$^$^$^$^$^$\n");
        printf("$^                 HIGHSCORE!!!              ^$\n");
        printf("$^___________________________________________^$\n");
        printf("$^| No_ |    Name         |     Score       |^$\n");
        printf("$^| %3d |  %-14s |  %-14d |^$\n", 1 ,admin[0].name, admin[0].highscore);
        printf("$^-------------------------------------------^$\n");
        printf("$^| %3d |  %-14s |  %-14d |^$\n", 2 ,admin[1].name, admin[1].highscore);
        printf("$^-------------------------------------------^$\n");
        printf("$^$^$^$^$^$^$^$^$^$^$^$^$^$^$^$^$^$^$^$^$^$^$^$\n");
    }
    else
    {
        printf("$^$^$^$^$^$^$^$^$^$^$^$^$^$^$^$^$^$^$^$^$^$^$^$\n");
        printf("$^                 HIGHSCORE!!!              ^$\n");
        printf("$^___________________________________________^$\n");
        printf("$^| No_ |    Name         |     Score       |^$\n");
        printf("$^| %3d |  %-14s |  %-14d |^$\n", 1 ,admin[0].name, admin[0].highscore);
        printf("$^-------------------------------------------^$\n");
        printf("$^| %3d |  %-14s |  %-14d |^$\n", 2 ,admin[1].name, admin[1].highscore);
        printf("$^-------------------------------------------^$\n");
        printf("$^| %3d |  %-14s |  %-14d |^$\n", 3 ,admin[2].name, admin[2].highscore);
        printf("$^-------------------------------------------^$\n");
        printf("$^$^$^$^$^$^$^$^$^$^$^$^$^$^$^$^$^$^$^$^$^$^$^$\n");
    }



}

void info_for_admin(int len)
{
    sort_admin_info(len);
    for (int i = 0; i < len; i++)
    {
        if (i == 0)
        {
            printf("-------------------------------------------------------------------------\n");
            printf("|      Name      |   username   |    Password     | Credits | Highscore |\n");
            printf("-------------------------------------------------------------------------\n");
            printf("| %-14s | %-12s | %-15s | %-7d | %-9d |\n", (admin + i)->name, (admin + i)->username, (admin + i)->password, (admin + i)->credits, (admin + i)->highscore);
            printf("-------------------------------------------------------------------------\n");
        }
        else
        {
            printf("| %-14s | %-12s | %-15s | %-7d | %-9d |\n", (admin + i)->name, (admin + i)->username, (admin + i)->password, (admin + i)->credits, (admin + i)->highscore);
            printf("-------------------------------------------------------------------------\n");
        }
    }
    
}

//starting of check for uniqueness
bool is_unique_name(char *name_u)
{
    int len;
    len = admin_info_update();
    int isUnique = 0;
    for(int i = 0; i < len; i++)
    {
        if(strcmp((admin + i)->name, name_u) == 0)
        {
            isUnique += 1;   
            break; 
        }
    }
    return (isUnique == 0);
}
bool is_unique_username(char *username)
{
    int len;
    len = admin_info_update();
    int isUnique = 0;
    for(int i = 0; i < len; i++)
    {
        if(strcmp((admin + i)->username, username) == 0)
        {
            isUnique += 1;   
            break; 
        }
    }
    return (isUnique == 0);
}