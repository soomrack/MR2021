// Quest.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>
using namespace std;

int Glob_next_step = 0;
int First_room_toogle = 0;
bool First_treasure = false;
bool Second_treasure = false;
bool Main_treasure = false;
bool Rock = false;

class Room_Choise_two
{
public:

    void setMassages(string Rooms_first, string Rooms_second)
    {
        first_massage = Rooms_first;
        second_massage = Rooms_second;
    }

    void setDecision(string Rooms_first_out, string Rooms_second_out)
    {
        first_massage_approved = Rooms_first_out;
        second_massage_approved = Rooms_second_out;
    }
    
    int setMake_Choice(string title)
    {
        cout << title;
        cout << "\nChose your action\n";
        cout << first_massage;
        cout << second_massage;
        cin >> Choise;
        return Choise;
    }

    void getMake_Choise()
    {
        if (Choise == 1)
        {
            cout << first_massage_approved;
        }

        if (Choise == 2)
        {
            cout << second_massage_approved;
        }
    }


private:
    int Choise;
    string first_massage;
    string second_massage;
    string first_massage_approved;
    string second_massage_approved;
};

class Room_Choise_three
{
public:

    void setMassages(string Rooms_first, string Rooms_second, string Rooms_third)
    {
        first_massage = Rooms_first;
        second_massage = Rooms_second;
        third_massage = Rooms_third;
    }

    void setDecision(string Rooms_first_out, string Rooms_second_out, string Rooms_third_out)
    {
        first_massage_approved = Rooms_first_out;
        second_massage_approved = Rooms_second_out;
        third_massage_approved = Rooms_third_out;
    }

    int setMake_Choice(string title)
    {
        cout << title;
        cout << "\nChose your action\n";
        cout << first_massage;
        cout << second_massage;
        cout << third_massage;
        cin >> Choise;
        return Choise;
    }

    void getMake_Choise()
    {
        if (Choise == 1)
        {
            cout << first_massage_approved;
        }

        if (Choise == 2)
        {
            cout << second_massage_approved;
        }

        if (Choise == 2)
        {
            cout << third_massage_approved;
        }
    }


private:
    int Choise;
    string first_massage;
    string second_massage;
    string third_massage;
    string first_massage_approved;
    string second_massage_approved;
    string third_massage_approved;
};



void enter()
{
    string enter_title = "You are standing on the threshold of a new dungeon that has recently appeared in these lands.\n";
    string enter_first = "1 - You have decided to enter the dungeon.\n";
    string enter_second = "2 - You turned around and decided to leave this adventure for later.\n";
    string enter_first_out = "\nWell, then let's start the adventure.\n";
    string enter_second_out = "\nYou hear a strangely familiar voice. From somewhere you are sure that it belongs to a former demon hunter - \"You are not ready\" - he tells you.";

    Room_Choise_two objRoom_Choise_two;
    objRoom_Choise_two.setMassages(enter_first, enter_second);
    objRoom_Choise_two.setDecision(enter_first_out, enter_second_out);
    Glob_next_step = objRoom_Choise_two.setMake_Choice(enter_title);
    objRoom_Choise_two.getMake_Choise();
    
   
    if (Glob_next_step == 2)
    {
        exit (0);
    }

}

void First_Room()
{   
        string Froom_title = "\nHere it is - the first room of the new dungeon. In principle, nothing special - a little dusty, but what else to expect from the newly opened maze.\n";
        string Froom_first = "1 - Oh, and what is that lying in the dust in the far corner?\n";
        string Froom_second = "2 - Okay, let's go further - there is nothing here.\n";
        string Froom_third = "3 - Perhaps let's take a look around.\n";
        string Froom_out = "\nGreat, we continue the journey.\n";

        
        Room_Choise_three objRoom_Choise_three;
        objRoom_Choise_three.setMassages(Froom_first, Froom_second, Froom_third);
        objRoom_Choise_three.setDecision("", Froom_out, "");
        Glob_next_step = objRoom_Choise_three.setMake_Choice(Froom_title);
        objRoom_Choise_three.getMake_Choise();
}

