// Alp Kaan Özgül 2638096

#include <stdio.h>
#include <stdlib.h>
#include <string.h>



struct mystruct {
    char name[100];
    int x_initial;
    int x_final;
    int y_initial;
    int y_final;
};                                                      //Here i declared structs

typedef struct {
    char name[100];
    int x_initial;
    int x_final;
    int y_initial;
    int y_final;
} SignaturesTable;



SignaturesTable* Load_SignaturesTable (char docname[100]);
int Search(int i,SignaturesTable* returnedarray);                                   //here are the functions
int* Sort(int i,SignaturesTable* returnedarray);
void Display_SignaturesTable(int i,SignaturesTable* returnedarray,int returned_sort[],int check,int position_check);

int main() {                                                                                                            // MAIN FUNCTION
    char docname[100];
    int i=9;
    int position_check;             //here are the variables of the main function
    int* returned_sort;
    int check=0;
    int choise;



    printf("Please enter the file name: \n");
    gets(docname);                                                              //As it is asked to pass the name of the text file to the function i got the name in main function
    SignaturesTable* returnedarray= Load_SignaturesTable(docname);

    Display_SignaturesTable(i,returnedarray,returned_sort,check,position_check);


    while(choise!=3) {                              //in this loop i made the program to loop until 3 is typed

        printf("\nTo search for a signature, please press 1\nTo sort signatures based on width or height, please press 2\nTo exit, please press 3\n");
        printf("Your choise: \n");
        scanf("%d", &choise);

        if (choise == 1) {
            check = 1;
            position_check = Search(i, returnedarray);
            Display_SignaturesTable(i, returnedarray, returned_sort, check, position_check);


        } else if (choise == 2) {
            check = 2;
            Sort(i, returnedarray);
            Display_SignaturesTable(i, returnedarray, returned_sort, check, position_check);


        }
    }

    free(returnedarray);  // to free the space in the ram
    return 0;
}


int Search(int i,SignaturesTable* returnedarray)                                                                            //SEARCH FUNCTION
{
    int position_check=0;
    int check=1;
    char name_input[100];


    printf("Enter the name of the signature owner:\n");
    while (check == 1) {
        fflush(stdin);
        gets(name_input);
        position_check=0;

        for (int j = 0; j < i; j++) {

                                                                            // here i compared the strings inorder to evaluate if the entered name is included or not and to forward process that inormation
            if (strcmp(name_input, returnedarray[j].name) == 0) {
                check = 0;

                break;
            }
            position_check=position_check+1;

        }

        if (check == 1) {
            printf("That owner does not exist! Please try again!\n");
            printf("Enter the name of the signature owner:\n");
        }

    }
    return position_check;


}


SignaturesTable* Load_SignaturesTable(char docname[100]) {
    int countrow = 0;

    FILE *infile;                               //here is to read the file
    infile = fopen(docname, "r");

    while (infile == NULL) {
        printf("This file does not exist. Please enter again:\n");
        gets(docname);
        infile = fopen(docname, "r");
    }

    printf("The signature records file (%s) has been successfully loaded!\n", docname);
    printf("The following records have been loaded:\n");

    char line[100];

    struct mystruct record;
                                                                    //here i counted how many rows are there in the text in order to dynamically alocate that many memory
    while (fgets(line, sizeof(line), infile) != NULL) {
        sscanf(line, "%[^;];%d;%d;%d;%d", record.name, &record.x_initial, &record.x_final, &record.y_initial, &record.y_final);
        countrow++;
    }

    SignaturesTable* SignaturesTable1 = (SignaturesTable*)malloc(countrow * sizeof(SignaturesTable));  // here i allocated countrow many memories for SignaturesTable sized struct
    if (SignaturesTable1 == NULL) {
        printf("Memory allocation failed.\n");
        fclose(infile);
        exit(1);
    }

    fclose(infile);
    infile = fopen(docname, "r");

    int i = 0;                                                              //here i inputed the data from the file to reserved memory cells
    while (fgets(line, sizeof(line), infile) != NULL && i < countrow) {
        sscanf(line, "%[^;];%d;%d;%d;%d;", SignaturesTable1[i].name, &SignaturesTable1[i].x_initial, &SignaturesTable1[i].x_final, &SignaturesTable1[i].y_initial, &SignaturesTable1[i].y_final);
        i++;
    }

    fclose(infile);

    return SignaturesTable1;
}


