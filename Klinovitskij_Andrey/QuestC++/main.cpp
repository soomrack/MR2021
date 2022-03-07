#include <iostream>

using namespace std;

class Character {
public:
    int DMG;
    int DEF;
    int HP;
    int EXP;

    Character();

    void increase_HP(int points) {
        HP += points;
    };

    void increase_DMG(int points) {
        DMG += points;
    };

    void increase_DEF(int points) {
        DEF += points;
    };

    void increase_EXP(int points) {
        EXP += points;
    };

};

Character::Character() {
    DMG = 1;
    DEF = 1;
    HP = 10;
    EXP = 0;
}


class Monster {
public:
    char Name;
    int DMG;
    int DEF;
    int HP;

    Monster();

    void increase_HP(int points) {
        HP += points;
    };

    void increase_DMG(int points) {
        DMG += points;
    };
};

Monster::Monster() {
    DMG = 7;
    DEF = 4;
    HP = 67;
}


int main() {
    Character Paladin;
    Monster Beholder;
    int skillpoints = 10;
    int choose = 0, count = 0, checkTrue = false;
    string direction;
    string attack;
    cout << "Greetings, traveler!\n"
            "You have 10 skill points to allocate to attack, defense and HP. \n"
            "Each point you spend on attack will increase your skill, "
            "each point you spend on defense will lower your damage, "
            "and each point you spend on HP will increase your life force by 10.\n";
    while (skillpoints > 0) {
        cout << "You have " << skillpoints << " skill points left. Choose wisely:\n";
        cout << " 1 - Increase attack;\n 2 - Increase defence;\n 3 - Increase health points;\n";
        cin >> choose;
        cout << "How many points do you wish to spend?\n";
        cin >> count;
        if (count <= skillpoints) {
            skillpoints -= count;
            switch (choose) {
                case 1:
                    Paladin.increase_DMG(count);
                    break;
                case 2:
                    Paladin.increase_DEF(count);
                    break;
                case 3:
                    Paladin.increase_HP(count * 10);
                    break;
                default:
                    cout << "\nYou made a mistake, enter the value again\n\n";
                    break;
            }
        } else {
            cout << "\nYou made a mistake, enter the value again! Don't cheat.\n\n";
        }
    }

    cout << "Great! Your stats:\n ATK: " << Paladin.DMG << "\n DEF: " << Paladin.DEF << "\n HP: " << Paladin.HP << endl;

    while (checkTrue == false) {
        cout << "\n\nYou're off on an adventure, sure of your abilities!\n"
                "You decided to fight evil and immediately chose to go to the tomb, in search of the undead.\n"
                "As you approach the fork in the road, you can choose your direction. North, East or West. \n"
                "Where will you go?\n";
        cin >> direction; //It's do nothing))
        if (direction == "East" || direction == "North" || direction == "West" ||
            direction == "east" || direction == "north" || direction == "west") {
            checkTrue = true;
            cout << "\n\nYou went " << direction << " and ended up in a cave. \n"
                                                    "As soon as you entered, the ceiling collapsed, blocking the exit.\n"
                                                    "Now all you have to do is walk forward.\n"
                                                    "After walking a short distance, you see a sleeping Beholder, but you're a hero, \n"
                                                    "you challenge him to a duel! Of course, he didn't understand anything, but he woke up. \n"
                                                    "The battle begins!\n";
        }
    }

    while (Paladin.HP > 0 && Beholder.HP > 0) {
        cout << "\n\nYour HP:" << Paladin.HP <<
             "\nBeholder HP: " << Beholder.HP << endl;
        cout << "Your move! What do you wish to do? Attack or Counterattack?\n";
        cin >> attack;
        if (attack == "attack" || attack == "Counterattack" || attack == "Attack" || attack == "counterattack") {
            if (attack == "attack" || attack == "Attack") {
                Beholder.increase_HP(-(Paladin.DMG - (Beholder.DEF / 3)));
                cout << "\nBYou swing your sword at Beholder. Perhaps you were able to damage him\n";
            } else {
                if (Paladin.DMG > Beholder.DEF)
                    Beholder.increase_HP(-(Paladin.DMG - (Beholder.DEF)));
                Paladin.increase_DEF(1);
                cout << "\nWhen Beholder almost attacked you, you dodged and gave a weak, stabbing attack on his eye. \n"
                           "You feel that you have become more defensive\n";
            }
            if (rand() % 3 + 1 + Beholder.DMG - Paladin.DEF * 2 / 3) {
                cout << "\nBeholder move! It does " << rand() % 3 + 1 + Beholder.DMG - Paladin.DEF * 2 / 3
                     << " damage to you";
                Paladin.increase_HP(-(rand() % 3 + 1 + Beholder.DMG - Paladin.DEF * 2 / 3));
            } else {
                cout << "\nBeholder couldn't damage you, you defended yourself too much. He's furious!\n";
                Beholder.increase_HP(-3);
                Beholder.increase_DMG(1);
            }
        } else cout << "\n\nTry again\n";
    }

    if (Paladin.HP < 0) {
        cout << "\n\nDon't feel bad, but you're dead.\n"
                "It's no surprise, you went level one on Beholder!\n"
                "You'll be more careful next time.\n";
    } else
        cout << "\n\nI don't know how you did it.\n"
                "It wasn't killable.\n"
                "But congratulations!\n";

    return 0;
}
