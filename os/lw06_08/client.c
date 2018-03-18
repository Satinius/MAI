#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <zmq.h>
#include <unistd.h>
#include "bank.h"

void help()
{
	fprintf(stdout, "%s\n", "|----------------------------|-------------------------------|");
	fprintf(stdout, "%s\n", "| For check you cash:        | check                         |");
	fprintf(stdout, "%s\n", "|----------------------------|-------------------------------|");
	fprintf(stdout, "%s\n", "| For send money to you:     | send me <number>              |");
	fprintf(stdout, "%s\n", "|----------------------------|-------------------------------|");
	fprintf(stdout, "%s\n", "| For send money to id:      | send to <id> <number>         |");
	fprintf(stdout, "%s\n", "|----------------------------|-------------------------------|");
	fprintf(stdout, "%s\n", "| For get cash:              | get <number>                  |");
	fprintf(stdout, "%s\n", "|----------------------------|-------------------------------|");
}

void getLinkClient(int argc, char const *argv[], char *link)
{
	memset(link, '\0', sizeof(link));
	strcat(link, "tcp://localhost:");

	if (argc > 2) {
		//printf("%s\n", "Lot argument.");
		return;
	} else if (argc == 2) {
		strcat(link, argv[1]);
	} else {
		strcat(link, "4040");
	}

}

// void getLinkServer(int argc, char const *argv[], char *link)
// {
// 	memset(link, '\0', sizeof(link));
// 	strcat(link, "tcp://*:");

// 	if (argc > 2) {
// 		//printf("%s\n", "Lot argument.");
// 		return;
// 	} else if (argc == 2) {
// 		strcat(link, argv[1]);
// 	} else {
// 		strcat(link, "4040");
// 	}

// }

int readCmd(RequestData * data)
{
    const int cmdSize = LSIZE;

    long long value = 0;
    long id;
    char cmd[cmdSize];
    scanf("%s", cmd);
    if (!strcmp(cmd, "login")) {
        scanf("%ld", &(data->id));
        data->action = LOG;
        data->value = 0;
        return 1;
    } else if (!strcmp(cmd, "registration")) {
        data->action = REG;
        data->value = 0;
        return 1;
    } else if (!strcmp(cmd, "send")) {
        scanf("%s", cmd);
        if (!strcmp(cmd, "me")) {
            scanf("%lld", &value);
            data->value = value;
            data->action = ADD;
        } else if (!strcmp(cmd, "to")) {
            scanf("%ld", &id);
            data->payee = id;
            scanf("%lld", &value);
            data->value = value;
            data->action = SEND_TO;
        }
        return 1;
    } else if (!strcmp(cmd, "check")) {
        data->action = CHECK;
        return 1;
    } else if (!strcmp(cmd, "get")) {
        scanf("%lld", &value);
        data->value = value;
        data->action = REMOVE;
        return 1;
    } else if (!strcmp(cmd, "end")) {
		return 0;
	} else return 1;
}

int readAnsw(RequestData * data)
{
    if (data->action == ADD_SUC) printf("%s\n", "Funds have been successfully added.");
    else if (data->action == ADD_FAIL) printf("%s\n", "An error occurred while receiving funds.");
    else if (data->action == REMOVE_SUC) printf("%s\n", "Funds have been successfully withdrawn.");
    else if (data->action == REMOVE_FAIL) printf("%s\n", "An error occurred during withdrawal.");
    else if (data->action == LOG_SUC) printf("%s\n", "Successful authorization.");
    else if (data->action == LOG_FAIL) printf("%s\n", "Authorization failed. Created a new account.");
    else if (data->action == REG_SUC) printf("%s\n", "Registration successful.");
    else if (data->action == REG_FAIL) printf("%s\n", "Registration failed.");
    else if (data->action == CHECK_SUC) printf("%s %lld.\n", "Your balance is", data->value);
    else if (data->action == SEND_SUC) printf("You successfully transferred %lld to user %ld", data->value, data->payee);
    else if (data->action == SEND_FAIL) printf("%s\n", "Transaction error.");
    return 0;
}



void wrongCmd()
{
    printf("%s\n", "You entered wrong command.");
}

int main(int argc, char const *argv[])
{
    void* context = zmq_ctx_new();
    void* socket = zmq_socket(context, ZMQ_REQ);
    char link[LSIZE];
    getLinkClient(argc, argv, link);
    zmq_connect(socket, link);
    
    char userInput[MSX]; 
    RequestData rd;

    zmq_msg_t regMsg;
    zmq_msg_init_size(&regMsg, sizeof(RequestData));
    long id;
    printf("Select: register or login.\n");
    scanf("%s", userInput);
    while (strcmp(userInput, "register") && strcmp(userInput, "login")) {
        wrongCmd();
        scanf("%s", userInput);
    }
    printf("Enter ID: ");
    scanf("%ld", &id);
    rd.id = id;
    if (!strcmp(userInput, "register")) {
        rd.action = REG;
        printf("Registration...\n");
    } else if (!strcmp(userInput, "login")) {
        rd.action = LOG;
        printf("Login...\n");
    }
	memcpy(zmq_msg_data(&regMsg), &rd, sizeof(RequestData));
    zmq_msg_send(&regMsg, socket, 0);
    zmq_msg_close(&regMsg);
    //printf("Message was send.\n");
    zmq_msg_t regReply;
	zmq_msg_init(&regReply);
	zmq_msg_recv(&regReply, socket, 0);
    RequestData *regAnswer = (RequestData *)zmq_msg_data(&regReply);
    zmq_msg_close(&regReply);
    //printf("The response is received.\n");
    if (regAnswer->action == LOG_SUC) {
        printf("Login succesfull.\n");
    } else if (regAnswer->action == LOG_FAIL) {
        printf("Login error.\nRegistration...\n");
        rd.action = REG;
        zmq_msg_init_size(&regMsg, sizeof(RequestData));
        memcpy(zmq_msg_data(&regMsg), &rd, sizeof(RequestData));
        zmq_msg_send(&regMsg, socket, 0);
        zmq_msg_close(&regMsg);

        zmq_msg_init(&regReply);
        zmq_msg_recv(&regReply, socket, 0);
        RequestData *regAnswer = (RequestData *)zmq_msg_data(&regReply);
        long tmp = regAnswer->id;
        rd.id = tmp;
        zmq_msg_close(&regReply);
        printf("Registration sucessfull. Your id is %ld\n", rd.id);
    } else if (regAnswer->action == REG_SUC) {
        printf("Registration sucessfull. Your id is %ld\n", regAnswer->id);
    }


    help();

    while (readCmd(&rd)) {
        zmq_msg_t msg;
        zmq_msg_init_size(&msg, sizeof(RequestData));
        memcpy(zmq_msg_data(&msg), &rd, sizeof(RequestData));
        if (zmq_msg_send(&msg, socket, 0) < 0) {
			perror("Sending error:\n");
			break;
		}
        zmq_msg_close(&msg);
        zmq_msg_t reply;
        zmq_msg_init(&reply);
        if (zmq_msg_recv(&reply, socket, 0) < 0) {
			perror("Recv error:\n");
			break;
		}
        RequestData *answer = (RequestData*) zmq_msg_data(&reply);
        zmq_msg_close(&reply);
        sleep(1);
        readAnsw(answer);
    }

    zmq_close(socket);
    zmq_ctx_destroy(context);
}