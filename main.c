#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
char *accountsfile = "accounts.txt";
typedef struct
{
    int month;
    int year;
} date;
typedef struct
{
    char accountNum[11];
    char name[100];
    char email[100];
    double balance;
    char mobile[100];
    date time;
} account;

typedef struct tm tm;
account accounts[100];

int linesgl;
int main()
{
    linesgl = numLinesFile(accountsfile);
    int flag = 1;
    char select[50];
    system("cls");
    printf("Welcome to Pinnacle bank, where safety is our top priorty!\n");
    printf("Please type 1 to login or type 0 to quit\n");
    while (flag)
    {
        gets(select);
        flag = 1;
        if (select[0] == '0')
        {
            quit();
            login();
            flag = 0;
        }
        else if (select[0] == '1')
        {
            login();
            flag = 0;
        }
        else
        {
            system("cls");
            printf("\033[1;31mInvalid entry!\n\033[0m\n");
            sleep(1);
            system("cls");
            printf("Please type 1 to login or type 0 to quit\n");
        }
    }
    while (1)
    {
        Load(accounts);
        printf("\t 0-) ADD\n");
        printf("\t 1-) DELETE\n");
        printf("\t 2-) MODIFY\n");
        printf("\t 3-) SEARCH\n");
        printf("\t 4-) ADVANCED SEARCH\n");
        printf("\t 5-) WITHDRAW\n");
        printf("\t 6-) DEPOSIT\n");
        printf("\t 7-) TRANSFER\n");
        printf("\t 8-) REPORT\n");
        printf("\t 9-) PRINT\n");
        printf("\t 10-) QUIT\n");
        printf("Type the number of the operation you wish to do\n");
        gets(select);
        while (select[0] < '0' || select[0] > '9')
        {
            printf("\033[1;31mInvalid character!\n\033[0m\n");
            printf("please type one from the above list \n");
            gets(select);
        }
        switch (select[0])
        {
        case '0':
            add();
            break;
        case '1':
            if (strcmp(select, "10") == 0)
            {
                quit();
            }
            else
                dlt();
            break;
        case '2':
            modify();
            break;
        case '3':
            Query(accounts);
            break;
        case '4':
            AdvSearch(accounts);
            break;
        case '5':
            withdraw();
            break;
        case '6':
            deposit();
            break;
        case '7':
            transfer();
            break;
        case '8':
            report();
            break;
        case '9':
            Print_Data();
            break;
        default:
            break;
        }
    }
}
void quit()
{
    char select[2];
    system("cls");
    printf("Are you sure you want to quit?\ntype 1 to quit or 0 to stay\n");
    gets(select);
    while (1)
    {
        system("cls");
        if (select[0] == '0')
            return;
        else if (select[0] == '1')
            break;
        else
        {
            printf("Please type 1 to quit or type 0 to stay\n");
            gets(select);
        }
    }
    printf("Thank you for your service! Pinnacle's bank is much better with you in it");
    exit(1);
}
int Acc(char *accountnumber)
{
    // to get the line of that account number
    FILE *accountptr = fopen(accountsfile, "r");
    char fileline[100];  // this is where we put a copy of the fileline to not change the org fileline
    char *accnum;        // this is the account number of the users
    int line = 0, i = 1; // which line has that account number
    while (fgets(fileline, 100, accountptr))
    {
        // the loop is for searching every line
        // to put the content in that fileline
        accnum = strtok(fileline, ","); // to get that account number from the line
        if (strcmp(accountnumber, accnum) == 0)
        {
            return (line = i);
        }
        i++;
    }
    fclose(accountptr);
    return line;
}
int numLinesFile(const char fname[])
{
    FILE *fptr = fopen(fname, "r");
    if (fptr == NULL)
    {
        printf("File does not exist!!!");
        exit(-1);
    }
    int noLines = 0;
    char ch[100];
    while (fgets(ch, 100, fptr))
    {

        noLines++;
    }
    fclose(fptr);
    return noLines;
}
void login()
{
    int validate_user = 0; // a flag to check if user exists
    char username[50], password[50], temp_username[50], temp_password[50], choice[5];
    char *token;
    const char delim[] = ".";
    FILE *usrptr = fopen("users.txt", "r");
    if (usrptr == NULL)
    {
        system("cls");
        printf("\033[1;31musers.txt file does not,please add it in and try again\n\033[0m\n");
        sleep(4);
        exit(-1);
    }
    do
    {
        system("cls");
        rewind(usrptr);
        printf("Enter your username:");
        gets(username);
        getMaskedPassword(password);

        while (!feof(usrptr))
        {
            fscanf(usrptr, "%s", temp_username);
            fscanf(usrptr, "%s", temp_password);
            if (strcmp(temp_username, username) == 0 && strcmp(temp_password, password) == 0)
            {
                validate_user = 1;
                break;
            }
        }
        if (validate_user == 1)
        {
            system("cls");
            printf("\nWelcome ");
            token = strtok(temp_username, delim);
            while (token != NULL)
            {
                printf("%s ", token);
                token = strtok(NULL, delim);
            }
            printf("\a\n");
        }
        else
        {
            system("cls");
            printf("\033[1;31mIncorrect username or password\n\033[0m\n");
            printf("Press \"1\" to renter your username and password.\n");
            printf("press \"0\" to Quit.\n");
            printf("Enter choice:");
            while (1)
            {
                gets(choice);
                system("cls");
                if (strcmp(choice,"0")==0)
                {
                    system("cls");
                    quit();
                    login();
                    return;
                }
                else if (strcmp(choice,"1")==0)
                {
                    break;
                }
                else
                {

                    printf("\033[1;31mInvalid Entry\n\033[0m\n");
                    Sleep(700);
                    system("cls");
                    printf("please enter 1 to retry or 0 to quit\n");
                    printf("Enter choice:");
                }
            }
        }
    }
    while (validate_user == 0);

    fclose(usrptr);
}
// function to mask the password while the user is entering it
void getMaskedPassword(char *password)
{
    printf("Enter password: ");
    fflush(stdout);
    int i = 0;
    while (1)
    {
        char ch = getch();

        if (ch == '\n' || ch == '\r' || i == 50)
        {
            break; // Exit the loop on Enter or reaching max length
        }

        else if (ch == '\b' && i > 0)
        {
            printf("\b \b"); // Delete last character printed if backspace is entered
            i--;
        }

        else
        {
            password[i++] = ch;
            printf("*"); // Print '*' instead of the actual character
        }
    }

    password[i] = '\0'; // Null terminate the password string
    printf("\n");
}

