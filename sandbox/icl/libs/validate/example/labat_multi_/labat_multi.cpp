/*-----------------------------------------------------------------------------+    
A Law Based Test Automaton 'LaBatea'
Author: Joachim Faulhaber
Copyright (c) 2007-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#include <boost/config/warning_disable.hpp>
#include <iostream>
#include <stdio.h>
#include <boost/thread.hpp> 
#include <boost/validate/driver/abelian_monoid_driver.hpp>

#include <omp.h>

using namespace std;
using namespace boost;
using namespace boost::icl;


void wait(int seconds) 
{ 
  boost::this_thread::sleep(boost::posix_time::seconds(seconds)); 
} 

boost::mutex g_io_Mutex; 

void test_abelian_monoid(int size)
{
    abelian_monoid_driver model_tester;
    g_io_Mutex.lock();
    cout << 
    ">> ------------------------------------------------------ <<\n"
    ">> -------- Law based test automaton 'LaBatea' ---------- <<\n"
    ">> Output will be generated in a few seconds\n"
    ">> terminate by typing <CTRL>C\n"
    ">> ------------------------------------------------------ <<\n";
    GentorProfileSgl::it()->set_std_profile(size,1);
    GentorProfileSgl::it()->report_profile();
    g_io_Mutex.unlock();
    wait(1);

    model_tester.terminate_at_law_count(18, 100);

    model_tester.validate();
}

// tread_abelian_monoid_1() runs the monoid validation for smaller containers
// so it will run faster.
void tread_abelian_monoid_1()
{
    test_abelian_monoid(16);
}

// tread_abelian_monoid_2() runs the monoid validation for smaller containers
// so it will run slower.
void tread_abelian_monoid_2()
{
    test_abelian_monoid(77);
}

void thread_() 
{ 
  for (int i = 0; i < 5; ++i) 
  { 
    wait(1); 
    g_io_Mutex.lock(); 
    std::cout << "Thread " << boost::this_thread::get_id() << ": " << i << std::endl; 
    g_io_Mutex.unlock(); 
  } 
} 

void treaded_abelian_monoid_test() 
{ 
  boost::thread t1(tread_abelian_monoid_1); 
  thread::id t1_id = t1.get_id();
  wait(1);
  cout << "tread_abelian_monoid_1.get_id() = " << t1_id << " started." << endl;
  wait(2);
  boost::thread t2(tread_abelian_monoid_2); 
  t1.join(); 
  t2.join(); 
} 

class Counter
{
public:
	static const int max = 1000000;

	Counter(int val, int max = 1000000): _value(val), _max(max){}

	int getMax()const { return _max; }

	int getAndIncrement()
	{
		lock_guard<mutex> scope_lock(_mutex);
		int prior = _value;
		_value = prior + 1;
		return prior;
	}

private:
	// The mutex accountable to lock critial sections of code of
	// an object shall be encapsulated in that object
	boost::mutex _mutex; // Class local mutex.
	// If no such object exists like for io streams, the mutex that
	// sychrnoizes access has to be global.
	int          _value;
	int          _max;

};

bool is_prim(int number)
{
	int half = number/2;
	for(int frac=2; frac <= half; frac++)
		if(number % frac == 0)
			return false;

	return true;
}

void print_prim(int max)
{
	for(int number=1; number <= max; number++)
		if(is_prim(number))
			cout << number << " ";
}


Counter g_count(1000000, 10000000);
std::map<thread::id, int> thread_ids;

class PrimeChecker
{
public:
	PrimeChecker(boost::mutex* mutx): p_io_Mutex(mutx) {}

	void operator()()
	{
		int cur = 1;
		p_io_Mutex->lock();
		cout << "collecting " << boost::this_thread::get_id() << endl;
		thread_ids[boost::this_thread::get_id()] = thread_ids.size();
		cout << "added: " << boost::this_thread::get_id() << " -> " 
			 << thread_ids[boost::this_thread::get_id()] << endl;
		p_io_Mutex->unlock();

		while(cur < g_count.getMax())
		{
			cur = g_count.getAndIncrement();
			if(is_prim(cur))
			{
				lock_guard<mutex> lock(*p_io_Mutex);
				//cout << "Thread " << boost::this_thread::get_id() << "  count " << cur << endl;
				cout << thread_ids[boost::this_thread::get_id()] << ":" << cur << " ";
				//p_io_Mutex->unlock();
				//this_thread::sleep(posix_time::milliseconds(1)); 
			}
		}
	}
private:
	boost::mutex* p_io_Mutex;
};

void getNumber()
{
	int cur = 1;
	while(cur < g_count.getMax())
	{
		cur = g_count.getAndIncrement();
		if(is_prim(cur))
		{
			g_io_Mutex.lock();
			//cout << "Thread " << boost::this_thread::get_id() << "  count " << cur << endl;
			cout << cur << " ";
			g_io_Mutex.unlock();
			//boost::this_thread::sleep(boost::posix_time::milliseconds(1)); 
		}
	}
}

void produce_prim()
{
	PrimeChecker primes(&g_io_Mutex);
	boost::thread primeChecker1(primes); 
	boost::thread primeChecker2(primes); 
	boost::thread primeChecker3(primes); 
	boost::thread primeChecker4(primes); 

	primeChecker1.join();
	primeChecker2.join();
	primeChecker3.join();
	primeChecker4.join();
}

//==============================================================================
#include <boost/signals2/signal.hpp>
#include <boost/bind.hpp>

using namespace boost::signals2;

struct Observable
{
    signal<void ()>    f1;
    signal<void (int)> f2;
    signal<void (int)> f3;
};

class Observer // implements the callbacks
{
public:
	Observer(int val) : _value(val) {}
	void f1(){ cout << "f1()[" << _value << "]\n"; }
	void f2(int i){ cout << "f2("<< i <<")\n"; }
	void f3(int i){ cout << "f3("<< i*_value <<")\n"; }
private:
	int _value;
};

class Different // implements the callbacks
{
public:
	void f1(){ cout << "f1()[" << "different" << "]\n"; }
};

void testObserver()
{
	Observable sub;
	Observer obs1(1);
	Observer obs2(2);
	Different diff;

	sub.f1.connect(bind(&Observer::f1, obs1));
	sub.f1.connect(bind(&Observer::f1, obs2));
	sub.f1.connect(bind(&Different::f1, Different()));

	sub.f2.connect(bind(&Observer::f2, obs1, _1));
	sub.f2.connect(bind(&Observer::f3, obs2, _1));

	sub.f1();
	sub.f2(3);
}

/*
int main()
{
	//treaded_abelian_monoid_test();
	//print_prim((numeric_limits<int>::max)());
	//produce_prim();
	testObserver();
    return 0;
}
*/

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
 {
     int id,i;
     omp_set_num_threads(4);
 
 #pragma omp parallel for private(id)
     for (i = 0; i < 4; ++i)
     {
         id = omp_get_thread_num();
 
         printf("Hello World from thread %d\n", id);
 //#pragma omp barrier
 //        if (id == 0) {
 //            printf("There are %d threads\n", omp_get_num_threads());
 //        }
     }
 
     return EXIT_SUCCESS;
 }

