#include <stdio.h>
#include <string.h>

struct blood_donor
{
    char donor_name[50];
    char blood_group[5];
    char area_city[50];
    long int contact_no;
    int age;
};

// Function declarations
void enter_donor_data(struct blood_donor donor[], int *number_of_donors);
void display_donors(struct blood_donor donor[], int number_of_donors);
void search_by_name(struct blood_donor donor[], int number_of_donors);
void append_donors(struct blood_donor donor[], int *number_of_donors);
void update_donor_data(struct blood_donor donor[], int number_of_donors);
void delete_donor_data(struct blood_donor donor[], int *number_of_donors);

int main() {
    struct blood_donor donor[200];
    int number_of_donors;
    int choice;

    do {
        printf("\n=========== BLOOD DONOR MANAGEMENT SYSTEM ===========\n");
        printf("1. Enter donor data\n");
        printf("2. Search by name\n");
        printf("3. Append data\n");
        printf("4. Update data\n");
        printf("5. Delete data\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                enter_donor_data(donor, &number_of_donors);
                break;
            case 2:
                search_by_name(donor, number_of_donors);
                break;
            case 3:
                append_donors(donor, &number_of_donors);
                break;
            case 4:
                update_donor_data(donor, number_of_donors);
                break;
            case 5:
                delete_donor_data(donor, &number_of_donors);
                break;
            case 6:
                printf("Exiting program... Thank you!\n");
                break;
            default:
                printf("Invalid choice! Try again.\n");
        }
    } while (choice != 6);

    return 0;
}

/*------------------------------------------------------
 Function 1: Enter donor data and write to file
------------------------------------------------------*/
void enter_donor_data(struct blood_donor donor[], int *number_of_donors) {
    FILE *data;
    printf("enter the number of donor who donnated blood: ");
    scanf("%d", number_of_donors);
    
    for (int i = 0; i < *number_of_donors; i++) {
        printf("ennter the donor %d data\n", i + 1);
        printf("\nNOTE: please use underscore instead of spaces\n");
        printf("name: ");
        scanf("%s", donor[i].donor_name);
        printf("\ndonoted blood group: ");
        scanf("%s", donor[i].blood_group);
        printf("area or city: ");
        scanf("%s", donor[i].area_city);
        printf("contact number: ");
        scanf("%lu", &donor[i].contact_no);
        printf("age: ");
        scanf("%d", &donor[i].age);    
    }

    data = fopen("donors_data.txt", "w");
    for (int i = 0; i < *number_of_donors; i++) {
        fprintf(data, "%-6d %-15s %-15s %-6d %-18lu %-15s\n",
                i + 1, donor[i].donor_name, donor[i].blood_group,
                donor[i].age, donor[i].contact_no, donor[i].area_city);
    }
    fclose(data);

    display_donors(donor, *number_of_donors);
}

/*------------------------------------------------------
 Function 2: Display donor list
------------------------------------------------------*/
void display_donors(struct blood_donor donor[], int number_of_donors) {
    printf("\n---------------- Donor List ----------------\n");
    printf("%-5s %-20s %-10s %-5s %-15s %-15s\n",
           "S.No", "Name", "Blood Group", "Age", "Contact", "AREA/CITY");
    for (int i = 0; i < number_of_donors; i++) {
        printf("%-5d %-20s %-10s %-5d %-15lu %-15s\n",
               i + 1, donor[i].donor_name, donor[i].blood_group,
               donor[i].age, donor[i].contact_no, donor[i].area_city);
    }
}

/*------------------------------------------------------
 Function 3: Search donor by name
------------------------------------------------------*/
void search_by_name(struct blood_donor donor[], int number_of_donors) {
    char donors_names[100][40];
    for (int i = 0; i < number_of_donors; i++) {
        strcpy(donors_names[i], donor[i].donor_name);
    }

    char search_name[50];
    printf("Enter the name you want to search: ");
    scanf("%s", search_name);

    int found = 0, search_data = -1;
    for (int i = 0; i < number_of_donors; i++) {
        if (strcmp(search_name, donors_names[i]) == 0) {
            found = 1;
            search_data = i;
            break;
        }
    }

    if (found) {
        printf("***************** The name is found, the donor data is: *****************\n");
        printf("%-5s %-20s %-10s %-5s %-15s %-15s\n",
               "S.No", "Name", "Blood Group", "Age", "Contact", "AREA/CITY");
        printf("%-5d %-20s %-10s %-5d %-15lu %-15s\n",
               search_data + 1, donor[search_data].donor_name,
               donor[search_data].blood_group, donor[search_data].age,
               donor[search_data].contact_no, donor[search_data].area_city);
    } else {
        printf("Not found!!!\n");
    }
}

