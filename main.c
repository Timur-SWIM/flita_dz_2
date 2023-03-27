/* таблица в структуре
 * ввод файла через аргументы*/

#include "main.h"

int main() {
    FILE *inputf, *outf;

    inputf = fopen("adjacency_matrix_0.txt", "r");
    outf = fopen("output_file.dot", "w");
    if (inputf == NULL || outf == NULL) {
        puts("Error: file not found");
        return -1;
    }
    char arr[11];
    int size_matrix = 0, str_len;

    while (fgets(arr, 100, inputf) != NULL){
        ++size_matrix;
    }
    size_matrix-=1;
    str_len = (size_matrix * 2) + 1;
    printf("counter -> %d\n", size_matrix);
    printf("str_len->%d\n", str_len);

    fputs("graph graf1{", outf);
    fputs("\n", outf);

    for (int i = 1; i < size_matrix + 1; i++){
        fgets(arr, str_len,inputf);
        deblank(arr);
        for  (int j = 0; j < size_matrix; j++){
            if (arr[j] == '1'){
                fprintf(outf, "%d--%d\n", i, j + 1);
            }
            if(arr[j] > '1'){
                fprintf(outf, "%d--%d [weight=%c, penwidth=%c]\n", i, j + 1, arr[j], arr[j]);
            }
        }
    }
    fputs("}", outf);
    fclose(inputf);
    fclose(outf);
    system("dot -Tpng -O output_file.dot");
    return 0;
}