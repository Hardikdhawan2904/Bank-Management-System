#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>  

int i, j;
int main_exit;
void menu();

struct date {
    int month, day, year;
};

struct {
    char name[60];
    int acc_no, age;
    char address[60];
    char citizenship[15];
    double phone;
    char acc_type[10];
    float amt;
    struct date dob;
    struct date deposit;
    struct date withdraw;
} add, check, upd, rem, transaction;

float interest(float t, float amount, int rate) {
    return (rate * t * amount) / 100.0;
}

void fordelay(int j) {
    usleep(j);
}

void exit_program() {
    printf("\nThank you for using our banking system!\n");
    exit(0);
}

void validate_input(char *input) {
    while (strlen(input) == 0 || input[0] == '\n') {
        printf("Invalid input. Please try again: ");
        fgets(input, 60, stdin);
    }
    input[strcspn(input, "\n")] = 0;  // Remove trailing newline
}

void new_acc() {
    FILE *ptr = fopen("record.txt", "a+");
    if (!ptr) {
        printf("Error opening file!\n");
        exit(1);
    }

    system("cls");
    printf("\t\t\t\xB2\xB2\xB2 ADD RECORD  \xB2\xB2\xB2\xB2");

    printf("\n\nEnter today's date (mm/dd/yyyy): ");
    if (scanf("%d/%d/%d", &add.deposit.month, &add.deposit.day, &add.deposit.year) != 3) {
        printf("Invalid date format! Try again.\n");
        while (getchar() != '\n');
        return;
    }

    printf("\nEnter the account number: ");
    if (scanf("%d", &check.acc_no) != 1) {
        printf("Invalid account number! Try again.\n");
        while (getchar() != '\n');
        return;
    }

    while (fscanf(ptr, "%d %s", &add.acc_no, add.name) != EOF) {
        if (check.acc_no == add.acc_no) {
            printf("Account number already in use!\n");
            fclose(ptr);
            return;
        }
    }

    add.acc_no = check.acc_no;
    printf("\nEnter the name: ");
    getchar();
    fgets(add.name, 60, stdin);
    validate_input(add.name);

    printf("\nEnter the date of birth (mm/dd/yyyy): ");
    scanf("%d/%d/%d", &add.dob.month, &add.dob.day, &add.dob.year);

    printf("\nEnter the age: ");
    scanf("%d", &add.age);

    printf("\nEnter the address: ");
    getchar();
    fgets(add.address, 60, stdin);
    validate_input(add.address);

    printf("\nEnter the citizenship number: ");
    fgets(add.citizenship, 15, stdin);
    validate_input(add.citizenship);

    printf("\nEnter the phone number: ");
    scanf("%lf", &add.phone);

    printf("\nEnter the amount to deposit: $ ");
    scanf("%f", &add.amt);

    printf("\nType of account (Saving/Current/Fixed1/Fixed2/Fixed3): ");
    scanf("%s", add.acc_type);

    fprintf(ptr, "%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d\n",
            add.acc_no, add.name, add.dob.month, add.dob.day, add.dob.year,
            add.age, add.address, add.citizenship, add.phone, add.acc_type,
            add.amt, add.deposit.month, add.deposit.day, add.deposit.year);
    
    fclose(ptr);
    printf("\nAccount created successfully!\n");

    printf("\nEnter 1 for main menu, 0 to exit: ");
    scanf("%d", &main_exit);
    if (main_exit == 1)
        menu();
    else
        exit_program();
}



void edit() {
    int acc_no, found = 0;
    FILE *ptr = fopen("record.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    if (!ptr || !temp) {
        printf("Error opening file!\n");
        exit(1);
    }

    printf("\nEnter account number to edit: ");
    scanf("%d", &acc_no);

    while (fscanf(ptr, "%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d\n",
                  &add.acc_no, add.name, &add.dob.month, &add.dob.day, &add.dob.year,
                  &add.age, add.address, add.citizenship, &add.phone, add.acc_type,
                  &add.amt, &add.deposit.month, &add.deposit.day, &add.deposit.year) != EOF) {
        if (add.acc_no == acc_no) {
            found = 1;
            printf("\nEnter new address: ");
            getchar();
            fgets(add.address, 60, stdin);
            validate_input(add.address);
            
            printf("\nEnter new phone number: ");
            scanf("%lf", &add.phone);
        }
        fprintf(temp, "%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d\n",
                add.acc_no, add.name, add.dob.month, add.dob.day, add.dob.year,
                add.age, add.address, add.citizenship, add.phone, add.acc_type,
                add.amt, add.deposit.month, add.deposit.day, add.deposit.year);
    }

    fclose(ptr);
    fclose(temp);
    
    if (!found)
        printf("\nAccount not found!\n");
    else
        printf("\nAccount updated successfully!\n");

    remove("record.txt");
    rename("temp.txt", "record.txt");

    printf("\nEnter 1 for main menu: ");
    scanf("%d", &main_exit);
    if (main_exit == 1)
        menu();
}


void transact() {
    printf("\nTransaction function under development.\n");
    printf("\nEnter 1 for main menu: ");
    scanf("%d", &main_exit);
    if (main_exit == 1)
        menu();
}

void erase() {
    printf("\nDelete function under development.\n");
    printf("\nEnter 1 for main menu: ");
    scanf("%d", &main_exit);
    if (main_exit == 1)
        menu();
}

void see() {
    printf("\nView account details function under development.\n");
    printf("\nEnter 1 for main menu: ");
    scanf("%d", &main_exit);
    if (main_exit == 1)
        menu();
}

void menu() {
    int choice;
    system("cls");
    printf("\n\t\tBANK MANAGEMENT SYSTEM\n");
    printf("\t1. Create new account\n");
    printf("\t2. View customer list\n");
    printf("\t3. Edit customer account\n");
    printf("\t4. Transactions\n");
    printf("\t5. Delete account\n");
    printf("\t6. View account details\n");
    printf("\t7. Exit\n\n");
    printf("\tEnter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1: new_acc(); break;
        case 2: view_list(); break;
        case 3: edit(); break;
        case 4: transact(); break;
        case 5: erase(); break;
        case 6: see(); break;
        case 7: exit_program(); break;
        default: printf("\nInvalid choice!\n");
    }
}

int main() {
    menu();
    return 0;
}
