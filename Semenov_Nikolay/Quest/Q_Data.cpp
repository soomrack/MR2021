#include "Q_Data.h"

A_Quest init_quest() {
    Q_Ticket ticket1;
    ticket1.add_question("Which of the US presidents wrote his own story about Sherlock Holmes?");
    ticket1.add_answer("John Kennedy", false);
    ticket1.add_answer("Franklin Roosevelt", true);
    ticket1.add_answer("Ronald Reagan",false);
    Q_Ticket ticket2;
    ticket2.add_question("What is the longest river in the world?");
    ticket2.add_answer("Amazon", true);
    ticket2.add_answer("Nile", false);
    ticket2.add_answer("Lena", false);
    Q_Ticket ticket3;
    ticket3.add_question("What duty was introduced in the XII century in England in order to force men to go to war?");
    ticket3.add_answer("Tax on parasitism", false);
    ticket3.add_answer("The cowardice tax", true);
    ticket3.add_answer("Tax on the absence of boots", false);
    Q_Ticket ticket4;
    ticket4.add_question("Where did the expression \"money does not smell?\"?");
    ticket4.add_answer("From the tax on toilets", true);
    ticket4.add_answer("From the givers for the transportation of perfumes", false);
    ticket4.add_answer("From the fees for unwashed socks", false);
    Q_Ticket ticket5;
    ticket5.add_question("How many planets are there in the solar system?");
    ticket5.add_answer("7", false);
    ticket5.add_answer("8", true);
    ticket5.add_answer("9", false);

    A_Quest quest;
    quest.add_ticket(ticket1);
    quest.add_ticket(ticket2);
    quest.add_ticket(ticket3);
    quest.add_ticket(ticket4);
    quest.add_ticket(ticket5);
    return quest;
}
