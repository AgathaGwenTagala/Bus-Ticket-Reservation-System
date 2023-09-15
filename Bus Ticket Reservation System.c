#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>

FILE *fp;
int main();

struct passenger
{
	int bus;
	int reserve;
	int seat;
	char name[50];
	char mobile[50];
};

struct passenger *return_passenger()
{
	fp = fopen("busStatus.txt", "a+");
	fseek(fp, 0, SEEK_SET);
    struct passenger *passenger = malloc(sizeof(struct passenger) * 100);
	int ch = getc(fp);
	int i = -1, j, k;
	char code[500];
	while (ch != EOF)
	{
		i++;
    	if (fgets(code, 500, fp) != NULL)
		{
			char *reserve_tok = strtok(code, "/");
			char *bus_tok = strtok(NULL, "/");
			char *name_tok = strtok(NULL, "/");
			char *mobile_tok = strtok(NULL, "/");
			char *seat_tok = strtok(NULL, "\n");
			strcpy(passenger[i].name, name_tok);
			strcpy(passenger[i].mobile, mobile_tok);
			passenger[i].reserve = atoi(reserve_tok);
			passenger[i].bus = atoi(bus_tok);
			passenger[i].seat = atoi(seat_tok);
			name_tok = NULL;
			mobile_tok = NULL;
			bus_tok = NULL;
			seat_tok = NULL;
			reserve_tok = NULL;
		}
		ch = getc(fp);
	}
	return passenger;
}

void head()
{
	system("cls");
	printf("\n\t       BUS TERMINAL\n");
	printf("\tNext-day Ticket Reservation\n\n");
}

int reservation_number()
{
	int number;
	head();
	printf("\tEnter Reservation Number: ");
	scanf("%d", &number);
	getchar();
	return number;
}

void list()
{
	system("cls");
	head();
	printf("\t\tBUS LIST\n\n");
	printf("\t[1] Genesis Bus\n\n");
	printf("\t[2] Baliwag Transit\n\n");
	printf("\t[3] Back to Main Menu\n\n");
	printf("\t>>> ");
}

void schedule(int choice)
{
	char gn, bt;
	switch (choice)
	{
		case 1:
			head();
			printf("\t\tSCHEDULE\n\n");
			printf("\tGenesis Bus\n\n");
			fp = fopen("busGN.txt", "r");
    		gn = fgetc(fp);
	    	while (gn != EOF)
    		{	printf ("%c", gn);
	       		gn = fgetc(fp); }
			break;
		case 2:
			head();
			printf("\t\tSCHEDULE\n\n");
			printf("\tBaliwag Transit\n\n");
			fp = fopen("busBT.txt", "r");
    		bt = fgetc(fp);
    		while (bt != EOF)
    		{	printf ("%c", bt);
        		bt = fgetc(fp); }
			break;
		case 3:
			choice = 3;
			main();
			break;
		default:
			printf("\n\tInvalid Option!");
			getch();
	}
}

void view()
{
	int choice;
	do
	{
		list();
		scanf("%d", &choice);
		schedule(choice);
		getch();
	} while (choice != 3);
}

void book()
{
	int choice, choice2, id, count = 1, a, tix, seat_no, reserve_no = 0;
	char name[30];
	char mobile[11];

	list();
	scanf("%d", &choice);
	schedule(choice);
	printf("\n\t[1] Continue\n");
	printf("\t[2] Back to Bus List\n\n");
	while (choice2 < 1 || choice2 > 2)
	{
		printf("\t>>> ");
		scanf("%d", &choice2);
		if (choice2 == 2)
			book();
		else if (choice2 == 1)
			break;
	}

	printf("\n\t\tBOOK TICKETS\n\n");
	printf("\tSTEP 1 <Choose Bus ID>\n");
	switch (choice)
	{
        case 1:
			while (id < 1 || id > 6)
			{
				printf("\n\tBus ID: ");
				scanf("%d", &id);
			}
			break;
		case 2:
			while (id < 7 || id > 12)
			{
				printf("\n\tBus ID: ");
				scanf("%d", &id);
			}
			break;
	}

	head();
	printf("\t\tBOOK TICKETS\n\n");
	printf("\tSTEP 2 <Enter Passenger Details>\n\n");
	printf("\tNumber of Tickets: ");
	scanf("%d", &tix);

	for (a = 0; a < tix; a++)
	{
		int j, k;
		struct passenger *passenger;
		passenger = return_passenger();
		for (j = 0; j < 100; j++)
		{
			if (passenger[j].reserve >= reserve_no && a == 0)
				reserve_no = passenger[j].reserve + 1;
		}
		if (reserve_no == 0)
			reserve_no = 1;
		printf("\n\tReservation Number %d", reserve_no);
		printf("\n\n\tPassenger Number: %d", a + 1);
		printf("\n\tPassenger Name: ");
		scanf("\n");
		gets(name);
		printf("\tContact Number: ");
		scanf("%s", &mobile);
		getchar();
		printf("\n\tSTEP 3 <Choose Seat Number>\n\n");
		printf("\t\tBus ID %02d\n\n", id);
		printf("\tO - Available	X - Reserved\n");
		for (j = 0; j < 32; j++)
		{
			char available = 'O';
			for (k = 0; k < 100; k++)
			{
				if (passenger[k].bus == id && passenger[k].seat == j + 1)
					available = 'X';
			}
			if (j % 4 == 0)
				printf("\n\t");
			printf("%02d [%c]\t", j + 1, available);
		}
		printf("\n");
		int check_seat = 1;
		while (check_seat == 1)
		{
			printf("\n\tSeat Number: ");
			scanf("%d", &seat_no);
			getchar();
			for (k = 0; k < 100; k++)
			{
				if (passenger[k].bus == id)
				{
					if (passenger[k].seat == seat_no)
					{
						check_seat = 1;
						break;
					}
					else
					check_seat = 0;						
				}
				else
					check_seat = 0;
			}
		}
		head();
		printf("\t\tBOOK TICKETS\n");
		fseek(fp, 0, SEEK_END);
		fprintf(fp," %d/%d/%s/%s/%d\n", reserve_no, id, name, mobile, seat_no);
		fclose(fp);
	}
	printf("\n\tReservation Successful!");
	getch();
}

