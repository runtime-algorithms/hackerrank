#include <stdio.h>
#include <stdlib.h>

/* 
 * https://www.hackerrank.com/challenges/connected-cell-in-a-grid/problem
 * my idea was to share a pointer across the grid 
 * I just wasn't adding values of connected grids at first
 * So literally everything before the 'add' variable
 *
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
int parseInt(){
    int sum=0;
    char c=getchar();
    while(c<'0'||c>'9') c=getchar();
    while(c>='0'&&c<='9'){
        sum=(10*sum)+(c-'0');
        c=getchar();
    }
    return sum;
}
int main(){
    //there was a connectedCell function that had rows,cols
    //the 3rd parseInt() was replaced with matrix[r][c]
    //the printf at the end was just returning max instead
    int rows=parseInt(),cols=parseInt();
    struct Reference *MATRIX[rows*cols];
    int max=0;
    for(int r=0;r<rows;r++){
        for(int c=0;c<cols;c++){
            int pos=r*cols+c, add=1;
            if(parseInt()==0){
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
    printf("%d",max);
    return 0;
}
