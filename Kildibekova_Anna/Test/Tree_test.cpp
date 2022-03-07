#include <iostream>
#include <string>

//Тест:Какое ты дерево

class Service {
public:
    int lemon_counter;
    int fir_tree_counter;
    int maple_counter;
    int pomegranate_counter;
private:
    int number_of_question;
public:
    bool lemon;
    bool fir_tree;
    bool maple;
    bool pomegranate;
public:
    Service ();
    void output_results(int, int, int, int, int, int, int, int);
    void output_greetings();
    void output_question(std::string);
    void counter ();
private:
    void sorting (int, int, int, int, int, int, int, int);
    bool sub_sorting (bool, int, int);
};

Service::Service () {
    lemon_counter = 0;
    fir_tree_counter = 0;
    maple_counter = 0;
    number_of_question = 0;
    pomegranate_counter = 0;
    lemon = false;
    fir_tree = false;
    maple = false;
    pomegranate = false;
}

void Service::counter () {
    if (lemon) {
        lemon_counter ++;
        lemon = false;
    }
    if (fir_tree) {
        fir_tree_counter ++;
        fir_tree = false;
    }
    if (maple) {
        maple_counter ++;
        maple = false;
    }
    if (pomegranate) {
        pomegranate_counter ++;
        pomegranate = false;
    }
}

bool Service::sub_sorting(bool big, int bigger, int less) {
    if (bigger <= less) {
        return false;
    } else return big;
}

void Service::sorting(int l_c_1, int l_k_2, int f_c_1, int f_c_2,
                      int m_c_1, int m_c_2, int p_c_1, int p_c_2) {

    lemon = true;
    fir_tree = true;
    maple = true;
    pomegranate = true;

    lemon_counter = l_c_1 + l_k_2;
    fir_tree_counter = f_c_1 + f_c_2;
    maple_counter = m_c_1 + m_c_2;
    pomegranate_counter = p_c_1 + p_c_2;

    lemon = sub_sorting(lemon, lemon_counter, fir_tree_counter);
    lemon = sub_sorting(lemon, lemon_counter, maple_counter);
    lemon = sub_sorting(lemon, lemon_counter, pomegranate_counter);

    fir_tree = sub_sorting(fir_tree, fir_tree_counter, lemon_counter);
    fir_tree = sub_sorting(fir_tree, fir_tree_counter, maple_counter);
    fir_tree = sub_sorting(fir_tree, fir_tree_counter, pomegranate_counter);

    maple = sub_sorting(maple, maple_counter, lemon_counter);
    maple = sub_sorting(maple, maple_counter, fir_tree_counter);
    maple = sub_sorting(maple, maple_counter, pomegranate_counter);

    pomegranate = sub_sorting(pomegranate, pomegranate_counter, lemon_counter);
    pomegranate = sub_sorting(pomegranate, pomegranate_counter, fir_tree_counter);
    pomegranate = sub_sorting(pomegranate, pomegranate_counter, maple_counter);
}

void Service::output_results (int l_c_1, int l_k_2, int f_c_1, int f_c_2,
                              int m_c_1, int m_c_2, int p_c_1, int p_c_2) {
    sorting(l_c_1, l_k_2, f_c_1, f_c_2, m_c_1, m_c_2, p_c_1, p_c_2);

    std::string winner = "не дерево";
    if (lemon) {
        winner = "лимон";
    }
    if (fir_tree) {
        winner = "ель";
    }
    if (maple) {
        winner = "клён";
    }
    if (pomegranate) {
        winner = "гранат";
    }

    std::cout<<"Тест завершён."<<std::endl;
    std::cout<<"Оказалось, что вы "<<winner<<"..."<<std::endl;
}

void Service::output_greetings () {
    std::cout<<"Здравствуйте! Предлагаем вам пройти тест \"Какое вы дерево\"."<<std::endl;
}

void Service::output_question (std::string question) {
    number_of_question++;
    std::cout<<number_of_question<<". "<<question<<std::endl;
}