void chest()
{
    if (Glob_next_step == 1)
    {
        string chest_title = "\nWow, it's a chest. Should you open it?\n";
        string chest_first = "1 - Of course, the treasures from the very beginning - hooray!\n";
        string chest_second = "2 - Heh, you can't fool me - there's probably some kind of trap there.\n";

        Room_Choise_two objRoom_Choise_two;
        objRoom_Choise_two.setMassages(chest_first, chest_second);
        //objRoom_Choise.setDecision(enter_first_out, enter_second_out);
        Glob_next_step = objRoom_Choise_two.setMake_Choice(chest_title);
        objRoom_Choise_two.getMake_Choise();
      
    }
}

void Look_around()
{
    string Look_around_title = "\nOh, the switch. Pull?\n";
    string Look_around_first = "1 - Yes, what's the worst that can happen?\n";
    string Look_around_second = "2 - It's better not to)\n";

    Room_Choise_two objRoom_Choise_two;
    objRoom_Choise_two.setMassages(Look_around_first, Look_around_second);
    //objRoom_Choise.setDecision(enter_first_out, enter_second_out);
    First_room_toogle = objRoom_Choise_two.setMake_Choice(Look_around_title);
    objRoom_Choise_two.getMake_Choise();

    if (First_room_toogle == 1)
    {
        cout << "\nYou hear a strange grinding noise.\n";
    }
    
}

void Poison_dead_end()
{
    cout << "\nAfter opening the chest, you hear a pop. After a second, you feel a sharp pain in your right shoulder. Looking more closely, you see a protruding needle with some liquid dripping from it. And that's the last thing you see....\n";
    cout << "\nYou failed, game over.\n";
    exit(0);
}

void Second_Room()
{
    string Sroom_title = "\nAfter a short walk along a dark corridor (in which, fortunately, there were no turns), you find yourself in a room filled with water.\n";
    string Sroom_first = "1 - What kind of traveler does not know how to swim. Forward, I see the next door.\n";
    string Sroom_second = "2 - Hmm, but water appears from somewhere... Let's check it out.\n";
    string Sroom_out = "\nAnd another room behind.\n";


    Room_Choise_two objRoom_Choise_two;
    objRoom_Choise_two.setMassages(Sroom_first, Sroom_second);
    objRoom_Choise_two.setDecision(Sroom_out, "");
    Glob_next_step = objRoom_Choise_two.setMake_Choice(Sroom_title);
    objRoom_Choise_two.getMake_Choise();
}

void WaterRock()
{
    string Rock_title = "\nIt was very difficult to look for something under the water, but in the end you found a recess into which a hand could fit. But is it worth it?\n";
    string Rock_first = "1 - Well, it's worth a shot.\n";
    string Rock_second = "2 - Oh, come on. You never know what might be there.\n";
    
    Room_Choise_two objRoom_Choise_two;
    objRoom_Choise_two.setMassages(Rock_first, Rock_second);
    Glob_next_step = objRoom_Choise_two.setMake_Choice(Rock_title);
    objRoom_Choise_two.getMake_Choise();

    Rock = true;
}

void Third_Room()
{
    string Troom_title = "\nAfter a half-hour walk (or so) you get into a fairly high room with a height of 3 people. In the center of the room there is a pillar on which something is clearly standing. Well, behind this pillar you can see a door with a picture of treasures. It looks like you are close to completing the path. That's just why there is this pillar?..\n";
    string Troom_first = "1 - What difference does it make - there it is, painted - treasures. Hurry there.\n";
    string Troom_second = "2 - Let's take a closer look...\n";
    string Troom_out = "\nFinally, the TREASURE.\n";


    Room_Choise_two objRoom_Choise_two;
    objRoom_Choise_two.setMassages(Troom_first, Troom_second);
    objRoom_Choise_two.setDecision(Troom_out, "");
    Glob_next_step = objRoom_Choise_two.setMake_Choice(Troom_title);
    objRoom_Choise_two.getMake_Choise();
}

