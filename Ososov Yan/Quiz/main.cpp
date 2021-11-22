#include <iostream>
#include <string>
using namespace std;

 class Player{
 public:
    void Name_input();
    string input_answer;
    void answering();
    void increase_points( int result);
    void showing_result();
 private:
    int points = 0;
    string Name;
 };
 Player Player1;

 class Question{
 public:
     Question( string specific_label, string specific_content, string specific_right_answer, int specific_task_value){
         label =  specific_label;
         content = specific_content;
         right_answer = specific_right_answer;
         task_value = specific_task_value;
     };
     void Marking();
     void Print_answer();
 private:
     string label;
     string content;
     string right_answer;
     int task_value;
 };
 void Introduction(){
     cout << "Hello! This is a test on topic Python programming. In order to start "
             "this test please text your name" << endl;
 }

 void Player::Name_input(){
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
         cout << "\nIt's awful result. You have to work hard to improve your knowledge! " << endl;
     } else{
         if (points <= 8){
             cout << "\nYou are somewhere in the midl. It is good result and if you make some effort you'll have a perfect result! " << endl;
         } else {
             if ( points == 9){
                 cout << "\nIt's perfect result. You are actually pointed on your goal! " << endl;
             } else{
                 if ( points == 10){
                     cout << "\nIt's awesome! Your result higher then mine! You should proud by your self " << endl;
                 }
             }
         }
     }


 }
void Question::Print_answer(){
     cout << label << content << endl;
 }

 void Question::Marking() {
     int result = 0;
     if (right_answer == Player1.input_answer){
         result = 1 * task_value;
     }
     Player1.increase_points(result);
 }


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

 int main() {
    Introduction();
    Player1.Name_input();

    first.Print_answer();
    Player1.answering();
    first.Marking();

    second.Print_answer();
    Player1.answering();
    second.Marking();

    third.Print_answer();
    Player1.answering();
    third.Marking();

    fourth.Print_answer();
    Player1.answering();
    fourth.Marking();

    fifth.Print_answer();
    Player1.answering();
    fifth.Marking();

    sixth.Print_answer();
    Player1.answering();
    sixth.Marking();

    Player1.showing_result();
    return 0;
 }
