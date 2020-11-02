#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <time.h>/* time_t, struct tm, time, localtime, strftime */
#define NUM_RESERVER 100
#define STR_SIZE 50

struct Reserver
{
	int reserverID; // or reserve_room_number
	char name[STR_SIZE];
	char gender[STR_SIZE];// male or female
	int total_member;
	//int reserve_status;// room reserved or not
	char address[STR_SIZE];
	int room_no;
	char reserve_date[STR_SIZE];
	long int reserve_time;
	int reserve_period;// or duration
};

typedef struct Reserver ReserverData;
ReserverData reserver[NUM_RESERVER];
int numReservers = 0;



void Read()
{
   FILE *fp;
    int i;

    fp = fopen("reservers.txt","r");
    if(fp == NULL)
        printf("Error reading file.");
    else
    {
        char c;
        int rows = 0;
        fscanf(fp, "%d", &rows);
        for(i = 0;i<rows; i++)
        {
            //if(feof(fp))
                //break;
            fscanf(fp, "%d", &reserver[i].reserverID);
            fscanf(fp, "%d", &reserver[i].room_no);
            int j = 0, count = 0;
            while(EOF!=(c=fgetc(fp))){
                if(c == '#')
                    break;
                if(c == ' ' && count != 1){
                    count++;
                    continue;
                }
                reserver[i].name[j++] = c;
            }
            reserver[i].name[j] = 0;
            fscanf(fp, "%d", &reserver[i].total_member);                                                                      // author Shahriar,Masudul
            j = 0;
            count = 0;
            while(EOF!=(c=fgetc(fp))){
                if(c == '#')
                    break;
                if(c == ' ' && count != 1){
                    count++;
                    continue;
                }
                reserver[i].gender[j++] = c;
            }
            reserver[i].gender[j] = 0;
            //fscanf(fp, "%d", &reserver[i].reserve_status);
            j = 0;
            count = 0;
            while(EOF!=(c=fgetc(fp))){
                if(c == '#')
                    break;
                if(c == ' ' && count != 1){
                    count++;
                    continue;
                }
                reserver[i].address[j++] = c;
            }
            reserver[i].address[j] = 0;
            j = 0;
            count = 0;
            while(EOF!=(c=fgetc(fp))){
                if(c == '#')
                    break;
                if(c == ' ' && count != 1){
                    count++;
                    continue;
                }
                reserver[i].reserve_date[j++] = c;
            }
            reserver[i].reserve_date[j] = 0;
            fscanf(fp, "%ld", &reserver[i].reserve_time);
            fscanf(fp, "%d", &reserver[i].reserve_period);
        }
        numReservers = i;//set numReservers = #of reserver records read from file
        printf("nums: %d", numReservers);
        fclose(fp);
    }

}

void View()
{
    int i;
    printf("ID|\tRoom_no\t|Name\t|\tGender\t|\tTotal_Member\t|\tAddress\t|\tReserve_date\t|\tReserve_status\t|\tReserve_period|\n");
    printf("----------------------------------------------------------------------------------------\n");
    for(i = 0; i < numReservers; i++)
    {
        if(reserver[i].reserverID != 0){//if the student ID has not been deleted
            printf("%d\t|", reserver[i].reserverID);
            printf("%d\t|", reserver[i].room_no);
            printf("%s\t|", reserver[i].name);
            printf("%s\t|", reserver[i].gender);
            printf("%d\t|", reserver[i].total_member);
            printf("%s\t|", reserver[i].address);
            printf("%s\t|", reserver[i].reserve_date);
            time_t current_t;
            double diff_t;

            time(&current_t);

            diff_t = (long int)current_t-reserver[i].reserve_time;
            if(diff_t >= 1){
                printf("%s\t|", "Available");
            } else {
                printf("%s\t|", "Not available");
            }
            printf("%d\n", reserver[i].reserve_period);
            printf("----------------------------------------------------------------------------------------\n");
        }
    }
    printf("\nEnter any key to continue\n");
    getch();
}

void Write()
{
    FILE *fp;
    int i, nr = numReservers;

    fp = fopen("reservers.txt","w");
    if(fp == NULL)
        printf("Error writing file.");
    else
    {
        for(i = 0; i<nr; i++)
        {
            if(reserver[i].reserverID == 0){//if the reserver ID has not already been deleted
                --nr;
            }
        }
        fprintf(fp, "%d\n", nr);
        for(i = 0; i<numReservers;i++)
        {
            if(reserver[i].reserverID != 0){//if the reserver ID has not already been deleted
                fprintf(fp, "%d ", reserver[i].reserverID);
                fprintf(fp, "%d ", reserver[i].room_no);
                fprintf(fp, "%s# ", reserver[i].name);
                fprintf(fp, "%d ", reserver[i].total_member);
                fprintf(fp, "%s# ", reserver[i].gender);
                //fprintf(fp, "%d ", reserver[i].reserve_status);
                fprintf(fp, "%s# ", reserver[i].address);
                fprintf(fp, "%s# ", reserver[i].reserve_date);
                fprintf(fp, "%ld ", reserver[i].reserve_time);
                fprintf(fp, "%d\n", reserver[i].reserve_period);
            }
        }
        fclose(fp);
    }
}