/*------------------------------------------------------
 Function 4: Append new donor data
------------------------------------------------------*/
void append_donors(struct blood_donor donor[], int *number_of_donors) {
    char choice1 = 'y';
    FILE *append_file = fopen("donors_data.txt", "a");
    if (append_file == NULL) {
        printf("Error opening file for appending!\n");
        return;
    }

    while (choice1 == 'y' || choice1 == 'Y') {
        printf("\nEnter new donor details:\n");
        printf("Name: ");
        scanf("%s", donor[*number_of_donors].donor_name);
        printf("Blood Group: ");
        scanf("%s", donor[*number_of_donors].blood_group);
        printf("Area/City: ");
        scanf("%s", donor[*number_of_donors].area_city);
        printf("Contact Number: ");
        scanf("%lu", &donor[*number_of_donors].contact_no);
        printf("Age: ");
        scanf("%d", &donor[*number_of_donors].age);

        (*number_of_donors)++;

        fprintf(append_file, "%-6d %-15s %-15s %-6d %-18lu %-15s\n",
                *number_of_donors,
                donor[*number_of_donors - 1].donor_name,
                donor[*number_of_donors - 1].blood_group,
                donor[*number_of_donors - 1].age,
                donor[*number_of_donors - 1].contact_no,
                donor[*number_of_donors - 1].area_city);

        printf("Do you want to add another donor? (y/n): ");
        scanf(" %c", &choice1);
    }
    fclose(append_file);
}

/*------------------------------------------------------
 Function 5: Update donor data
------------------------------------------------------*/
void update_donor_data(struct blood_donor donor[], int number_of_donors) {
    int serial_number;
    printf("\nEnter the serial number of donor to update: ");
    scanf("%d", &serial_number);

    if (serial_number < 1 || serial_number > number_of_donors) {
        printf("Invalid serial number.\n");
        return;
    }

    int idx = serial_number - 1;
    int choice;
    char more = 'y';

    while (more == 'y' || more == 'Y') {
        printf("\nWhich field do you want to update?\n");
        printf("1. Age\n2. Contact Number\n3. Blood Group\n4. Name\n5. City\nEnter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter new age: ");
                scanf("%d", &donor[idx].age);
                break;
            case 2:
                printf("Enter new contact number: ");
                scanf("%lu", &donor[idx].contact_no);
                break;
            case 3:
                printf("Enter new blood group: ");
                scanf("%s", donor[idx].blood_group);
                break;
            case 4:
                printf("Enter new name: ");
                scanf("%s", donor[idx].donor_name);
                break;
            case 5:
                printf("Enter new city: ");
                scanf("%s", donor[idx].area_city);
                break;
            default:
                printf("Invalid choice.\n");
                break;
        }

        printf("\nDo you want to update another field for this donor? (y/n): ");
        scanf(" %c", &more);
    }

    FILE *temp = fopen("temp.txt", "w");
    for (int i = 0; i < number_of_donors; i++) {
        fprintf(temp, "%-5d %-15s %-10s %-5d %-15lu %-15s\n",
                i + 1, donor[i].donor_name, donor[i].blood_group,
                donor[i].age, donor[i].contact_no, donor[i].area_city);
    }
    fclose(temp);
    remove("donors_data.txt");
    rename("temp.txt", "donors_data.txt");
}

/*------------------------------------------------------
 Function 6: Delete donor data
------------------------------------------------------*/
void delete_donor_data(struct blood_donor donor[], int *number_of_donors) {
    char name_to_delete[50];
    printf("Enter the name which you want to delete: ");
    scanf("%s", name_to_delete);
    int find_name = 0;

    for (int i = 0; i < *number_of_donors; i++) {
        if (strcmp(donor[i].donor_name, name_to_delete) == 0) {
            find_name = 1;
            for (int j = i; j < *number_of_donors - 1; j++) {
                donor[j] = donor[j + 1];
            }
            (*number_of_donors)--;
            break;
        }
    }

    FILE *tem = fopen("tem.txt", "w");
    for (int i = 0; i < *number_of_donors; i++) {
        fprintf(tem, "%-5d %-15s %-10s %-5d %-15lu %-15s\n",
                i + 1, donor[i].donor_name, donor[i].blood_group,
                donor[i].age, donor[i].contact_no, donor[i].area_city);
    }
    fclose(tem);
    remove("donors_data.txt");
    rename("tem.txt", "donors_data.txt");
    printf("File updated after deletion.\n");
}
