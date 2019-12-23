#include <iostream>
#include <thread>
#include <vector>
#include <assert.h>

#define N 3
#define K 2

bool phase_1[N]; // stands for b in the paper
bool phase_2[N]; // stands for c in the paper
int current = K; // stands for k in the paper

int protect;

void f(int this_thread_num) // this_thread_num stands for i in the paper
{
#ifdef __linux
    std::cout << "Thread #" << this_thread_num << ": on CPU " << sched_getcpu() << "\n";
#endif
    while (true)
    {
        //try lock
        phase_1[this_thread_num] = true;

    Li1:
        if (current != this_thread_num)
        {
            phase_2[this_thread_num] = false;
            if (!phase_1[current])
                current = this_thread_num;
            goto Li1;
        }
        phase_2[this_thread_num] = true;
        for (int j = 0; j < N; j++)
            if (j != this_thread_num && phase_2[j])
                goto Li1;
        //got lock

        //冲突区
        protect = this_thread_num;
        assert(protect == this_thread_num);

        //unlock
        phase_2[this_thread_num] = false;
        phase_1[this_thread_num] = false;
    }
}

int main(int argc, char *argv[])
{
    std::vector<std::thread> threads;
    for (int i = 0; i < N; ++i)
        threads.push_back(std::thread(f, i));

    for (auto &t : threads)
        t.join();

    return 0;
}