int* Sort(int q, SignaturesTable* returnedarray)
{
    char sort_choice;

    printf("Sort by (w: width, h: height):\n");
    fflush(stdin);
    scanf("%c", &sort_choice);

    if (sort_choice == 'w') {                           //here is the bubble sort alghoritm to sort width values

        for (int i = 0; i < q; i++) {
            for (int j = 0; j < q - i - 1; j++) {
                int diff1 = returnedarray[j].x_final - returnedarray[j].x_initial;
                int diff2 = returnedarray[j + 1].x_final - returnedarray[j + 1].x_initial;

                if (diff1 < diff2) {
                    // Swap the elements
                    SignaturesTable temp = returnedarray[j];
                    returnedarray[j] = returnedarray[j + 1];
                    returnedarray[j + 1] = temp;
                }
            }
        }



    }
    else if (sort_choice=='h')                                          //here is the bubble sort alghoritm to sort height values
    {
        for (int i = 0; i <q ; i++) {
            for (int j = 0; j < q - i - 1; j++) {
                int diff1 = returnedarray[j].y_final - returnedarray[j].y_initial;
                int diff2 = returnedarray[j + 1].y_final - returnedarray[j + 1].y_initial;

                if (diff1 < diff2) {
                    // Swap the elements
                    SignaturesTable temp = returnedarray[j];
                    returnedarray[j] = returnedarray[j + 1];
                    returnedarray[j + 1] = temp;
                }
            }
        }
    }


}

void Display_SignaturesTable(int i,SignaturesTable* returnedarray,int returned_sort[],int check,int position_check)
{
    int width,height;                                           //here is the display function to display the information
    if (check==0)
    {
        printf("%-15s %-12s %-10s %-13s %-11s %-8s %-8s\n", "full_name", "x_initial", "x_final", "y_initial", "y_final", "width", "height");
        for (int j = 1; j < i - 1; j++) {
            width = returnedarray[j].x_final - returnedarray[j].x_initial;
            height = returnedarray[j].y_final - returnedarray[j].y_initial;
            printf("%-15s   %-12d %-10d %-13d %-11d %-8d %-8d\n", returnedarray[j].name, returnedarray[j].x_initial,
                   returnedarray[j].x_final, returnedarray[j].y_initial, returnedarray[j].y_final, width, height);
        }

    }

    if (check==2) {

        printf("%-15s %-12s %-10s %-13s %-11s %-8s %-8s\n", "full_name", "x_initial", "x_final", "y_initial", "y_final", "width", "height");
        for (int j = 0; j < i-1; j++) {
            width = (returnedarray[j].x_final) - (returnedarray[j].x_initial);
            height = (returnedarray[j].y_final) - (returnedarray[j].y_initial);
            printf("%-15s   %-12d %-10d %-13d %-11d %-8d %-8d\n", returnedarray[j].name, returnedarray[j].x_initial,
                   returnedarray[j].x_final, returnedarray[j].y_initial, returnedarray[j].y_final, width, height);
        }
    }

    if (check==1)
    {
        printf("%s start signing at x=%d and y=%d and finalized at x=%d and\n"
               "y=%d. Hence, Elina Cantu has a signature of width %d and height %d\n\n",returnedarray[position_check].name,returnedarray[position_check].x_initial,returnedarray[position_check].y_initial,returnedarray[position_check].x_final,returnedarray[position_check].y_final,(returnedarray[position_check].x_final)-(returnedarray[position_check].x_initial),(returnedarray[position_check].y_final)-(returnedarray[position_check].y_initial));
    }
}

