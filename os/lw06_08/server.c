#include <zmq.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include <stdio.h>
#include <pthread.h>
#include <signal.h>
#include "bank.h"

void INThandler(int);

void getLinkServer(int argc, char const *argv[], char *link)
{
	memset(link, '\0', sizeof(link));
	strcat(link, "tcp://*:");

	if (argc > 2) {
		//printf("%s\n", "Lot argument.");
		return;
	} else if (argc == 2) {
		strcat(link, argv[1]);
	} else {
		strcat(link, "4040");
	}

}

int readRequest(RequestData *data, UsersDB *b)
{
    User user;
    //printf("Reading request... ID - %ld Action - %d Value - %lld\n", data->id, data->action, data->value);
    switch(data->action) {
        case LOG:
        {
            long index = dbFind(b, data->id);
            if (index != -1)
                data->action = LOG_SUC;
            else
                data->action = LOG_FAIL;
            break;
        }
        case REG:
        {
            long index = dbFind(b, data->id);
            if (index != -1) {
                //printf("This ID is already taken.\n");
                long i = 0;
                while (dbFind(b, i) != -1) {
                    i++;
                }
                data->id = i;
            }
            user.id = data->id;
            user.balance = 0;
            if(!dbAdd(b, user))
                data->action = REG_SUC;
            else
                data->action = REG_FAIL;
            break;
        }
        case ADD:
        {
            if (!addMoney(b, data->value, data->id))
                data->action = ADD_SUC;
            else
                data->action = ADD_FAIL;
            break;
        }
        case REMOVE:
        {
            
            if(!withdrowMoney(b, data->value, data->id))
                data->action = REMOVE_SUC;
            else
                data->action = REMOVE_FAIL;
            break;
        }

        case SEND_TO:
        {
            if(!transferMoney(b, data->value, data->id, data->payee))
                data->action = SEND_SUC;
            else
                data->action = SEND_FAIL;
            break;
        }

        case CHECK:
        {
            data->value = checkBalance(b, data->id);
            data->action = CHECK_SUC;
            break;
        }
    }
}

void renameFiles()
{
    rename("users", "toremove");
    rename("userstmp", "users");
    remove("toremove");
}

int main(int argc, char *argv[]) 
{
    void *context = zmq_ctx_new();
    UsersDB *users = dbCreate(1);
    if ((users = dbLoad(users, "database")) == NULL) {
        printf("Creating a new database... ");
        users = dbCreate(1);
        dbSave(users, "database");
        printf("Succesfull.");
    }
    //dbPrint(users);
    void * socket = zmq_socket(context, ZMQ_REP);

    char link[LSIZE];
	getLinkServer(argc, argv, link);

    zmq_bind(socket, link);
    for(;;) {
        zmq_msg_t msg;
        int rc = zmq_msg_init(&msg);
        assert(rc == 0);
        if (zmq_msg_recv(&msg, socket, 0) < 0) {
            perror("Recv error:");
            break;
        }
        RequestData *msgRD = (RequestData *)zmq_msg_data(&msg);
        //printf("Request...\n");
        
        readRequest(msgRD, users);

        zmq_msg_t reply;
        zmq_msg_init_size(&reply, sizeof(RequestData));
        dbSave(users, "database");
        dbPrint(users);
        memcpy(zmq_msg_data(&reply), msgRD, sizeof(RequestData));
        if (zmq_msg_send(&reply, socket, 0) < 0) {
            perror("Send error:");
            break;
        }
        //printf("Reply sent.\n");
        zmq_msg_close(&reply);
    }
    zmq_close(socket);
    zmq_ctx_destroy(context);
    return 0;
}