void print()
{
	int j, k, no_of_tix = 0, total = 0, pos;
	int fee[12] = {110, 120, 130, 110, 120, 130, 150, 160, 170, 150, 160, 170};
	char time_table[12][10] = {"08:00AM","09:00AM","10:00AM","12:00PM","01:00PM","02:00PM","08:15AM","09:15AM","10:15AM","12:15PM","01:15PM","02:15PM"};
	char departure[20];
	int number = reservation_number();
	head();
	printf("\t\tPRINT TICKETS\n\n");
	struct passenger *passenger;
	passenger = return_passenger();
	for (j = 0; j < 100; j++)
	{
		if (passenger[j].reserve == number)
		{
			total += fee[passenger[j].bus-1];
			no_of_tix++;
			strcpy(departure, time_table[passenger[j].bus-1]);
			printf("\tReservation Number: %d", passenger[j].reserve);
			printf("\n\n\tBus ID: %02d", passenger[j].bus);
			printf("\n\tDeparture Time: %s", departure);
			printf("\n\tSeat Number: %02d", passenger[j].seat);
			printf("\n\n\tPassenger Name: %s", passenger[j].name);
			printf("\n\tContact Number: %s", passenger[j].mobile);
			printf("\n\tTicket Price: P%d", fee[passenger[j].bus-1]);
			printf("\n\n\t\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\n\n");
			pos = 1;
		}
	}
	if (pos == 1)
	{
		printf("\t\tRECEIPT\n");
		printf("\n\tTicket (x%d)", no_of_tix);
		printf("\n\tService Fee:\t   P%s", "15.00");
		printf("\n\tTOTAL AMOUNT:\t   P%d.00", total + 15);
		printf("\n\n\t\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\n\n");
	}
	else
		printf("\tReservation Number %d Not Found!\n\tPlease try again.", number);
	fclose(fp);
	getch();
}

void cancel()
{
	int j, pos = 0;
	int number = reservation_number();
	head();
	printf("\t\tCANCEL RESERVATION\n\n");
	fp = fopen("busStatus.txt", "r+");
	if (fp == NULL)
	{
		printf("\tNo Reservations!\n\tBook tickets first!");
		getch();
		return;
	}
	struct passenger *passenger;
	passenger = return_passenger();
	fclose(fp);
	fp = fopen("busStatus.txt", "w");
	for (j = 0; j < 100; j++)
	{
		if(passenger[j].reserve != number && passenger[j].reserve != 0)
			fprintf(fp," %d/%d/%s/%s/%d\n", passenger[j].reserve, passenger[j].bus, passenger[j].name, passenger[j].mobile, passenger[j].seat);
		if(passenger[j].reserve == number)
			pos = 1;
	}
	if(pos == 1)
		printf("\tReservation Number %d Cancelled!", number);
	else
		printf("\tReservation Number %d Not Found!\n\tPlease try again.", number);
	fclose(fp);
	getch();
}

int main()
{
	int choice;
	do
	{
		head();
		printf("\t\tMAIN MENU\n\n");
		printf("\t[1] View Bus Schedule\n\n");
		printf("\t[2] Book Tickets\n\n");
		printf("\t[3] Print Tickets\n\n");
		printf("\t[4] Cancel Reservation\n\n");
		printf("\t[5] Exit\n\n");
		printf("\t>>> ");
		scanf("%d", &choice);
		switch (choice)
		{
			case 1:
				view();
				break;
			case 2:
				book();
				break;
			case 3:
				print();
				break;
			case 4:
				cancel();
				break;
			case 5:
				choice = 5;
				break;
			default:
				printf("\n\tInvalid Option!");
				getch();
		}
	} while (choice != 5);
	head();
	printf("\tThe journey of a thousand miles\n\t  begins with a single step.\n\n\t\t\t- Lao Tzu\n");
	exit(0);
}