void Load(account accounts[])
{
    FILE *accptr = fopen("accounts.txt", "r");
    if (accptr == NULL)
    {
        system("cls");
        printf("Error, there doesnt exist a file with the name accounts.txt, Please add it in "
               "and we will proceed with the program");
        exit(1);
    }
    char delim[] = ",-", linebfr[100];
    char *token;
    int numAccs = numLinesFile("accounts.txt");
    accptr = fopen("accounts.txt", "r");
    for (int i = 0; i < numAccs && !feof(accptr); i++)
    {
        fgets(linebfr, 100, accptr);
        token = strtok(linebfr, delim); // account number
        strcpy(accounts[i].accountNum, token);
        char temp[15];
        strcpy(temp, token);
        strcat(temp, ".txt");
        FILE *tempptr = fopen(temp, "r");
        if (tempptr == NULL)
        {
            fclose(tempptr);
            tempptr = fopen(temp, "w");
            fprintf(tempptr, "\n");
        }
        fclose(tempptr);
        token = strtok(NULL, delim); // name
        strcpy(accounts[i].name, token);
        token = strtok(NULL, delim); // email
        strcpy(accounts[i].email, token);
        token = strtok(NULL, delim); // balance
        accounts[i].balance = atof(token);
        token = strtok(NULL, delim); // mobile
        strcpy(accounts[i].mobile, token);
        token = strtok(NULL, delim); // month
        accounts[i].time.month = atoi(token);
        token = strtok(NULL, delim); // year
        accounts[i].time.year = atoi(token);
    }
    fclose(accptr);
}
int save()
{
    int i = 0;
    int flag = 0;
    char select[2];
    printf("Would you like to save the changes?\n");
    do
    {
        printf("Type 1 to save or type 0 to discard the changes\n");
        gets(select);
        if (select[0] == '0')
        {
            system("cls");
            printf("Are you sure? once its lost it can never be retrieved,type 1 to save or type 0 to discard\n");
            gets(select);
            if (select[0] == '0')
            {
                system("cls");
                return 0;
            }
        }
        if (select[0] == '1')
        {
            system("cls");
            printf("Saving");
            for (i = 0; i < 4; i++)
            {
                Sleep(500);
                printf(".");
            }
            i = 0;
            FILE *fptr = fopen(accountsfile, "w");
            fprintf(fptr, "%s,%s,%s,%.4f,%s,%i-%i", accounts[i].accountNum, accounts[i].name, accounts[i].email, accounts[i].balance, accounts[i].mobile, accounts[i].time.month, accounts[i].time.year);
            i++;
            while (i < linesgl)
            {
                fprintf(fptr, "\n");
                fprintf(fptr, "%s,%s,%s,%.4f,%s,%i-%i", accounts[i].accountNum, accounts[i].name, accounts[i].email, accounts[i].balance, accounts[i].mobile, accounts[i].time.month, accounts[i].time.year);
                i++;
            }
            fclose(fptr);
            printf("Saved successfully!\n");
            sleep(2);
            system("cls");
            return 1;
        }
        else
        {
            system("cls");
            printf("Please type 1 to save or type 0 to discard\n");
            gets(select);
        }
    }
    while (flag);
}
void add()
{
    account s;
    time_t currentTime;
    system("cls");
    printf("Please enter your account's number (it has to be 10 numbers)\n");
    int i, n, count, flag;
    do
    {
        flag = 0;
        gets(s.accountNum);
        while (Acc(s.accountNum)) // if there's duplicate account number it'll loop.
        {
            system("cls");
            printf("This account number already exists, please enter another\n");
            gets(s.accountNum);
        }
        n = strlen(s.accountNum);
        count = 0;
        for (i = 0; (i < n) && n == 10; i++)
        {
            if (isdigit(s.accountNum[i]))
            {
                count++;
            }
            else
            {
                flag = 1;
                break;
            }
        }

        if ((count != 10) || flag)
        {
            system("cls");
            printf("\033[1;31mInvalid account number!\n\033[0m\n");
            printf("Please enter a new account number with 10 digits\n");
        }
    }
    while ((count != 10) || flag);
    system("cls");
    printf("Please enter your real full name\n");
    do
    {
        flag = 0;
        gets(s.name);
        n = strlen(s.name);
        if ((s.name[0] == '\0') || (s.name[0] == ' '))
            flag = 1;
        for (i = 0; (i < n); i++)
        {
            if (!(((s.name[i] >= 'a') && (s.name[i] <= 'z')) || ((s.name[i] >= 'A') && (s.name[i] <= 'Z')) || (s.name[i] == ' ')))
            {
                system("cls");
                printf("\033[1;31mInvalid name!\n\033[0m\n");
                printf("Please enter your real full name\n");
                flag = 1;
            }
        }
    }
    while (flag);
    system("cls");
    printf("Please enter your e-mail address\n");
    int flag1 = 0, flag2 = 0;
    do
    {
        gets(s.email);
        flag1 = 0;
        flag2 = 0;
        n = strlen(s.email) + 1;
        for (i = 1; i < n; i++)
        {
            if (s.email[i] == '@')
                flag1++;
        }
        if (flag1 == 1)
        {
            char *comp = strstr(s.email, "gmail.com");
            if ((comp == NULL))
                ;
            else if ((strcmp(comp, "gmail.com") == 0))
                flag2++;
            comp = strstr(s.email, "outlook.com");
            if ((comp == NULL))
                ;
            else if (strcmp(comp, "outlook.com") == 0)
                flag2++;
            comp = strstr(s.email, "yahoo.com");
            if ((comp == NULL))
                ;
            else if (strcmp(comp, "yahoo.com") == 0)
                flag2++;
            comp = strstr(s.email, "icloud.com");
            if ((comp == NULL))
                ;
            else if (strcmp(comp, "icloud.com") == 0)
                flag2++;
            comp = strstr(s.email, "hotmail.com");
            if ((comp == NULL))
                ;
            else if (strcmp(comp, "hotmail.com") == 0)
                flag2++;
        }
        if (flag1 != 1 || flag2 != 1)
        {
            system("cls");
            printf("Please enter a valid e-mail address\n");
        }

    }
    while (flag1 != 1 || flag2 != 1);
    system("cls");
    printf("Please enter your mobile phone number\n");
    do
    {
        gets(s.mobile);
        n = strlen(s.mobile);
        count = 0;
        for (i = 0; (i < n) && n == 11; i++)
        {
            if (isdigit(s.mobile[i]))
            {
                count++;
            }
        }

        if (count != 11)
        {
            system("cls");
            printf("Invalid phone number! Please enter a valid one\n");
        }
    }
    while (count != 11 || !(s.mobile[0] == '0' && s.mobile[1] == '1'));
    s.balance = 0; // this is a new acc so theres no bread

    time(&currentTime); // takes current time from the user's device.
    tm *time = localtime(&currentTime);
    s.time.month = time->tm_mon + 1;
    s.time.year = time->tm_year + 1900;

    accounts[numLinesFile(accountsfile)] = s;
    system("cls");
    linesgl++;
    save();
}
void withdraw()
{
    char accountnumber[11], withdraw[6], accountfile[15];
    float withdrawint;
    int balance;
    int index;
    int flag;
    system("cls");
    printf("Please type the account number or type 0 to quit\n");
    do
    {
        flag = 0;
        gets(accountnumber);
        if (strcmp(accountnumber, "0") == 0){
                system("cls");
            return;
        }

        if (!Acc(accountnumber))
        {
            system("cls");
            printf("This account number does not exist, please write another or type 0 to quit\n");
            flag = 1;
        }
        else
        {
            index = Acc(accountnumber) - 1;
            if (accounts[index].balance == 0)
            {
                system("cls");
                printf("im afraid that the account doesnt have any balance to withdraw from,please write another or type 0 to quit\n");
                flag = 1;
            }
        }
    }
    while (flag);
    system("cls");
    printf("How much would you like to withdraw?\n");
    gets(withdraw);
    withdrawint = atof(withdraw);
    while (withdrawint > 10000 || withdrawint > accounts[index].balance || withdrawint == 0)
    {
        system("cls");
        if (withdrawint > 10000)
            printf("I am afraid that the withdraw limit is 10000, please withdraw another amount or type 0 to quit\n");
        else if (withdrawint > accounts[index].balance)
            printf("I am afraid that the account's balance is insufficient, please withdraw another amount or type 0 to quit\n");
        else if (withdrawint == 0)
            printf("Please insert a number or type 0 to quit\n");
        gets(withdraw);
        withdrawint = atof(withdraw);
        if (withdrawint == 0)
        {
            system("cls");
            return;
        }
    }
    accounts[index].balance -= withdrawint;
    system("cls");
    printf("Transaction is successful,");
    if (save())
    {
        strcpy(accountfile, accountnumber);
        strcat(accountfile, ".txt");
        FILE *accountptr = fopen(accountfile, "a");
        fprintf(accountptr, "%.4f was withdrawn\n", withdrawint);
        fclose(accountptr);
    }
}

