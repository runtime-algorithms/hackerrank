#include <assert.h>
#include <ctype.h>
#include <limits.h> //used?
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h> //used
#include <stdlib.h> //used
#include <string.h>
//the rest are unused
char* readline();
char* ltrim(char*);
char* rtrim(char*);
char** split_string(char*);

int parse_int(char*);

/* https://www.hackerrank.com/challenges/connected-cell-in-a-grid/problem
 * Completed the 'connectedCell' function below.
 * my idea was to share a pointer across the grid 
 * I just wasn't adding values of connected grids at first
 * So literally everything before the 'add' variable
 *
 * The function is expected to return an INTEGER.
 * The function accepts 2D_INTEGER_ARRAY matrix as parameter.
 */
typedef struct Reference{
    int *data;
}Reference;
struct Reference *newReference(int n){
    struct Reference *toReturn=(struct Reference*)malloc(sizeof(struct Reference));
    toReturn->data=(int*)malloc(sizeof(int));
    *(toReturn->data)=n;
    return toReturn;
}
int getData(struct Reference *x){
    if(x==NULL) return 0;
    return *(x->data);
}
void editData(struct Reference *x, int n){*(x->data)=n;}
void editDataPtr(struct Reference *x, int *n){x->data=n;}
int connectedCell(int rows, int cols, int** matrix) {
    struct Reference *MATRIX[rows*cols];
    int max=0;
    for(int r=0;r<rows;r++){
        for(int c=0;c<cols;c++){
            int pos=r*cols+c, add=1;
            if(matrix[r][c]==0){
                MATRIX[pos]=NULL;
                continue;
            }
            int p[4]={
                (r-1)*cols+(c-1),
                (r-1)*cols+c,
                (r-1)*cols+(c+1),
                r*cols+(c-1)
            };
            struct Reference *P[4]={
                r>0&&c>0? MATRIX[p[0]]: NULL,
                r>0? MATRIX[p[1]]: NULL,
                r>0&&c<cols-1? MATRIX[p[2]]: NULL,
                c>0? MATRIX[p[3]]: NULL
            };
            struct Reference *nmax=P[0];
            for(int i=1;i<4;i++)
                if(getData(nmax)<getData(P[i])) nmax=P[i];
            if(nmax==NULL){
                nmax=newReference(1);
                MATRIX[pos]=nmax;
                if(max<1) max=1;
            }
            else{
                for(int i=0;i<4;i++){
                    if(P[i]!=NULL&&P[i]->data!=nmax->data){
                        int data=getData(P[i]);
                        if(data>1) editDataPtr(P[i], nmax->data);
                        else MATRIX[p[i]]=nmax;
                        P[i]=nmax;
                        add+=data;
                    }
                }
                MATRIX[pos]=nmax;
                editData(nmax, getData(nmax)+add);
                if(max<getData(nmax)) max=getData(nmax);
            }
        }
    }
    return max;
}
//everything below is what the challenge gave me as I selected the C language
int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    int n = parse_int(ltrim(rtrim(readline())));

    int m = parse_int(ltrim(rtrim(readline())));

    int** matrix = malloc(n * sizeof(int*));

    for (int i = 0; i < n; i++) {
        *(matrix + i) = malloc(m * (sizeof(int)));

        char** matrix_item_temp = split_string(rtrim(readline()));

        for (int j = 0; j < m; j++) {
            int matrix_item = parse_int(*(matrix_item_temp + j));

            *(*(matrix + i) + j) = matrix_item;
        }
    }

    int result = connectedCell(n, m, matrix);

    fprintf(fptr, "%d\n", result);

    fclose(fptr);

    return 0;
}

char* readline() {
    size_t alloc_length = 1024;
    size_t data_length = 0;

    char* data = malloc(alloc_length);

    while (true) {
        char* cursor = data + data_length;
        char* line = fgets(cursor, alloc_length - data_length, stdin);

        if (!line) {
            break;
        }

        data_length += strlen(cursor);

        if (data_length < alloc_length - 1 || data[data_length - 1] == '\n') {
            break;
        }

        alloc_length <<= 1;

        data = realloc(data, alloc_length);

        if (!data) {
            data = '\0';

            break;
        }
    }

    if (data[data_length - 1] == '\n') {
        data[data_length - 1] = '\0';

        data = realloc(data, data_length);

        if (!data) {
            data = '\0';
        }
    } else {
        data = realloc(data, data_length + 1);

        if (!data) {
            data = '\0';
        } else {
            data[data_length] = '\0';
        }
    }

    return data;
}

char* ltrim(char* str) {
    if (!str) {
        return '\0';
    }

    if (!*str) {
        return str;
    }

    while (*str != '\0' && isspace(*str)) {
        str++;
    }

    return str;
}

char* rtrim(char* str) {
    if (!str) {
        return '\0';
    }

    if (!*str) {
        return str;
    }

    char* end = str + strlen(str) - 1;

    while (end >= str && isspace(*end)) {
        end--;
    }

    *(end + 1) = '\0';

    return str;
}

char** split_string(char* str) {
    char** splits = NULL;
    char* token = strtok(str, " ");

    int spaces = 0;

    while (token) {
        splits = realloc(splits, sizeof(char*) * ++spaces);

        if (!splits) {
            return splits;
        }

        splits[spaces - 1] = token;

        token = strtok(NULL, " ");
    }

    return splits;
}

int parse_int(char* str) {
    char* endptr;
    int value = strtol(str, &endptr, 10);

    if (endptr == str || *endptr != '\0') {
        exit(EXIT_FAILURE);
    }

    return value;
}