void Pillar()
{
    string Pillar_title = "\nSomething glitters in the torchlight above. And if it glitters, then you need to pick it up). But how?\n";
    string Pillar_first = "1 - There, the treasures are waiting for me in the next room.\n";
    string Pillar_second = "2 - Let's try to climb. In the end, you can safely wrap your arms around this pillar.\n";
    string Pillar_third = "3 - Maybe we can throw something in there?\n";


    Room_Choise_three objRoom_Choise_three;
    objRoom_Choise_three.setMassages(Pillar_first, Pillar_second, Pillar_third);
    Glob_next_step = objRoom_Choise_three.setMake_Choice(Pillar_title);
    objRoom_Choise_three.getMake_Choise();
}

void Fall_dead_end()
{
    cout << "\nAfter all, you are a researcher. Therefore, you have no problems with climbing... But you did not take into account that the 6-meter pole is not designed to hold the human body. In the middle, you begin to feel wobbling, and when you almost reach the object at the top, the pillar finally loses its balance and you fall to the ground from a great height, and the pillar collapses on you... What a stupid ending....\n";
    cout << "\nYou failed, game over.\n";
    exit(0);
}

void sphinx_room()
{
    string Froom_title = "\nThe first thing you see when you enter the room is a sphinx lying on books and calmly leafing through them. Yes, damn it, it's really a sphinx... It's kind of scary. It looks like he noticed you too, and started talking: \"No one has visited me for a long time, little man.It even got boring somehow.We sphinxes are peaceful creatures, but we love riddles very much.A great remedy for boredom.But since you may well not have time for this, I'll give you a choice: I can send you outside right away, it's still the end of the dungeon.And I can make a riddle - if you guess, I will reward you with this scepter... But if you don't guess....\"\n";
    string Froom_first = "1 - You know, I don't want to take any chances. Let's part in peace.\n";
    string Froom_second = "2 - Let's try. I know a lot  -I'll answer the riddle somehow.\n";
    string Froom_third = "3 - Try to grab the scepter and rush to the exit.\n";


    Room_Choise_three objRoom_Choise_three;
    objRoom_Choise_three.setMassages(Froom_first, Froom_second, Froom_third);
    Glob_next_step = objRoom_Choise_three.setMake_Choice(Froom_title);
    objRoom_Choise_three.getMake_Choise();
}

void riddle()
{
    cout << "\nGood. Listen up : Every night I’m told what to do, and each morning I do what i’m told. But I still don’t escape your scold. Who am I?\n";
    string answer = "A";
    string answer_correct_one = "alarm_clock";
    string answer_correct_two = "Alarm_clock";
    string answer_correct_three = "Alarm_Clock";    

    cin >> answer;

    if ((answer_correct_one.compare(answer) == 0) || (answer_correct_two.compare(answer) == 0) || (answer_correct_three.compare(answer) == 0))
    {
        cout << "\nOh, you surprised me. Hold your scepter. Now get lost... And in the blink of an eye you find yourself again in front of the dungeon doors.\n";
        cout << "\nCongratulations, you have found a treasure.\n";
        Main_treasure = true;

    }
    if ((answer_correct_one.compare(answer) != 0) && (answer_correct_two.compare(answer) == 0) && (answer_correct_three.compare(answer) == 0))
    {
        cout << "\nWhat a pity. Well, you chose this path yourself. You feel that something is happening to you. Look at your hands and notice with horror that they are covered with gold. You look in horror at the sphinx and ... That's the last thing you remember.\n";
        cout << "\nYou failed, game over.\n";
        exit(0);
    }
}

void Gold_dead_end()
{
    cout << "\nAs soon as you touch the scepter, the sphinx makes a whistling sound. You feel that something is happening to you. Look at your hands and notice with horror that they are covered with gold. You look in horror at the sphinx and ... That's the last thing you remember.\n";
    cout << "\nYou failed, game over.\n";
    exit(0);
}