void deposit()
{
    char accountnumber[11], deposit[6], accountfile[15];
    float depositint;
    int balance;
    int flag, index;
    system("cls");
    printf("Please type the account number or type 0 to quit\n");
    do
    {
        flag = 0;
        gets(accountnumber);
        if (strcmp(accountnumber, "0") == 0)
        {
            system("cls");
            return;
        }
        if (!Acc(accountnumber))
        {
            system("cls");
            printf("This account number does not exist, please write another or type 0 to quit\n");
            flag = 1;
        }
    }
    while (flag);
    index = Acc(accountnumber) - 1;
    system("cls");
    printf("How much would you like to deposit?\n");
    gets(deposit);
    depositint = atof(deposit);
    while (depositint > 10000 || depositint == 0)
    {
        system("cls");
        if (depositint > 10000)
            printf("I am afraid that the deposit limit is 10000, please withdraw another amount\n");
        else if (depositint == 0)
            printf("Please insert a number or type 0 to quit\n");
        gets(deposit);
        depositint = atof(deposit);
        if (depositint == 0)
        {
            system("cls");
            return;
        }
    }
    accounts[index].balance += depositint;
    system("cls");
    printf("Transaction is successful, ");
    if (save())
    {
        strcpy(accountfile, accountnumber);
        strcat(accountfile, ".txt");
        FILE *accountptr = fopen(accountfile, "a");
        fprintf(accountptr, "%.4f was deposited\n", depositint);
        fclose(accountptr);
    }
}
void transfer()
{
    char accountnumbersend[11], transfer[6], accountnumberrec[11], accountfile1[15], accountfile2[15];
    float transferint;
    int balance, flag;
    system("cls");
    printf("Please type the account number of the sender or type 0 to quit\n");
    do
    {
        flag = 0;
        gets(accountnumbersend);
        if (strcmp(accountnumbersend, "0") == 0)
        {
            system("cls");
            return;
        }
        if (!Acc(accountnumbersend))
        {
            system("cls");
            printf("This account number does not exist, please write another or type 0 to quit\n");
            flag = 1;
        }
        else
        {
            int indexsend = Acc(accountnumbersend) - 1;
            if (accounts[indexsend].balance == 0)
            {
                system("cls");
                printf("im afraid that the account doesnt have any balance to withdraw from,please write another or type 0 to quit\n");
                flag = 1;
            }
        }
    }
    while (flag);
    int indexsend = Acc(accountnumbersend) - 1;
    system("cls");
    printf("Please type the account number of the receiver or type 0 to quit\n");
    do
    {
        flag = 0;
        gets(accountnumberrec);
        if (strcmp(accountnumberrec, "0") == 0)
        {
            system("cls");
            return;
        }
        if (!Acc(accountnumberrec))
        {
            system("cls");
            printf("This account number does not exist, please write another or type 0 to quit\n");
            flag = 1;
        }
        if (strcmp(accountnumberrec, accountnumbersend) == 0)
        {
            system("cls");
            printf("The receiver cant be the same as the sender\n");
            flag = 1;
        }
    }
    while (flag);
    int indexrec = Acc(accountnumberrec) - 1;
    system("cls");
    printf("How much would you like to transfer\n");
    gets(transfer);
    transferint = atof(transfer);
    while (transferint > 10000 || transferint > accounts[indexsend].balance || transferint == 0)
    {
        system("cls");
        if (transferint > 10000)
            printf("I am afraid that the transfer limit is 10000, please withdrw another amount or type 0 to quit\n");
        else if (transferint > accounts[indexsend].balance)
            printf("I am afraid that the account's balance is insufficient, please withdraw another amount or type 0 to quit\n");
        else if (transferint == 0)
            printf("Please insert a number or type 0 to quit\n");
        gets(transfer);
        transferint = atof(transfer);
        if (transferint == 0)
        {
            system("cls");
            return;
        }
    }
    accounts[indexsend].balance -= transferint;
    accounts[indexrec].balance += transferint;
    system("cls");
    printf("Transaction is successful, ");
    if (save())
    {
        strcpy(accountfile1, accountnumbersend);
        strcat(accountfile1, ".txt");
        FILE *accountptr = fopen(accountfile1, "a");
        fprintf(accountptr, "%.4f was transfered from\n", transferint);
        fclose(accountptr);
        strcpy(accountfile2, accountnumberrec);
        strcat(accountfile2, ".txt");
        accountptr = fopen(accountfile2, "a");
        fprintf(accountptr, "%.4f was transfered to\n", transferint);
        fclose(accountptr);
    }
}

