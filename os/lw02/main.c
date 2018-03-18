#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>

int get_length(FILE *f)
{
    int length = 0;
    int s;
    while((fscanf(f, "%d", &s)!= EOF)) {
        if (!f)
            break;
        length++;
    }
    rewind(f);
    return length;
}

int read_file_to_array(FILE *f, int *arr, int length)
{
    for (int i = 0; i < length; ++i) {
        fscanf(f, "%d", &arr[i]);
        //printf("%d\n", arr[i]);
    }
}

int compare(const void * a, const void * b)
{
    return (*(int*)a - *(int*)b);
}

int main(int argc, char *argv[]){
    if (argc != 3) {
        printf("Please select two files\n");
        _exit(-1);
    }
    int fst_pipe[2], snd_pipe[2], fstSort, sndSort;
    int size;
    int status;
    /* Попытаемся создать pipe */
    if(pipe(fst_pipe) < 0){
        /* Если создать pipe не удалось, печатаем об этом сообщение
        и прекращаем работу */
        printf("Can\'t create pipe\n");
        exit(-1); 
    } 
    if(pipe(snd_pipe) < 0){
        /* Если создать pipe не удалось, печатаем об этом сообщение
        и прекращаем работу */
        printf("Can\'t create pipe\n");
        exit(-1); 
    }
    if ((fstSort = fork()) == 0) {
        FILE *input = fopen(argv[1], "r");
        if (input == NULL){
            fprintf(stdout, "One of files does not exist.\n");
            _exit (EXIT_FAILURE);
        }
        int length = get_length(input);
        int size = write(fst_pipe[1], &length, sizeof(int));
        if (!length) {
            printf("1st length was 0\n");
            exit(0);
        }
        int *arr = (int*)malloc(length * sizeof(int));
        read_file_to_array(input, arr, length);
        qsort(arr, length, sizeof(int), compare);
        size = write(fst_pipe[1], arr, sizeof(int) * length);
        fclose(input);
        printf("1st Input file was closed\n");
        close(fst_pipe[0]);
        printf("1st pipe 0 was closed.\n");
        close(fst_pipe[1]);
        printf("1st pipe 1 was closed. Exit from first sort\n");
        exit(0);
    }
    if (fstSort > 1 && ((sndSort = fork()) == 0)) {
        // Процесс второй сортировки
        FILE *input = fopen(argv[2], "r");
        if (input == NULL){
            fprintf(stdout, "One of files does not exist.\n");
            _exit (EXIT_FAILURE);
        }
        int length = get_length(input);
        int size = write(snd_pipe[1], &length, sizeof(int));
        if (!length) {
            printf("2nd length was 0\n");
            exit(0);
        }
        int *arr = (int*)malloc(length * sizeof(int));
        read_file_to_array(input, arr, length);
        qsort(arr, length, sizeof(int), compare);
        size = write(snd_pipe[1], arr, sizeof(int) * length);
        fclose(input);
        printf("2nd Input file was closed\n");
        close(snd_pipe[0]);
        printf("2st pipe 0 was closed.\n");
        close(snd_pipe[1]);
        printf("2st pipe 1 was closed. Exit from second sort\n");
        exit(0);
    }
    if (fstSort < 1 || sndSort < 1) {
        /* Если создать процесс не удалось, сообщаем об этом и 
        завершаем работу */
        printf("Can\'t fork child\n");
        exit(-1);
    }

    int l;
    if (l = waitpid(sndSort, &status, 0) != sndSort) {
        printf("%d %d\n", l, status);
        status = -1;
    }
    if (status == -1) {
        printf("Error in childs 2\n");
        _exit (EXIT_FAILURE);
    }
    if ((l = waitpid(fstSort, &status, 0)) != fstSort) {
        printf("%d %d\n", l, status);
        status = -1;
    }
    if (status == -1) {
        printf("Error in childs\n");
        _exit (EXIT_FAILURE);
    }
    
    int length_x, length_y, length;
    size = read(fst_pipe[0], &length_x, sizeof(int));
    size = read(snd_pipe[0], &length_y, sizeof(int));
    length = length_x + length_y;
    FILE *output = fopen("output.txt", "w");
    fprintf(output, "Length = %d\n", length);
    int i = 0, j = 0, x, y;
    if (i != length_x)
            size = read(fst_pipe[0], &x, sizeof(int));
    if (j != length_y)
            size = read(snd_pipe[0], &y, sizeof(int));
    while (i < length_x && j < length_y) {
        if (x <= y) {
            fprintf(output, "%d\n", x);
            i++;
            if (i != length_x)
                size = read(fst_pipe[0], &x, sizeof(int));
        } else {
            fprintf(output, "%d\n", y);
            j++;
            if (j != length_y)
                size = read(snd_pipe[0], &y, sizeof(int));
        }
    }
    while (i < length_x) {
        fprintf(output, "%d\n", x);
        i++;
        if (i != length_x)
            size = read(fst_pipe[0], &x, sizeof(int));
    }
    while (j < length_y) {
        fprintf(output, "%d\n", y);
        j++;
        if (j != length_y)
            size = read(snd_pipe[0], &y, sizeof(int));
    }
    fclose(output);
    close(fst_pipe[1]);
    close(fst_pipe[0]);
    close(snd_pipe[1]);
    close(snd_pipe[0]);
    exit(0);
}