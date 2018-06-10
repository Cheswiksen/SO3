#include <ncurses.h>
#include <unistd.h>
#include <thread>
#include <mutex>
#include <condition_variable>
#define A 20
std::mutex m;
std::mutex mu;
std::condition_variable cv[5];
std::condition_variable shop;
int shops[4];
bool Bshops[4];
int road[4];
int roadHome[4];
int roadHome2[4];
int Que[5];
int kasa = 0;

void bigThread(int name)
{
    std::unique_lock<std::mutex> lk1(m);
    cv[0].wait(lk1);
    Que[0] = name;
    lk1.unlock();

    std::unique_lock<std::mutex> lk2(m);
    cv[1].wait(lk2);
    Que[0] = 0;
	Que[1] = name;
    lk2.unlock();
    cv[0].notify_one();

    std::unique_lock<std::mutex> lk3(m);
    cv[2].wait(lk3);
    Que[1] = 0;
	Que[2] = name;
    lk3.unlock();
    cv[1].notify_one();

    std::unique_lock<std::mutex> lk4(m);
    cv[3].wait(lk4);
    Que[2] = 0;
	Que[3] = name;
    lk4.unlock();
    cv[2].notify_one();

    std::unique_lock<std::mutex> lk5(m);
    cv[4].wait(lk5);
    Que[3] = 0;
	Que[4] = name;
    lk5.unlock();
    cv[3].notify_one();


    while(true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(900));
        for(int i=0; i<4;i++)
        {
            if(Bshops[i]==0)
            {
                mu.lock();                
                Que[4] = 0;
                Bshops[i] = 1;
                road[i] = name;
                mu.unlock();
                std::this_thread::sleep_for(std::chrono::milliseconds(900));
                mu.lock();
                road[i] = 0;
                shops[i] = name;
                mu.unlock();
                std::this_thread::sleep_for(std::chrono::milliseconds(900));
                cv[4].notify_one();                
                std::this_thread::sleep_for(std::chrono::seconds(rand() % 10 + 5));
                mu.lock();
                Bshops[i] = 0;
                shops[i] = 0;
                roadHome[i] = name;
                mu.unlock();
                std::this_thread::sleep_for(std::chrono::milliseconds(900));
                mu.lock();
                roadHome[i] = 0;
                roadHome2[i] = name;
                mu.unlock();
                std::this_thread::sleep_for(std::chrono::milliseconds(900));
                mu.lock();
                roadHome2[i] = 0;
                mu.unlock();
                return;
            }
        }
    }
}

void view()
{
	int iter = 0;
	int count = 0;
    move(5,5);
    printw("|");
    move(5,8);
    printw("|");
    move(5,11);
    printw("|");
    move(5,14);
    printw("|");
    move(5,17);
    printw("|");
    move(5,20);
    printw("|");

    //road
    move(2, 28);
    printw("!");
    move(2, 31);
    printw("!");

    move(4, 28);
    printw("!");
    move(4, 31);
    printw("!");

    move(6, 28);
    printw("!");
    move(6, 31);
    printw("!");

    move(8, 28);
    printw("!");
    move(8, 31);
    printw("!");
    //shopsy
    move(2, 35);
    printw("$");
    move(2, 38);
    printw("$");

    move(4, 35);
    printw("$");
    move(4, 38);
    printw("$");

    move(6, 35);
    printw("$");
    move(6, 38);
    printw("$");

    move(8, 35);
    printw("$");
    move(8, 38);
    printw("$");


    //road home
    move(2, 40);
    printw("|");
    move(2, 43);
    printw(">");

    move(4, 40);
    printw("|");
    move(4, 43);
    printw(">");

    move(6, 40);
    printw("|");
    move(6, 43);
    printw(">");

    move(8, 40);
    printw("|");
    move(8, 43);
    printw(">");

    //road home2

    move(2, 45);
    printw(">");
    move(2, 48);
    printw(">");

    move(4, 45);
    printw(">");
    move(4, 48);
    printw(">");

    move(6, 45);
    printw(">");
    move(6, 48);
    printw(">");

    move(8, 45);
    printw(">");
    move(8, 48);
    printw(">");

    refresh();
	while (true)
	{
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        m.lock();
		move(5, (iter*3)+6);
        printw("  ");
        move(5, (iter*3)+6);
		printw("%d", Que[iter]);        
        if(iter!=4)
        {
            //road

            move(2, 29);
            printw("  ");
            move(2, 29);
            printw("%d", road[0]);

            move(4, 29);
            printw("  ");
            move(4, 29);
            printw("%d", road[1]);

            move(6, 29);
            printw("  ");
            move(6, 29);
            printw("%d", road[2]);

            move(8, 29);
            printw("  ");
            move(8, 29);
            printw("%d", road[3]);

            //shops
            move(2, 36);
            printw("  ");
            move(2, 36);
            printw("%d", shops[0]);

            move(4, 36);
            printw("  ");
            move(4, 36);
            printw("%d", shops[1]);

            move(6, 36);
            printw("  ");
            move(6, 36);
            printw("%d", shops[2]);

            move(8, 36);
            printw("  ");
            move(8, 36);
            printw("%d", shops[3]);

            //road home

            move(2, 41);
            printw("  ");
            move(2, 41);
            printw("%d", roadHome[0]);

            move(4, 41);
            printw("  ");
            move(4, 41);
            printw("%d", roadHome[1]);

            move(6, 41);
            printw("  ");
            move(6, 41);
            printw("%d", roadHome[2]);

            move(8, 41);
            printw("  ");
            move(8, 41);
            printw("%d", roadHome[3]);

            //road home2

            move(2, 46);
            printw("  ");
            move(2, 46);
            printw("%d", roadHome2[0]);

            move(4, 46);
            printw("  ");
            move(4, 46);
            printw("%d", roadHome2[1]);

            move(6, 46);
            printw("  ");
            move(6, 46);
            printw("%d", roadHome2[2]);

            move(8, 46);
            printw("  ");
            move(8, 46);
            printw("%d", roadHome2[3]);
        }
		iter++;
		if (iter == 5)
		{
			iter = 0;
		}
		refresh();
		m.unlock();
   	}
}


int main()
{
	initscr();
	curs_set(0);
	std::thread T[A];
	std::thread view_thread = std::thread(view);

	for (int i = 0; i < A; i++)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		T[i] = std::thread(bigThread, i + 1);
	}

    for(int i=0;i<5;i++)
    {
        cv[i].notify_one();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    shop.notify_one();

	for (int i = 0; i < A; i++)
	{
		T[i].join();
	}
	view_thread.join();
	getch();
	endwin();
	return 0;
}
