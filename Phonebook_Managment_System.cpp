#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Define a struct to represent each contact in the phonebook
struct contact {
    char name[50];
    char phone_number[20];
};

// Keep track of the number of contacts in the phonebook
int num_contacts = 0;

// Function to add a contact to the phonebook
void add_contact() {
    struct contact new_contact;

    printf("Enter name: ");
    scanf("%s", new_contact.name);

    printf("Enter phone number: ");
    scanf("%s", new_contact.phone_number);

    // Open the phonebook file in append mode
    FILE *fp = fopen("phonebook.txt", "a");

    // Write the new contact to the file
    fprintf(fp, "%s %s\n", new_contact.name, new_contact.phone_number);

    // Close the file
    fclose(fp);

    printf("Contact added successfully!\n");
}

// Function to print all contacts in the phonebook
void print_phonebook() {
    // Open the phonebook file in read mode
    FILE *fp = fopen("phonebook.txt", "r");

    if (fp == NULL) {
        printf("Phonebook is empty.\n");
        return;
    }

    printf("Phonebook:\n");

    // Read each line from the file and print the contact
    char line[100];
    while (fgets(line, 100, fp) != NULL) {
        char name[50];
        char phone_number[20];
        sscanf(line, "%s %s", name, phone_number);
        printf("%d. %s - %s\n", ++num_contacts, name, phone_number);
    }

    // Close the file
    fclose(fp);
}

// Function to search for a contact in the phonebook
void search_contact() {
    // Open the phonebook file in read mode
    FILE *fp = fopen("phonebook.txt", "r");

    if (fp == NULL) {
        printf("Phonebook is empty.\n");
        return;
    }

    char search_name[50];
    printf("Enter name to search for: ");
    scanf("%s", search_name);

    // Read each line from the file and search for the contact
    char line[100];
    while (fgets(line, 100, fp) != NULL) {
        char name[50];
        char phone_number[20];
        sscanf(line, "%s %s", name, phone_number);
        if (strcmp(name, search_name) == 0) {
            printf("%s - %s\n", name, phone_number);
            return;
        }
    }

    printf("Contact not found.\n");

    // Close the file
    fclose(fp);
}

// Function to delete a contact from the phonebook

void delete_contact() {
    // Open the phonebook file in read mode
    FILE *fp = fopen("phonebook.txt", "r");
    if (fp == NULL) {
        printf("Phonebook is empty.\n");
        return;
    }

    char delete_name[50];
    printf("Enter name to delete: ");
    scanf("%s", delete_name);

    // Open a temporary file in write mode
    FILE *temp_fp = fopen("temp.txt", "w");
    if (temp_fp == NULL) {
        printf("Error creating temporary file.\n");
        return;
    }

    // Read each line from the file and copy to the temporary file except the one to be deleted
    char line[100];
    int contact_deleted = 0;
    while (fgets(line, 100, fp) != NULL) {
        char name[50];
        char phone_number[20];
        sscanf(line, "%s %s", name, phone_number);
        if (strcmp(name, delete_name) == 0) {
            contact_deleted = 1;
        } else {
            fprintf(temp_fp, "%s %s\n", name, phone_number);
        }
    }

    // Close the files
    fclose(fp);
    fclose(temp_fp);

    if (!contact_deleted) {
        printf("Contact not found.\n");
        // Delete the temporary file
        remove("temp.txt");
    } else {
        // Delete the original file
        remove("phonebook.txt");
        // Replace it with the temporary file
        rename("temp.txt", "phonebook.txt");
        printf("Contact deleted successfully!\n");
    }
}

int main() {
            printf("**********Phonebook Management System**********\n");
    int choice;
    do {

        printf("\n\n");
        printf("1. Add contact\n\n");
        printf("2. Print all contacts\n\n");
        printf("3. Search for a contact\n\n");
        printf("4. Delete a contact\n\n");
        printf("5. Exit\n\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                add_contact();
                break;
            case 2:
                print_phonebook();
                break;
            case 3:
                search_contact();
                break;
            case 4:
                delete_contact();
                break;
            case 5:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice.\n");
                break;
        }
    } while (choice != 5);

    return 0;
}
