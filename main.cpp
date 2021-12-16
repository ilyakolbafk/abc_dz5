#include <iostream>
#include <thread>
#include <string>
#include <mutex>
#include <random>
#include <climits>

using namespace std;

int female = -1, male = -1, lastRoom = -1, counter = 0;
mutex mut;

char *singles = new char[10];
pair<char, char> *doubles = new pair<char, char>[15];

int to_double_room(char chel) {
    int last, opp;
    char client;
    if (chel == 'G') {
        last = male;
        opp = female;
        client = 'G';
    } else {
        last = female;
        opp = male;
        client = 'L';
    }

    if (last != -1) {
        if (doubles[last].second == 'x')
            doubles[last].second = client;
        else {
            last++;
            while (doubles[last].second != 'x' || last == opp)
                last++;
            doubles[last].first = client;
        }
    } else {
        last++;
        while (doubles[last].second != 'x' || last == opp)
            last++;
        doubles[last].first = client;
    }

    return last;
}

void single_room(const string &person) {
    if (lastRoom >= 9) {
        mut.lock();
        counter++;
        mut.unlock();
        cout << "There are no free rooms. " << person <<
             " have to go away and find another place to sleep ";
        cout << "(Thread id_" << this_thread::get_id() << ")\n";
        return;
    }
    mut.lock();
    if (person == "Gentleman")
        singles[++lastRoom] = 'G';
    else
        singles[++lastRoom] = 'L';
    mut.unlock();

    cout << person << " settled into a single room " << lastRoom + 1 <<
         "! (Thread id_" << this_thread::get_id() << ")\n";
}

void double_room(const string &person) {
    mut.lock();
    if (person == "Gentleman")
        male = to_double_room('G');
    else
        female = to_double_room('L');
    mut.unlock();

    cout << person << " settled into a double room " << (person == "Gentleman" ? male + 1 : female + 1) <<
         "! (Thread id_" << this_thread::get_id() << ")\n";
}

void reception(const string &person) {
    cout << person + " wants to book a room. ";
    int lastCurrent, opposite;

    if (person[0] != 'L') {
        lastCurrent = male;
        opposite = female;
    } else {
        lastCurrent = female;
        opposite = male;
    }

    if (lastCurrent < 15 && (doubles[14].second == 'x' &&
                             opposite != 14 || doubles[lastCurrent].second == 'x'))
        double_room(person);
    else
        single_room(person);
}

int parse() {
    int vis;
    string n;
    while (true) {
        cout << "Input visitors count:\n";
        cin >> vis;
        if (vis == 0) {
            cin.clear();
            cin >> n;
            cout << "\nInvalid input\n";
        } else if (vis < 0) {
            cout << "\nNegative number is entered\n";
        } else if (vis > 10000) {
            cout << "\nEnter a number less than 10000\n";
        } else {
            return vis;
        }
    }
}

int main() {
    cout << "Hotel is empty now.\n\n";
    for (int i = 0; i < 10; ++i)
        singles[i] = 'x';

    for (int i = 0; i < 15; ++i)
        doubles[i] = {'x', 'x'};

    // заполняем рандомными полами
    random_device rnd;
    mt19937 rng(rnd());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(0, 10);
    int vis = parse();

    for (int i = 0; i < vis; ++i) {
        auto t = new thread(reception, dist6(rng) % 2 ? "Lady" : "Gentleman");
        t->join();
    }

    // показываем содержимое отеля
    cout << "\nSingle rooms\n";
    for (int i = 0; i < 10; i++) {
        cout << "| " << singles[i] << " ";
    }
    cout << "\n\n";
    cout << "Double rooms\n";
    for (int i = 0; i < 15; i++) {
        cout << "| " << doubles[i].first << '_' << doubles[i].second << ' ';
    }
    cout << "\n\n";
    if (counter == 0)
        cout << "There was enough room for everyone\n";
    else
        cout << "We did not manage to cater " << counter << " visitors.\n";

    return 0;
}

