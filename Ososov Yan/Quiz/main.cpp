#include <iostream>
#include <string>
using namespace std;

 class Player{
 public:
     string input_answer;
 private:
     int points;
    string Name;
 public:
     void name_input();
     void answering();
     void increase_points( int result);
     void showing_result();
     Player();
 };
Player::Player(){
    points =0;
};
 class Question{
 private:
     string label;
     string content;
     string right_answer;
     int task_value;
 public:
     Question(string specific_label, string specific_content, string specific_right_answer, int specific_task_value);
     int marking(string input_answer);
     void print_answer();
 };

 Question::Question(string specific_label, string specific_content, string specific_right_answer, int specific_task_value){
     label =  specific_label;
     content = specific_content;
     right_answer = specific_right_answer;
     task_value = specific_task_value;
 }

 void introduction(){
     cout << "Hello! This is a test on topic Python programming. In order to start "
             "this test please text your name" << endl;
 }

 void Player::name_input(){
    cin>>Name;
 }

 void Player::increase_points(int result){
     points = points + result;
 }
 void Player::answering(){
     cin >> input_answer;
 }
 void Player::showing_result(){
     cout << Name << ", You've passed this test with a score " << points << " out of 10. " << endl;
     if (points <= 5){
         cout << "It's awful result. You have to work hard to improve your knowledge! " << endl;
         return;
     }
     if (points <= 8){
         cout << "You are somewhere in the midl. It is good result and if you make some effort you'll have a perfect result! " << endl;
         return;
     }
     if ( points == 9){
         cout << "It's perfect result. You are actually pointed on your goal! " << endl;
         return;
     }
     if ( points == 10){
         cout << "It's awesome! Your result higher then mine! You should proud by your self " << endl;
         return;
     }
 }
void Question::print_answer(){
     cout << label << content << endl;
 }

 int Question::marking(string input_answer) {
     int result = 0;
     if (right_answer == input_answer){
         result = 1 * task_value;
     }
     return result;
 }

void quiz_content(){
    Player User;
    Question first("The first question.","\nWhat attributes of the model field should be set to True "
                                         "\nso that this field can be empty in the database table,and the form in adding data"
                                         "\nto the database table was optional?"
                                         "\nOne or more correct answers are allowed. "
                                         "\nYou have to text the sequences of symbols in alphabet sequence below."
                                         "\n a) null"
                                         "\n b) default"
                                         "\n c) blank"
                                         "\n d) on_delete" ,
                   "ac", 2 );


    Question second("\nThe second question.","\nDjango (Python) built-in DBMS working with a database"
                                             "\nYou have to text the its name below.","SQLite", 3 );

    Question third(" \nThe third question.","\nAll fields for communication between models have one "
                                            "\nrequired parameter - the name of the primary model "
                                            "\nYou have to text is this statement true or false below.",
                   "true", 1 );

    Question fourth("\nThe fourth question.","\nYou cannot filter data by a field that defines "
                                             "\na one-to-many relationship from another model "
                                             "\nYou have to text is this statement true or false below.",
                    "false", 1 );

    Question fifth("\nThe fifth question.","\nIn the following code, the primary model name is:"
                                           "\nb_genre = Book.objects.filter(genre__name__icontains=“fiction”)"
                                           "\nYou have to text the suitable symbol below."
                                           "\n a) genre"
                                           "\n b) name"
                                           "\n c) icotains"
                                           "\n d) fiction" , "b", 1 );

    Question sixth("\nThe sixth question.","\nWhat attributes of the model field should be set to True "
                                           "\nso that this field can be empty in the database table,and the form in adding data"
                                           "\nto the database table was optional?"
                                           "\nOne or more correct answers are allowed. "
                                           "\nYou have to text the sequences of symbols in alphabet sequence below."
                                           "\n a) fields"
                                           "\n b) models.py"
                                           "\n c) metadata"
                                           "\n d) methods"
                                           "\n e) objects" ,
                   "acd", 2 );
    introduction();
    User.name_input();

    first.print_answer();
    User.answering();
    User.increase_points(first.marking( User.input_answer ));
    second.print_answer();
    User.answering();
    User.increase_points(second.marking( User.input_answer ));
    third.print_answer();
    User.answering();
    User.increase_points(third.marking( User.input_answer ));
    fourth.print_answer();
    User.answering();
    User.increase_points(fourth.marking( User.input_answer ));
    fifth.print_answer();
    User.answering();
    User.increase_points(fifth.marking( User.input_answer ));
    sixth.print_answer();
    User.answering();
    User.increase_points(sixth.marking( User.input_answer ));

    User.showing_result();
 }


 int main() {
     quiz_content();
    return 0;
 }
