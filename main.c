#include <stdio.h>
#include <stdlib.h>

// subject for change and updates: addition of struct
// addition of salary calculator

#define NUM 2

void menu();
void free_up(char **name, int *hours, float *sales, int n);
void add_employees(char ***name, int **hours, float **sales, int *n, int *capacity);
float total_sales(float *sales, int n);
char *evaluation(float sale);
void print_database(char **name, int *hours, float *sales, int n);


int main()
{
    int capacity = NUM;
    int num = 0; // no employee

    int opt;

    char **name = calloc(capacity, sizeof(char *));
    int *hours = calloc(capacity, sizeof(int));
    float *sales = calloc(capacity, sizeof(float));

    for (int i = 0; i < num; i++) {
        name[i] = calloc(50, sizeof(char));
    }

    do {
        menu();
        printf("\nEnter option: ");
        scanf("%d", &opt);

        switch(opt)
        {
            case 1: add_employees(&name, &hours, &sales, &num, &capacity); break;
            case 2: printf("\nTotal Accumulated Sales: %.2f\n\n", total_sales(sales, num)); break;
            case 3: print_database(name, hours, sales, num); break;
            case 4: printf("\n\nExiting Program....\n\n"); break;
        }

    } while (opt != 4);

    free_up(name, hours, sales, num);
    return 0;
}

void menu()
{
    printf("=== Employee Database System ===\n");
    printf("1. Add Employee\n");
    printf("2. Show Total Sales\n");
    printf("3. Show Entire Database\n");
    printf("4. Exit Program\n");
}

void free_up(char **name, int *hours, float *sales, int num)
{
    for (int i = 0; i < num; i++) {
        free(name[i]);
    }
    free(name);
    free(hours);
    free(sales);
}

void add_employees(char ***name, int **hours, float **sales, int *n, int *capacity)
{
    int choice = 1;

    while (choice == 1) {
      // dynamically reallocates a new memore whenever an employee is added. 
        if (*n >= *capacity) {
            *capacity += 1;

            *name = realloc(*name, *capacity * sizeof(char*));
            *hours = realloc(*hours, *capacity * sizeof(int));
            *sales = realloc(*sales, *capacity * sizeof(float));

            if (!*name || !*hours || !*sales) { // error handling 
                perror("Memory allocation failed!");
                exit(1);
            }
        }

        (*name)[*n] = calloc(50, sizeof(char)); // error handling 
        if (!(*name)[*n]) {
            perror("Memory allocation failed!");
            exit(1);
        }

        printf("\nEmployee #%d:\n", *n + 1);
        printf("Enter the employee name: ");
        scanf("%s", (*name)[*n]);

        printf("Enter the hours worked by %s: ", (*name)[*n]);
        scanf("%d", &(*hours)[*n]);

        printf("Enter the accumulated sales: ");
        scanf("%f", &(*sales)[*n]);

        (*n)++;

        printf("\nWould you like to add more? (1 - Yes, 2 - No): ");
        scanf("%d", &choice);
    }
    printf("\n");
}

float total_sales(float *sales, int n)
{
    float total = 0;
    for (int i = 0; i < n; i++) {
        total += *(sales+i);
    }
    return total;
}

char *evaluation(float sale) {
    if (sale > 500) {
        return "Excellent Performance";
    } else if (sale >= 250 && sale <= 450) {
        return "Good Performance";
    } else if (sale < 200) {
        return "Poor Performance";
    } else {
        return "Average Performance";
    }
}

void print_database(char **name, int *hours, float *sales, int n)
{
    printf("\n=== Employee Database ===\n");
    printf("--------------------------");

    for (int i = 0; i < n; i++) {
        printf("\nEmployee Name: %s\tHours: %d\tSales: $%.2f", name[i], hours[i], sales[i]);
    }

    printf("\n\n=== Sales Evaluation ===\n");
    printf("-------------------------");
    for (int i = 0; i < n; i++) {
        printf("\nEmployee Name: %s\tPerformance: %s", name[i], evaluation(sales[i]));
    }
    printf("\n\n");
}
