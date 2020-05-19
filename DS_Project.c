#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<conio.h>
#include<string.h>
#include<stdbool.h>

struct employee{
    char name[255];
    char password[10];
    float totalReceipt, totalTips, numberOfOrders;
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
    bool isPaid;
    struct bill *next;
}* bills;
struct myBill{
    int billId;
    int tableNo;
    char *desc;
    int amount;
    bool isPaid;
    struct myBill *next;
}* myBills;
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
char empName[255] = "";

customerMenu(){
    printf("\nOur customers our priority\n");
    printf("Choose one of the following\n");
    char c;
    do{
        printf("\n1.Press a call\n2.View my bill\n0.Exit\nMake a choice: ");
        scanf("%s", &c);
        switch(c){
            case '1':
                pressCall();
                break;
            case '2':
                printBill();
                break;
            case '0':
                printf("Thank for being with us, hope you will come back again...\n");
                break;
            default:
                printf("You made a wrong choice!!! Please try again\n");
                break;
        }
    }while(c!= '0');
}
managerMenu(){
    char password[10];
    printf("Enter your password here: ");
    int i;
    i=0;
    do{
        password[i] = getch();
        if(password[i]!='\r'){
            printf("*");
        }
        i++;
    }while(password[i - 1] != '\r');
    printf("\n");
    password[i - 1] = '\0';
    if(strcmp(password, "admin1234") != 0){
        printf("Wrong password, please try again...\n");
        return;
    }
    printf("\nWelcome back Manager\n");
    printf("Choose one of the following\n");
    char c;
    do{
        printf("\n1.Register an employee\n2.Remove an employee\n3.Search employee\n4.Display orders\n5.Display employees\n6.Print a bill for a given customer\n7.Print a list of all bills\n0.Exit\nMake a choice: ");
        scanf("%s", &c);
        switch(c){
            case '1':
                addEmployee();
                break;
            case '2':
                removeEmployee();
                break;
            case '3':
                searchEmployee();
                break;
            case '4':
                displayOrders();
                break;
            case '5':
                displayEmployees();
                break;
            case '6':
                printBill();
                break;
            case '7':
                allBill();
                break;
            case '0':
                printf("Thank you....\n");
                break;
            default:
                printf("You made a wrong choice!!! Please try again\n");
                break;
        }
    }while(c!= '0');
}
waiterMenu(){
    char name[255], password[10];
    printf("Enter your name here: ");
    scanf("%s", name);
    printf("Enter your password here: ");
    int i;
    i=0;
    do{
        password[i] = getch();
        if(password[i]!='\r'){
            printf("*");
        }
        i++;
    }while(password[i - 1] != '\r');
    printf("\n");
    password[i - 1] = '\0';
    struct employee *emp;
    emp = employees;
    if(employees == NULL){
        printf("Incorrect username/password\n");
        return;
    }
    while(strcmp(emp->name, name) !=0 || strcmp(emp->password, password) != 0){
        if(emp->next == NULL){
            printf("Incorrect username/password\n");
            return;
        }
        emp = emp->next;
    }
    strcpy(empName, name);
    printf("\nWelcome back %s\n", empName);
    printf("Choose one of the following\n");
    char c;
    do{
        printf("\n1.Receive a call\n2.Register a command\n3.Display orders\n4.Deliver an order\n5.Print a bill for a given customer\n6.Receive Payment\n0.Exit\nMake a choice: ");
        scanf("%s", &c);
        switch(c){
            case '1':
                receiveCall();
                break;
            case '2':
                registerCommand();
                break;
            case '3':
                displayOrders();
                break;
            case '4':
                deliver();
                break;
            case '5':
                printBill();
                break;
            case '6':
                receivePayment();
                break;
            case '0':
                printf("Thank you....\n");
                break;
            default:
                printf("You made a wrong choice!!! Please try again\n");
                break;
        }
    }while(c!= '0');
}
cookerMenu(){char name[255], password[10];
    printf("Enter your name here: ");
    scanf("%s", name);
    printf("Enter your password here: ");
    int i;
    i=0;
    do{
        password[i] = getch();
        if(password[i]!='\r'){
            printf("*");
        }
        i++;
    }while(password[i - 1] != '\r');
    printf("\n");
    password[i - 1] = '\0';
    struct employee *emp;
    emp = employees;
    if(employees == NULL){
        printf("Incorrect username/password\n");
        return;
    }
    while(strcmp(emp->name, name) !=0 || strcmp(emp->password, password) != 0){
        if(emp->next == NULL){
            printf("Incorrect username/password\n");
            return;
        }
        emp = emp->next;
    }
    strcpy(empName, name);
    printf("\nWelcome back %s\n", empName);
    printf("Choose one of the following\n");
    char c;
    do{
        printf("\n1.Display orders\n2.Notify ready commands\n0.Exit\nMake a choice: ");
        scanf("%s", &c);
        switch(c){
            case '1':
                displayOrders();
                break;
            case '2':
                finishCommand();
                break;
            case '0':
                printf("Thank you....\n");
                break;
            default:
                printf("You made a wrong choice!!! Please try again\n");
                break;
        }
    }while(c!= '0');
}
main(){
    printf("\nWelcome to XYZ Restaurant\n");
    char c;
    init();
    printf("Enter as:");
    do{
        printf("\n1.Customer\n2.Manager\n3.Waiter/Waitress\n4.Cooker\n0.Exit\nMake a choice: ");
        scanf("%s", &c);
        switch(c){
            case '1':
                customerMenu();
                break;
            case '2':
                managerMenu();
                break;
            case '3':
                waiterMenu();
                break;
            case '4':
                cookerMenu();
                break;
            case '0':
                printf("......Bye Bye.....\n");
                break;
            default:
                printf("You made a wrong choice!!! Please try again...");
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
        if(calls == NULL){
            printf("There is no new calls");
            return;
        }
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
            found++;
            if(drinksOrders->status == "ready"){
                b->billId = billId + 1;
                billId = billId + 1;
                b->tableNo = drinksOrders->tableNo;
                b->desc = drinksOrders->desc;
                b->isPaid = false;
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
            else{
                printf("The order you are trying to deliver is not yet ready.\n");
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
                        b->isPaid = false;
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
                found++;
                if(foodsOrders->status == "ready"){
                    b->billId = billId + 1;
                    billId = billId + 1;
                    b->tableNo = foodsOrders->tableNo;
                    b->desc = foodsOrders->desc;
                    b->isPaid = false;
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
                    printf("Order successfully delivered.\n");
                    return;
                }
                else{
                    printf("The order you are trying to deliver is not yet ready.\n");
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
                            b->isPaid = false;
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
                            printf("Order successfully delivered.\n");
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
    printf("\nBillId\tTable No\tDescription\tAmount\tPaid?");
    while(q != NULL){
        printf("\n%d\t%d\t\t%s\t%d\t%s", q->billId, q->tableNo, q->desc, q->totalAmount, q->isPaid ? "YES" : "NO");
        q = q->next;
    }
    printf("\n");
}
printBill(){
    struct bill *q;
    struct myBill *temp, *myTemp;
    temp = (struct myBill*)malloc(sizeof(struct myBill));
    q = bills;
    totalAmount = 0;
    struct myBill* myBills = NULL;
    if(bills == NULL){
        printf("There is no bill found.\n");
        return;
    }
    int tableno;
    printf("Enter the table number: ");
    scanf("%d", &tableno);
    while(q != NULL){
        if(q->tableNo == tableno){
            temp->billId = q->billId;
            temp->tableNo = q->tableNo;
            temp->desc = q->desc;
            temp->amount = q->totalAmount;
            temp->isPaid = q->isPaid;
            totalAmount += q->totalAmount;
            temp->next = NULL;
            if(myBills == NULL){
                myBills = temp;
                printf("\nBill Id\tTable No\tDescription\tAmount\tPaid?");
                printf("\n%d\t%d\t\t%s\t%d\t%s", myBills->billId, myBills->tableNo, myBills->desc, myBills->amount, myBills->isPaid ? "YES" : "NO");
            }
            else{
                myTemp = myBills;
                while(myTemp->next != NULL)
                    myTemp = myTemp->next;
                myTemp->next = temp;
                printf("\n%d\t%d\t\t%s\t%d\t%s", myBills->billId, myBills->tableNo, myBills->desc, myBills->amount, myBills->isPaid ? "YES" : "NO");
            }
        }
        q = q->next;
    }
    if(!temp->tableNo){
        printf("there is no bill for this table.");
        return;
    }
    printf("\nTOTAL AMOUNT TO PAY: %d RWF   ", totalAmount);
    printf("\n");
}
receivePayment(){
    int amount;
    struct bill *q;
    struct employee *emp;
    if(bills == NULL){
        printf("There is no pending payment.\n");
        return;
    }
    q = bills;
    emp = employees;
    int orId;
    printf("Enter the Id of the bill that is paid: ");
    scanf("%d", &orId);
    while(q != NULL){
        if(q->billId == orId){
            if(q->isPaid){
                printf("This bill was already paid.\n");
                return;
            }
            else{
                printf("Enter the amount to pay: ");
                scanf("%d", &amount);
                if(amount < q->totalAmount){
                    printf("The amount you entered is below the price to for this bill, Please try again\n");
                    return;
                }
                q->isPaid = true;
                while(strcmp(emp->name, empName) != 0)
                    emp = emp->next;
                emp->totalReceipt += amount;
                emp->totalTips += (amount - q->totalAmount);
                emp->numberOfOrders += 1;
                printf("Payment done successfully\n");
                return;
            }
        }
        q = q->next;
    }
    printf("Bill with this id doesn't exist.\n");
}
searchEmployee(){
    char choice, name[255];
    struct employee  *p;
    p = employees;
    if(employees == NULL){
        printf("No employees were found.\n");
        return;
    }
    printf("Enter the name of the employee to search: ");
    scanf("\n");
    scanf("%[^\n]%*c", name);
    while(strcmp(p->name , name) != 0){
        if(p->next == NULL){
            printf("The name you entered doesn't march any employee.\n");
            return;
        }
        p = p->next;
    }
    printf("Name: %s\n", p->name);
    printf("pass: %s\n", p->password);
    printf("Total receipts: %f (Average: %f)\n", p->totalReceipt, p->totalReceipt/p->numberOfOrders);
    printf("Total tips: %f (Average: %f)\n", p->totalTips, p->totalTips/p->numberOfOrders);
}
addEmployee(){
    char choice;
    int i;
    do{
        struct employee *p, *q;
        p = (struct employee*)malloc(sizeof(struct employee));
        printf("Enter the name of employee: ");
        scanf("\n");
        scanf("%[^\n]%*c", p->name);
        printf("Create a password for this employee: ");
        i=0;
        do{
            p->password[i] = getch();
            if(p->password[i]!='\r'){
                printf("*");
            }
            i++;
        }while(p->password[i - 1] != '\r');
        printf("\n");
        p->password[i - 1] = '\0';
        p->totalReceipt = 0;
        p->totalTips = 0;
        p->numberOfOrders = 0;
        p->next = NULL;
        if(employees == NULL){
            employees = p;
            printf("\nEmployee successfully registered.\n");
        }
        else{
            q = employees;
            while(q->next != NULL)
                q = q->next;
            q->next = p;
            printf("Employee successfully registered.\n");
        }
        printf("\nPress (Y) to add another employee or press another key to exit: ");
        scanf("%s", &choice);
    }while(toupper(choice) == 'Y');
}
displayEmployees(){
    struct employee *q;
    q = employees;
    if(employees == NULL){
        printf("NO Employee found.\n");
        return;
    }
    printf("========================================\n");
    while(q != NULL){
        printf("Name: %s\n", q->name);
        printf("pass: %s\n", q->password);
        printf("Total receipts: %f (Average: %f)\n", q->totalReceipt, q->totalReceipt/q->numberOfOrders);
        printf("Total tips: %f (Average: %f)\n", q->totalTips, q->totalTips/q->numberOfOrders);
        printf("========================================\n");
        q = q->next;
    }
    printf("\n");
}
removeEmployee(){
    char choice, name[255];
    struct employee *q, *p;
    p = employees;
    if(employees == NULL){
        printf("No employees were found.\n");
        return;
    }
    q = employees->next;
    printf("Enter the name of the employee to be removed: ");
    scanf("\n");
    scanf("%[^\n]%*c", name);
    if(strcmp(employees->name, name) == 0){
        employees = employees->next;
        p = NULL;
        printf("Employee removed.\n");
    }
    while(strcmp(q->name , name) != 0){
        if(q->next == NULL){
            printf("The name you entered doesn't march any employee.\n");
            return;
        }
        q = q->next;
        p = p->next;
    }
    p->next = q->next;
    q = NULL;
    printf("Employee removed.\n");
}
