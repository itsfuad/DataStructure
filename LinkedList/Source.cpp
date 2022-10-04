#include <iostream>
#include <array>
#include <list>

template <typename T>
class Node
{
	T data;
	Node* next;
	Node* prev;
	template <typename T>
	friend class List;
	template <typename T>
	friend std::ostream& operator<<(std::ostream& os, const List<T>& li);
};

template <typename T>
class List
{
public:
	List()
		: Head(nullptr), Tail(nullptr)
	{
		std::cout << "List created" << std::endl;
	}

	List(const List& li)
	{
		Head = nullptr;
		Tail = nullptr;
		Node<T>* temp = li.Head;
		while (temp != nullptr)
		{
			pushBack(temp->data);
			temp = temp->next;
		}
		std::cout << "Copied" << std::endl;
	}

	void operator=(const List& li)
	{
		std::cout << "Moved" << std::endl;
		Head = li.Head;
		Tail = li.Tail;
	}

	template <typename... Args>
	List(Args... args)
		: Head(nullptr), Tail(nullptr)
	{
		(pushBack(args), ...);
	}

	void pushBack(T data)
	{
		Node<T>* temp = new Node<T>();
		temp->data = data;
		temp->next = nullptr;
		if (Head == nullptr)
		{
			Head = temp;
			Tail = temp;
			Head->prev = nullptr;
			Tail->prev = nullptr;
		}
		else
		{
			Tail->next = temp;
			temp->prev = Tail;
			Tail = Tail->next;
		}
	}

	void pushFront(T data)
	{
		if (Head != nullptr)
		{
			Node<T>* temp = new Node<T>();
			temp->data = data;
			temp->next = Head;
			temp->prev = nullptr;
			Head->prev = temp;
			Head = temp;
		}
		else
		{
			pushBack(data);
		}
	}

	template <typename... Args>
	void emplaceBack(Args... data)
	{
		(pushBack(data), ...);
	}

	template <typename... Args>
	void emplaceFront(Args... data)
	{
		(pushFront(data), ...);
	}

	void popFront()
	{
		if (Head != nullptr)
		{
			Node<T>* temp = Head;
			if (Head->next != nullptr)
			{
				Head = Head->next;
				Head->prev = nullptr;
				delete temp;
			}
			else 
			{
				Head = nullptr;
				Tail = nullptr;
				delete temp;
			}
		}
	}

	void popBack()
	{
		if (Tail != nullptr)
		{
			Node<T>* temp = Tail;
			if (Tail->prev != nullptr)
			{
				Tail = Tail->prev;
				Tail->next = nullptr;
				delete temp;
			}
			else
			{
				Head = nullptr;
				Tail = nullptr;
				delete temp;
			}
		}
	}

	void clear()
	{
		while (Tail != nullptr)
		{
			popBack();
		}
	}

	void print()
	{
		Node<T>* temp = Head;
		while (temp != nullptr)
		{
			std::cout << temp->data << std::endl;
			temp = temp->next;
		}
	}

	List& reverse()
	{
		Node<T>* temp = Tail;
		List<T>* li = new List<T>();
		while (temp != nullptr)
		{
			li->pushBack(temp->data);
			temp = temp->prev;
		}
		return *li;
	}

	~List()
	{
		std::cout << "List distroyed" << std::endl;
	}

private:
	Node<T>* Head;
	Node<T>* Tail;
	template <typename T>
	friend std::ostream& operator<<(std::ostream& os, const List<T>& li);
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const List<T>& li)
{
	Node<T>* temp = li.Head;
	os << "[ ";
	while (temp != nullptr)
	{
		os << temp->data;
		if (temp->next != nullptr) os << ", ";
		temp = temp->next;
	}
	os << " ]";
	return os;
}



int main()
{
	List<int> li(2, 4, 6);
	List<int> li2(1, 3, 5);

	li2 = li;
	li.popBack();

	std::cout << li << std::endl;
	std::cout << li2 << std::endl;

	return 0;
}