void Counting()
{
    cout << "Well, your journey is over.";
    if ((First_treasure == true) && (Second_treasure == true) && (Main_treasure == true))
    {
        cout << "\nYou managed to collect all the treasures: a strangely shaped orb from the pillar, a crown of dragons from the first room and the scepter of the sphinx.\n";
        cout << "\n100% passing. Hooray!\n";
        exit(0);
    }
    if (((First_treasure == true) && (Main_treasure == true) && (Second_treasure != true)) || ((Main_treasure == true) && (Second_treasure == true) && (First_treasure != true)))
    {
        cout << "\nNot bad, not bad. These things are worthy of going down into dangerous dungeons.\n";
        cout << "\n75% passing. Wow, god job.\n";
        exit(0);
    }
    if (((First_treasure == true) && (Second_treasure == true) && (Main_treasure != true)) || ((Main_treasure == true) && (First_treasure != true) && (Second_treasure != true)))
    {
        cout << "\nSomething tells you that the whole dungeon could bring you more treasures...\n";
        cout << "\n50% passing. Well done!\n";
        exit(0);
    }
    if (((Main_treasure != true) && (First_treasure == true) && (Second_treasure != true)) || ((Main_treasure != true) && (First_treasure != true) && (Second_treasure == true)))
    {
        cout << "\nWell, not empty-handed, and that's fine.\n";
        cout << "\n25% passing. Maybe you'll try again - here are the doors.\n";
        exit(0);
    }
    if ((Main_treasure != true) && (First_treasure != true) && (Second_treasure != true))
    {
        cout << "\nWhy did you just waste this time?\n";
        cout << "\n0% passing. Yeah... there's not even anything to say.\n";
        exit(0);
    }
}

int main()
{
    enter();

    if (Glob_next_step == 1)
    {
        FirstRoom:
        First_Room();        
        if (Glob_next_step == 1)
        {
            if (First_treasure == false)
            {
            chest();
                if (Glob_next_step == 1)
                {
                        if (First_room_toogle == 1)
                        {
                               First_treasure = true;
                               cout << "\nCongratulations, you have found a treasure.\n";
                               goto FirstRoom;
                        }
                        if ((First_room_toogle == 2) || (First_room_toogle == 0))
                            {
                                Poison_dead_end();
                            }
                }
            }
            if (First_treasure == true)
            {
                cout << "\nYou've already taken the item out of there.\n";
                goto FirstRoom;
            }
            
            if (Glob_next_step == 2)
            {
                goto FirstRoom;
            }
        }

        if (Glob_next_step == 3)
        {
            Look_around();
            goto FirstRoom;
        }
                       
    }
    
    if (Glob_next_step == 2)
    {
    SecondRoom:
        Second_Room();
        if ((Glob_next_step == 2) && (Rock == false))
        {
            WaterRock();
            cout << "\nNow you have the stone. Congratulations, or something... There aren't many of them around, so I had to get him out of there.\n";
            goto SecondRoom;
        }
        if ((Glob_next_step == 2) && (Rock == true))
        {
            cout << "\nYou've already taken the item out of there.\n";
            goto SecondRoom;
        }
    }
    
    if (Glob_next_step == 1)
    {
    ThirdRoom:
        Third_Room();
        cout << Second_treasure;
        if ((Glob_next_step == 2) && (Second_treasure == true))
        {
            cout << "\nYou've already taken the item out of there.\n";
            goto ThirdRoom;
        }
        if (Glob_next_step == 2)
        {
            Pillar:
            Pillar();
            if (Glob_next_step == 1)
            {
                goto ThirdRoom;
            }
            if (Glob_next_step == 2)
            {
                Fall_dead_end();
            }
            if (Glob_next_step == 3)
            {
                if (Rock == true)
                {
                    cout << "\nHow good that you found the stone recently. Thanks to the water in which he lay, his shape is ideal for throwing.\n";
                    Second_treasure = true;
                    cout << "\nCongratulations, you have found a treasure.\n";
                    goto ThirdRoom;
                }
                if (Rock == false)
                {
                    cout << "Eh, it's a pity that there is nothing. And don't even try to throw your backpack in there!";
                    goto Pillar;
                }
            }
        }
        

    }

    if (Glob_next_step == 1)
    {
        sphinx_room();
        if (Glob_next_step == 1)
        {
            cout << "\nIt's a pity, of course, but I understand. Goodbye, says the sphinx, and in the blink of an eye you find yourself again in front of the dungeon doors.\n";
        }
        if (Glob_next_step == 2)
        {
            riddle();
        }
        if (Glob_next_step == 3)
        {
            Gold_dead_end();
        }
    }

    Counting();

    return 0;
}

