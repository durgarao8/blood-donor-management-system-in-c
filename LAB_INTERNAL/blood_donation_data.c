#include<stdio.h>
#include<string.h>
struct blood_donor
{
    /* data */
    char donor_name[50];
    char blood_group[5];
    char area_city[50];
    long int contact_no;
    int age;
};

int main(){
        struct blood_donor donor[200];
        int number_of_donors;
        FILE *data;
        printf("enter the number of donor who donnated blood");
        scanf("%d",&number_of_donors);
        for(int i=0;i<number_of_donors;i++){
            printf("ennter the donor %d data\n",i+1);
            printf("\nNOTE: please use underscore instead f spaces\n");
            printf("name:");
            scanf("%s",donor[i].donor_name);
            printf("\ndonoted blood group:");
            scanf("%s",donor[i].blood_group);
            printf("area or city:");
            scanf("%s",donor[i].area_city);
            printf("contect number :");
            scanf("%lu",&donor[i].contact_no);
            printf("age :");
            scanf("%d",&donor[i].age);    
        }
        data=fopen("donors_data.txt","w");
        //fprintf(data,"%-6s %-15s %-15s %-6s %-18s %-15s\n","S.No", "Name", "Blood Group", "Age", "Contact Number", "Area");
        for(int i=0;i<number_of_donors;i++){
            fprintf(data,"%-6d %-15s %-15s %-6d %-18lu %-15s\n",i+1,donor[i].donor_name,donor[i].blood_group,donor[i].age,donor[i].contact_no,donor[i].area_city);

        }
        fclose(data);
        printf("\n---------------- Donor List ----------------\n");
        printf("%-5s %-20s %-10s %-5s %-15s %-15s\n","S.No", "Name", "Blood Group", "Age", "Contact", "AREA/CITY");
        for (int  i = 0; i < number_of_donors; i++)
        {
            /* code */
            printf("%-5d %-20s %-10s %-5d %-15lu %-15s\n",i+1,donor[i].donor_name,donor[i].blood_group,donor[i].age,donor[i].contact_no,donor[i].area_city);
            
        }
        
        //assifging names to the another array of strong for seaaerching and deleting
        char donors_names[100][40];
        for (int  i = 0; i < number_of_donors; i++)
        {
            /* code */
            //strcpy(donors_names[i],donor[i].donor_name);
           strcpy(donors_names[i],donor[i].donor_name);
        }
        //searching by name 

        char search_name[50];
        printf("enter the name you want to search");
        //fgets(search_name,sizeof(search_name),stdin);
        scanf("%s",search_name);
        int found;
        int search_data;
        for (int  i = 0; i < number_of_donors; i++)
        {
            /* code */
            if(strcmp(search_name,donors_names[i])==0){
                    found=1;
                    search_data=i;

                break;
            }
        }
        if(found){
            printf("*****************The name is found the donor data is:*****************\n");
            printf("%-5s %-20s %-10s %-5s %-15s %-15s\n","S.No", "Name", "Blood Group", "Age", "Contact", "AREA/CITY");
            printf("%-5d %-20s %-10s %-5d %-15lu %-15s\n",search_data+1,donor[search_data].donor_name,donor[search_data].blood_group,donor[search_data].age,donor[search_data].contact_no,donor[search_data].area_city);
        }else{
            printf("not found!!!\n");
        }
        //appending
         // 🔹 APPEND NEW DONOR SECTION (Added after search)
    char choice1 = 'y';
    int new_count = 0;
    FILE *append_file = fopen("donors_data.txt", "a");
    if (append_file == NULL) {
        printf("Error opening file for appending!\n");
        return 1;
    }

    printf("\nDo you want to add new donors? (y/n): ");
    scanf(" %c", &choice1);

    while (choice1 == 'y' || choice1 == 'Y') {
        printf("\nEnter new donor details:\n");
        printf("Name: ");
        scanf("%s", donor[number_of_donors].donor_name);
        printf("Blood Group: ");
        scanf("%s", donor[number_of_donors].blood_group);
        printf("Area/City: ");
        scanf("%s", donor[number_of_donors].area_city);
        printf("Contact Number: ");
        scanf("%lu", &donor[number_of_donors].contact_no);
        printf("Age: ");
        scanf("%d", &donor[number_of_donors].age);

        number_of_donors++;
        new_count++;

                fprintf(append_file, "%-6d %-15s %-15s %-6d %-18lu %-15s\n",
                number_of_donors,
                donor[number_of_donors - 1].donor_name,
                donor[number_of_donors - 1].blood_group,
                donor[number_of_donors - 1].age,
                donor[number_of_donors - 1].contact_no,
                donor[number_of_donors - 1].area_city);

        printf("Do you want to add another donor? (y/n): ");
        scanf(" %c", &choice1);
    }
    fclose(append_file);

        //Updating the data
            int serial_number;
    printf("\nEnter the serial number of donor to update: ");
    scanf("%d", &serial_number);

    if (serial_number < 1 || serial_number > number_of_donors) {
        printf("Invalid serial number.\n");
        return 1;
    }

    int idx = serial_number - 1; // Safe index
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
                scanf(" %s", donor[idx].donor_name);
                break;
            case 5:
                printf("Enter new city: ");
                scanf(" %s", donor[idx].area_city);
                break;
            default:
                printf("Invalid choice.\n");
                break;
        }

        printf("\nDo you want to update another field for this donor? (y/n): ");
        scanf(" %c", &more);
    }
    FILE *temp;
    // Write updated data back to file
    temp = fopen("temp.txt", "w");
    if (temp == NULL) {
        printf("Error: Could not open temp.txt.\n");
        return 1;
    }

    for (int i = 0; i < number_of_donors; i++) {
        fprintf(temp, "%-5d %-15s %-10s %-5d %-15lu %-15s\n",
                i+1,
                donor[i].donor_name,
                donor[i].blood_group,
                donor[i].age,
                donor[i].contact_no,
                donor[i].area_city);
    }

    fclose(temp);
    remove("donors_data.txt");
    rename("temp.txt", "donors_data.txt");
    char name_to_delete[50];
    printf("enter the name which you want to delete");
    scanf("%s",name_to_delete);
    int find_name=0;
    for (int  i = 0; i < number_of_donors; i++)
    {
        /* code */
        if(strcmp(donor[i].donor_name,name_to_delete)==0){
            find_name=1;
            for(int j=i;j<number_of_donors-1;j++){
                donor[j]=donor[j+1];
            }
            number_of_donors--;
        }
    }
    FILE *tem;
    tem=fopen("tem.txt","w");
    for (int  i = 0; i<number_of_donors ;i++)
    {
        /* code */
         fprintf(tem, "%-5d %-15s %-10s %-5d %-15lu %-15s\n",
                i+1,
                donor[i].donor_name,
                donor[i].blood_group,
                donor[i].age,
                donor[i].contact_no,
                donor[i].area_city);
        
    }
    fclose(tem);
    remove("donors_data.txt");
    rename("tem.txt","donors_data.txt");
    printf("file is created\n");
    
    
}        
        