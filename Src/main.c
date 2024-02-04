#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "main.h"

uint8_t await_user_input();
void 	display_rec		(STUDENT_INFO_t *records);
uint8_t add_rec			(STUDENT_INFO_t *records);
uint8_t del_rec			(STUDENT_INFO_t *records, int32_t *recordNumber);
uint8_t find_rec		(STUDENT_INFO_t *records, int32_t *recordNumber);

#define MAX_RECORDS 10
STUDENT_INFO_t records[MAX_RECORDS];

int main(void) {
	printf("Student records management program");
	await_user_input();

	return 0;
}

uint8_t await_user_input() {
	int16_t input;

	printf("\n\nDisplay all records 		--> 1");
	printf("\nAdd new record 			--> 2");
	printf("\nDelete a record 		--> 3");
	printf("\nExit application		--> 0");

	printf("\n\nEnter code here: ");
	scanf("%hd", &input);

	switch(input) {
	case 1:
		display_rec(records);
		await_user_input();
		return 0;

	case 2:
		if(add_rec(records)) printf("\nRecord added!");
		await_user_input();
		return 0;

	case 3:
		int32_t recordNumber;
		printf("\nPrint record number for deletion: ");
		scanf("%d", &recordNumber);
		if(del_rec(records, &recordNumber)) printf("\nRecord deleted!");
		await_user_input();
		return 0;

	case 0:
		return 0;

	default:
		printf("Error! Try some of commands given below");
		await_user_input();
		return 0;
	}
}

void display_rec(STUDENT_INFO_t *records) {
	printf("\n---------------------------------");
	uint32_t recordsCounter = 0;
	for(uint16_t i = 0; i < MAX_RECORDS; i++) {
		if(records[i].record_number == 0) continue;
		printf("\nRecord number: %d", records[i].record_number);
		printf("\nStudent name: %s", records[i].name);
		printf("\nBranch: %s", records[i].branch);
		printf("\nDate of birth: %s", records[i].dob);
		printf("\nSemester: %d\n", records[i].semester);
		recordsCounter++;
	}
	if(!recordsCounter) printf("\nOoops! There are still no records");
	printf("\n---------------------------------");
}

uint8_t add_rec(STUDENT_INFO_t *records) {
	uint32_t recordsCounter = 0;

	for(uint16_t i = 0; i < MAX_RECORDS; i++) {
		if(records[i].record_number != 0) recordsCounter++;
	}

	if(recordsCounter == MAX_RECORDS) {
		printf("\nOoops! The record limit has been reached, delete some records(s) to be able to add new");
		return 0;
	} else {
		for(uint16_t i = 0; i < MAX_RECORDS; i++) {
			if(records[i].record_number == 0) {
				int32_t temp;
				printf("\nEnter record number: ");
				scanf("%d", &temp);
				if(temp == 0) {
					printf("\nYou cannot create records with record number \"0\"");
					return 0;
				}
				if(find_rec(records, &temp)) {
					printf("\nError! Record with such number already exists! ");
					return 0;
				}
				records[i].record_number = temp;
				getchar();

				printf("Enter student name: ");
				scanf("%[^\n]s", records[i].name);
				getchar();

				printf("Enter branch: ");
				scanf("%[^\n]s", records[i].branch);
				getchar();

				printf("Enter date of birth: ");
				scanf("%[^\n]s", records[i].dob);
				getchar();

				printf("Enter semester: ");
				scanf("%d", &temp);
				if(temp < 0 || temp > 100) {
					printf("\nError! Semester must be in range from 0 to 100! ");
					del_rec(records, &(records[i].record_number));
					return 0;
				}
				records[i].semester = temp;
				getchar();

				break;
			}
		}
	}
	return 1;
}

uint8_t del_rec(STUDENT_INFO_t *records, int32_t *recordNumber) {
	if(*recordNumber == 0) {
		printf("\nYou cannot delete records with record number \"0\"");
		return 0;
	}

	for(uint16_t i = 0; i < MAX_RECORDS; i++) {
		if(records[i].record_number == *recordNumber) {
			records[i].record_number = 0;
			strcpy(records[i].name, "");
			strcpy(records[i].branch, "");
			strcpy(records[i].dob, "");
			records[i].semester = 0;
			return 1;
		}
	}
	printf("\nThere is no record with such number");
	return 0;
}

uint8_t find_rec(STUDENT_INFO_t *records, int32_t *recordNumber) {
	for(uint16_t i = 0; i < MAX_RECORDS; i++) {
		if (records[i].record_number == *recordNumber) return 1;
	}
	return 0;
}


