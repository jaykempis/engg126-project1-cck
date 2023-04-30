//https://www.modernescpp.com/index.php/dining-philiosophers-problem-i
// dp_5.cpp
#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>

int myrand(int min, int max) {
  return rand()%(max-min)+min;
}

void lock(std::atomic<int>& m) {
  while (m)
    ; // busy waiting
  m=1;
}

void unlock(std::atomic<int>& m) {
  m=0;
}

void phil(int ph, std::atomic<int>& ma, std::atomic<int>& mb) {
  while(true) {
    int duration=myrand(1000, 2000);
    std::cout<<ph<<" thinks for "<<duration<<" ms\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(duration));

    lock(ma);
    std::cout<<ph<<" got first chopstick\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    lock(mb);
    std::cout<<ph<<" got second chopstick\n";

    duration=myrand(1000, 2000);
    std::cout<<ph<<" eats for "<<duration<<" ms\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(duration));

    unlock(mb);
    unlock(ma);
  }
}

int main() {
  std::cout<<"dp_5\n";
  srand(time(nullptr));

  std::atomic<int> m1{0}, m2{0}, m3{0}, m4{0}, m5{0};

  std::thread t1([&] {phil(1, m1, m2);});
  std::thread t2([&] {phil(2, m2, m3);});
  std::thread t3([&] {phil(3, m3, m4);});
  std::thread t4([&] {phil(4, m4, m5);});
  std::thread t5([&] {phil(5, m1, m5);});

  t1.join();
  t2.join();
  t3.join();
  t4.join();
  t5.join();
}


//https://cppsecrets.com/users/60226869466583727773846564717765737646677977/C00-DINING-PHILOSOPHERS-PROBLEM.php
/*#include <iostream>
#include <mutex>
#include <thread>

using namespace std;

int main()
{
    const int no_of_philosophers = 5;
    
    struct Chopstics
    {
    public:
        Chopstics(){;}
        std::mutex mu;
    };
    
    auto eat = [](Chopstics &left_chopstics, Chopstics& right_chopstics, int philosopher_number) {
        
        std::unique_lock<std::mutex> llock(left_chopstics.mu);
        std::unique_lock<std::mutex> rlock(right_chopstics.mu);
        
        cout << "Philosopher " << philosopher_number << " is eating" << endl;
        
        std::chrono::milliseconds timeout(1500);
        std::this_thread::sleep_for(timeout);
        
        cout << "Philosopher " << philosopher_number << " has finished eating" << endl;
    };
    
    //create chopstics
    Chopstics chp[no_of_philosophers];
    
    //create philosophers
    std::thread philosopher[no_of_philosophers];
    
    //Philosophers Start reading
    cout << "Philosopher " << (0+1) << " is thinking.." << endl;
    philosopher[0] = std::thread(eat, std::ref(chp[0]), std::ref(chp[no_of_philosophers-1]), (0+1));
    
    for(int i = 1; i < no_of_philosophers; ++i) {
        cout << "Philosopher " << (i+1) << " is thinking.." << endl;
        philosopher[i] = std::thread(eat, std::ref(chp[i]), std::ref(chp[i-1]), (i+1));
    }
    
    for(auto &ph: philosopher) {
        ph.join();
    }
    
    return 0;
}
*/