void getLowerCase(char from[], char to[])
{
    int i;
    for (i = 0; from[i] != '\0'; i++)
    {
        to[i] = tolower(from[i]);
    }
    to[i] = '\0';
}

//
void AdvSearch(account accounts[])
{
    char keyword[40], monthName[15], lowercaseKW[40], lowercaseName[40], choice[5];
    int numAccs = numLinesFile("accounts.txt"), found = 0, i, j;
    do
    {
        system("cls");
        printf("Enter a keyword:");
        gets(keyword);
        printf("\nSearch results:\n");
        for (i = 0, found = 0; i < numAccs; i++)
        {
            getLowerCase(keyword, lowercaseKW);
            getLowerCase(accounts[i].name, lowercaseName);
            if (strstr(lowercaseName, lowercaseKW) != NULL)
            {
                found = 1;
                printf("\nAccount Number: %s\n", accounts[i].accountNum);
                printf("Name: %s\n", accounts[i].name);
                printf("E-mail: %s\n", accounts[i].email);
                printf("Balance: %lf\n", accounts[i].balance);
                printf("Mobile: %s\n", accounts[i].mobile);
                // to convert the integer month to month's name
                switch (accounts[i].time.month)
                {
                case 1:
                    strcpy(monthName, "January");
                    break;
                case 2:
                    strcpy(monthName, "February");
                    break;
                case 3:
                    strcpy(monthName, "March");
                    break;
                case 4:
                    strcpy(monthName, "April");
                    break;
                case 5:
                    strcpy(monthName, "May");
                    break;
                case 6:
                    strcpy(monthName, "June");
                    break;
                case 7:
                    strcpy(monthName, "July");
                    break;
                case 8:
                    strcpy(monthName, "August");
                    break;
                case 9:
                    strcpy(monthName, "September");
                    break;
                case 10:
                    strcpy(monthName, "October");
                    break;
                case 11:
                    strcpy(monthName, "November");
                    break;
                case 12:
                    strcpy(monthName, "December");
                    break;
                }
                printf("Date Opened: %s %d\n\n", monthName, accounts[i].time.year);
            }
        }
        if (!found)
        {
            printf("Keyword was not found!\n\n");
        }
        do
        {
            printf("Press \"1\" to search for another account.\n");
            printf("press \"0\" to exit.\n");
            printf("Enter choice:");
            gets(choice);
            system("cls");
        }
        while (!(strcmp(choice,"0") == 0 || strcmp(choice,"1") == 0 ));

    }
    while (!(strcmp(choice,"0") == 0));

    system("cls");
}

