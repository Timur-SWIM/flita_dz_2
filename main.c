#include "main.h"

int main() {
    FILE *inputf, *outf;

    inputf = fopen("adjacency_matrix_0.txt", "r");
    outf = fopen("output_file.dot", "w");
    if (inputf == NULL || outf == NULL){
        puts("Error: file not found");
        return -1;}
    char arr[11];

    fputs("digraph graf1{", outf);
    fputs("\n", outf);

    for (int i = 1; i < SIZE_MATRIX + 1; i++){
        fgets(arr, ARRLEN,inputf);
        deblank(arr);
        for  (int j = 0; j < SIZE_MATRIX; j++){
            if (arr[j] == '1'){
                fprintf(outf, "%d->%d\n", i, j + 1);
            }
            if(arr[j] > '1'){
                fprintf(outf, "%d->%d \n", i, j + 1);
            }
        }
    }
    fputs("}", outf);
    fclose(inputf);
    fclose(outf);
    system("dot -Tpng -O output_file.dot");
    return 0;
}