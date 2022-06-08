#pragma once
template <typename T>
class Vector {
	T* elements;
	size_t size;
	size_t capacity;

	void copyFrom(const Vector<T>& other);
	void free();
	void resize();

public:
	Vector();
	Vector(size_t capacity);
	Vector(const Vector& other);
	Vector<T>& operator=(const Vector<T>& other);
	~Vector();
	
	size_t Size() const;
	bool deleteAt(size_t i); 
	void push_back(const T* el);
	void push_back(const Account* el);
	T& operator[](size_t i);
	T& operator[](size_t i) const;
	bool isEmpty() const;
};

template<class T>
void swap(T& a, T& b)
{
	T c = a;
	a = b;
	b = c;
}

template<typename T>
Vector<T>::Vector()
{
	capacity = 4;
	size = 0;
	elements = new T[capacity];
}

template<typename T>
Vector<T>::Vector(size_t capacity)
{
	this->capacity = capacity;
	size = 0;
	elements = new T[capacity];
}

template<typename T>
void Vector<T>::copyFrom(const Vector<T>& other)
{
	capacity = other.capacity;
	size = other.size;
	elements = new T[capacity];

	for (size_t i = 0; i < size; i++)
		elements[i] = other.elements[i];
}

template<typename T>
void Vector<T>::free()
{
	delete[] elements;
}

template<typename T>
void Vector<T>::resize()
{
	T* temp = new T[capacity *= 2];

	for (size_t i = 0; i < size; i++)
		temp[i] = elements[i];

	free();
	elements = temp;
}

template<typename T>
Vector<T>::Vector(const Vector& other)
{
	copyFrom(other);
}

template<typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

template<typename T>
Vector<T>::~Vector()
{
	free();
}

template<typename T>
size_t Vector<T>::Size() const
{
	return size;
}

template<typename T>
bool Vector<T>::deleteAt(size_t i)
{
	if (i >= size)
		return false;

	swap(elements[i], elements[size - 1]);
	size--;
	return true;
}

template<typename T>
void Vector<T>::push_back(const T* el)
{
	if (size == capacity)
		resize();

	elements[size++] = *el;
}

template<typename T>
void Vector<T>::push_back(const Account* el)
{
	if (size == capacity)
		resize();

	elements[size++] = el->clone();
}

template<typename T>
T& Vector<T>::operator[](size_t i)
{
	return elements[i];
}

template<typename T>
T& Vector<T>::operator[](size_t i) const
{
	return elements[i];
}

template<typename T>
bool Vector<T>::isEmpty() const
{
	return size == 0;
}