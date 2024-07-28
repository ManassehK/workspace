#include <iostream> 
using namespace std;
const int DefaultSize =10;

class Array
{
public:
    //constructors
    Array(int itsSize = DefaultSize);
    Array (const Array &rhs);
    ~Array () { delete [] pType; }

    //operators
    Array& operator= (const Array&);
    int& operator [] (int offset);
    const int& operator[] (int offset) const;

    int GetistSize() const { return itsSize; }


    //friend function
    friend ostream& operator<< (ostream&, const Array&);

     //exception class defined
    class xBoundary {};
    class xSize
    {
        public:
        xSize(int size):itsSize(size){}
        ~xSize(){}
        int GetSize(){ return itsSize; }
        private:
            int itsSize;
    };
    class xTooBig : public xSize
    {
        public:
        xTooBig(int size):xSize(size){}
    };
    class xTooSmall : public xSize
    {
        public:
        xTooSmall(int size):xSize(size){}
    };
    class xZero : public xTooSmall 
    {
        public:
        xZero(int size):xTooSmall(size){}
    };
    class xNegative : public xSize 
    {
        public:
        xNegative(int size):xSize(size){}
    };
private:
    int *pType;
    int itsSize;   
};

Array::Array(int size):
    itsSize(size)
{
    if (size == 0)
        throw xZero(size);
 if (size > 30000)
        throw xTooBig(size);
if (size < 1)
        throw xNegative(size);
if (size < 10)
        throw xTooSmall(size);
    pType = new int[size];
    for (int i = 0; i < size; i++)
        pType[i] = 0; 
}

Array& Array::operator= (const Array &rhs)
{
    if (this == &rhs)
        return *this;
    delete [] pType;
    itsSize = rhs.GetistSize();
    pType = new int[itsSize];
    for (int i = 0; i < itsSize; i++)
    {
        pType[i] = rhs[i];
    }
    return *this;
}

Array::Array(const Array &rhs)
{
itsSize = rhs.GetistSize();
pType = new int[itsSize];
for (int i = 0; i < itsSize; i++)
    {
    pType[i] = rhs[i];
    }
 }

int& Array::operator[](int offSet)
{
    int size = GetistSize();
    if (offSet >= 0 && offSet < GetistSize())
        return pType[offSet];
     throw xBoundary();
    return pType[0]; // appease MSC
 }

const int& Array::operator[](int offSet) const
{
    int size = GetistSize();
    if (offSet >= 0 && offSet < GetistSize())
        return pType[offSet];
    throw xBoundary();
    return pType[0]; // appease MSC
 }

ostream& operator<< (ostream& output, const Array& theArray)
{
    for (int i = 0; i<theArray.GetistSize(); i++)
        output <<"["<<i<< "]" << theArray[i] << endl;
    return output;
 }

int main()
{   
    Array intArray(9);
    try
    {
        for (int j=0;j<100; j++)
        {
            intArray[j]= j;
            cout<<"intArray["<<j<<"] okay..."<<endl;
        }
    }
    catch (Array::xBoundary)
    {
        cout<<" Unable to process your input! "<<endl;
    }
    catch (Array::xZero theException)
    {
        cout<<"You asked for an array of zero objects!";
        cout<<" "<<endl;
    }
    catch (Array::xTooBig)
    {
        cout<<"This array is too big..."<<endl;
    }
    catch (Array::xTooSmall)
    {
        cout<<"This array is too small..."<<endl;
    }
    catch(...)
    {
        cout<<"Something went wrong!"<<endl;
    }
    cout<<"Done. "<<endl;
     return 0;
}

   
   
