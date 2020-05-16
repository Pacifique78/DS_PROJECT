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
    char *desc;
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
int callId = 0;
int orderId = 0;
int billId = 0;
int totalAmount = 0;

main(){
    printf("Welcome to XYZ Restaurant\n");
    printf("Choose one of the following\n");
    char c;
    init();
    do{
        printf("\n1.Press a call\n2.Receive a call\n3.Register a command\n4.Display orders\n5.Finish the command\n6.View ready commands\n7.Deliver order\n8.Search a specific employee\n9.Print all employees\n10.View pending orders\np.Print Bill\n0.Exit\nMake a choice: ");
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
                deliver();
                break;
            case '8':
                searchEmployee();
                break;
            case '9':
                displayEmployees();
                break;
            case '10':
                viewPending();
                break;
            case 'p':
                printBill();
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
        printf("There is no new calls.\n");
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
        if(calls->callId != cid){
            printf("You must start with the first order(first come first served).\n");
            return;
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
                    p->status = "ready";
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
                    pf->orderId = orderId + 1;
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
    if(drinksOrders == NULL && foodsOrders == NULL){
        printf("There is no new orders.\n");
        return;
    }
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
    if(drinksOrders == NULL && foodsOrders == NULL){
        printf("There is no new orders.\n");
        return;
    }
    struct drinksOrder *q;
    struct foodsOrder *p;
    q = drinksOrders;
    p = foodsOrders;
    int orId, changed = 0;
    printf("Enter the Id of the order that is ready: ");
    scanf("%d", &orId);
    while(q != NULL){
        if(q->orderId == orId){
            q->status = "ready";
            changed++;
        }
        q = q->next;
    }
    if(changed == 0){
        while(p != NULL){
            if(p->orderId == orId){
                p->status = "ready";
                changed++;
            }
            p = p->next;
        }
        if(changed == 0){
            printf("The order Id you entered was not found.\n");
            return;
        }
        else{
            printf("The order is now ready.\n");
            return;
        }
    }
    else{
        printf("The order is now ready.\n");
        return;
    }
}
viewReadyCommands(){
    displayOrders();
}
deliver(){
    if(drinksOrders == NULL && foodsOrders == NULL){
        printf("There is no order to deliver.\n");
        return;
    }
    struct drinksOrder *q, *qf;
    struct foodsOrder *p, *pf;
    struct bill *b, *bf;
    qf = drinksOrders;
    pf = foodsOrders;
    b = bills;
    b = (struct bill*)malloc(sizeof(struct bill));
    int orId, found = 0;
    printf("Enter the Id of the order that is ready to be delivered: ");
    scanf("%d", &orId);
    if(drinksOrders != NULL){
        q = drinksOrders->next;
        if(drinksOrders->orderId == orId){
            if(drinksOrders->status == "ready"){
                b->billId = billId + 1;
                billId = billId + 1;
                b->tableNo = drinksOrders->tableNo;
                b->desc = drinksOrders->desc;
                printf("Enter the amount for this order: ");
                scanf("%d", &b->totalAmount);
                if(bills == NULL){
                    bills = b;
                }
                else{
                    bf = bills;
                    while(bf->next != NULL)
                        bf = bf->next;
                    bf->next = b;
                }
                drinksOrders = drinksOrders->next;
                pf = NULL;
                printf("Order successfully delivered.\n");
                return;
            }
        }
        else{
            while(q != NULL){
                if(q->orderId == orId){
                    found++;
                    if(q->status == "ready"){
                        b->billId = billId + 1;
                        billId = billId + 1;
                        b->tableNo = q->tableNo;
                        b->desc = q->desc;
                        printf("Enter the amount for this order: ");
                        scanf("%d", &b->totalAmount);
                        if(bills == NULL){
                            bills = b;
                        }
                        else{
                            bf = bills;
                            while(bf->next != NULL)
                                bf = bf->next;
                            bf->next = b;
                        }
                        qf->next = q->next;
                        printf("Order successfully delivered.\n");
                    }
                    else{
                        printf("The order you are trying to deliver is not yet ready.\n");
                        return;
                    }
                }
                q = q->next;
                qf = qf->next;
            }
        }
    }
    if(foodsOrders != NULL){
        p = foodsOrders->next;
        if(found == 0){
            if(foodsOrders->orderId == orId){
                if(foodsOrders->status == "ready"){
                    b->billId = billId + 1;
                    billId = billId + 1;
                    b->tableNo = foodsOrders->tableNo;
                    b->desc = foodsOrders->desc;
                    printf("Enter the amount for this order: ");
                    scanf("%d", &b->totalAmount);
                    if(bills == NULL){
                        bills = b;
                    }
                    else{
                        bf = bills;
                        while(bf->next != NULL)
                            bf = bf->next;
                        bf->next = b;
                    }
                    foodsOrders = foodsOrders->next;
                    pf = NULL;
                    printf("Order successfully delivered.");
                    return;
                }
            }
            else{
                while(p != NULL){
                    if(p->orderId == orId){
                        found++;
                        if(p->status == "ready"){
                            b->billId = billId + 1;
                            billId = billId + 1;
                            b->tableNo = p->tableNo;
                            b->desc = p->desc;
                            printf("Enter the amount for this order: ");
                            scanf("%d", &b->totalAmount);
                            if(bills == NULL){
                                bills = b;
                            }
                            else{
                                bf = bills;
                                while(bf->next != NULL)
                                    bf = bf->next;
                                bf->next = b;
                            }
                            pf->next = p->next;
                            printf("Order successfully delivered.");
                        }
                        else{
                            printf("The order you are trying to deliver is not yet ready.");
                            return;
                        }
                    }
                    p = p->next;
                    pf = pf->next;
                }
            }
        }
    }
    if(found == 0){
        printf("The order id you entered does not exist. Please try again.");
        return;
    }
}
allBill(){
    struct bill *q;
    q = bills;
    if(bills == NULL){
        printf("There is no bills at all.\n");
        return;
    }
    printf("\nBillId\tTable No\tDescription\tAmount");
    while(q != NULL){
        printf("\n%d\t%d\t\t%s\t%d", q->billId, q->tableNo, q->desc, q->totalAmount);
        q = q->next;
    }
    printf("\n");
}
printBill(){
    allBill();
    struct bill *q, *myBills, *temp, *myTemp;
    temp = (struct bill*)malloc(sizeof(struct bill));
    q = bills;
    myBills = NULL;
    if(bills == NULL){
        printf("There is no bill found.\n");
        return;
    }
    int tableNo;
    printf("Enter the table number: ");
    scanf("%d", &tableNo);
    while(q != NULL){
        if(q->tableNo == tableNo){
                printf("%d\t%s\t%d", q->tableNo, q->desc, tableNo);
            if(myBills == NULL){
                temp = q;
                temp->next = NULL;
                myBills = temp;
            }
            else{
                myTemp = myBills;
                while(myTemp != NULL)
                    myTemp = myTemp->next;
                temp = q;
                temp->next = NULL;
                myTemp->next = temp;
            }
        }
        q = q-> next;
    }
    if(myBills == NULL){
        printf("No bill for this table.\n");
        return;
    }
    printf("\nBillId\tTable No\tDescription\tAmount");
    myTemp = myBills;
    while(myTemp != NULL){
        printf("\n%d\t%d\t\t%s\t%d", myTemp->billId, myTemp->tableNo, myTemp->desc, myTemp->totalAmount);
        myTemp = myTemp->next;
    }
    printf("\n");
}
searchEmployee(){

}
displayEmployees(){

}

viewPending(){

}
