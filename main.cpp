#include <iostream>
#include <thread>
#include <random>
#include <mutex>
#include <syncstream>

using namespace std;

const int countOfPhilosophers = 3;
random_device generator;
uniform_int_distribution<int> intDistribution;
mutex mtx[3];
int forks[3] = {};

class Philosophers {
  public:
    int id;


    void thinking() {
        int thinkingTime = intDistribution(generator) % 6 + 15;
        osyncstream (cout) << "Philosopher " << this->id << " started thinking." << endl;
        this_thread::sleep_for(chrono::seconds(thinkingTime));
        osyncstream (cout) << "Philosopher " << this->id << " finished thinking." << endl;
    }
    void eating() {
        int eatingTime = intDistribution(generator) % 6 + 10;
        osyncstream (cout) << "Philosopher " << this->id << " started eating." << endl;
        this_thread::sleep_for(chrono::seconds(eatingTime));
        osyncstream (cout) << "Philosopher " << this->id << " finished eating." << endl;
    }
    bool takeAFork(int forkNum) {
        if(mtx[forkNum - 1].try_lock()) {
            forks[forkNum - 1] = this->id;
            osyncstream (cout) << "Philosopher " << this->id << " take fork " << forkNum << "."  << endl;
            return true;
        }
        return false;
    }
    void takeForks() {
        int leftFork = this->id - 1;
        if (leftFork == 0) {
            leftFork = countOfPhilosophers;
        }
        int rightFork = this->id;
        bool isLeftTaken = false;
        bool isRightTaken = false;

        while (!isLeftTaken or !isRightTaken) {
            if (!isLeftTaken) {
                isLeftTaken = takeAFork(leftFork);
            }
            if (!isRightTaken) {
                isRightTaken = takeAFork(rightFork);
            }
            if ((isLeftTaken or isRightTaken) and (isLeftTaken != isRightTaken)) {
                int tryingTimes = intDistribution(generator) % 51 + 100;   // 5-10 seconds
                int notTakenFork;
                if (!isLeftTaken) {
                    notTakenFork = leftFork;
                }
                else {
                    notTakenFork = rightFork;
                }
                for (int i = 0; i < tryingTimes; i++) {
                    if (takeAFork(notTakenFork)) {
                        return;
                    }
                    this_thread::sleep_for(chrono::milliseconds(100));
                }
                if (notTakenFork != leftFork) {
                    putAFork(leftFork);
                    isLeftTaken = false;
                }
                else {
                    putAFork(rightFork);
                    isRightTaken = false;
                }
                this_thread::sleep_for(chrono::milliseconds(200));
            }
            this_thread::sleep_for(chrono::milliseconds(50));
        }
    }
    void putAFork(int forkNum) {
        forks[forkNum - 1] = 0;
        osyncstream (cout) << "Philosopher " << this->id << " put fork " << forkNum << "."  << endl;
        mtx[forkNum - 1].unlock();
    }
    void putForks() {
        int leftFork = this->id - 1;
        if (leftFork == 0) {
            leftFork = countOfPhilosophers;
        }
        int rightFork = this->id;
        putAFork(leftFork);
        putAFork(rightFork);
    }
};

void func(Philosophers ph) {
    while(1) {
        ph.thinking();
        ph.takeForks();
        ph.eating();
        ph.putForks();
    }
}

int main() {
    auto* threads = new jthread[countOfPhilosophers]{};
    for (int j = 1; j <= countOfPhilosophers; j++)
    {
        Philosophers ph {j};
        threads[j-1] = jthread{func, ph};
    }
    delete[] threads;
    return 0;
}
