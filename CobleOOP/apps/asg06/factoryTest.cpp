#include<iostream>
#include<string>

using std::string;
using namespace std;
struct Office {
    string      m_street;
    string      m_city;
    int32_t    m_cubicle;
};



class Employee 
{
private:
    string m_name;
    Office* m_office;
    
public:
    Employee(const Employee& rhs) : m_name{ rhs.m_name }, m_office{ new Office{*rhs.m_office}} {}
    Employee(string n, Office* o) : m_name(n), m_office(o) {}   //<------------------- Moved private to public. Spent days trying to figure out how to make this work otherwise.
    Employee& operator=(const Employee& rhs) 
    {
        if (this == &rhs) 
            return *this;
        
        m_name = rhs.m_name;
        m_office = new Office{ *rhs.m_office };
        return *this;
    }

    friend ostream& operator<<(ostream& os,const Employee& o) {
        return os  << o.m_name << " works at "
            << o.m_office->m_street << " " << o.m_office->m_city
            << " seats @" << o.m_office->m_cubicle;
    }
};

class EmployeeFactory
{
    public:
    Employee make(string n, Office* o)
    {
        return Employee(n, o);
    }
};

int main()
{
    Office* B = new Office;
    B->m_city = "Athens";
    B->m_cubicle = 103;
    B->m_street = "N Beaty";
    EmployeeFactory EF;
    Employee A = EF.make("Dr. Evil",B);
    Employee C = EF.make("The Special Clown in Charge", B);
    std::cout << A << endl;
    std::cout << C << endl;
    
    return 0;
}