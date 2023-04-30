//ENGG 126: Project 3
// Carson, Castro & Kempis

#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>
#include <string>
#include <sstream>

#define n 5

using namespace std;

int myrand(int min, int max) 
{
  return rand()%(max-min)+min;
}

void lock(atomic<int>& m) 
{
  while (m)
    ; // busy waiting
  m=1;
}

void unlock(atomic<int>& m) 
{
  m=0;
}

struct philosp{
    int state = 0;
    int eat = 0;
}Philostatus[n];

void helpCMD ()
{
  cout<<"\nLists of possible commands: \n"
      <<"* r            - show report on the philosophers \n"
      <<"* exit            - closes the program"<<endl;
}

void phil(int ph, atomic<int>& ma, atomic<int>& mb) {
  bool run = true;
  while(run) {

    //philosopaher states
    //1 = thinking, 2 = has first chopstick, 3 = has second chopstick, 4 = eating

    int duration=myrand(1000, 2000);
    //cout<<ph<<" is thinking for "<<duration<<" ms\n";
    Philostatus[ph].state = 1;
    this_thread::sleep_for(chrono::milliseconds(duration));

    lock(ma);
    //cout<<ph<<" got first chopstick\n";
    Philostatus[ph].state = 2;
    this_thread::sleep_for(std::chrono::milliseconds(1000));

    lock(mb);
    //cout<<ph<<" got second chopstick\n";
    Philostatus[ph].state = 3;

    duration=myrand(1000, 2000);
    //cout<<ph<<" is eating for "<<duration<<" ms\n";
    Philostatus[ph].eat += 1;
    Philostatus[ph].state = 4;
    //cout << "Philosopher " << ph << " has eaten " << Philostatus[ph].eat << " times..." << endl;
    
    this_thread::sleep_for(std::chrono::milliseconds(duration));

    unlock(mb);
    unlock(ma);

  }
}

void showReport(string cmd)
{
  while(true)
  {
    string cmdline;
    cout << "\n[CMD]: " << endl;
    cin >> cmd;

    if (cmd == "r")
    {
      cout << "\n======State======: " << endl;    
      for (int i=1; i <=5; i++)
      {
        if (Philostatus[i].state == 1)
        {
          cout << "Philosopher " << i << " is thinking..." << endl;
        }
        else if (Philostatus[i].state == 2)
        {
          cout << "Philosopher " << i << " has the first chopstick..." << endl;
        }
        else if (Philostatus[i].state == 3)
        {
          cout << "Philosopher " << i << " has the second chopstick..." << endl;
        }
        else if (Philostatus[i].state == 4)
        {
          cout << "Philosopher " << i << " is eating..." << endl;
        }
      }

      cout << "\n======Plates======: " << endl; 
      for (int i=1; i <=5; i++) cout << "Philosopher " << i << " has eaten " << Philostatus[i].eat << " times..." << endl;
      //cout << "Philosopher 1 has eaten " << Philostatus[0].eat << " times" << endl;
    }
    else if(cmd == "exit") exit(0);
    else cout << "This Command is not recognized" << endl;
  }

}

int main() {
  cout<<"======Dining Philosophers======\n";
  srand(time(nullptr));

  atomic<int> m1{0}, m2{0}, m3{0}, m4{0}, m5{0};

  string start, cmd;
  cout << "Begin Dinner? (Y/N): ";
  cin >> start;


  if (start == "Y" || start == "y")
  {

    cout << "Dinner Has Begun " << endl;

    thread t1([&] {phil(1, m1, m2);});
    thread t2([&] {phil(2, m2, m3);});
    thread t3([&] {phil(3, m3, m4);});
    thread t4([&] {phil(4, m4, m5);});
    thread t5([&] {phil(5, m1, m5);});

    //thread for user commands
    thread report([&] {showReport(cmd);});

    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    report.join();

  }
  else if(start == "N" || start == "n") exit(0);
  else cout << "This Command is not recognized" << endl;
  
}