void Query(account accounts[])
{
    char tempAccNum[20], monthName[15], choice[10];
    int numAccs = numLinesFile("accounts.txt"), found = 0;
    do
    {
        system("cls");
        printf("Enter the account number:");
        gets(tempAccNum);
        while (strlen(tempAccNum) != 10 || !isStrDigit(tempAccNum))
        {
            printf("\033[1;31mInvalid Entry\n\033[0m\n");
            Sleep(700);
            system("cls");
            printf("Account number must be 10 digits.\n");
            printf("Enter the account number:");
            gets(tempAccNum);
        }
        int i = 0;
        found = 0;
        for (i = 0; i < numAccs; i++)
        {
            if (strcmp(tempAccNum, accounts[i].accountNum) == 0)
            {
                found = 1;
                break;
            }
        }
        system("cls");
        if (found)
        {
            printf("Account's Information:\n\n");
            printf("Account Number: %s\n", accounts[i].accountNum);
            printf("Name: %s\n", accounts[i].name);
            printf("E-mail: %s\n", accounts[i].email);
            printf("Balance: %lf\n", accounts[i].balance);
            printf("Mobile: %s\n", accounts[i].mobile);
            // to convert the integer month to month's name
            switch (accounts[i].time.month)
            {
            case 1:
                strcpy(monthName, "January");
                break;
            case 2:
                strcpy(monthName, "February");
                break;
            case 3:
                strcpy(monthName, "March");
                break;
            case 4:
                strcpy(monthName, "April");
                break;
            case 5:
                strcpy(monthName, "May");
                break;
            case 6:
                strcpy(monthName, "June");
                break;
            case 7:
                strcpy(monthName, "July");
                break;
            case 8:
                strcpy(monthName, "August");
                break;
            case 9:
                strcpy(monthName, "September");
                break;
            case 10:
                strcpy(monthName, "October");
                break;
            case 11:
                strcpy(monthName, "November");
                break;
            case 12:
                strcpy(monthName, "December");
                break;
            }
            printf("Date Opened: %s %d\n\n", monthName, accounts[i].time.year);
        }
        else
        {
            printf("Account number \"%s\" is not found!\n\n", tempAccNum);
        }
        do
        {
            printf("Press \"1\" to search for another account.\n");
            printf("press \"0\" to exit.\n");
            printf("Enter choice:");
            gets(choice);
            system("cls");
        }
        while (!(strcmp(choice,"0") == 0 || strcmp(choice,"1") == 0 ));
    }
    while (!(strcmp(choice, "0") == 0));
    system("cls");
}
void dlt()
{
    system("cls");
    char accnum[100];
    int line;
    char select[10];
    int i = 1;

    do
    {
        printf("Enter the account's account number you please to delete\n");
        gets(accnum);
        system("cls");
        while (!Acc(accnum))
        {
            printf("theres no account with this number, please try to enter it again\n");
            gets(accnum);
            system("cls");
        }
        line = Acc(accnum) - 1;
        if (accounts[line].balance != 0)
        {
            printf("balance = %f\n", accounts[line].balance);
            while (1)
            {
                printf("we're afraid that you cant't delete an account with money in it,if you please to delete another account press 1 ,to exit press 0\n");
                gets(select);
                system("cls");
                if (select[0] == '1')
                {
                    break;
                }
                else if (select[0] == '0')
                {
                    return;
                }
                else
                    printf("Invalid choice, please select from the given options.\n");
            }
        }
    }
    while (accounts[line].balance != 0);

    while (1)
    {
        printf("Are you sure you want to delete account number %s ?\n", accnum); // confirmation.
        printf("to delete type 1, to discard type 0\n");
        gets(select);
        system("cls");
        if (select[0] == '1')
        {
            break;
        }
        else if (select[0] == '0')
        {
            return;
        }
        else
            printf("Invalid choice, please select from the given options.\n");
    }
    for (i = line; i < numLinesFile(accountsfile); i++)
    {
        accounts[line] = accounts[line + 1];
    }
    printf("Successfully deleted, ");
    linesgl--;
    int sv=save();
    if(sv)
    {
        strcat(accnum,".txt");
        remove(accnum);
    }
    else
        linesgl++;
}

