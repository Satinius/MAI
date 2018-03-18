#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define string char *
#define TYPE string
#define MIN_LENGTH 4

typedef struct {
    TYPE *array;
    int left;
    int right;
    int tid;
} thread_data_t;

int number_of_threads;
pthread_mutex_t lock_number_of_threads;

int cstring_cmp(const void *a, const void *b) 
{ 
    const char **ia = (const char **)a;
    const char **ib = (const char **)b;
    return strcmp(*ia, *ib);
	/* strcmp functions works exactly as expected from
	comparison function */ 
} 

void merge(TYPE *data, int left, int right, int tid) {
    int ctr = 0;
    int i = left;
    int mid = left + ((right - left) / 2);
    int j = mid + 1;
    TYPE * c = (TYPE *)malloc((right - left + 1) * sizeof(TYPE));
    for (int k = 0; k < right - left + 1; k++) {
        c[k] = (TYPE)malloc(sizeof(char)*65);
    }
    while (i <= mid && j <= right) {
        if (strcmp(data[i], data[j]) <= 0) {
            strcpy(c[ctr++], data[i++]);
        } else {
            strcpy(c[ctr++], data[j++]);
        }
    }

    if (i == mid + 1) {
        while (j <= right) {
            strcpy(c[ctr++], data[j++]);
        }
    } else {
        while (i <= mid) {
            strcpy(c[ctr++], data[i++]);
        }
    }

    i = left;
    ctr = 0;
    while (i <= right) {
        strcpy(data[i++], c[ctr]);
        free(c[ctr++]);
    }
    free(c);
    return;
}


void *merge_sort_threaded(void *arg) {
    thread_data_t *data = (thread_data_t *) arg;
    int l = data->left;
    int r = data->right;
    int t = data->tid;

    if (r - l + 1 <= MIN_LENGTH) {
        qsort(data->array + l, r - l + 1, sizeof(TYPE), cstring_cmp);
    } else {
        // Try to create two threads
        int m = l + ((r - l) / 2);
        thread_data_t data_0;
        data_0.left = l;
        data_0.right = m;
        data_0.array = data->array;
        pthread_mutex_lock(&lock_number_of_threads);
        data_0.tid = number_of_threads++;
        pthread_mutex_unlock(&lock_number_of_threads);

        pthread_t thread0;
        int rc = pthread_create(&thread0, NULL, merge_sort_threaded, &data_0);
        int created_thread_0 = 1;
        if (rc) {
            //Failed to creade thread
            created_thread_0 = 0;
            qsort(data->array + l, m - l + 1, sizeof(TYPE), cstring_cmp);
        }

        thread_data_t data_1;
        data_1.left = m + 1;
        data_1.right = r;
        data_1.array =data->array;
        pthread_mutex_lock(&lock_number_of_threads);
        data_1.tid = number_of_threads++;
        pthread_mutex_unlock(&lock_number_of_threads);
        pthread_t thread1;
        rc = pthread_create(&thread1, NULL, merge_sort_threaded, &data_1);
        
        int created_thread_1 = 1;

        if(rc) {
            //Failed to create thread
            created_thread_1 = 0;
            qsort(data->array +m + 1, r - m, sizeof(TYPE), cstring_cmp);
        }

        if (created_thread_0) {
            pthread_join(thread0, NULL);
        }
        if (created_thread_1) {
            pthread_join(thread1, NULL);
        }
        merge(data->array, l, r, t);
    }
    pthread_exit(NULL);
    return NULL;
}

void merge_sort(TYPE * array, int start, int finish)
{
    thread_data_t data;
    data.array = array;
    data.left = start;
    data.right = finish;

    number_of_threads = 0;
    pthread_mutex_init(&lock_number_of_threads, NULL);
    data.tid = 0;

    pthread_t thread;
    int rc = pthread_create(&thread, NULL, merge_sort_threaded, &data);

    if (rc) {
        //Failed
        printf("Sort failed, start qsort\n");
        qsort(array + start, finish - start + 1, sizeof(TYPE), cstring_cmp);
    }
    pthread_join(thread, NULL);
    return;
}

int string_count(FILE *f) {
    int i = 0;
    string s = (string)malloc(sizeof(char) * 65);
    while (!feof(f)) {
        fscanf(f, "%s", s);
        i++;
    }
    rewind(f);
    return i;
}

void read_to_array(FILE *f, TYPE *arr, int size) {
    for (int i = 0; i < size; ++i) {
        fscanf(f, "%s", arr[i]);
    }   
}

void print_array(FILE *f, TYPE *arr, int size) {
    for (int i = 0; i < size; ++i) {
        fprintf(f, "%s\n", arr[i]);
    }  
}

void initialize_string_array(string *arr, int str_len, int size) {
    arr = (string *)malloc(sizeof(string *) * size);
    for (int i = 0; i < size; ++i) {
        arr[i] = (string)malloc(sizeof(char) * str_len + 1);
        arr[i][str_len] = '\0';
    }
}

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stdout, "Error: enter input file name (and output optionaly).\n");
        return 0;
    }
    FILE * input = fopen(argv[1], "r");
    FILE * output = stdout;
    if (argc > 2) output = fopen(argv[2], "w");

    int size = string_count(input);
    //initialize_string_array(arr, 65, size);
    string * arr = (string *) malloc (sizeof(string*)*size);
    for (int i = 0; i < size; ++i) {
        arr[i] = (string)malloc(sizeof(char) * 65);
        arr[i][64] = '\0';
    }

    read_to_array(input, arr, size);

    merge_sort(arr, 0, size - 1);

    print_array(output, arr, size);
    fclose(input);
    fclose(output);
    return 0;
}