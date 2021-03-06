#include <iostream>
using namespace std;
#include <utility>

struct Monom
{
	int st;
	double con;
	Monom(int _st = 0, double _con = 0) : st(_st), con(_con) {};


	int getX() const
	{
		return st / 100;
	}
	int getY() const
	{
		return (st / 10) % 10;
	}
	int getZ() const
	{
		return st % 10;
	}
	bool operator>(const Monom& second) const
	{
		return this->st > second.st;
	}
	bool operator<(const Monom& second) const
	{
		return this->st < second.st;
	}
	bool operator>=(const Monom& second) const
	{
		return this->st >= second.st;
	}
	bool operator<=(const Monom& second) const
	{
		return this->st <= second.st;
	}
	bool operator==(const Monom& second) const
	{
		return this->st == second.st;
	}

	Monom operator*(const Monom& second) const
	{
		Monom res;
		int x, y, z;
		z = this->getZ() + second.getZ();
		if (z > 9)
		{
			throw std::string("Z  > 9");
		}
		y = (this->getY() + second.getY());
		if (y > 9)
		{
			throw std::string("Y  > 9");
		}
		x = (this->getX() + second.getX());
		if (x > 9)
		{
			throw std::string("X  > 9");
		}
		res.st = x * 100 + y * 10 + z;
		res.con = this->con*second.con;
		return res;
	}
};


class Polynom
{
	friend Monom;
	struct Node
	{
		Monom value;
		Node* next;
		Node(Monom _val = Monom(0, 0), Node* _next = NULL) : value(_val), next(_next) {};
	};
	int size = 0;
	Node* m_Head = NULL;

public:
	Polynom() {};
	void push(Monom val)
	{
		Node** tmp = &m_Head;
		Node* next = NULL;
		for (; (*tmp) != NULL; tmp = &((*tmp)->next))
		{
			if ((*tmp)->value >= val)
			{
				Monom swap = (*tmp)->value;
				next = (*tmp)->next;
				(*tmp)->value = val;
				val = swap;
				tmp = &((*tmp)->next);
				break;
			}
		}
		++size;
		*tmp = new Node(val, next);
	}
	void clear()
	{
		Node* deleteLater;
		for (Node* tmp = m_Head; tmp != NULL; delete deleteLater)
		{
			deleteLater = tmp;
			tmp = tmp->next;
		}
		size = 0;
		m_Head = NULL;
	}
	void norm()
	{
		for (Node** tmp = &m_Head; tmp != NULL; )
		{
			if ((*tmp)->next)
			{
				if ((*tmp)->value == (*tmp)->next->value)
				{
					(*tmp)->value.con += (*tmp)->next->value.con;
					Node* deleteLayter = (*tmp)->next;
					(*tmp)->next = deleteLayter->next;
					--size;
					delete deleteLayter;
				}
				else
				{
					tmp = &(*tmp)->next;
				}
			}
			else
			{
				break;
			}
		}
		for (Node** tmp = &m_Head; (*tmp) != NULL; tmp = &((*tmp)->next))
		{
			if ((*tmp)->value.con == 0)
			{
				Node* deleteLayter = *tmp;
				tmp = &(*tmp)->next;
				delete deleteLayter;
			}
		};
		out();
	}
	void out()
	{
		cout << "MONOM" << endl;
		for (Node* tmp = m_Head; tmp != NULL; tmp = tmp->next)
		{
			cout << tmp->value.con << "*x^" << tmp->value.getX() << "*y^" << tmp->value.getY() << "*z^" << tmp->value.getZ() << endl;
		}
		cout << "end MONOM" << endl;
	}
	Polynom operator*(double multi) const
	{
		Polynom polynom;
		Monom monom;
		for (Node* tmp = m_Head; tmp != NULL; tmp = tmp->next)
		{
			monom = tmp->value;
			monom.con *= multi;
			polynom.push(monom);
		}
		polynom.norm();
		return polynom;
	}

