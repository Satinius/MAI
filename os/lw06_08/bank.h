#ifndef BANK_H
#define BANK_H

#include <string.h>
#include <stdbool.h>
#include <stdio.h>

#define MSX   11
#define LSIZE 32

typedef struct {

    long long  balance;
    long id;
} User;

typedef struct {

    size_t  used;
    size_t  capacity;
    User    *base;

} UsersDB;

typedef enum {
    REG, REG_SUC, REG_FAIL,
    LOG, LOG_SUC, LOG_FAIL,
    ADD, ADD_SUC, ADD_FAIL,
    SEND_TO, SEND_SUC, SEND_FAIL,
    REMOVE, REMOVE_SUC, REMOVE_FAIL,
    CHECK, CHECK_SUC
} RequestToken;

typedef struct {
    long id;
    char message[MSX];
    int action;
    long long value;
    long payee;
} RequestData;

UsersDB * dbCreate(int size);
int dbFind(UsersDB * b, long id);
int dbAdd(UsersDB * b, User data);
int dbClean(UsersDB * b);

int addMoney(UsersDB * b, long long money, long userId);
int withdrowMoney(UsersDB * b, long long money, long userId);
int transferMoney(UsersDB * b, long long money, long senderId, long payeeId);
int checkBalance(UsersDB * b, long userId);

int dbSave(UsersDB * b, char * filename);
UsersDB * dbLoad(UsersDB * b, char * filename);

#endif