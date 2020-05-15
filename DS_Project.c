#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

struct employee{
    char name[255];
    int totalReceipt, totalTips, numberOfCustomers;
    struct employee *next;
}* employees = NULL;
struct call{
    int callId;
    int tableNo;
    char desc[1024];
    struct call *next;
}* calls;
struct foodsOrder{
    int orderId;
    int tableNo;
    char *desc;
    char *status;
    struct foodsOrder *next;
}* foodsOrders;
struct drinksOrder{
    int orderId;
    int tableNo;
    char *desc;
    char *status;
    struct drinksOrder *next;
}* drinksOrders;
struct bill{
    int billId;
    int tableNo;
    char desc[1024];
    int totalAmount;
    struct bill *next;
}* bills;
void init(){
    struct employee* employees = NULL;
    struct call* calls = NULL;
    struct foodsOrder* foodsOrders = NULL;
    struct drinksOrder* drinksOrders = NULL;
    struct bill* bills = NULL;
}

void shutdown(){
    struct employee* employees = NULL;
    struct call* calls = NULL;
    struct foodsOrder* foodsOrders = NULL;
    struct drinksOrder* drinksOrders = NULL;
    struct bill* bills = NULL;
    free(employees);
    free(calls);
    free(foodsOrders);
    free(drinksOrders);
    free(bills);
}
int callId = 0, orderId = 0;

main(){
    printf("Welcome to XYZ Restaurant\n");
    printf("Choose one of the following\n");
    char c;
    init();
    do{
        printf("\n1.Press a call\n2.Receive a call\n3.Register a command\n4.Display orders\n5.Finish the command\n6.View ready commands\n7.Search a specific employee\n8.Print all employees\n9.View pending orders\n0.Exit\nMake a choice: ");
        scanf("%s", &c);
        switch(c){
            case '1':
                pressCall();
                break;
            case '2':
                receiveCall();
                break;
            case '3':
                registerCommand();
                break;
            case '4':
                displayOrders();
                break;
            case '5':
                finishCommand();
                break;
            case '6':
                viewReadyCommands();
                break;
            case '7':
                searchEmployee();
                break;
            case '8':
                displayEmployees();
                break;
            case '9':
                viewPending();
                break;
            default:
                printf("You made a wrong choice!!!!\n");
                break;
        }
    }while(c!= '0');
    shutdown();
}

pressCall(){
    char choice;
    int table;
    printf("\nEnter the table number: ");
    scanf("%d", &table);
    do{
        struct call *p, *q;
        p = (struct call*)malloc(sizeof(struct call));
        p->tableNo = table;
        printf("Enter the description of your order(Ex: 1 cup of coffee): ");
        scanf("\n");
        scanf("%[^\n]%*c", p->desc);
        p->callId = callId + 1;
        callId = callId + 1;
        p->next = NULL;
        if(calls == NULL){
            calls = p;
        }
        else{
            q = calls;
            while(q->next != NULL)
                q = q->next;
            q->next = p;
        }
        printf("\nPress (Y) to add another order or press another key to exit: ");
        scanf("%s", &choice);
    }while(toupper(choice) == 'Y');
    printf("\nThank you for making an order, Please wait for few minutes.");
}
receiveCall(){
    struct call *q;
    q = calls;
    if(calls == NULL){
        printf("\nThere is no new calls.");
        return;
    }
    printf("\nCallId\tTable No\tDescription");
    while(q != NULL){
        printf("\n%d\t%d\t\t%s", q->callId, q->tableNo, q->desc);
        q = q->next;
    }
    printf("\n");
}
registerCommand(){
    char choice;
    int cid;
    do{
        printf("Enter the call Id to register: ");
        scanf("%d", &cid);
        struct call *cal;
        cal = calls;
        while(cal->callId != cid){
            if(cal->next == NULL){
                printf("The call id you enter doesn't exist, Please try again later.\n");
                return;
            }
            cal = cal->next;
        }
        char type;
        printf("Enter the type of order the customer requested (D for Drinks and F for Food): ");
        scanf("%s", &type);
        struct drinksOrder *p, *q;
        struct foodsOrder *pf, *qf;
        switch(toupper(type)){
            case 'D':
                p = (struct drinksOrder*)malloc(sizeof(struct drinksOrder));
                if(calls == NULL){
                    printf("This order have not been added or it have been already delivered.");
                    break;
                }else{
                    p->orderId = orderId + 1;
                    orderId = orderId + 1;
                    p->tableNo = calls->tableNo;
                    p->desc = calls->desc;
                    p->status = "pending";
                    p->next = NULL;
                    calls = calls->next;
                    if(drinksOrders == NULL){
                        drinksOrders = p;
                    }
                    else{
                        q = drinksOrders;
                        while(q->next != NULL)
                            q = q->next;
                        q->next = p;
                    }
                    printf("Order successfully registered.\n");
                    break;
                }
            case 'F':
                pf = (struct foodsOrder*)malloc(sizeof(struct foodsOrder));
                if(calls == NULL){
                    printf("This order have not been added or it have been already delivered.");
                    break;
                }else{
                    p->orderId = orderId + 1;
                    orderId = orderId + 1;
                    pf->tableNo = calls->tableNo;
                    pf->desc = calls->desc;
                    pf->status = "pending";
                    pf->next = NULL;
                    calls = calls->next;
                    if(foodsOrders == NULL){
                        foodsOrders = pf;
                    }
                    else{
                        qf = foodsOrders;
                        while(qf->next != NULL)
                            qf = qf->next;
                        qf->next = pf;
                    }
                    printf("Order successfully registered.\n");
                    break;
                }
            default:
                printf("Wrong choice!!! Please try again.\n");
                break;
        }
        printf("\nPress (Y) to register another order for this customer or press another key to exit: ");
        scanf("%s", &choice);
    }while(toupper(choice) == 'Y');
}
displayOrders(){
    struct drinksOrder *q;
    struct foodsOrder *p;
    q = drinksOrders;
    p = foodsOrders;
    printf("\nOrderId\tTable No\tDescription\t\tStatus");
    while(q != NULL){
        printf("\n%d\t%d\t\t%s\t\t%s", q->orderId, q->tableNo, q->desc, q->status);
        q = q->next;
    }
    while(p != NULL){
        printf("\n%d\t%d\t\t%s\t\t%s", p->orderId, p->tableNo, p->desc, p->status);
        p = p->next;
    }
    printf("\n");
}
finishCommand(){

}
viewReadyCommands(){

}
searchEmployee(){

}
displayEmployees(){

}

viewPending(){

}
