#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_STUDENTS 100
#define FILE_NAME "students.dat"

// Student structure
struct Student
{
    int student_id;
    char class_id[20];
    char name[50];
    char email[50];
    char phone[20];
};

// Function Prototypes
void addStudent();
void viewAllStudents();
void searchStudent();
void updateStudent();
void deleteStudent();
void seedSampleData();

int loadStudents(struct Student list[]);
void saveStudents(struct Student list[], int count);

void clearInputBuffer();
void printHeader();
void printRow(struct Student s);

// Main Function
int main()
{
    int choice;

    FILE *fp = fopen(FILE_NAME, "rb");

    if(fp == NULL)
    {
        seedSampleData();
    }
    else
    {
        fclose(fp);
    }

    do
    {
        printf("\n====================================\n");
        printf("     STUDENT MANAGEMENT SYSTEM\n");
        printf("====================================\n");
        printf("1. Add Student\n");
        printf("2. View All Students\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("0. Exit\n");

        printf("\nEnter Choice: ");

        if(scanf("%d",&choice)!=1)
        {
            clearInputBuffer();
            printf("Invalid Input!\n");
            continue;
        }

        clearInputBuffer();

        switch(choice)
        {
            case 1:
                addStudent();
                break;

            case 2:
                viewAllStudents();
                break;

            case 3:
                searchStudent();
                break;

            case 4:
                updateStudent();
                break;

            case 5:
                deleteStudent();
                break;

            case 0:
                printf("\nThank You!\n");
                break;

            default:
                printf("Invalid Choice!\n");
        }

    }while(choice!=0);

    return 0;
}

// Clear input buffer
void clearInputBuffer()
{
    int ch;

    while((ch=getchar())!='\n' && ch!=EOF);
}

// Table Header
void printHeader()
{
    printf("\n-------------------------------------------------------------------------------\n");
    printf("%-8s %-10s %-20s %-25s %-15s\n",
           "ID","Class","Name","Email","Phone");
    printf("-------------------------------------------------------------------------------\n");
}

// Print One Student
void printRow(struct Student s)
{
    printf("%-8d %-10s %-20s %-25s %-15s\n",
           s.student_id,
           s.class_id,
           s.name,
           s.email,
           s.phone);
}

// Load Students
int loadStudents(struct Student list[])
{
    FILE *fp=fopen(FILE_NAME,"rb");

    if(fp==NULL)
        return 0;

    int count=0;

    while(fread(&list[count],sizeof(struct Student),1,fp)==1
          && count<MAX_STUDENTS)
    {
        count++;
    }

    fclose(fp);

    return count;
}

// Save Students
void saveStudents(struct Student list[],int count)
{
    FILE *fp=fopen(FILE_NAME,"wb");

    if(fp==NULL)
    {
        printf("File Error!\n");
        return;
    }

    fwrite(list,sizeof(struct Student),count,fp);

    fclose(fp);
}
// Create Sample Data
void seedSampleData()
{
    struct Student samples[5] =
    {
        {1001,"BSCS-3A","Sakina","sakina@gmail.com","03001234567"},
        {1002,"BSCS-3A","Maryam","maryam@gmail.com","03111234567"},
        {1003,"BSCS-3B","Sara Ali","sara@gmail.com","03221234567"},
        {1004,"BSCS-3B","Ayesha Noor","ayesha@gmail.com","03331234567"},
        {1005,"BSCS-3C","Hassan Malik","hassan@gmail.com","03441234567"}
    };

    saveStudents(samples,5);
}

// Add Student
void addStudent()
{
    struct Student list[MAX_STUDENTS];
    struct Student s;

    int count=loadStudents(list);

    if(count>=MAX_STUDENTS)
    {
        printf("Storage Full!\n");
        return;
    }

    printf("\nEnter Student ID : ");
    scanf("%d",&s.student_id);
    clearInputBuffer();

    for(int i=0;i<count;i++)
    {
        if(list[i].student_id==s.student_id)
        {
            printf("Student ID Already Exists!\n");
            return;
        }
    }

    printf("Enter Class : ");
    fgets(s.class_id,sizeof(s.class_id),stdin);
    s.class_id[strcspn(s.class_id,"\n")]=0;

    printf("Enter Name : ");
    fgets(s.name,sizeof(s.name),stdin);
    s.name[strcspn(s.name,"\n")]=0;

    printf("Enter Email : ");
    fgets(s.email,sizeof(s.email),stdin);
    s.email[strcspn(s.email,"\n")]=0;

    printf("Enter Phone : ");
    fgets(s.phone,sizeof(s.phone),stdin);
    s.phone[strcspn(s.phone,"\n")]=0;

    list[count]=s;
    count++;

    saveStudents(list,count);

    printf("\nStudent Added Successfully.\n");
}

// View All Students
void viewAllStudents()
{
    struct Student list[MAX_STUDENTS];

    int count=loadStudents(list);

    if(count==0)
    {
        printf("\nNo Student Record Found.\n");
        return;
    }

    printf("\nTotal Students : %d\n",count);

    printHeader();

    for(int i=0;i<count;i++)
    {
        printRow(list[i]);
    }

    printf("-------------------------------------------------------------------------------\n");
}
// Search Student
void searchStudent()
{
    struct Student list[MAX_STUDENTS];
    int count = loadStudents(list);
    int id, found = 0;

    printf("\nEnter Student ID : ");
    scanf("%d", &id);
    clearInputBuffer();

    for(int i = 0; i < count; i++)
    {
        if(list[i].student_id == id)
        {
            printHeader();
            printRow(list[i]);
            printf("-------------------------------------------------------------------------------\n");
            found = 1;
            break;
        }
    }

    if(!found)
    {
        printf("Student Not Found.\n");
    }
}

// Update Student
void updateStudent()
{
    struct Student list[MAX_STUDENTS];
    int count = loadStudents(list);
    int id, found = -1;
    char temp[100];

    printf("\nEnter Student ID : ");
    scanf("%d", &id);
    clearInputBuffer();

    for(int i = 0; i < count; i++)
    {
        if(list[i].student_id == id)
        {
            found = i;
            break;
        }
    }

    if(found == -1)
    {
        printf("Student Not Found.\n");
        return;
    }

    printf("Enter New Class : ");
    fgets(temp, sizeof(temp), stdin);
    temp[strcspn(temp, "\n")] = 0;
    if(strlen(temp) > 0)
        strcpy(list[found].class_id, temp);

    printf("Enter New Name : ");
    fgets(temp, sizeof(temp), stdin);
    temp[strcspn(temp, "\n")] = 0;
    if(strlen(temp) > 0)
        strcpy(list[found].name, temp);

    printf("Enter New Email : ");
    fgets(temp, sizeof(temp), stdin);
    temp[strcspn(temp, "\n")] = 0;
    if(strlen(temp) > 0)
        strcpy(list[found].email, temp);

    printf("Enter New Phone : ");
    fgets(temp, sizeof(temp), stdin);
    temp[strcspn(temp, "\n")] = 0;
    if(strlen(temp) > 0)
        strcpy(list[found].phone, temp);

    saveStudents(list, count);

    printf("\nStudent Updated Successfully.\n");
}

// Delete Student
void deleteStudent()
{
    struct Student list[MAX_STUDENTS];
    int count = loadStudents(list);
    int id, found = -1;
    char choice;

    printf("\nEnter Student ID : ");
    scanf("%d", &id);
    clearInputBuffer();

    for(int i = 0; i < count; i++)
    {
        if(list[i].student_id == id)
        {
            found = i;
            break;
        }
    }

    if(found == -1)
    {
        printf("Student Not Found.\n");
        return;
    }

    printf("Delete %s? (Y/N): ", list[found].name);
    scanf(" %c", &choice);
    clearInputBuffer();

    if(tolower(choice) != 'y')
    {
        printf("Delete Cancelled.\n");
        return;
    }

    for(int i = found; i < count - 1; i++)
    {
        list[i] = list[i + 1];
    }

    count--;

    saveStudents(list, count);

    printf("Student Deleted Successfully.\n");
}