	Polynom operator*(const Polynom& second) const
	{
		Polynom res;
		for (unsigned i = 0; i < this->Size(); ++i)
		{
			for (unsigned j = 0; j < second.Size(); ++j)
			{
				try
				{
					res.push(this->at(i) * second.at(j));
				}
				catch (std::string &st)
				{
					cout << st << endl << "Exit: -1" << endl;
					exit(-1);
				}
			}
		}

		res.norm();

		return res;
	}
	Polynom operator+(const Polynom& second) const
	{
		Polynom result;
		int i = 0, j = 0, n = this->Size(), m = second.Size();
		int size = n + m;

		while (i < n && j < m)
		{
			if (this->at(i) >= second.at(j))
			{
				result.push(second.at(j));
				++j;
			}
			else
			{
				result.push(this->at(i));
				++i;
			}
		}
		while (i < n)
		{
			result.push(this->at(i));
			++i;
		}
		while (j < n)
		{
			result.push(second.at(j));
			++j;
		}
		result.norm();
		return result;
	}
	Polynom operator-(const Polynom& second) const
	{

		return (*this) + second * -1;
	}
	Polynom& operator=(const Polynom& second)
	{

		this->clear();
		for (Node* tmp = second.m_Head; tmp != NULL; tmp = tmp->next)
		{
			this->push(tmp->value);
		}
		return *this;
	}
	bool operator==(const Polynom& second) const
	{
		if (this->size != second.size)
		{
			return false;
		}
		Node* tmp1 = this->m_Head;
		Node* tmp2 = second.m_Head;
		while (tmp1 != NULL)
		{
			if (tmp1->value.st != tmp2->value.st && tmp1->value.con != tmp2->value.con)
			{
				return false;
			}
			tmp1 = tmp1->next;
			tmp2 = tmp2->next;
		}
		return true;
	}
	Monom at(int index) const
	{
		Node* tmp = m_Head;
		for (int i = 0; i != index; ++i)
		{
			tmp = tmp->next;
		}
		return tmp->value;
	}
	int Size() const
	{
		return size;
	}
	~Polynom()
	{
		clear();
	}

};

class Table
{
       
protected:
    int SIZE = 100; 
    unsigned m_last = 0;
	std::pair<string, Polynom> *table;
	
public:
    Table()
    {
        table = new std::pair<string, Polynom>[SIZE];
    }
    ~Table()
    {
        delete table;
    }
    
    virtual void  insert(string key, Polynom pol) = 0;
    virtual Polynom  search(string key) = 0;
    virtual Polynom  pop(string key) = 0;
};

class UnsortedTable: public Table
{
    public:
    void insert(string key, Polynom pol)
    {
        increaseSizeIfNeed();
        table[m_last].first = key;
        table[m_last++].second = pol;
    }
    void increaseSizeIfNeed()
    {
    	if(m_last == SIZE)
        {
	    	std::pair<string, Polynom> *newtable = new std::pair<string, Polynom>[SIZE*2];
	        for(int i = 0; i <SIZE; ++i)
	        {
	            newtable[i].first = table[i].first;
	            newtable[i].second = table[i].second;
	        }
	        delete[] table;
	        table = newtable;
	        SIZE *=2;
	    }
        
    }
    
    virtual Polynom  pop(string key)
    {
       for(int i = 0; i < m_last; ++i)
        {
            if(key == table[i].first)
            {
                table[i].first ="";
                return table[i].second;
            }
        }
        cout << "Ne nayden";
        return Polynom(); 
    }

};

class SortedTable : public UnsortedTable
{
	SortedTable():Table() {};
	virtual void  insert(string key, Polynom pol)
	{
		increaseSizeIfNeed();
		unsigned i;
		for(i = 0; table[i].first < key && table[i].first != ""; ++i)
		{

		}
		unsigned inserted = i;
		for( ; i < m_last; ++i)
		{
			table[i+1].first = table[i].first;
			table[i+1].second = table[i].second;
		}
		table[inserted].first = key;
		table[inserted].second = pol; 
		++m_last;
	}
    virtual Polynom  pop(string key)
    {
       for(int i = 0; i < m_last; ++i)
        {
            if(key == table[i].first)
            {
                table[i].first ="";
                --m_last;
                Polynom val  = table[i].second;
                for( ; i < m_last; ++i)
                {
                	table[i].first = table[i+1].first;
                	table[i].second = table[i+1].second;
                }
                return val;
            }
        }
        cout << "Ne nayden";
        return Polynom(); 
    }
};

class HashTable: public UnsortedTable
{
public:
	void insert(string key, Polynom pol)
	{

	}
protected:
	unsigned hash(string key)
	{
		unsigned res = 1;
		for(unsigned i = 0; i < strlen[i];++i)
		{
			res*= key[i];
		}
		return res % 100;
	}

	void insert(string key, Polynom pal)
	{
		unsigned hashKey = hash(key);
		increaseSizeIfNeed();
		unsigned i = hashKey;
		while(table[i++].first != "")
		{}
		table[i].first = key;
		table[i].second = pal;
		++m_last;
	}
	Polynom search(string key)
	{
		unsigned hashKey = hash(key);
		for(int i = hashKey; i < m_last; ++i)
		{
			if(key == table[i].first)
			{
				return table.[i].second;
			}
		}
		cout << "Ne naiden " << endl;
		return Polynom();
	}
	Polynom pop(string key)
	{
		unsigned hashKey = hash(key);
		for(int i = hashKey; i < m_last; ++i)
		{
			if(key == table[i].first)
			{
				--m_last;
				table[i].first = "";
				return table[i].second;
			}
		}
		cout << "Ne naiden " << endl;
		return Polynom();
	}

}