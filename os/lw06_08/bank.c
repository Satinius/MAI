#include "bank.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

UsersDB * dbCreate(int size) 
{
    if (size <= 0) {
		fprintf(stderr, "%s\n", "Uncorrect size!");
		return (NULL);
	}

	UsersDB *result = (UsersDB*) malloc(sizeof(UsersDB));
	if (result == NULL) {
		perror("Memory allocated error:");
		exit(-1);
	}

	result->base = (User*) malloc(sizeof(User) * size);
	if (result->base == NULL) {
		perror("Memory allocated error:");
		exit(-1);
	}

	result->capacity = size;
	result->used = 0;
	return result;
}

int dbFind(UsersDB * b, long id)
{
    for (int i = 0; i < b->used; ++i)
        if (b->base[i].id == id) return i;
    return -1;
}

int dbAdd(UsersDB * b, User data)
{
    if (b->used == b->capacity) {
        b->capacity *= 2;
        b->base = (User *)realloc(b->base, b->capacity * sizeof(User));
        
        if (b->base == NULL) {
			perror("Memory reallocated error:");
			exit(-1);
		}
    }

    b->base[b->used].balance = data.balance;
    b->base[b->used].id = data.id;

    b->used++;
    return 0;
}

int dbClean(UsersDB * b)
{
    free(b->base);
    free(b);
    b = NULL;
    return 0;
}

int addMoney(UsersDB * b, long long money, long userId)
{
    int index = dbFind(b, userId);
    if (index >= 0 && money > 0) {
        b->base[index].balance += money;
        return 0;
    }
    return -1;
}

int withdrowMoney(UsersDB * b, long long money, long userId)
{
    int index = dbFind(b, userId);
    if (index >= 0) {
        long long current = checkBalance(b, userId);
        if (current < money) {
            //printf("Current funds - %lld, user wants to remove - %lld.\nLack of funds.\n", current, money);
            return 1;
        } else {
            b->base[index].balance -= money;
            return 0;
        }
    } else {
        return -1;
    }
}
int transferMoney(UsersDB * b, long long money, long senderId, long payeeId)
{
    if (dbFind(b, payeeId) != -1 && checkBalance(b, senderId) > money) {
        withdrowMoney(b, money, senderId);
        addMoney(b, money, payeeId);
        return 0;
    } else {
        return 1;
    }
}
int checkBalance(UsersDB * b, long userId)
{
    int index = dbFind(b, userId);
    if (index >= 0) {
        return b->base[index].balance;
    } else {
        return -1;
    }
}

int dbSave(UsersDB * b, char * filename)
{
    FILE * file = fopen(filename, "wb");
    fwrite(&(b->capacity), sizeof(b->capacity), 1, file);
    fwrite(&(b->used), sizeof(b->used), 1, file);
    for (int i = 0; i < b->used; i++) {
        fwrite(&(b->base[i].id), sizeof(b->base[i].id), 1, file);
        fwrite(&(b->base[i].balance), sizeof(b->base[i].balance), 1, file); 
    }
    fclose(file);
    return 0;
}

int dbPrint(UsersDB * b)
{
    printf("%d %d\n", b->used, b->capacity);
    for (int i = 0; i < b->used; i++)
    {
        printf("%ld :: %lld\n", b->base[i].id, b->base[i].balance);
    }
}

UsersDB * dbLoad(UsersDB * b, char * filename)
{
    FILE * file = fopen(filename, "rb");
    if (file == NULL) {
        printf("%s don't exist.\n", filename);
        return NULL;
    }
    
    fread(&(b->capacity), sizeof(b->capacity), 1, file);
    b = dbCreate(b->capacity);
    fread(&(b->used), sizeof(b->used), 1, file);
    for (int i = 0; i < b->used; i++) {
        fread(&(b->base[i].id), sizeof(b->base[i].id), 1, file);
        fread(&(b->base[i].balance), sizeof(b->base[i].balance), 1, file);
    }
    fclose(file);
    return b;
}