/* таблица в структуре
 * ввод файла через аргументы*/

#include "main.h"

int main(int argc, char *argv[]) {
    matrix_t graf;
    FILE *inputf, *outf;
    //"Downloads/graphs/outputs/adjacency_matrix_0.txt"
    printf("readable file -> %s\n", argv[1]);
    inputf = fopen(argv[1], "r");
    outf = fopen("output_file.dot", "w");
    /**  checking the existence of the file  **/
    if (inputf == NULL || outf == NULL) {
        puts("Error: file not found");
        return -1;
    }

    char arr[ARR_MAX_SIZE];
    int size_matrix = 0, str_len;

    /** Analysis of the adjacency matrix **/
    while (fgets(arr, ARR_MAX_SIZE, inputf) != NULL)
        ++size_matrix;
    size_matrix-=1;
    graf.size = size_matrix;
    str_len = (size_matrix * 2) + 1;
    graf.string_length = str_len;
    printf("counter -> %d\n", graf.size);
    printf("str_len->%d\n", graf.string_length);

    /** Setting the cursor position in the stream **/
    if (fseek(inputf,0,SEEK_SET)==0)
        puts("Setting the cursor position in the stream comlpete\n");
    else{
        printf("Error");
        return -1;
    }

    fputs("graph graf1{", outf);
    fputs("\n", outf);
    char arr_string[graf.string_length];
    char adj_matrix[graf.size][graf.size];
    int i, j, k;
    for (i = 1; i < graf.size + 1; i++){
        fgets(arr_string, graf.string_length,inputf);
        deblank(arr_string);
        /** Create adjacency_matrix and print **/
        for (k = 0; k < size_matrix; k++){
            adj_matrix[i - 1][k] = arr_string[k];
            printf("[%c] ", adj_matrix[i - 1][k]);
        }
        printf("\n");
    }
    /** orientation check **/
    int counter = 0;

    for (j = 1; j < 5; j++){
        if (adj_matrix[0][j] == adj_matrix[j][0]){
            ++counter;
        }
    }
    if (counter > 1)
        graf.orientation = false;
    else
        graf.orientation = true;

    counter = 0;
    /** loop check **/
    for (i = 0; i < 4; i++){
        if (adj_matrix[i][i] != 0 )
            ++counter;
    }
    graf.loop = counter;
    counter = 0;

    /** Bringing to a step - by - step view  **/
    if (!graf.orientation){
        int  n = 1;
        for (j = 0; j < 5; j++){
            for (i = n; i < 5; i++){
                adj_matrix[i][j] = '0';
            }
            n++;
        }
    }

    puts("\n");
    /** Writing data to dot-file  **/
    for (i = 1; i < size_matrix + 1; i++){
        for (k = 0; k < size_matrix; k++){
            if (adj_matrix[i - 1][k] == '1'){
                fprintf(outf, "%d--%d\n", i, k + 1);
            }
            if (adj_matrix[i - 1][k] > '1'){
                fprintf(outf, "%d--%d [weight=%c, penwidth=%c]\n",
                        i, k + 1, adj_matrix[i - 1][k], adj_matrix[i - 1][k]);
                counter++;
            }
            printf("[%c] ", adj_matrix[i - 1][k]);
        }
        printf("\n");
    }
    if (counter > 0)
        graf.weight = true;
    fputs("}", outf);

    fclose(inputf);
    fclose(outf);
    printf("size matrix ->%d\n", graf.size);
    printf("count of loop ->%d\n", graf.loop);
    if (graf.weight){
        printf("weight true\n");
    }
    if (graf.orientation)
        printf("orientation true \n");
    system("dot -Tpng -O output_file.dot");
    return 0;
}
