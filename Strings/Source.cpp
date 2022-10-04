#include <iostream>

class String
{
public:

	String() = default;

	String(const char* other)
		: m_buffer(nullptr), m_size(strlen(other))
	{
		m_buffer = new char[m_size + 1];
		memcpy(m_buffer, other, m_size + 1);
		std::cout << "Created " << other << " mem: " << &other << std::endl;
	}

	String(const String& other)
	{
		m_size = other.m_size;
		m_buffer = new char[m_size + 1];
		memcpy(m_buffer, other.m_buffer, m_size + 1);
		std::cout << "Copied " << m_buffer << " mem: " << &m_buffer << std::endl;
	}

	String(String&& other)
	{
		m_size = other.m_size;
		m_buffer = other.m_buffer;
		other.m_size = 0;
		other.m_buffer = nullptr;
		std::cout << "Moved " << m_buffer << " mem: " << &m_buffer << std::endl;
	}

	~String()
	{
		std::cout << "Destroyed " << &m_buffer << std::endl;
		delete m_buffer;
	}

	char& operator[] (unsigned int index)
	{
		return m_buffer[index];
	}

	unsigned int m_size;
private:
	char* m_buffer;

	friend std::ostream& operator<< (std::ostream& os, const String& string);
};

std::ostream& operator<< (std::ostream& os, const String& string)
{
	os << string.m_buffer;
	return os;
}

class Entity
{
public:
	Entity(const String& name)
		: m_name(name)
	{

	}
	Entity(String&& name)
		: m_name(std::move(name))
	{

	}
	void printname()
	{
		for (int i = 0; i < m_name.m_size; i++)
		{
			std::cout << m_name[i];
		}
		std::cout << "\n";
	}
private:
	String m_name;
};

int main()
{
	Entity player("Nuzat");
	player.printname();

	String myname = "Fuad";

	std::cout << myname << std::endl;
}