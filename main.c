#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h> 
#include <sys/msg.h> 
#include <sys/types.h> 
#include <unistd.h> 
#include <sys/wait.h>
#include <signal.h>

struct applicant 
{
    char name[20];
    char days[10];
};
struct messg { 
     long mtype;
    char mtext[1024];
}; 

void handler(int signumber)
{
    if(signumber == SIGUSR1)
    {
        printf("Signal from bus1 has arrived\n");
    }
    else
    {
        printf("Signal from bus2 has arrived\n");
    }
}

int countNewLines(const char* str) {
    int count = 0;
    while (*str != '\0') {
        if (*str == '\n') {
            count++;
        }
        str++;
    }
    return count;
}
    static int num_applicants = 0;
    int max_applicants = 50;

    
    int max_monday = 10;
    int max_tuesday = 10;
    int max_wednesday = 10;
    int max_thursday = 10;
    int max_friday = 10;
    
    static int num_monday = 0;
    static int num_tuesday = 0;
    static int num_wednesday = 0;
    static int num_thursday = 0;
    static int num_friday = 0;
    

int check_day(char input_day[])
{
    if ((strcmp(input_day, "Monday") == 0) && num_monday == max_monday) 
    {
        printf("Monday is already full.\n");
        return 0;
    }
    else if(((strcmp(input_day, "Tuesday") == 0)) && num_tuesday == max_tuesday)
    {
        printf("Tuesday is already full.\n");
        return 0;
    }
    else if ((strcmp(input_day, "Wednesday") == 0) && num_wednesday == max_wednesday) 
    {
        printf("Wednesday is already full.\n");
        return 0;
    }
    else if ((strcmp(input_day, "Thursday") == 0) && num_thursday == max_thursday) 
    {
        printf("Thursday is already full.\n");
        return 0;
    }
    else if ((strcmp(input_day, "Friday") == 0) && num_friday == max_friday) 
    {
        printf("Friday is already full.\n");
        return 0;
    }
    else if (strcmp(input_day, "Monday") != 0 && strcmp(input_day, "Tuesday") != 0 && strcmp(input_day, "Wednesday") != 0 && strcmp(input_day, "Thursday") != 0 && strcmp(input_day, "Friday") != 0)
    {
        printf("Please enter only Monday/Tuesday/Wednesday/Thursday/Friday.\n");
        return 0;
    }
    return 1;
}

void add_Day(char input_day[])
{
    if (strcmp(input_day, "Monday") == 0) 
    {
        num_monday++;
    }
    else if (strcmp(input_day, "Tuesday") == 0) 
    {
        num_tuesday++;
    }
    else if (strcmp(input_day, "Wednesday") == 0) 
    {
        num_wednesday++;
    }
    else if (strcmp(input_day, "Thursday") == 0) 
    {
        num_thursday++;
    }
    else if (strcmp(input_day, "Friday") == 0) 
    {
        num_friday++;
    } 
}

void remove_day(char from_day[])
{
    if (strcmp(from_day, "Monday") == 0) 
    {
        num_monday--;
    }
    else if (strcmp(from_day, "Tuesday") == 0) 
    {
        num_tuesday--;
    }
    else if (strcmp(from_day, "Wednesday") == 0) 
    {
        num_wednesday--;
    }
    else if (strcmp(from_day, "Thursday") == 0) 
    {
        num_thursday--;
    }
    else if (strcmp(from_day, "Friday") == 0) 
    {
        num_friday--;
    }
}