void Delete()
{
    int i,id,p;
    printf("Enter visitor's id to delete: ");
    scanf("%d", &id);
    int cr;
    while((cr = getchar()) != '\n');

    for(i=0;i<numReservers;i++)
    {
        if(reserver[i].reserverID == id)
        {
            p = 1;
            break;
        }
    }
    if(p==1)
    {
        printf("Match found!\n");
            printf("Confirm delete...:(y/n):");
            char c[1];
            scanf("%s", c);
            while((cr = getchar()) != '\n');
            if(strcmp(c,"y") == 0){
                reserver[i].reserverID = 0;
                //--numReservers;
                printf("Reserver id successfully deleted!!!\n");
            } else {
                printf("Delete process aborted!\n");
            }
    }
    else if(p!=1)
    {
        printf("Sorry! ID not found!!!\n\n");
    }
    printf("Enter any key to continue\n");
    getch();
    return;
}

ReserverData Input()
{
    ReserverData r;
    printf("Enter the reserverID and room_no: ");
    //TODO: Check if the id already exist or is invalid (e.g. negative number or zero), in which case we will show error and go back to main menu
    scanf("%d %d", &r.reserverID, &r.room_no);
    if(r.reserverID <= 0){
        printf("Invalid ID!\n");
        return Input();
    } else {
        int k;
        for(k=0; k<numReservers; k++){
            if(r.reserverID == reserver[k].reserverID){
                printf("ID already exists!\n");
                return Input();
            }
        }
    }
    int c;
    while((c = getchar()) != '\n');
    printf("Enter reserver name: ");
    gets(r.name);
    printf("Enter reserver gender: ");
    gets(r.gender);
    printf("Enter reserver total member: ");
    scanf("%d", &r.total_member);

    // reserver status
    //r.reserve_status = 1;
    while((c = getchar()) != '\n');
    printf("Enter reserver address: ");
    gets(r.address);
    printf("Enter reserve period: ");
    scanf("%d", &r.reserve_period);
    // reserve_date
    time_t now;
    time(&now);
    // set reserve time in sec
    r.reserve_time = (long int)now + (r.reserve_period * 24 * 60 * 60);

    struct tm* now_tm;
    now_tm = localtime(&now);

    char out[80];
    strftime(out, 80, "%Y-%m-%d %H:%M:%S", now_tm);
    strcpy(r.reserve_date,out);

    numReservers++;

    printf("The given reserver has been added successfully. Enter any key to continue\n");
    getch();
    return r;

}

void Search()
{
    int p = 0,i;
    char name[STR_SIZE];
    printf("Enter a resersver name to search: ");
    gets(name);
    int cr;
    //while((cr = getchar()) != '\n' && cr != EOF);
    for(i=0;i<numReservers;i++)
    {
         if(reserver[i].reserverID != 0 && strcmp(reserver[i].name,name) == 0)
        {
            p = 1;
            break;
        }
    }
    if(p==1)
    {
        printf("Reserver found!!!\n");
        printf("Reserver found at room no: %d\n", reserver[i].room_no);
    }
    else
    {
        printf("Reserver not found!!!\n");
    }
    printf("Enter any key to continue\n");
    getch();
}

int main(){
	char ch;
	Read();//read the reserver data from file (NOTE: I am only reading from file initially and then writing to file before exiting to minimize read/write to/from file)
	while(1){
        printf("\n\t\t\tEnter a choice:\n");
        printf("\t\t\t1. Add a reserver\n");
        printf("\t\t\t2. View reserver records\n");
        printf("\t\t\t3. Delete a reserver record\n");
        printf("\t\t\t4. Search user by name\n");
        printf("\t\t\t5. Exit\n");
        scanf("%c", &ch);
        char cf;
        fflush(stdin);
        system("cls");
        switch(ch){
            case '1': reserver[numReservers] = Input();//read a reserver's record from user
                    break;
            case '2': View();//show reserver records
                    break;
            case '3': Delete();//delete reserver records
                    break;
            case '4': Search();//Search user by name
                    break;
            case '5': Write();//write to the file all the reserver records
            printf("\n\n\n\n\n\n\n\n\t\t\tTHANK YOU FOR BEING WITH US\n");
                      printf("\t\t\t***************************\n\n\n\n\n");
                    return;//exit from program
            default: printf("Wrong option chosen; choose again\n");
        }
        system("cls");
	}
    return 0;
}


