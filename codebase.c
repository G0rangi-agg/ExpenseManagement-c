#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EXPENSES 100
#define MAX_USERS 5

// User Authentication Module
typedef struct {
    char username[20];
    char password[20];
} User;

User users[MAX_USERS] = { {"admin", "pass123"}, {"user1", "abc123"} };
  
typedef struct {
    char category[50];
    float amount;
    char date[15];
} Expense;

Expense expenses[MAX_EXPENSES];
int eC = 0;    //ec=Expense Count

// Function Prototypes
int authenticate();
void addExpense();
void updateExpense();
void deleteExpense();
void displayExpenses();
void saveToFile();
void loadFromFile();
float cte();      //cte= Calculate total expenses
void sec();      //sec= Search Expense By Category
void generateReport();
void menu();

// Authentication Function
int authenticate() {
    char uname[20], pass[20];
    printf("Username: ");
    scanf("%s", uname);
    printf("Password: ");
    scanf("%s", pass);

    for (int i = 0; i < MAX_USERS; i++) {
        if (strcmp(uname, users[i].username) == 0 && strcmp(pass, users[i].password) == 0) {
            printf("Login successful!\n");
            return 1;
        }
    }
    printf("Invalid credentials. Access denied.\n");
    return 0;
}

// Add an expense
void addExpense() {
    if (eC >= MAX_EXPENSES) {
        printf("Expense list is full!\n");
        return;
    }

    printf("Enter category: ");
    scanf("%s", expenses[eC].category);
    printf("Enter amount: ");
    scanf("%f", &expenses[eC].amount);
    printf("Enter date (YYYY-MM-DD): ");
    scanf("%s", expenses[eC].date);

    eC++;
    printf("Expense added successfully!\n");
    saveToFile();
}

// Update an expense
void updateExpense() {
    int index;
    printf("Enter the expense number to update (1-%d): ", eC);
    scanf("%d", &index);
    if (index < 1 || index > eC) {
        printf("Invalid index!\n");
        return;
    }
    
    index--;
    printf("Enter new category: ");
    scanf("%s", expenses[index].category);
    printf("Enter new amount: ");
    scanf("%f", &expenses[index].amount);
    printf("Enter new date (YYYY-MM-DD): ");
    scanf("%s", expenses[index].date);

    printf("Expense updated successfully!\n");
    saveToFile();
}

// Delete an expense
void deleteExpense() {
    int index;
    printf("Enter the expense number to delete (1-%d): ", eC);
    scanf("%d", &index);
    if (index < 1 || index > eC) {
        printf("Invalid index!\n");
        return;
    }

    index--;
    for (int i = index; i < eC - 1; i++) {
        expenses[i] = expenses[i + 1];
    }
    
    eC--;
    printf("Expense deleted successfully!\n");
    saveToFile();
}

// Display expenses
void displayExpenses() {
    printf("\n=== Expense List ===\n");
    if (eC == 0) {
        printf("No expenses recorded.\n");
        return;
    }

    for (int i = 0; i < eC; i++) {
        printf("%d. Category: %s | Amount: $%.2f | Date: %s\n", 
               i + 1, expenses[i].category, expenses[i].amount, expenses[i].date);
    }
    printf("Total Expenses: $%.2f\n", cte());
}

// Calculate total expenses
float cte() {
    float total = 0.0;
    for (int i = 0; i < eC; i++) {
        total += expenses[i].amount;
    }
    return total;
}

// Search expenses by category (String Manipulation)
void sec() {
    char searchCategory[50];
    printf("Enter category to search: ");
    scanf("%s", searchCategory);

    printf("\n=== Expenses in Category: %s ===\n", searchCategory);
    int found = 0;
    for (int i = 0; i < eC; i++) {
        if (strcmp(expenses[i].category, searchCategory) == 0) {
            printf("%d. Amount: $%.2f | Date: %s\n", i + 1, expenses[i].amount, expenses[i].date);
            found = 1;
        }
    }

    if (!found) {
        printf("No expenses found in this category.\n");
    }
}

// Save expenses to file
void saveToFile() {
    FILE *file = fopen("expenses.txt", "w");
    if (file == NULL) {
        printf("Error saving file!\n");
        return;
    }

    fprintf(file, "%d\n", eC);
    for (int i = 0; i < eC; i++) {
        fprintf(file, "%s %f %s\n", expenses[i].category, expenses[i].amount, expenses[i].date);
    }

    fclose(file);
}

// Load expenses from file
void loadFromFile() {
    FILE *file = fopen("expenses.txt", "r");
    if (file == NULL) {
        return;  
    }

    fscanf(file, "%d", &eC);
    for (int i = 0; i < eC; i++) {
        fscanf(file, "%s %f %s", expenses[i].category, &expenses[i].amount, expenses[i].date);
    }

    fclose(file);
}

// Generate report
void generateReport() {
    FILE *file = fopen("report.txt", "w");
    if (file == NULL) {
        printf("Error creating report file!\n");
        return;
    }

    fprintf(file, "=== Expense Management Report ===\n");
    fprintf(file, "Total Expenses: $%.2f\n", cte());
    fprintf(file, "Expense Breakdown:\n");

    for (int i = 0; i < eC; i++) {
        fprintf(file, "%d. Category: %s | Amount: $%.2f | Date: %s\n", 
                i + 1, expenses[i].category, expenses[i].amount, expenses[i].date);
    }

    fclose(file);
    printf("Report generated successfully!\n");
}

// Main menu
void menu() {
    int choice;
    do {
        printf("\nExpense Management System\n");
        printf("1. Add Expense\n");
        printf("2. Update Expense\n");
        printf("3. Delete Expense\n");
        printf("4. Display Expenses\n");
        printf("5. Search Expense by Category\n");
        printf("6. Generate Report\n");
        printf("7. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addExpense(); break;
            case 2: updateExpense(); break;
            case 3: deleteExpense(); break;
            case 4: displayExpenses(); break;
            case 5: sec(); break;
            case 6: generateReport(); break;
            case 7: printf("Exiting...\n"); break;
            default: printf("Invalid choice! Try again.\n");
        }
    } while (choice != 7);
}

// Main function
int main() {
    if (!authenticate()) {
        return 0;
    }

    loadFromFile();
    menu();

    return 0;
}