class Ans_f_key : public Service {
public:
    Ans_f_key();
    void test(std::string, std::string, std::string, std::string, std::string);
private:
    void input(std::string, std::string, std::string, std::string);
};

Ans_f_key::Ans_f_key() {

}

void Ans_f_key::input(std::string answ_lemon, std::string answ_fir_tree,
                      std::string answ_maple,std::string answ_pomegranate) {
    std::string answer = " ";
    std::cin>>answer;
    if (answer == answ_lemon) {
        lemon = true;
    }
    if (answer == answ_fir_tree) {
        fir_tree = true;
    }
    if (answer == answ_maple) {
        maple = true;
    }
    if (answer == answ_pomegranate) {
        pomegranate = true;
    }
    if (answer != answ_pomegranate && answer != answ_maple &&
        answer != answ_fir_tree && answer != answ_lemon) {
        std::cout<<"Ответ введён некорректно\n"<<std::endl;
    }

}

void Ans_f_key::test(std::string question, std::string answ_lemon, std::string answ_fir_tree,
                     std::string answ_maple,std::string answ_pomegranate) {
    output_question(question);
    input(answ_lemon, answ_fir_tree,
          answ_maple, answ_pomegranate);
    counter();
}

class Ans_to_choice : public Service {
public:
    Ans_to_choice();
    void test(std::string, int, int, int, int);
private:
    void input(int, int, int, int);
};

Ans_to_choice::Ans_to_choice() {

}

void Ans_to_choice::input(int answ_lemon, int answ_fir_tree,
                      int answ_maple,int answ_pomegranate) {
    int answer = 0;
    std::cin>>answer;
    if (answer == answ_lemon) {
        lemon = true;
    }
    if (answer == answ_fir_tree) {
        fir_tree = true;
    }
    if (answer == answ_maple) {
        maple = true;
    }
    if (answer == answ_pomegranate) {
        pomegranate = true;
    }
    if (answer != answ_pomegranate && answer != answ_maple &&
        answer != answ_fir_tree && answer != answ_lemon) {
        std::cout<<"Ответ введён некорректно"<<std::endl;
    }

}

void Ans_to_choice::test(std::string question, int answ_lemon, int answ_fir_tree,
                     int answ_maple, int answ_pomegranate) {
    output_question(question);
    input(answ_lemon, answ_fir_tree,
          answ_maple, answ_pomegranate);
    counter();
}

class User : public Service{
public:
    User();
    Ans_f_key ansFKey;
    Ans_to_choice ansToChoice;
};

User::User() {
}

int main() {

    Service service;
    Ans_f_key ansFKey;
    Ans_to_choice ansToChoice;
    User user;

    service.output_greetings();
    ansFKey.test("Кем вы хотите быть? (лимон/ель/клен/гранат)","гранат","лимон","ель","клен");
    ansFKey.test("Какое время года вам нравится больше всего? (весна/лето/зима/осень)",
                 "весна","зима","осень","лето");
    ansFKey.test("Выберите один из цветов: синий, красный, белый, коричневый",
                 "белый","синий","коричневый","красный");
    ansFKey.test("Какое ваше любимое животное? (собака/лиса/журавль/лягушка)",
                 "собака","лягушка","лиса","журавль");
    ansToChoice.test("Вас больше привлекает:\n1.) Рассвет\t2.) Закат\t3.) Лунное затмение"
                     "\t4.) Солнечное затмение", 3,2 , 1,4 );
    ansToChoice.test("Какое у вас обычно настроение?\n1.) Спокойное\t2.) Радостное\t"
                     "3.)Грустное\t4.)Никакое, вы просто спите",4,1,3,2);


    user.output_results(ansFKey.lemon_counter, ansToChoice.lemon_counter,
                        ansFKey.fir_tree_counter, ansToChoice.fir_tree_counter,
                        ansFKey.maple_counter, ansToChoice.maple_counter,
                        ansFKey.pomegranate_counter, ansToChoice.pomegranate_counter);

    return 0;
}