void modify()
{
    system("cls");
    char accnum[100];
    account m;
    char select[10];
    int line;
    int count;
    int i;
    int flag;
    int n = numLinesFile("accounts.txt");
    int len;

    printf("Enter the account's account number you wish to modify\n");
    gets(accnum);
    system("cls");
    while (!Acc(accnum))
    {
        printf("theres no account with this number, please try to enter it again\n");
        gets(accnum);
        system("cls");
    }
    line = Acc(accnum) - 1;

    while (1)
    {
        printf("Please select what you want to modify\n");
        printf("\t 0-) NAME\n");
        printf("\t 1-) MOBILE NUMBER\n");
        printf("\t 2-) E-MAIL ADDRESS\n");
        gets(select);
        system("cls");
        if (select[0] == '0')
        {
            printf("Please enter the new full name: ");
            do
            {
                flag = 0;
                gets(m.name);
                len = strlen(m.name);
                if ((m.name[0] == '\0') || (m.name[0] == ' '))
                    flag = 1;
                for (i = 0; (i < n); i++)
                {
                    if (!(((m.name[i] >= 'a') && (m.name[i] <= 'z')) || ((m.name[i] >= 'A') && (m.name[i] <= 'Z')) || (m.name[i] == ' ')))
                    {
                        system("cls");
                        printf("\033[1;31mInvalid name!\n\033[0m\n");
                        printf("Please enter the new real full name\n");
                        flag = 1;
                    }
                }
            }
            while (flag);
            strcpy(accounts[line].name, m.name);
            system("cls");
            printf("The name has been modified successfully! ,\n");
            save();
            return;
        }
        else if (select[0] == '1')
        {
            printf("Please enter the new mobile number\n");
            do
            {
                gets(m.mobile);
                n = strlen(m.mobile);
                count = 0;
                for (i = 0; (i < n) && (n == 11); i++)
                {
                    if (isdigit(m.mobile[i]))
                    {
                        count++;
                    }
                }

                if (count != 11)
                {
                    system("cls");
                    printf("Invalid phone number! Please enter a valid one\n");
                }
            }
            while (count != 11 || !(m.mobile[0] == '0' && m.mobile[1] == '1'));
            strcpy(accounts[line].mobile, m.mobile);
            system("cls");
            printf("The mobile number has been modified successfully! ,\n");
            save();
            return;
        }
        else if (select[0] == '2')
        {
            printf("Please enter your new e-mail address\n");
            int flag1 , flag2;
            do
            {
                gets(m.email);
                flag1 = 0;
                flag2 = 0;
                n = strlen(m.email) + 1;
                for (i = 1; i < n; i++)
                {
                    if (m.email[i] == '@')
                        flag1++;
                }
                if (flag1 == 1)
                {
                    char *comp = strstr(m.email, "gmail.com");
                    if ((comp == NULL))
                        ;
                    else if ((strcmp(comp, "gmail.com") == 0))
                        flag2++;
                    comp = strstr(m.email, "outlook.com");
                    if ((comp == NULL))
                        ;
                    else if (strcmp(comp, "outlook.com") == 0)
                        flag2++;
                    comp = strstr(m.email, "yahoo.com");
                    if ((comp == NULL))
                        ;
                    else if (strcmp(comp, "yahoo.com") == 0)
                        flag2++;
                    comp = strstr(m.email, "icloud.com");
                    if ((comp == NULL))
                        ;
                    else if (strcmp(comp, "icloud.com") == 0)
                        flag2++;
                    comp = strstr(m.email, "hotmail.com");
                    if ((comp == NULL))
                        ;
                    else if (strcmp(comp, "hotmail.com") == 0)
                        flag2++;
                }
                if (flag1 != 1 || flag2 != 1)
                {
                    system("cls");
                    printf("Please enter a valid e-mail address\n");
                }

            }
            while (flag1 != 1 || flag2 != 1);
            strcpy(accounts[line].email, m.email);
            system("cls");
            printf("The e-mail address has been modified successfully!\n");
            save();
            return;
        }
        else
        {
            system("cls");
            printf("Invalid option,please choose from the given options...\n");
        }
    }
}

