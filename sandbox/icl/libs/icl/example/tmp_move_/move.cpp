#include <iostream>

using namespace std;


class Mob 
{
public:

    Mob(int val=0): _mine(new int)
    { 
        cout << ".";
        *_mine = val;
    }

    Mob(const Mob& src):_mine(new int)
    {
        cout << "[copy].";
        *_mine = *(src._mine);
    }

    Mob& operator = (const Mob& src)
    {
        if(this != &src)
        {
            cout << "[c=]";
            //delete _mine;
            //_mine = new int;
            *_mine = *(src._mine);
        }
        return *this;
    }

    Mob(Mob&& victim): _mine(victim._mine) //Klau
    {
        cout << "[move]";
        victim._mine = 0; //Dtor wird gleich aufgerufen.
    }

    Mob& operator = (Mob&& victim)
    {
        if(this != &victim)
        {
            cout << "[m=]~";
            delete _mine;
            _mine = victim._mine; //Klau
            victim._mine = 0; //Dtor wird gleich aufgerufen. 
        }
        return *this;
    }

    ~Mob()
    {
        if(_mine)
            cout << "~" ;
        else
            cout << "'";
        delete _mine; 
    }

    int mine()const 
    {
        return *_mine; 
    }

    void inc()
    {
        ++(*_mine);
    }

    Mob& operator += (const Mob& addend)
    {
        *_mine += *(addend._mine);
        return *this;
    }

private:
    int* _mine;
};


//Mob operator + (const Mob& lhs, const Mob& rhs)
//{
//    return lhs.mine() + rhs.mine();
//}

//Mob operator + (const Mob& lhs, const Mob& rhs)
//{
//    Mob tmp(lhs);
//    return std::move(tmp += rhs);
//}

Mob operator + (Mob&& lhs, const Mob& rhs)
{
    return std::move(lhs += rhs);
}

/*msvc-11 only
Mob inc_a_tmp(Mob& x)
{ 
    cout << "[f(&)]";
    x.inc(); 
    return move(x); 
}
*/

Mob inc(Mob&& x)
{ 
    cout << "[inc(&&)]";
    x.inc(); 
    return std::move(x); 
}

Mob inc(Mob& x)
{ 
    cout << "[inc(&)]";
    x.inc(); 
    return x; 
}

Mob mob_answer1()
{
    return Mob(40)+Mob(2); //Call move ctor
}

Mob mob_answer2()
{
    Mob tmp;
    tmp = Mob(40)+Mob(2); //Calls move assign 
    return tmp;           //Calls move ctor
}


int g(int&& x){ return x++; }

void test1()
{
    //cout << "Test: "  << (Mob(1) + Mob(2)).mine() << endl;
    Mob mc = inc(Mob(1) + Mob(2));
    cout << "Test 1. Expect:4 Get:" << mc.mine() << endl;
    cout << "mob_answer1()" << endl; 
    mob_answer1(); 
    cout << endl;
    //cout << "Mob answer1: " << mob_answer1().mine() << endl;
    cout << "mob_answer2()" << endl; mob_answer2(); cout << endl;
    //int answer2 = mob_answer2().mine();
    //cout << "Mob answer2: " << mob_answer2().mine() << endl;

    cout << endl;
    Mob a3 = Mob(1) + Mob(2);
    cout << "\n1+2=" << a3.mine() << endl;

    cout << endl;
    Mob a6 = (Mob(1) + Mob(2)) + Mob(3);
    cout << "\n1+2+3=" << a6.mine() << endl;

    cout << endl;
    Mob a6r = Mob(1) + (Mob(2) + Mob(3));
    cout << "\n1+(2+3)=" << a6r.mine() << endl;
}

void test_bindings()
{
    int a = 1, b = 2;
    cout << "test_bindings(). Expect: 4 Get: " << g(a+b) << endl;
}

int main()
{
    cout << ">>Testing move                                       <<\n";
    cout << "-------------------------------------------------------\n";
    test1();
    //test_bindings();
    return 0;
}

