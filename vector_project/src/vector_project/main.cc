#include <new>
#include <fstream>
#include <algorithm>
#include <random>

template <typename T>
class Vector
{
protected:
	T * allocator;
public:
	size_t size;
	//constructors:

	//empty constructor
	Vector()
	{
		allocator = new T[0];
		size = 0;
	}

	//copy constructor
	Vector(Vector &existingVector)
	{
		/*size = existingVector.sizeOfVector();
		allocator = new T[size];//check this is new line
		for (size_t counter = 0; counter < size; counter++)
		{
			allocator[counter] = std::forward(existingVector.allocator[counter]);
		}*/
		Vector<T> tmp();
		tmp=existingVector;
		this->swap(tmp);
	}

	//move constructor
	Vector(Vector &&existingVector)
	{
		this->swap(existingVector);
	}

	//simple methods
	//begin() - return iterator on the first element
	T *begin() const
	{
		return allocator;
	}

	//end() - iterator on the after last element
	T *end() const
	{
		return (allocator + size);
	}

	//size() - num of elements in the Vector
	size_t sizeOfVector() const
	{
		return size;
	}

	//difficult methods:
	//push_back(T) - add element at the tail
	void push_back(T&& value)
	{
		T *newAlloc = new T[size + 1];
		size_t counter = 0;
		while (counter < size) {
			newAlloc[counter] = std::move(this->allocator[counter]);
			counter++;
		}
		newAlloc[size] = std::move(value);
		delete[] allocator;
        allocator = newAlloc;
		size += 1; 
	}

	//pop_back() - drop element at the tail
	void pop_back()
	{
		T *newAlloc = new T[size];
		size_t counter = 0;
		while (counter < size) {
			newAlloc[counter] = std::move(this->allocator[counter]);
			counter++;
		}
		delete[] allocator;
        allocator = newAlloc;		 
		size -= 1;
	}

	//erase() - delete elements //look cpp
	//erase one element at position = num_of_pos
	void erase(size_t num_of_pos)
	{		
		//move the tail on one position and pop_back		
		if (this->sizeOfVector() > num_of_pos) {
			for (size_t counter = num_of_pos; counter<this->sizeOfVector(); counter++) {
				allocator[counter] = std::forward<T>(allocator[counter + 1]);
			}
			this->pop_back();
		}
		else if(this->sizeOfVector() == num_of_pos)	this->pop_back();	
	}

	void erase(size_t first_num, size_t last_num)
	{
		if (first_num>last_num) {
			first_num += last_num;
			last_num = first_num - last_num;
			first_num = first_num - last_num;
		};		
		//move the tail on (last_num-first_num) position and pop_back
		if (this->sizeOfVector() >= last_num) {
			for (size_t counter = first_num; counter<this->sizeOfVector(); counter++) {
				if (size>=counter+(last_num - first_num)+1){
					allocator[counter] = std::forward<T>(allocator[counter + (last_num - first_num)+1]);
				};
			};
			for (size_t counter = first_num; counter<size; counter++) {
				this->pop_back();
			};
		};
	}
	//swap() vectors
	void swap(Vector<T> &rightVector)
	{
		/*Vector<T> tmp(*this);
		*this = std::move(rightVector);
		rightVector = std::move(tmp);*/
		T *tmpAlloc=allocator;
		size_t tmpSize = size;

		allocator=rightVector.allocator;
		size=rightVector.size;

        rightVector.allocator = tmpAlloc;
        rightVector.size = tmpSize;
	}

	//operators:
	//operator=
	Vector &operator=(const Vector &&rightVector)
	{
		size = existingVector.sizeOfVector();
		allocator = new T[size];//check this is new line
		for (size_t counter = 0; counter < size; counter++)
		{
			allocator[counter] = std::forward(existingVector.allocator[counter]);
		}
		
		//Vector<T> tmp(rightVector);
		//this->swap(tmp);
		return *this;
		
	}

	Vector &operator=(Vector &&rightVector)
	{
		this->swap(rightVector);
		return *this;
	}

	T &operator[](const size_t pos) {
		return allocator[pos];
	}

	//destructor
	~Vector()
	{
		delete[] allocator;
	}
};

//swap() vectors
template <typename T>
void Swap(Vector<T> &leftVector, Vector<T> &rightVector)
{
	leftVector.swap(rightVector);
};

int main()
{
	std::ofstream myLog("myLog.txt", std::ofstream::out);

	//push_back test:
	//create vector with ofstream elements
	std::ofstream ofs1("ofs1.txt", std::ofstream::out);
	std::ofstream ofs2("ofs2.txt", std::ofstream::out);
	std::ofstream ofs3("ofs3.txt", std::ofstream::out);
	std::ofstream ofs4("ofs4.txt", std::ofstream::out);
	std::ofstream ofs5("ofs5.txt", std::ofstream::out);
	std::ofstream ofs6("ofs6.txt", std::ofstream::out);

	Vector<std::ofstream> myVec; 
	
	myVec.push_back(std::move(ofs1));
	myVec.push_back(std::move(ofs2));
	myVec.push_back(std::move(ofs3));
	myVec.push_back(std::move(ofs4));

	//shuffle elements in vector
	std::random_device rd;
	std::mt19937 g(rd());
	std::shuffle(myVec.begin(), myVec.end(), g);

	//show the results in files
	myVec[0] << 1;
	myVec[1] << 2;
	myVec[2] << 3;
	myVec[3] << 4;

	//oper= test:
	Vector<std::ofstream> anotherVec1;
	Vector<std::ofstream> anotherVec2;
	anotherVec1.push_back(std::move(ofs5));
	anotherVec2.push_back(std::move(ofs6));

	anotherVec1=std::move(anotherVec2);
	anotherVec1[0] << "must be ofs6.txt file";


	//pop_back test
	myLog << "pop_back test"<<"\n";
	myLog << "size: ";
	myLog << myVec.sizeOfVector();
	myLog << "\n";	

	myVec[3] << "\n"<<"it was pop_back, so it contains only one number";
	myVec.pop_back();

	myLog << "size: ";
	myLog << myVec.sizeOfVector();
	myLog << "\n";

	myVec[0] << "==1";
	myVec[0] << "\n";

	myVec[1] << "==2";
	myVec[1] << "\n";

	myVec[2] << "==3";
	myVec[2] << "\n";

	*(myVec.end()-1)<<" & !=4"<<"\n";

	//erase test
	myLog << "erase test"<<"\n";
	myLog << "size: ";
	myLog << myVec.sizeOfVector();
	myLog << "\n";	

	myVec[0]<<" it was erased";
	myVec[1]<<" it was erased";
	myVec.erase(0,1);

	myLog << "size: ";
	myLog << myVec.sizeOfVector();
	myLog << "\n";
	//myVec[0] << "==1";
	//myVec[1] << "!=2 & ==3";
	myVec[0]<<"==3";

	return 0;
}