void report()
{
    char accountnumber[11], accounthistory[15], line[50], select[10];
    int flag = 0;
    long position;
    FILE *fileptr;
    system("cls");
    printf("Please type the account number you would like to see its report or type 0 to quit \n");
    do
    {
        flag = 0;
        gets(accountnumber);
        if (strcmp(accountnumber, "0") == 0)
        {
            system("cls");
            return;
        }
        if (!Acc(accountnumber))
        {
            system("cls");
            printf("This account number does not exist, please write another or type 0 to quit\n");
            flag = 1;
        }
    }
    while (flag);
    system("cls");
    strcpy(accounthistory, accountnumber);
    strcat(accounthistory, ".txt");
    fileptr = fopen(accounthistory, "r");
    int lines = numLinesFile(accounthistory);
    int i = 0;
    if (fseek(fileptr, -5, SEEK_END))
    {
        printf("Empty history, the account has not done any transactions");
        while (1)
        {
            printf("\nWould you like to see another account?\ntype 1 to see another account\ntype 0 to return to the main menu\n");
            gets(select);
            if (strcmp(select, "0") == 0)
            {
                system("cls");
                return;
            }
            else if (strcmp(select, "1") == 0)
            {
                report();
                return;
            }
            else
            {
                system("cls");
                printf("\033[1;31mInvalid entry!\n\033[0m\n");
            }
        }
    }
    printf("Here is the report for %s \n\n\n", accounts[Acc(accountnumber) - 1].name);
    position = ftell(fileptr); // current position of the file pointer
    while ((i < 5) && (i < lines - 1))
    {
        while (position > 0)
        {
            position--;
            fseek(fileptr, position, SEEK_SET);
            char c = fgetc(fileptr);
            if (c == '\n')
            {
                // reverse the file pointer until we reach newline
                position--; // because there are 2 new lines
                break;
            }
        }
        fgets(line, 50, fileptr);
        printf("%s \n", line);
        i++;
    }
    while (1)
    {
        printf("\nWould you like to see another account?\ntype 1 to see another account\ntype 0 to return to the main menu\n");
        gets(select);
        if (strcmp(select, "0") == 0)
        {
            system("cls");
            return;
        }
        else if (strcmp(select, "1") == 0)
        {
            report();
            system("cls");
            return;
        }
        else
        {
            system("cls");
            printf("\033[1;31mInvalid entry!\n\033[0m\n");
        }
    }
    system("cls");
}
int CompareByNameZtoA(void *x, void *y) // qsort function to compare by name
{
    char a[20], b[20];
    account accountA = *(account *)x; // derefrence of the pointer
    account accountB = *(account *)y;
    getLowerCase(accountA.name, a);
    getLowerCase(accountB.name, b);
    return strcmp(b, a);
}
int CompareByNameAtoZ(void *x, void *y) // qsort function to compare by name
{
    char a[20], b[20];
    account accountA = *(account *)x; // derefrence of the pointer
    account accountB = *(account *)y;
    getLowerCase(accountA.name, a);
    getLowerCase(accountB.name, b);
    return strcmp(a, b);
}
void Sort_By_Name()
{
    char x[10], select[10];
    int numoflines = numLinesFile("accounts.txt");
    do
    {
        system("cls");
        printf("How Would You Like It To Be Sorted?\n1.A to Z\n2.Z to A\nPlease Enter Your Choice:\n");
        gets(select);
        if (select[0] == '1')
        {
            qsort(accounts, numoflines, sizeof(account), CompareByNameAtoZ); // qsort by name
            system("cls");
            printf("Sorted from A to Z Names:\n");
        }
        else if (select[0] == '2')
        {
            qsort(accounts, numoflines, sizeof(account), CompareByNameZtoA); // qsort by name
            system("cls");
            printf("Sorted from Z to A Names:\n");
        }
        else
        {
            system("cls");
            printf("\033[1;31mInvalid Choice Please Try Again\033[0m\n");
            sleep(1);
            system("cls");
        }
    }
    while (select[0] < '1' || select[0] > '2');

    for (int i = 0; i < numoflines; i++)
    {
        printf("Account %d: Name: %s Email: %s Balance: %.2f Mobile: %s Date Created: %d/%d \n", i + 1, accounts[i].name, accounts[i].email, accounts[i].balance, accounts[i].mobile, accounts[i].time.month, accounts[i].time.year);
    }
    do
    {
        printf("\n1.Print Again\n2.Return To Main Menu\nPlease Enter Your Choice\n");
        gets(x);
        if (x[0] < '1' || x[0] > '2')
        {
            system("cls");
            printf("\033[1;31mInvalid Choice Please Try Again\033[0m\n");
            sleep(2);
            system("cls");
        }
    }
    while (x[0] < '1' || x[0] > '2');
    if (x[0] == '1')
        Print_Data();
    else if (x[0] == '2')
        return;
}
int CompareByAscendinglyDate(void *x, void *y) // qsort function to compare by date
{
    account accountA = *(account *)x;
    account accountB = *(account *)y;
    if (accountA.time.year > accountB.time.year)
        return 1;
    if (accountA.time.year < accountB.time.year)
        return -1;
    if (accountA.time.month > accountB.time.month)
        return 1;
    if (accountA.time.month < accountB.time.month)
        return -1;
    return 0;
}
int CompareByDescsendinglyDate(void *x, void *y) // qsort function to compare by date
{
    account accountA = *(account *)x;
    account accountB = *(account *)y;
    if (accountA.time.year < accountB.time.year)
        return 1;
    if (accountA.time.year > accountB.time.year)
        return -1;
    if (accountA.time.month < accountB.time.month)
        return 1;
    if (accountA.time.month > accountB.time.month)
        return -1;
    return 0;
}

