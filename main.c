/* EL2208 Praktikum Pemecahan Masalah dengan C 2023/2024
* Modul            : Tubes - Travelling Salesmen Problem 
* Nama (NIM)       : Dwi Rezky Fahlan (18321018)
* Asisten (NIM)    : Emmanuella Pramudita Rumanti (13220031)
* Nama File        : main.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <windows.h>

#define MAX_ROWS 100 
#define MAX_COLUMNS 4 
#define MAX_VALUE_LENGTH 20 
#define PI 3.14159265358979323846 
float total_distance = 0; //initiate total distance

float distance(float la1, float la2, float lo1, float lo2) {
    //convert to radian
    la1 = la1 * PI / 180; 
    la2 = la2 * PI / 180;
    lo1 = lo1 * PI / 180;
    lo2 = lo2 * PI / 180;
    //formula
    float sub_a = pow(sin((la2 - la1) / 2), 2);
    float sub_b = cos(la1) * cos(la2) * pow(sin((lo2 - lo1) / 2), 2);
    float d = 2 * 6371 * asin(sqrt(sub_a + sub_b)); 
    return d;
}


void route(char mat[MAX_ROWS][MAX_COLUMNS][MAX_VALUE_LENGTH], char start[20], int rows) {
    int visited[MAX_ROWS] = {0}; //declare an array to keep track of visited cities
    int current_city = -1; //declare Var to store current city index
    float min_distance; //declare Var to store the minimum distance

    //find index of starting city
    for (int i = 0; i < rows; i++) {
        if (strcmp(mat[i][0], start) == 0) {
            current_city = i; //store the starting city index in current_city
            break;
        }
    }
    if (current_city == -1) {
        printf("Starting point not found.\n");
        return;
    }

    printf("Best route:\n"); //start print
    printf("%s", start); //print the starting city

    visited[current_city] = 1; //Mark visited as 1

    //iterate through all cities
    for (int i = 0; i < rows - 1; i++) {
        min_distance = INFINITY; //initiate min distance
        int next_city = -1; //intiate index for next city

        //find the nearest neighbor 
        for (int j = 0; j < rows; j++) {
            if (!visited[j]) {
                float dist = distance(atof(mat[current_city][1]), atof(mat[j][1]), atof(mat[current_city][2]), atof(mat[j][2]));
                if (dist < min_distance) {
                    min_distance = dist;
                    next_city = j;
                }
            }
        }
        //mark the nearest neighbor as visited and print it
        if (next_city != -1) {
            visited[next_city] = 1;
            printf(" -> %s", mat[next_city][0]);
            current_city = next_city;
            //add the distance to the total distance
            total_distance += min_distance;
        }
    }
    //return to the starting city
    printf(" -> %s", start);
    //add distance from last city to start city
    total_distance += distance(atof(mat[current_city][1]), atof(mat[0][1]), atof(mat[current_city][2]), atof(mat[0][2]));
    //print total distance
    printf("\nTotal distance: %.2f km\n", total_distance);
}

int main() {
    //input file name
    printf("Enter filename: ");
    char filename[100];
    scanf("%s", filename);

    //input starting point
    printf("Enter starting point: ");
    char start[20];
    scanf("%s", start);

    //intiate and record start time
    clock_t start_t, end_t;
    double t;
    start_t = clock();

    // Open the file
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        printf("Can't open file -> recheck the file name, and file existance\n");
        return 1;
    }

    char buffer[1024];
    char mat[MAX_ROWS][MAX_COLUMNS][MAX_VALUE_LENGTH];

    int row = 0;
    while (fgets(buffer, 1024, fp) && row < MAX_ROWS) {
        char *value = strtok(buffer, ";\n");
        int column = 0;
        while (value != NULL && column < MAX_COLUMNS) {
            //copy tokenized value to matrix
            strncpy(mat[row][column], value, MAX_VALUE_LENGTH - 1);
            mat[row][column][MAX_VALUE_LENGTH - 1] = '\0'; //ensure null-termination
            
            column++;
            value = strtok(NULL, ";\n");
        }
        row++;
    }

    // Close the file
    fclose(fp);

    // Calculate the route
    route(mat, start, row);

    //record end time
    end_t = clock();

    //calculate time
    t = ((double) (end_t - start_t)) / CLOCKS_PER_SEC;

    //print time elapsed
    printf("Time elapsed for core computation: %f s\n", t);

    return 0;
}
