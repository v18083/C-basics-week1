#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define FILENAME "bank_data.dat"
#define ACCOUNT_NUMBER_START 1001

typedef struct {
    int account_number;
    char name[50];
    char email[50];
    char password[20];
    float balance;
    char date_created[20];
} Account;

Account accounts[100];
int count = 0;
int next_account_number = ACCOUNT_NUMBER_START;

void loadData() {
    FILE *file = fopen(FILENAME, "rb");
    if (file) {
        fread(&count, sizeof(int), 1, file);
        fread(&next_account_number, sizeof(int), 1, file);
        fread(accounts, sizeof(Account), count, file);
        fclose(file);
    }
}

void saveData() {
    FILE *file = fopen(FILENAME, "wb");
    fwrite(&count, sizeof(int), 1, file);
    fwrite(&next_account_number, sizeof(int), 1, file);
    fwrite(accounts, sizeof(Account), count, file);
    fclose(file);
}

int findAccount(char *email) {
    for (int i = 0; i < count; i++) {
        if (strcmp(accounts[i].email, email) == 0) return i;
    }
    return -1;
}

void getCurrentDate(char *buffer) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(buffer, "%02d-%02d-%d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
}

void registerUser() {
    if (count >= 100) { printf("System full!\n"); return; }
    
    Account acc;
    printf("\nName: "); scanf(" %[^\n]", acc.name);
    printf("Email: "); scanf("%s", acc.email);
    printf("Password: "); scanf("%s", acc.password);
    printf("Deposit (ZMW): "); scanf("%f", &acc.balance);
    
    if (findAccount(acc.email) != -1) { printf("Email exists!\n"); return; }
    if (acc.balance < 0) { printf("Invalid deposit!\n"); return; }
    
    acc.account_number = next_account_number++;
    getCurrentDate(acc.date_created);
    accounts[count++] = acc;
    saveData();
    printf("Account created! No: %d\n", acc.account_number);
}

void viewAccountDetails(int index) {
    printf("\nAccount No: %d\n", accounts[index].account_number);
    printf("Name: %s\n", accounts[index].name);
    printf("Email: %s\n", accounts[index].email);
    printf("Balance: ZMW %.2f\n", accounts[index].balance);
    printf("Created: %s\n", accounts[index].date_created);
}

void viewAllAccounts() {
    if (count == 0) { printf("No accounts!\n"); return; }
    
    printf("\nAll Accounts (%d):\n", count);
    for (int i = 0; i < count; i++) {
        printf("%d | %s | %s | ZMW %.2f | %s\n", 
               accounts[i].account_number, accounts[i].name,
               accounts[i].email, accounts[i].balance, accounts[i].date_created);
    }
}

void userLogin() {
    char email[50], password[20];
    printf("\nEmail: "); scanf("%s", email);
    printf("Password: "); scanf("%s", password);
    
    int index = findAccount(email);
    if (index == -1 || strcmp(accounts[index].password, password) != 0) {
        printf("Login failed!\n"); return;
    }
    
    printf("Welcome %s! (Acc: %d)\n", accounts[index].name, accounts[index].account_number);
    
    int choice;
    do {
        printf("\n1.Deposit 2.Withdraw 3.Transfer 4.Balance 5.Details 6.Logout\nChoice: ");
        scanf("%d", &choice);
        
        float amt;
        char target[50];
        int targetIndex;
        
        switch(choice) {
            case 1:
                printf("Amount: "); scanf("%f", &amt);
                if (amt <= 0) { printf("Invalid!\n"); break; }
                accounts[index].balance += amt;
                saveData();
                printf("New Balance: ZMW %.2f\n", accounts[index].balance);
                break;
            case 2:
                printf("Amount: "); scanf("%f", &amt);
                if (amt <= 0) printf("Invalid!\n");
                else if (amt > accounts[index].balance) printf("Insufficient!\n");
                else {
                    accounts[index].balance -= amt;
                    saveData();
                    printf("New Balance: ZMW %.2f\n", accounts[index].balance);
                }
                break;
            case 3:
                printf("To email: "); scanf("%s", target);
                printf("Amount: "); scanf("%f", &amt);
                targetIndex = findAccount(target);
                if (targetIndex == -1) printf("Not found!\n");
                else if (amt <= 0) printf("Invalid!\n");
                else if (amt > accounts[index].balance) printf("Insufficient!\n");
                else if (index == targetIndex) printf("Same account!\n");
                else {
                    accounts[index].balance -= amt;
                    accounts[targetIndex].balance += amt;
                    saveData();
                    printf("Transfer done to %s!\n", accounts[targetIndex].name);
                }
                break;
            case 4:
                printf("Balance: ZMW %.2f\n", accounts[index].balance);
                break;
            case 5:
                viewAccountDetails(index);
                break;
            case 6:
                printf("Logout\n"); break;
            default: printf("Invalid!\n");
        }
    } while(choice != 6);
}

void adminMenu() {
    int choice;
    do {
        printf("\n1.View All 2.Stats 3.Back\nChoice: ");
        scanf("%d", &choice);
        
        if (choice == 1) viewAllAccounts();
        else if (choice == 2) {
            printf("Accounts: %d, Next No: %d\n", count, next_account_number);
            if (count > 0) {
                float total = 0;
                for (int i = 0; i < count; i++) total += accounts[i].balance;
                printf("Total Balance: ZMW %.2f\n", total);
            }
        }
        else if (choice == 3) break;
        else printf("Invalid!\n");
    } while(1);
}

int main() {
    printf("=== VINCENT BANKING SYSTEM (ZMW) ===\n");
    loadData();
    
    int choice;
    do {
        printf("\n1.Register 2.Login 3.Admin 4.Exit\nChoice: ");
        scanf("%d", &choice);
        
        if (choice == 1) registerUser();
        else if (choice == 2) userLogin();
        else if (choice == 3) adminMenu();
        else if (choice == 4) saveData();
        else printf("Invalid!\n");
    } while(choice != 4);
    
    printf("Goodbye!\n");
    return 0;
}
