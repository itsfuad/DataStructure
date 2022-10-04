#include <iostream>

template <typename T>
class Array
{
public:
	Array()
		:m_max_size(4), m_size(0), m_data(nullptr)
	{
		m_data = new T[4];
		std::cout << "Array created!" << std::endl;
	}

	void add(T data)
	{
		if (m_size >= m_max_size)
		{
			std::cout << "Overdflow! Allocating new bytes of memory." << std::endl;
			m_max_size = m_max_size + m_max_size / 2;
			T* temp = new T[m_max_size];
			for (int i = 0; i < m_size; i++)
			{
				temp[i] = m_data[i];
			}
			delete[] m_data;
			m_data = temp;

			m_add(data);
		}
		else
		{
			m_add(data);
		}
	}


	void print()
	{
		std::cout << "[ ";
		for (int i = 0; i < m_size; i++)
		{
			std::cout << *(m_data+i);
			if (i + 1 != m_size)
			{
				std::cout << ", ";
			}
		}
		std::cout << " ]\n";
		std::cout << "Size: " << m_size << std::endl;
	}


	~Array()
	{
		std::cout << "Array destroyed!" << std::endl;
	}

private:
	void m_add(T data)
	{
		m_data[m_size] = data;
		m_size++;
	}

private:
	T* m_data;
	uint32_t m_max_size;
	uint32_t m_size;
};


int main()
{
	Array<std::string> arr;

	arr.add("C++");
	arr.add("Javascript");
	arr.add("Swift");
	arr.add("Java");
	arr.add("Kotlin");
	arr.add("Rust");
	arr.add("C#");
	arr.add("Golang");


	arr.print();
}