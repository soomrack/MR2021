#include <iostream>
#include <string.h>

int score = 0;

class Task {
public:
    std::string question;
    std::string answer_1;
    std::string answer_2;
    std::string answer_3;
    std::string answer_4;
    int answer_1_points;
    int answer_2_points;
    int answer_3_points;
    int answer_4_points;
    int user_answer;

    Task();
    Task(std::string ques,
         std::string ans_1,
         std::string ans_2,
         std::string ans_3,
         std::string ans_4,
         int ans_1_points,
         int ans_2_points,
         int ans_3_points,
         int ans_4_points
         ) {
        question = ques;
        answer_1 = ans_1;
        answer_2 = ans_2;
        answer_3 = ans_3;
        answer_4 = ans_4;
        answer_1_points = ans_1_points;
        answer_2_points = ans_2_points;
        answer_3_points = ans_3_points;
        answer_4_points = ans_4_points;
    };

    void print_question();
    int user_answer_get();
};

void Task::print_question() {
        std::cout << "" << std::endl;
        std::cout << question << std::endl;
        std::cout <<  "1) " + answer_1 << std::endl;
        std::cout <<  "2) " + answer_2 << std::endl;
        std::cout <<  "3) " + answer_3 << std::endl;
        std::cout <<  "4) " + answer_4 << std::endl;
}
int Task::user_answer_get() {
    tryAgain:
    std::cin >> user_answer;
    if (Task::user_answer == 1) {
        score = score + answer_1_points;
    } else if(Task::user_answer == 2) {
        score = score + answer_2_points;
    } else if (Task::user_answer == 3) {
        score = score + answer_3_points;
    } else if (Task::user_answer == 4) {
        score = score + answer_4_points;
    } else{
        std::cout << "Ошибка, вы ввели несуществующий вариант!" << std::endl;
        goto tryAgain;
    }
}

void total_result() {
    std::cout << "Результат теста:" << std::endl;
    if (score >= 20) {
        //Вы крутой
        std::cout << "Ля внатуре жесткий! Че творишь! Просто лев уасяяяя!"
                     "\nМаксимальный балл. Красава внатуре." << std::endl;
    } else if (score >= 16) {
        //вы средний
        std::cout << "Отличные результаты! По уровню крутости вы волк!"
                     "\nНе такой крутой как лев, но зато в цирке не выступаете!"
                     "\nЕсть куда расти." << std::endl;
    } else if (score >= 12) {
        //вы так себе
        std::cout << "Вы обычный парень. Средний результат. Ничего крутого в вас нет."
                     "\nНо жизнь длинная, все может поменяться."
                     "\nИ надеюсь в лучшую сторону!" << std::endl;
    } else if (score >= 8) {
        //вы не очень
        std::cout << "По уровню крутости вы сурикат! Почему? Ну хотите будете посудомойкой!"
                     "\n Расти и расти вам! :)" << std::endl;
    } else {
        //хуже всех
        std::cout << "Очень слабые результаты. Наверняка вы ставили специально плохие ответы."
                     "\n Если нет, вам предстоит длинный путь развития! ";
    }
}



int main() {
    //Вводные слова
    std::cout << "\nПриветствую вас, noname! Этот тест на крутость."
                 "\nПри ответе просто пишите номер варианта ответа, который вы выбрали."
                 "\nНапишите что-нибудь, и нажмите enter" << std::endl;
    //Для запуска программы
    std::string anything;
    std::cin >> anything;
    std::cout << "Погнали!" << std::endl;

    //Создаем вопрос и сразу его выдаем пользователю
    Task q1("Сколько жмешь от груди?","Не знаю","Ну 50 кг будет","80 кг спокойно","100 кг мой минимум",1,2,3,4);
    q1.print_question();
    q1.user_answer_get();

    Task q2("Алкоголь это ...", "Зло", "По кайфу", "Чутка можно по праздникам", "А так то сиги люблю",4,1,2,1);
    q2.print_question();
    q2.user_answer_get();

    Task q3("stdio.h это ...", "Название сборной России по Доте", "Библиотека с функциями ввода и вывода", "Сетевой маршрутизатор", "Проект США по борьбе с киберпреступностью",1,4,1,1);
    q3.print_question();
    q3.user_answer_get();

    Task q4("Облигация это ...", "Доля во владении компании" , "Налоговая льгота" , "Процесс вывода компании на биржу" ,"Средства которые инвестор предоставляет компании в долг",1,1,1,4);
    q4.print_question();
    q4.user_answer_get();

    Task q5("Кто такой Мачомен?","Гений, плейбой, филантроп", "Супергерой, противник Мегамозга", "Хакер, впервые взломавший Пентагон", "Суперзлодей, враг Бэтмена",1,4,1,1);
    q5.print_question();
    q5.user_answer_get();

    total_result();
    return 0;
}