int main (int argc, char* argv[]) 
{
    struct applicant *applicants = (struct applicant*)malloc(max_applicants * sizeof(struct applicant));
    char days[5][10] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday"};
    char input[20];
    FILE *fp;
    FILE *fp2;

    
    // Read from file
    fp = fopen("applicants.txt", "r");
    if (fp == NULL) 
    {
        //printf("File not found.\n");
    } 
    else 
    {
        while (fscanf(fp, "%s %s", applicants[num_applicants].name, applicants[num_applicants].days) != EOF) 
        {
            add_Day(applicants[num_applicants].days);
            num_applicants++;
            if (num_applicants == max_applicants) 
            {
                break;
            }
        }
    }
    fclose(fp);

    while(1) 
    {
        //Printing the Menu
        printf("++++++++++++++++++++++++++++++++++++++++++++++++++\n");
        printf("WELCOME TO THE \"Drink my friend\" APPLICATION SYSTEM\n");
        printf("Choose an option from the menu below:\n");
        printf("1. Add applicant\n");
        printf("2. Modify applicant\n");
        printf("3. Delete applicant\n");
        printf("4. List all applicants\n");
        printf("5. Start the bus\n");
        printf("6. Exit\n");
        printf("++++++++++++++++++++++++++++++++++++++++++++++++++\n");
        scanf("%s", input);

        if (strcmp(input, "1") == 0) 
        {
            if (num_applicants == max_applicants) 
            {
                printf("The maximum number of applicants has been reached.\n");
            } 
            else 
            {
                char temp_name[20];
                char temp_days[60];
                printf("Name: ");
                scanf("%s",temp_name);
                while(1)
                {
                    printf("Enter Days with spaces: ");
                    fgets(temp_days, 60, stdin);
                    temp_days[strcspn(temp_days, "\n")] = '\0';
                    //scanf("%[^\n]",temp_days);
                    char *token;
                    char *words[6]; // Assuming no more than 6 words in the string
                    int ii = 0;

                    token = strtok(temp_days, " ");
                    while (token != NULL) 
                    {
                        words[ii++] = token;
                        token = strtok(NULL, " ");
                    }

                    int flag = 0;
                    for (int j = 0; j < ii; j++) 
                    {
                        if (check_day(words[j]) == 1) 
                        {
                            add_Day(words[j]);
                            strcpy(applicants[num_applicants].name, temp_name);
                            strcpy(applicants[num_applicants].days, words[j]);
                            num_applicants++;
                            flag = 1;
                        }
                    }  
                    if (flag == 1) 
                    {
                        break;
                    }
                    else
                    {
                        continue;
                    }
                }
            }
        } 
        else if (strcmp(input, "2") == 0) 
        {
            printf("Name: ");
            scanf("%s", input);

            int found = 0;
            int i;
            int occur = 1;
            for (i = 0;i < num_applicants; i++) 
            {
                if (strcmp(applicants[i].name, input) == 0) 
                {
                    char current_day[10];
                    strcpy(current_day,applicants[i].days);
                    
                    while(1)
                    {
                        printf("What would you like to change for occurence number %d? (Name/Days/Both/None)\n - if you want keep this entry same type \"None\"\n",occur);
                        char temp_name[20];
                        strcpy(temp_name, applicants[i].name);
                        char temp_days[10];
                        char temp_option[5];
                        scanf("%s", temp_option);

                        if(strcmp(temp_option, "Name") == 0)
                        {
                            printf("New name: ");
                            scanf("%s", applicants[i].name);
                            occur++;
                            break;
                        }
                        if(strcmp(temp_option, "Day") == 0)
                        {
                            printf("New Day: ");
                            scanf("%s", temp_days);
                            if (check_day(temp_days) == 0) 
                            {
                                continue;
                            }
                            else
                            {
                                strcpy(applicants[i].days, temp_days);
                                add_Day(temp_days);
                                remove_day(current_day);
                                occur++;
                                break;
                            }
                        }
                        if(strcmp(temp_option, "Both") == 0)
                        {
                            printf("New name: ");
                            scanf("%s", temp_name);
                            printf("New day: ");
                            scanf("%s", temp_days);
                            if (check_day(temp_days) == 0) 
                            {
                                continue;
                            }
                            else
                            {
                                strcpy(applicants[i].days, temp_days);
                                strcpy(applicants[i].name, temp_name);
                                add_Day(temp_days);
                                remove_day(current_day);
                                occur++;
                                break;
                            }
                        }
                        if(strcmp(temp_option, "None") == 0)
                        {
                            occur++;
                            break;
                        }
                    }
                    found = 1;
                }
            }
            if (found == 0) 
            {
                printf("No applicant found with that name.\n");
            }
        } 
        else if (strcmp(input, "3") == 0) 
        {
            printf("Name: ");
            scanf("%s", input);

            int found = 0;
            int i;
            for (i = 0; i < num_applicants; i++) 
            {
                if (strcmp(applicants[i].name, input) == 0) 
                {
                    remove_day(applicants[i].days);
                    for (int j = i; j < num_applicants - 1; j++) 
                    {
                        applicants[j] = applicants[j + 1];
                    }
                    num_applicants--;
                    found = 1;
                }
            }
            if (found == 0) 
            {
                printf("No applicant found with that name.\n");
            } 
        } 
        else if (strcmp(input, "4") == 0) 
        {
            printf("All applicants:\n");
            for (int i = 0; i < num_applicants; i++) 
            {
                printf("%s: %s\n", applicants[i].name, applicants[i].days);
            }
        }
        else if (strcmp(input, "5") == 0) 
        {
            pid_t bus1;
            pid_t bus2;
            int pipefd[2]; // unnamed pipe file descriptor array
            int pipefb[2]; // unnamed pipe file descriptor array

            if (pipe(pipefd) == -1 || pipe(pipefb) == -1) 
            {
                perror("Pipe failed");
                exit(EXIT_FAILURE);
            }

            int mqueue; 
            key_t key;

            key = ftok(argv[0],1); 
            mqueue = msgget( key, 0600 | IPC_CREAT ); 
            if ( mqueue < 0) 
            { 
                perror("msgget error"); 
                exit(EXIT_FAILURE);
            } 

            printf("Day: ");
            scanf("%s", input);
            signal(SIGUSR1,handler);
            signal(SIGUSR2,handler);

            int countNos = 0;
            for (int i = 0; i < num_applicants; i++) 
            {
                if(strcmp(applicants[i].days, input) == 0)
                {
                    countNos++;
                }
            }
            printf("Number of applicants for %s: %d\n", input, countNos);
            
            if(countNos > 5)
            {
                char sz[100] = "";  // char array for reading from pipe
                char sz2[100] = "";  // char array for reading from pipe
                char ss[100];
                char ss2[100];
                bus1 = fork();
                if (bus1==0)
                { 
                    sleep(3);
                    //printf("Bus 1 ready to go, will send signal now !\n");
                    kill(getppid(),SIGUSR1);
                    //sleep(1);
                    //sleep(2);

                    close(pipefd[1]);  //Usually we close the unused write end

	                //printf("Bus1 starts to get the list of workers from the pipe!\n");
                    //sleep(2);
                    read(pipefd[0],ss,sizeof(ss)); // reading max 100 chars
                    close(pipefd[0]); 
                    printf("Bus1 gets the following workers:\n%s",ss);

                    struct messg m;
                    m.mtype = 7;
                    sprintf(m.mtext, "Bus 1 delivers %d number of workers successfully:\n", countNewLines(ss));
                    int haha =msgsnd( mqueue, &m, strlen(m.mtext)+1 , 0 );
                    if(haha < 0)
                    {
                        perror("msgsnd");
                        exit(1);
                    }
                    abort();
                }
                bus2 = fork();
                if (bus2==0)
                { 
                    sleep(5);
                    //printf("Bus 2 ready to go, will send signal now !\n");
                    kill(getppid(),SIGUSR2);
                    //sleep(4);

                    close(pipefb[1]);  //Usually we close the unused write end
	                //printf("Bus2 starts to get the list of workers from the pipe!\n");
                    //sleep(3);
                    read(pipefb[0],ss2,sizeof(ss2));
                    close(pipefb[0]); 
                    printf("Bus2 gets the following workers:\n%s",ss2);

                    struct messg m;
                    m.mtype = 8;
                    sprintf(m.mtext, "Bus 2 delivers %d number of workers successfully:\n", countNewLines(ss2));
                    int haha =msgsnd( mqueue, &m, strlen(m.mtext)+1 , 0 );
                    if(haha < 0)
                    {
                        perror("msgsnd");
                        exit(1);
                    }
                    abort();
                }
                //else
                //{
                    //printf("Waiting for signal from bus1\n");
                    pause(); //waits till a signal arrive 
                    //sleep(1);
                    
                    close(pipefd[0]); //Usually we close unused read end
                    close(pipefb[0]); //Usually we close unused read end

                    int count = 0;
                    for (int i = 0; i < num_applicants; i++) 
                    {
                        if(strcmp(applicants[i].days, input) == 0)
                        {
                            count++;
                            if(count < 6)
                            {
                                strcat(sz,applicants[i].name);
                                strcat(sz,"\n");
                            }
                            else
                            {
                                strcat(sz2,applicants[i].name);
                                strcat(sz2,"\n");
                            }
                        }
                    }

                    //sleep(1);
                    //printf("Parent wrote the message to the pipe1!\n");
                    write(pipefd[1], sz, sizeof(sz));
                    //sleep(10);
                    //printf("Waiting for the other bus to signal!\n");
                    pause();
                    //sleep(2);
                    //printf("Parent wrote the message to the pipe2!\n");
                    write(pipefb[1], sz2, sizeof(sz2));

                    close(pipefd[1]); // Closing write descriptor 
                    close(pipefb[1]); // Closing write descriptor
                    
                    struct messg m;
                    struct messg m2;
                    int haha =msgrcv(mqueue, &m, 1024, 7, 0 );
                    if (haha < 0) 
                    {
                        perror("msgrcv");
                        exit(1);
                    }
                    int haha1 =msgrcv(mqueue, &m2, 1020, 8, 0 );
                    if (haha1 < 0) 
                    {
                        perror("msgrcv");
                        exit(1);
                    }
                    printf(m.mtext);
                    printf("\n");
                    printf(m2.mtext);
                    printf("\n");

                    int status;
                    waitpid(bus1, &status, 0);

                    waitpid(bus2, &status, 0);

                    int haha3 = msgctl( mqueue, IPC_RMID, NULL );
                    if(haha3 < 0)
                    {
                        perror("msgctl");
                        exit(1);
                    }
                    //printf("Parent process ended\n");
                    fflush(NULL);
                //}

            }
            else if (countNos > 0 && countNos < 6)
            {
                char sz[100] = "";  // char array for reading from pipe
                char ss[100];
                bus1 = fork();
                if (bus1==0)
                { 
                    //sleep(3);
                    //printf("Bus 1 ready to go, will send signal soon !\n");
                    kill(getppid(),SIGUSR1);
                

                    close(pipefd[1]);  //Usually we close the unused write end
	                //printf("Bus1 starts to get the list of workers from the pipe!\n");
                    read(pipefd[0],ss,sizeof(ss)); // reading max 100 chars
                    close(pipefd[0]); 
                    printf("Bus1 gets the following workers:\n%s",ss);

                    struct messg m;
                    m.mtype = 9;
                    sprintf(m.mtext, "Bus 1 delivers %d number of workers successfully:\n", countNewLines(ss));
                    int haha =msgsnd( mqueue, &m, strlen(m.mtext)+1 , 0 );
                    if(haha < 0)
                    {
                        perror("msgsnd");
                        exit(1);
                    }
                    abort();
                }
                else
                {
                    //printf("Waiting for signal from bus\n");
                    pause(); //waits till a signal arrive 
                    
                    close(pipefd[0]); //Usually we close unused read end
                    for (int i = 0; i < num_applicants; i++) 
                    {
                        if(strcmp(applicants[i].days, input) == 0)
                        {
                            strcat(sz,applicants[i].name);
                            strcat(sz,"\n");
                        }
                    }
                    //printf("%s",sz);
                    //printf("Parent wrote the message to the pipe!\n");
                    write(pipefd[1], sz, sizeof(sz));
                    close(pipefd[1]); // Closing write descriptor 

                    struct messg m;
                    int haha1 = msgrcv(mqueue, &m, 1020, 9, 0 );
                    if (haha1< 0) 
                    {
                        perror("msgrcv");
                        exit(1);
                    }
                    printf(m.mtext);
                    printf("\n");
               

                    int status;
                    waitpid(bus1, &status, 0);

                    int haha = msgctl( mqueue, IPC_RMID, NULL );
                    if(haha < 0)
                    {
                        perror("msgctl");
                        exit(1);
                    }
               
                    //printf("Parent process ended\n");
                    fflush(NULL);
                }
                    
            }
            else
            {
                printf("No workers available for the day!\n");
            }

        }
        else if (strcmp(input, "6") == 0) 
        {
            fp2 = fopen("applicants.txt", "w");
            for (int i = 0; i < num_applicants; i++) 
            {
                fprintf(fp2, "%s %s\n", applicants[i].name, applicants[i].days);
            }
            fclose(fp2);
            break;
        } 
        else 
        {
            printf("Invalid input.\n");
        }
    }

    free(applicants);
    return 0;
}