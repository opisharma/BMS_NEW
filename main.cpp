#include <stdio.h>
#include <string.h>

struct User {
    char fullName[100];
    char username[30];
    char email[50];
    char phone[15];
    char password[30];
};

void registerUser() {
    FILE *file;
    struct User user;
    char line[256];
    int usernameExists = 0, emailExists = 0;

    // Get user input
    printf("Enter full name: ");
    fgets(user.fullName, sizeof(user.fullName), stdin);
    strtok(user.fullName, "\n");

    printf("Enter username: ");
    fgets(user.username, sizeof(user.username), stdin);
    strtok(user.username, "\n");

    printf("Enter email: ");
    fgets(user.email, sizeof(user.email), stdin);
    strtok(user.email, "\n");

    printf("Enter phone number: ");
    fgets(user.phone, sizeof(user.phone), stdin);
    strtok(user.phone, "\n");

    printf("Enter password: ");
    fgets(user.password, sizeof(user.password), stdin);
    strtok(user.password, "\n");

    // Open the file in read mode to check for existing usernames and emails
    file = fopen("users.txt", "r");
    if (file != NULL) {
        // Read existing user data to check for duplicates
        while (fgets(line, sizeof(line), file)) {
            char existingUsername[30], existingEmail[50];
            sscanf(line, "%*[^,],%[^,],%[^,]", existingUsername, existingEmail);

            // Check if the username or email already exists
            if (strcmp(existingUsername, user.username) == 0) {
                usernameExists = 1;
            }
            if (strcmp(existingEmail, user.email) == 0) {
                emailExists = 1;
            }
        }
        fclose(file);
    }

    // If duplicates exist, prompt the user and return
    if (usernameExists) {
        printf("\nUsername already exists. Please choose a different username.\n");
        return;
    }
    if (emailExists) {
        printf("Email already exists. Please choose a different email.\n");
        return;
    }

    // Open the file in append mode to register the new user
    file = fopen("users.txt", "a");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    // Write the new user to the file
    fprintf(file, "%s,%s,%s,%s,%s\n", user.fullName, user.username, user.email, user.phone, user.password);
    fclose(file);
    printf("\nRegistration successful!\n\n");
}

int loginUser() {
    FILE *file;
    struct User user;
    char username[30], password[30];

    file = fopen("users.txt", "r");
    if (file == NULL) {
        printf("No users registered yet. Please register first.\n");
        return 0;
    }

    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    strtok(username, "\n");

    printf("Enter password: ");
    fgets(password, sizeof(password), stdin);
    strtok(password, "\n");

    while (fscanf(file, "%[^,],%[^,],%[^,],%[^,],%[^\n]\n",
                  user.fullName, user.username, user.email, user.phone, user.password) == 5) {
        if (strcmp(user.username, username) == 0 && strcmp(user.password, password) == 0) {
            fclose(file);
            printf("\nLogin Successful!\n");
            return 1;
        }
    }

    fclose(file);
    printf("Invalid username or password. Please try again.\n\n");
    return 0;
}

void showMenu() {
    int choice;

    while (1) {
        printf("\n\t\tMAIN MENU\n");
        printf("1. Add Customer\n");
        printf("2. View Customers\n");
        printf("3. Edit Customer\n");
        printf("4. Delete Customer\n");
        printf("5. Search Customer\n");
        printf("6. Transactions\n");
        printf("7. About\n");
        printf("8. Logout\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Add Customer functionality will be implemented here.\n");
                break;
            case 2:
                printf("View Customers functionality will be implemented here.\n");
                break;
            case 3:
                printf("Edit Customer functionality will be implemented here.\n");
                break;
            case 4:
                printf("Delete Customer functionality will be implemented here.\n");
                break;
            case 5:
                printf("Search Customer functionality will be implemented here.\n");
                break;
            case 6:
                printf("Transactions functionality will be implemented here.\n");
                break;
            case 7:
                printf("About functionality will be implemented here.\n");
                break;
            case 8:
                printf("Logging out...\n");
                return;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    }
}

int main() {
    int choice;

    do {
        printf("1. Register\n");
        printf("2. Login\n");
        printf("Choose an option: ");
        scanf("%d", &choice);
        getchar();

        if (choice == 1) {
            registerUser();
        } else if (choice == 2) {
            if (loginUser()) {
                showMenu();
            } else {
                printf("Invalid login. Please try again.\n");
            }
        } else {
            printf("Invalid choice. Please choose again.\n");
        }
    } while (choice != 3);

    return 0;
}
