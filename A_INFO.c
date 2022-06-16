#include "A_INFO.h"

int menu() { // 입력된 숫자에 따라 메뉴 실행
	char num;
	while (1) {
		printf("\n\n\t*** 원하는 기능의 숫자를 입력하세요. ***\n\n");
		printf("\t1. 입실 및 퇴실 명단 추가\n");
		printf("\t2. 명단 업데이트\n");
		printf("\t3. 명단 삭제\n");
		printf("\t4. 명단 검색\n");
		printf("\t5. 전체 명단 출력\n");
		printf("\t6. 종료\n\n");

		printf("\t>> ");
		scanf(" %c", &num);

		switch (num) {
		case '1':
			get_studentinfo();
			break;

		case '2':
			update_node();
			break;

		case '3':
			delete_node();
			break;


		case '4':
			search_list();
			break;

		case '5':
			print_list();
			break;

		case '6':
			printf("\n\t프로그램을 종료합니다.\n");
			printf("\n\t****************************************\n");
			delete_list();
			return 0;

		default:
			printf("\n\t유효하지 않은 입력입니다. 다시 입력하세요.\n\n");
			print_star();
			break;
		}
	}
}

void print_star() {
	printf("\n\t****************************************\n");
}

void print_line() {
	printf("\n\t학번\t      이름\t학년  입실 시간  퇴실 시간\n");
	printf("\t==================================================\n");
}

void error_id() {
	printf("\n\n\tError: 명단에 존재하지 않는 학번입니다.\n\n");
}

void get_studentinfo() { // 학생 정보 입력
	SINFO student;
	int state;
	printf("\n");
	print_star();
	printf("\n\t< 입실 및 퇴실 명단 추가 >\n");
	printf("\n\t  학생 정보를 입력하세요.\n\n");

	while (1) {
		printf("\t* 입실: 0 입력 / 퇴실: 1 입력 (종료: 2 입력)>> ");
		scanf("%d", &state);

		if (state == 2)
			break;

		printf("\t* 학번 >> ");
		scanf("%s", &student.id);
		if (search_listId(student.id)) {
			printf("\n\t  이미 명단에 존재합니다.\n"); // 입력한 학번이 이미 존재하면 종료
			break;
		}

		printf("\t* 이름 >> ");
		scanf("%s", &student.name);
		printf("\t* 학년 >> ");
		scanf("%d", &student.grade);

		if (state == 0) { // 입실 선택 시
			printf("\t* 입실 시간 >> ");
			scanf("%lf", &student.in_time);
			student.in_cnt = 1;
			if (student.out_cnt != 1) student.out_time = 999;
		}

		else if (state == 1) { // 퇴실 선택 시
			printf("\t* 퇴실 시간 >> ");
			scanf("%lf", &student.out_time);
			student.out_cnt = 1;
			if (student.in_cnt != 1) student.in_time = 999;
		}
		printf("\n");
		insert_node(&student); // 노드 삽입

	}
	print_star();
}

void insert_node(SINFO* student) {
	SINFO* temp = (SINFO*)malloc(sizeof(SINFO)); // 입력받은 학생 정보 동적할당
	SINFO* list, * previous; // 명단, 이전 노드

	strcpy(temp->id, student->id);
	strcpy(temp->name, student->name);
	temp->grade = student->grade;
	temp->in_time = student->in_time;
	temp->out_time = student->out_time;
	list = listhead;

	previous = NULL;
	while (list != NULL) {
		if (temp->in_time > list->in_time) { // 입실 시간에 따라 순차적으로 정렬
			previous = list;
			list = list->next;
		}
		else
			break;
	}
	if (previous == NULL) { // 이전 노드가 없을 시
		temp->next = listhead;
		listhead = temp;
	}
	else {
		temp->next = list;
		previous->next = temp;
	}
}

void info(SINFO* student) { // 학생 정보
	printf("\t%s    %s\    %d", student->id, student->name, student->grade);
	if (student->in_time == 999) printf("     None\t %.2lf\n", student->out_time);
	else if (student->out_time == 999) printf("     %.2lf\t None\n", student->in_time);
	else printf("     %.2lf\t %.2lf\n", student->in_time, student->out_time);
}
void print_list() { // 학생 정보 출력
	SINFO* student = NULL;
	student = listhead;
	printf("\n");
	print_star();
	printf("\n\t< 명단 출력 >\n");
	print_line();

	while (student != NULL) {
		info(student);
		student = student->next;
	}
}

void delete_node() { // 학번을 입력받아서 해당하는 노드가 존재하면 삭제
	char search[20];
	SINFO* temp = listhead;

	printf("\n\t삭제할 명단의 학번을 입력하시오>> ");
	scanf("%s", search);


	if (listhead != NULL && strcmp(temp->id, search) == 0) { //첫 번째 노드를 삭제하는 경우
		listhead = listhead->next;
		printf("\n\t ** 삭제 완료 ** ");
	}
	else {
		while (temp->next != NULL) { // 다음 노드가 존재하는 경우
			{
				if (strcmp(temp->name, search) == 0) { // 입력한 학번이 존재할 경우
					temp->next = temp->next->next;
					printf("\n\t ** 삭제 완료 ** ");
				}
				temp = temp->next;
			}
		}
	}
}

void update_node() { // 학생 정보 업데이트
	char search[20];
	int state;
	SINFO* temp = listhead;

	printf("\n");
	print_star();
	printf("\n\t< 업데이트 >\n\n");
	printf("\t* 학번을 입력하세요>> ");
	scanf("%s", search);
	if (search_listId(search) == 1) {
		printf("\t* 업데이트할 기록 - 입실: 0 입력 / 퇴실: 1 입력 >> ");
		scanf("%d", &state);

		if (state == 0 || state == 1) {

			if (temp != NULL && strcmp(temp->id, search) == 0) { // 입력한 학번이 존재하면 실행
				if (state == 0) { // 입실 정보 입력
					printf("\t* 입실 시간 >> ");
					scanf("%lf", &temp->in_time);
					temp->in_cnt = 1;
					printf("\n\n\t  ** 업데이트 완료 **\n");
				}

				else { // 퇴실 정보 입력
					printf("\t* 퇴실 시간 >> ");
					scanf("%lf", &temp->out_time);
					temp->out_cnt = 1;
					printf("\n\n\t  ** 업데이트 완료 **\n");
				}
			}
		}
		else {
			printf("\n\n\tError: 유효하지 않은 입력입니다.\n\n");
			print_star();
		}
	}
	else {
		error_id(); // 에러 메시지 출력
		print_star();
	}
	if (temp != NULL) temp = temp->next;
}

void delete_list() { // 동적할당 해제
	SINFO* temp = listhead;
	while (listhead) {
		listhead = listhead->next;
		free(temp);
		temp = listhead;
	}
}

void search_list() { // 학번을 입력받은 후 명단에서 학번 검색
	int cnt = 0;
	char search[20];
	SINFO* temp = listhead;

	printf("\n\t검색할 명단의 학번을 입력하시오>> ");
	scanf("%s", search);

	while (temp != NULL) {
		if (strcmp(temp->id, search) == 0) { // 학번이 존재하면 출력

			print_line();
			info(temp);
			cnt++;
		}
		temp = temp->next;

	}
	if (cnt == 0) {
		error_id(); // 에러 메시지 출력
		print_star();
	}
}


int search_listId(char search[20]) { // id를 매개변수로 명단에서 학번 검색
	SINFO* temp = listhead;
	while (temp != NULL) {
		if (strcmp(temp->id, search) == 0) {
			return 1;
		}
		temp = temp->next;
	}
}

int main(void) {
	menu();
}