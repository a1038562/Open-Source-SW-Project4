#include "A_INFO.h"

int menu() { // �Էµ� ���ڿ� ���� �޴� ����
	char num;
	while (1) {
		printf("\n\n\t*** ���ϴ� ����� ���ڸ� �Է��ϼ���. ***\n\n");
		printf("\t1. �Խ� �� ��� ��� �߰�\n");
		printf("\t2. ��� ������Ʈ\n");
		printf("\t3. ��� ����\n");
		printf("\t4. ��� �˻�\n");
		printf("\t5. ��ü ��� ���\n");
		printf("\t6. ����\n\n");

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
			printf("\n\t���α׷��� �����մϴ�.\n");
			printf("\n\t****************************************\n");
			delete_list();
			return 0;

		default:
			printf("\n\t��ȿ���� ���� �Է��Դϴ�. �ٽ� �Է��ϼ���.\n\n");
			print_star();
			break;
		}
	}
}

void print_star() {
	printf("\n\t****************************************\n");
}

void print_line() {
	printf("\n\t�й�\t      �̸�\t�г�  �Խ� �ð�  ��� �ð�\n");
	printf("\t==================================================\n");
}

void error_id() {
	printf("\n\n\tError: ��ܿ� �������� �ʴ� �й��Դϴ�.\n\n");
}

void get_studentinfo() { // �л� ���� �Է�
	SINFO student;
	int state;
	printf("\n");
	print_star();
	printf("\n\t< �Խ� �� ��� ��� �߰� >\n");
	printf("\n\t  �л� ������ �Է��ϼ���.\n\n");

	while (1) {
		printf("\t* �Խ�: 0 �Է� / ���: 1 �Է� (����: 2 �Է�)>> ");
		scanf("%d", &state);

		if (state == 2)
			break;

		printf("\t* �й� >> ");
		scanf("%s", &student.id);
		if (search_listId(student.id)) {
			printf("\n\t  �̹� ��ܿ� �����մϴ�.\n"); // �Է��� �й��� �̹� �����ϸ� ����
			break;
		}

		printf("\t* �̸� >> ");
		scanf("%s", &student.name);
		printf("\t* �г� >> ");
		scanf("%d", &student.grade);

		if (state == 0) { // �Խ� ���� ��
			printf("\t* �Խ� �ð� >> ");
			scanf("%lf", &student.in_time);
			student.in_cnt = 1;
			if (student.out_cnt != 1) student.out_time = 999;
		}

		else if (state == 1) { // ��� ���� ��
			printf("\t* ��� �ð� >> ");
			scanf("%lf", &student.out_time);
			student.out_cnt = 1;
			if (student.in_cnt != 1) student.in_time = 999;
		}
		printf("\n");
		insert_node(&student); // ��� ����

	}
	print_star();
}

void insert_node(SINFO* student) {
	SINFO* temp = (SINFO*)malloc(sizeof(SINFO)); // �Է¹��� �л� ���� �����Ҵ�
	SINFO* list, * previous; // ���, ���� ���

	strcpy(temp->id, student->id);
	strcpy(temp->name, student->name);
	temp->grade = student->grade;
	temp->in_time = student->in_time;
	temp->out_time = student->out_time;
	list = listhead;

	previous = NULL;
	while (list != NULL) {
		if (temp->in_time > list->in_time) { // �Խ� �ð��� ���� ���������� ����
			previous = list;
			list = list->next;
		}
		else
			break;
	}
	if (previous == NULL) { // ���� ��尡 ���� ��
		temp->next = listhead;
		listhead = temp;
	}
	else {
		temp->next = list;
		previous->next = temp;
	}
}

void info(SINFO* student) { // �л� ����
	printf("\t%s    %s\    %d", student->id, student->name, student->grade);
	if (student->in_time == 999) printf("     None\t %.2lf\n", student->out_time);
	else if (student->out_time == 999) printf("     %.2lf\t None\n", student->in_time);
	else printf("     %.2lf\t %.2lf\n", student->in_time, student->out_time);
}
void print_list() { // �л� ���� ���
	SINFO* student = NULL;
	student = listhead;
	printf("\n");
	print_star();
	printf("\n\t< ��� ��� >\n");
	print_line();

	while (student != NULL) {
		info(student);
		student = student->next;
	}
}

void delete_node() { // �й��� �Է¹޾Ƽ� �ش��ϴ� ��尡 �����ϸ� ����
	char search[20];
	SINFO* temp = listhead;

	printf("\n\t������ ����� �й��� �Է��Ͻÿ�>> ");
	scanf("%s", search);


	if (listhead != NULL && strcmp(temp->id, search) == 0) { //ù ��° ��带 �����ϴ� ���
		listhead = listhead->next;
		printf("\n\t ** ���� �Ϸ� ** ");
	}
	else {
		while (temp->next != NULL) { // ���� ��尡 �����ϴ� ���
			{
				if (strcmp(temp->name, search) == 0) { // �Է��� �й��� ������ ���
					temp->next = temp->next->next;
					printf("\n\t ** ���� �Ϸ� ** ");
				}
				temp = temp->next;
			}
		}
	}
}

void update_node() { // �л� ���� ������Ʈ
	char search[20];
	int state;
	SINFO* temp = listhead;

	printf("\n");
	print_star();
	printf("\n\t< ������Ʈ >\n\n");
	printf("\t* �й��� �Է��ϼ���>> ");
	scanf("%s", search);
	if (search_listId(search) == 1) {
		printf("\t* ������Ʈ�� ��� - �Խ�: 0 �Է� / ���: 1 �Է� >> ");
		scanf("%d", &state);

		if (state == 0 || state == 1) {

			if (temp != NULL && strcmp(temp->id, search) == 0) { // �Է��� �й��� �����ϸ� ����
				if (state == 0) { // �Խ� ���� �Է�
					printf("\t* �Խ� �ð� >> ");
					scanf("%lf", &temp->in_time);
					temp->in_cnt = 1;
					printf("\n\n\t  ** ������Ʈ �Ϸ� **\n");
				}

				else { // ��� ���� �Է�
					printf("\t* ��� �ð� >> ");
					scanf("%lf", &temp->out_time);
					temp->out_cnt = 1;
					printf("\n\n\t  ** ������Ʈ �Ϸ� **\n");
				}
			}
		}
		else {
			printf("\n\n\tError: ��ȿ���� ���� �Է��Դϴ�.\n\n");
			print_star();
		}
	}
	else {
		error_id(); // ���� �޽��� ���
		print_star();
	}
	if (temp != NULL) temp = temp->next;
}

void delete_list() { // �����Ҵ� ����
	SINFO* temp = listhead;
	while (listhead) {
		listhead = listhead->next;
		free(temp);
		temp = listhead;
	}
}

void search_list() { // �й��� �Է¹��� �� ��ܿ��� �й� �˻�
	int cnt = 0;
	char search[20];
	SINFO* temp = listhead;

	printf("\n\t�˻��� ����� �й��� �Է��Ͻÿ�>> ");
	scanf("%s", search);

	while (temp != NULL) {
		if (strcmp(temp->id, search) == 0) { // �й��� �����ϸ� ���

			print_line();
			info(temp);
			cnt++;
		}
		temp = temp->next;

	}
	if (cnt == 0) {
		error_id(); // ���� �޽��� ���
		print_star();
	}
}


int search_listId(char search[20]) { // id�� �Ű������� ��ܿ��� �й� �˻�
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