void Sort_By_Date()
{
    char x[10];
    char select[10];
    int numoflines = numLinesFile("accounts.txt");
    do
    {
        system("cls");
        printf("How Would You Like It To Be Sorted?\n1.Oldest to youngest\n2.Youngest to oldest\nPlease Enter Your Choice:\n");
        gets(select);
        if (select[0] == '1')
        {
            qsort(accounts, numoflines, sizeof(account), CompareByAscendinglyDate); // qsort by date opened
            system("cls");
            printf("Sorted by oldest to youngest Date:\n");
            for (int i = 0; i < numoflines; i++)
            {
                printf("Account %d: Name: %s Email: %s Balance: %.2f Mobile: %s Date Created: %d/%d \n", i + 1, accounts[i].name, accounts[i].email, accounts[i].balance, accounts[i].mobile, accounts[i].time.month, accounts[i].time.year);
            }
        }
        else if (select[0] == '2')
        {
            qsort(accounts, numoflines, sizeof(account), CompareByDescsendinglyDate); // qsort by date opened
            system("cls");
            printf("Sorted by youngest to oldest Date:\n");
            for (int i = 0; i < numoflines; i++)
            {
                printf("Account %d: Name: %s Email: %s Balance: %.2f Mobile: %s Date Created: %d/%d \n", i + 1, accounts[i].name, accounts[i].email, accounts[i].balance, accounts[i].mobile, accounts[i].time.month, accounts[i].time.year);
            }
        }
        else
        {
            system("cls");
            printf("\033[1;31mInvalid Choice Please Try Again\033[0m\n");
            sleep(1);
            system("cls");
        }
    }
    while (select[0] < '1' || select[0] > '2');
    do
    {
        printf("\n1.Print Again\n2.Return To Main Menu\nPlease Enter Your Choice\n");
        gets(x);
        if (x[0] < '1' || x[0] > '3')
        {
            system("cls");
            printf("\033[1;31mInvalid Choice Please Try Again\033[0m\n");
            sleep(1);
            system("cls");
        }
    }
    while (x[0] < '1' || x[0] > '2');
    if (x[0] == '1')
        Print_Data();
    else if (x[0] == '2')
        return;
}
int CompareByBalanceAscending(void *x, void *y) // qsort function to compare balances
{
    account accountA = *(account *)x;
    account accountB = *(account *)y;
    if (accountA.balance < accountB.balance)
        return -1;
    if (accountA.balance > accountB.balance)
        return 1;
    return 0;
}
int CompareByBalanceDescending(void *x, void *y)
{
    account accountA = *(account *)x;
    account accountB = *(account *)y;
    if (accountA.balance < accountB.balance)
        return 1;
    if (accountA.balance > accountB.balance)
        return -1;
    return 0;
}
void Sort_By_Balance()
{
    char x[10], select[10];
    int numoflines = numLinesFile("accounts.txt");
    do
    {
        system("cls");
        printf("How Would You Like It To Be Sorted?\n1.Ascending\n2.Descending\nPlease Enter Your Choice:\n");
        gets(select);
        if (select[0] == '2')
        {
            qsort(accounts, numoflines, sizeof(account), CompareByBalanceDescending); // qsort according to balance
            system("cls");
            printf("Sorted By Balance Descending:\n");
            for (int i = 0; i < numoflines; i++)
            {
                printf("Account %d: Name: %s Email: %s Balance: %.2f Mobile: %s Date Created: %d/%d \n", i + 1, accounts[i].name, accounts[i].email, accounts[i].balance, accounts[i].mobile, accounts[i].time.month, accounts[i].time.year);
            }
        }
        else if (select[0] == '1')
        {
            qsort(accounts, numoflines, sizeof(account), CompareByBalanceAscending); // qsort according to balance
            system("cls");
            printf("Sorted By Balance Ascending:\n");
            for (int i = 0; i < numoflines; i++)
            {
                printf("Account %d: Name: %s Email: %s Balance: %.2f Mobile: %s Date Created: %d/%d \n", i + 1, accounts[i].name, accounts[i].email, accounts[i].balance, accounts[i].mobile, accounts[i].time.month, accounts[i].time.year);
            }
        }
        else
        {
            system("cls");
            printf("\033[1;31mInvalid Choice Please Try Again\033[0m\n");
            sleep(2);
            system("cls");
        }
    }
    while (select[0] < '1' || select[0] > '2');
    do
    {
        printf("\n1.Print Again\n2.Return To Main Menu\nPlease Enter Your Choice\n");
        gets(x);
        if (x[0] < '1' || x[0] > '2')
        {
            system("cls");
            printf("\033[1;31mInvalid Choice Please Try Again\033[0m\n");
            sleep(2);
            system("cls");
        }
    }
    while (x[0] < '1' || x[0] > '3');
    if (x[0] == '1')
        Print_Data();
    else if (x[0] == '2')
    {
        system("cls");
        return;
    }
}
void Print_Data()
{
    char x[4];
    do
    {
        system("cls");
        printf("1-Sort By Name\n2-Sort By Date\n3-Sort By Balance\nPlease Enter Your Choice:\n"); // entry menu
        gets(x);
        if (x[0] < '1' || x[0] > '3')
        {
            system("cls");
            printf("\033[1;31mInvalid Choice Please Try Again\033[0m\n");
            sleep(2);
            system("cls");
        }
    }
    while (x[0] < '1' || x[0] > '3');
    if (x[0] == '1')
        Sort_By_Name();
    else if (x[0] == '2')
        Sort_By_Date();
    else if (x[0] == '3')
        Sort_By_Balance();
    system("cls");
}

int isStrDigit(char str[])
{
    int check = 1;
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (!isdigit(str[i]))
        {
            check = 0;
            break;
        }
    }
    return check;
}
