#include <random>
#include <iostream>
#include <string>
#include <tuple>
using namespace std;

class BullsAndCows {

public:

    vector<bool> myArray;

    BullsAndCows() : myArray(9000, true) {
        generateNumber = generateNum();
        for (int i = 0; i < 9000; i++) {
            int num = i + 1000;
            if (checkNumber(num) == false) {
                myArray[i] = false;
            }
        }
    }

    bool playFirstGame(int i) {
        string userNum;
        while (true) {
            cout << i + 1 << ") ";
            cin >> userNum;
            if (userNum.size() == 4) {
                if (checkNumber(stoi(userNum)) == true) {
                break;
                }
                else {
                    cout << "\033[31m" << "Вы ввели некорректное число" << "\033[0m" << endl;
                }
            }
            else {
                cout << "\033[31m" << "Вы ввели некорректное число" << "\033[0m" << endl;
            }
            
        }
        
        tuple<int, int> bullsAndCowsTuple = bullsAndCowsCounter(generateNumber, userNum);
        int bulls = get<0>(bullsAndCowsTuple);
        int cows = get<1>(bullsAndCowsTuple);
        cout << "Коровы: " << cows << " Быки: " << bulls << endl;
        if (bulls == 4) {
            return true;
        }
        if (i == 9 && bulls != 4) {
            cout << "Неудача, было загадано число " << generateNumber;
        }
        return false;
    }




    tuple<bool, int> playSecondGame(int i) {
        int choiсe = 9;
        int bulls = 0;
        int cows = 0;

        for (int j = 0; j < 9000; j++) {

            if (myArray[j] == true) {
                choiсe = j;
                break;
            }
        }
        if (choiсe == 9) {
            cout << "\033[31m" << "Похоже, где-то вы ошиблись с количеством быков и коров" << "\033[0m" << endl;
            return make_tuple(true, -1);
        }
        cout << i + 1 << ") " << 1000 + choiсe << endl;
        cout << "Количество коров: ";
        cin >> cows;
        cout << "Количество быков: ";
        cin >> bulls;
        if (bulls == 4) {
            cout << "Было загадано число " << 1000 + choiсe << endl;
            return make_tuple(true, 0);
        }
        for (int j = 0; j < 9000; j++) {

            if (j == choiсe) {
                myArray[j] = false;
            }
            if (myArray[j] == true) {
                tuple<int, int> bullsAndCowsTuple= bullsAndCowsCounter(to_string(1000 + choiсe), to_string(1000 + j));
                int count_bulls = get<0>(bullsAndCowsTuple);
                int count_cows = get<1>(bullsAndCowsTuple);
                if ((count_cows != cows) || (count_bulls != bulls)) {
                    myArray[j] = false;
                }
            }
        }
        return make_tuple(false, 0);
       
    }
    void playThirdGame() {
        bool flag = false;
        for (int i = 0; i < 10; i++) {
            cout << "Вы угадываете число:" << endl;
            bool firstResult = playFirstGame(i);
            cout << "Бот угадывает число:" << endl;
            tuple<bool, int> secondResult = playSecondGame(i);
            bool res = get<0>(secondResult);
            int num = get<1>(secondResult);

            if (firstResult == true && res == true && num != -1) {
                cout << "Ничья";
                flag = true;
                break;
            }
            if (firstResult == true && res == false) {
                cout << "Вы выиграли";
                flag = true;
                break;
            }
            if (firstResult == false && res == true && num != -1) {
                cout << "Бот выиграл";
                flag = true;
                break;
            }
            if (num == -1){
                flag = true;
                break;
            }
        }
        if (flag == false) {
            cout << "Ничья";
        }

    }



private:

    tuple<int, int> bullsAndCowsCounter(string mainNumber, string iteratedNumber) {
        int bullsCounter = 0;
        int cowsCounter = 0;
        for (int i = 0; i < 4; i++) {
            if (iteratedNumber[i] == mainNumber[i]) {
                bullsCounter += 1;
            }
            else {
                if (mainNumber.find_first_of(iteratedNumber[i]) != string::npos) {
                    cowsCounter += 1;
                }
            }
        }
        return make_tuple(bullsCounter, cowsCounter);

    }


    bool checkNumber(int num) {
        string number = to_string(num);
        int count = 0;
        for (char x : number) {
            for (int j = 0; j < 4; j++) {
                if (number[j] == x) {
                    count += 1;
                }
            }
        }
        if (count != 4) {
            return false;
        }
        return true;

    }

    string generateNumber;

    string generateNum() {
        string randomNumber;
        while (true) {
            random_device rd;
            mt19937 gen(rd());
            uniform_int_distribution<> dis(1000, 9999);
            randomNumber = to_string(dis(gen));
            bool flag = false;
            int count = 0;
            for (char x : randomNumber) {
                for (int i = 0; i < 4; i++) {
                    if (randomNumber[i] == x) {
                        count += 1;
                    }
                }
            }
            if (count == 4) {
                break;
            }
        }
        return randomNumber;
    }
};


int main()
{
    setlocale(LC_ALL, "Russian");
    cout << "БЫКИ И КОРОВЫ" << endl << endl;
    cout << "Выберите режим игры:" << endl;
    cout << "   1. Бот загадывает число, вы отгадываете." << endl;
    cout << "   2. Вы загадываете число, бот отгадывает." << endl;
    cout << "   3. Игра с ботом на скорость" << endl << endl;
    BullsAndCows game;
    int num;
    cin >> num;
    bool flag = false;
    switch (num)
    {
    case 1:
        for (int i = 0; i < 10; i++) {
            bool result = game.playFirstGame(i);
            if (result == true) {
                cout << "Победа" << endl;
                break;
            }
        }
        break;


    case 2:
        for (int i = 0; i < 10; i++) {
            tuple<bool, int> secondResult = game.playSecondGame(i);
            bool res = get<0>(secondResult);
            int num = get<1>(secondResult);
            if (res == true) {
                flag = true;
                break;
            }
        }
        if (flag == false) {
            cout << "Неудача" << endl;
        }
        break;

    case 3:
        game.playThirdGame();
        break;

    default:
        break;
    }
    
}
