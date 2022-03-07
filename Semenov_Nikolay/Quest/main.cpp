#include "Q_API.h"
#include "Q_Data.h"

int main() {
	User student;
	A_Quest quest = init_quest();
	quest.run(student);
	student.print_stat();
	system("pause");
	return 0;
}