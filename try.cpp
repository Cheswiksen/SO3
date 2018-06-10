#include <ncurses.h>
#include <unistd.h>
#include <thread>
#include <mutex>
#include <condition_variable>
#define A 20
std::mutex m;
std::mutex mu;
std::mutex mtx;
std::condition_variable cv[5];
std::condition_variable shop;
int shops[4];
bool Bshops[4];
int road[4];
int roadHome[4];
int roadHome2[4];
int Que[5];
int kasa = 0;
int Circle[20];
void bigThread(int name)
{
    while (1) 
    {
        for(int ik=19; ik>=0;ik--)
        {
            m.lock();
            if(Circle[ik]==0)
            {
                Circle[ik]=name;
                Circle[ik+1]=0;
            }
            else
            {
                ik++;
            }
            m.unlock();
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 1300 + 500));
        m.lock();
        if(Que[0]==0){
            Circle[0]=0;
            m.unlock();
            break;            
            }
        else
        {
            Circle[0]=0;
        }
        m.unlock();
    }

    std::unique_lock<std::mutex> lk1(m);
    cv[0].wait(lk1, [](){return !Que[0];});
    Que[0] = name;
    lk1.unlock();

    std::unique_lock<std::mutex> lk2(m);
    cv[1].wait(lk2, [](){return !Que[1];});
    Que[0] = 0;
	Que[1] = name;
    lk2.unlock();
    cv[0].notify_one();

    std::unique_lock<std::mutex> lk3(m);
    cv[2].wait(lk3, [](){return !Que[2];});
    Que[1] = 0;
	Que[2] = name;
    lk3.unlock();
    cv[1].notify_one();

    std::unique_lock<std::mutex> lk4(m);
    cv[3].wait(lk4, [](){return !Que[3];});
    Que[2] = 0;
	Que[3] = name;
    lk4.unlock();
    cv[2].notify_one();

    std::unique_lock<std::mutex> lk5(m);
    cv[4].wait(lk5, [](){return !Que[4];});
    Que[3] = 0;
	Que[4] = name;
    lk5.unlock();
    cv[3].notify_one();


    while(true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 1300 + 500));
        for(int i=0; i<4;i++)
        {
            if(Bshops[i]==0)
            {
                cv[4].notify_one();
                mu.lock();                
                Que[4] = 0;
                Bshops[i] = 1;
                mu.unlock();
                if(i==0)
                {
                    mu.lock();
                    move(3,21);
                    printw("%d", name);
                    mu.unlock();
                    std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 1300 + 500));
                    mu.lock();
                    move(3,21);
                    printw("  ");
                    move(2,23);
                    printw("%d", name);
                    mu.unlock();
                        
                    std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 1300 + 500));
                    for(int q=23; q<32; q+=2)
                    {
                        mu.lock();
                        move(2,q);
                        printw("  ");
                        move(2,q+2);
                        printw("%d", name);
                        mu.unlock();
                        std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 1300 + 500));
                    }
                }
                if(i==1)
                {
                    mu.lock();
                    move(4,21);
                    printw("%d", name);
                    mu.unlock();
                    std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 1300 + 500));
                    for(int q=21; q<32; q+=2)
                    {
                        mu.lock();
                        move(4,q);
                        printw("  ");
                        move(4,q+2);
                        printw("%d", name);
                        mu.unlock();
                        std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 1300 + 500));
                    }
                }
                if(i==2)
                {
                    mu.lock();
                    move(6,21);
                    printw("%d", name);
                    mu.unlock();
                    std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 1300 + 500));
                    for(int q=21; q<32; q+=2)
                    {
                        mu.lock();
                        move(6,q);
                        printw("  ");
                        move(6,q+2);
                        printw("%d", name);
                        mu.unlock();
                        std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 1300 + 500));
                    }
                }
                if(i==3)
                {
                    mu.lock();
                    move(7,21);
                    printw("%d", name);
                    mu.unlock();
                    std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 1300 + 500));
                    mu.lock();
                    move(7,21);
                    printw("  ");
                    move(8,23);
                    printw("%d", name);
                    mu.unlock();
                        
                    std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 1300 + 500));
                    for(int q=23; q<32; q+=2)
                    {
                        mu.lock();
                        move(8,q);
                        printw("  ");
                        move(8,q+2);
                        printw("%d", name);
                        mu.unlock();
                        std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 1300 + 500));
                    }
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 1300 + 500));
                mu.lock();
                if(i==0)
                {
                    move(2,33);
                    printw("  ");
                }
                if(i==1)
                {
                    move(4,33);
                    printw("  ");
                }
                if(i==2)
                {
                    move(6,33);
                    printw("  ");
                }
                if(i==3)
                {
                    move(8,33);
                    printw("  ");
                }                                       
                shops[i] = name;
                mu.unlock();
                std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 1300 + 500));
                //cv[4].notify_one();                
                std::this_thread::sleep_for(std::chrono::seconds(rand() % 10 + 5));
                mu.lock();
                Bshops[i] = 0;
                shops[i] = 0;
                mu.unlock();
                if(i==0)
                {
                    mu.lock();
                    move(2,39);
                    printw("%d", name);
                    mu.unlock();
                    std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 1300 + 500));
                    for(int q=39; q<50; q+=2)
                    {
                        mu.lock();
                        move(2,q);
                        printw("  ");
                        move(2,q+2);
                        printw("%d", name);
                        mu.unlock();
                        std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 1300 + 500));
                    }
                    mu.lock();
                    move(2,51);
                    printw("  ");
                    mu.unlock();
                }
                if(i==1)
                {
                    mu.lock();
                    move(4,39);
                    printw("%d", name);
                    mu.unlock();
                    std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 1300 + 500));
                    for(int q=39; q<50; q+=2)
                    {
                        mu.lock();
                        move(4,q);
                        printw("  ");
                        move(4,q+2);
                        printw("%d", name);
                        mu.unlock();
                        std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 1300 + 500));
                    }
                    mu.lock();
                    move(4,51);
                    printw("  ");
                    mu.unlock();
                }
                if(i==2)
                {
                    mu.lock();
                    move(6,39);
                    printw("%d", name);
                    mu.unlock();
                    std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 1300 + 500));
                    for(int q=39; q<50; q+=2)
                    {
                        mu.lock();
                        move(6,q);
                        printw("  ");
                        move(6,q+2);
                        printw("%d", name);
                        mu.unlock();
                        std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 1300 + 500));
                    }
                    mu.lock();
                    move(6,51);
                    printw("  ");
                    mu.unlock();
                }
                if(i==3)
                {
                    mu.lock();
                    move(8,39);
                    printw("%d", name);
                    mu.unlock();
                    std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 1300 + 500));
                    for(int q=39; q<50; q+=2)
                    {
                        mu.lock();
                        move(8,q);
                        printw("  ");
                        move(8,q+2);
                        printw("%d", name);
                        mu.unlock();
                        std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 1300 + 500));
                    }
                    mu.lock();
                    move(8,51);
                    printw("  ");
                    mu.unlock();
                }
                return;
            }
        }
    }
}

void view()
{
	int iter = 0;
	int count = 0;
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
        }
		iter++;
		if (iter == 5)
		{
            for(int w=0;w<20;w++)
            {
                if(Circle[w]==0)
                {
                    move(5+w,3);
                    printw("  ");
                }
                else
                {
                    move(5+w,3);
                    printw("%d",Circle[w]);
                }
            }
            //Queue
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

            //Shops
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
