//learning.cpp
#include <iostream>

int main(){

    /*
        int a = 42;

        |--------a---------|
        ____________________
        |  0x10001         | <-- Memory address (MemBlock)
        |__________________| 
        |  0101010         | <--  Actual data (42) (DataBlock)
        |__________________|
        |-----4 bytes------|
        
        This is how memory looks at its infancy. The whole block is labeled a by the compiler.
    */

    //assigning a variable
    int a = 42;

    //sizeof() returns the memory size of the variable 
    int size_of_a = sizeof(a);
    /* c++ has specific sizes for every datatype
        1. char = 1 byte
        2. short = 2 byte
        3. int = 4 byte
        4. long = 4 (in LLP64 model like Windows) or 8 byte (in LP64 model like Linux/macos)
        5. long long = 8 bytes (stupid naming convention, damn you c++!)
        6. float = 4 bytes
        7. double = 8 bytes
    */

    /*
        OPERATORS SUMMARY!
        1. & (Address-of operator): It allows us to access the memory address of the variable 
        2. <datatype>* (Declaring a pointer): A pointer after a datatype declaration says
        that you are declaring a pointer of this datatype exx. int*, char*, void* etc.
        3. *ptr (Dereferencing operator): This says, give me tha data stored at this mem address
        *ptr means give me the data at the memory address ptr is pointing 
    */

//-------------------------------------------------------------------------------------------

    //Pointers
    int* p = &a;
    /*
        Pointer is a variable that stores memory address of another variable.
        Ampersand of variable gives memory address.
        So int* a_address (or pointer) = &a

        |--------a---------|
        ____________________
        |  0x10001         | <-- &a (memory address of a)
        |__________________|  
        |  0101010         | <-- value inside a
        |__________________|
        |-----4 bytes------|

        |--------p---------|
        ____________________
        |  0x10005         | <-- Memory address of itself
        |__________________| 
        |  0x10001         | <--  Memory address of a
        |__________________|
        |-----8 bytes------|
    */

    //deferencing a pointer; accessing the datablock the pointer is pointing to
    int b = *p;
    //now b = whatever p is pointing to and p is pointing to a, so b = a

    //Multiple pointers; u can create pointers for pointers, pointers for everyone!
    int** q = &p; //double pointer
    int*** r = &q; //triple pointer

    //Null pointers
    int* n = nullptr;
    /*
        Null pointers are special type of pointers in which 
        they have their memory address but they point to nothing
        i.e. they have memblock but datablock is 0 or null

        |--------n---------|
        ____________________
        |  0x10006         | <-- memory address of n
        |__________________|  
        |  null            | <-- stores virtually nothing i.e. points to nothing
        |__________________|
        |-----8 bytes------|
    */

    //void pointers
    void* v = &a;
    /*
        Void pointer point to a variable irrespective of its data type

        int pointer (int* p) is:
        |--------a---------|
        ____________________
        |  0x10001         | <-- &p (memory address of p)
        |__________________|  
        |  &integer        | <-- can only point to a variable of datatype integer
        |__________________|
        |-----8 bytes------|

        void pointer (void* p) is:
        |--------v---------|
        ____________________
        |  0x10005         | <-- &p (memory address of p)
        |__________________| 
        |  &void/any       | <--  can point to a variable irrespective to its datatype
        |__________________|
        |-----8 bytes------|

        However, it cannot be dereferenced directly without first being cast 
        back to a specific type because the computer doesn't know how many bytes to read.
        std::cout << *vPtr; // Error! Not allowed
        std::cout << *(static_cast<int*>(vPtr)); First being point to int then deferenced
    */

    //Dangling Pointers
    int val = 67;
    int* val_ptr = &val;
    delete val_ptr;
    val_ptr = nullptr; //reset it
    /*
        Here we created an int val and assign value 67 to it.
        We then create a pointer val_ptr and point it to val.
        delete val_ptr does not delete val_ptr but the variable it is pointing to!!
        delete val_ptr in C++ or free(val_ptr) in C says;
        "Go to the memory address stored inside val_ptr, and free up that block 
        of heap memory so the operating system can use it for something else"
        So delete val_ptr deleted val, that is memory of val was freed, but
        val_ptr still exists, now pointing to nothing, this is a dangling pointer
        This may cause problems and crashes, hence we always reset it to point nothing 
    */


//-----------------------------------------------------------------------------------------
    
    //Arrays
    //declaring a arr; telling os to  create an array with the elements inside it
    int scores[5] = {1, 2, 3, 4, 5};
    //creating a contigious block of memeory

    //asking os to give you 5 blocks of memory
    int* k = new int[5]; //now os has gave me 5blocks of continous memory
    //now k only stores the memory address of the first block/ index 0

    /*
        |--------k0--------|
        ____________________
        |  0x10010         |  
        |__________________|  
        |  null            | 
        |__________________|
        |-----4 bytes------|

        |--------k1--------|
        ____________________
        |  0x10011         |  
        |__________________|  
        |  null            | 
        |__________________|
        |-----4 bytes------|

        |--------k2--------|
        ____________________
        |  0x10012         |  
        |__________________|  
        |  null            | 
        |__________________|
        |-----4 bytes------|
        ...and so on...
    */

    //acessing the first element of the array since k is mem address of 1st element
    int k0 = *k; 

    //to access the next element simple add 1 to the index 0 mem address i.e. k so;
    int k1 = *(k+1);
    //here k+1 refers to memory address of next element and *(k+1) deferences it
    //it is important to note k+1 doesnt add 1 in  memory address but sizeof(*k)
    //that is the size of data type that pointer is pointing to
    //thats why if k is pointer to iny a and store address 1000, k+1 = 1004 since int is 4 bytes

    //when we access an element inside array using index i;
    int i;
    //and suppose we want element 3;
    i = 3;
    //then we put it like k[i];
    int k3 = k[i];
    //this simply can be written as
    int k3 = *(k+i); //or
    int k3 = *(i+k);//since addition is commutative
    //all mean the same thing

    //it uses the formula Address = p * (i + sizeof(T)), where T is sizeof data type, ex. int
    int* k3_address = k + (i * sizeof(*k));
    int* k3_address = k + i;
    int* k3_address = &k[i];
    //so technically k3_address = k + (i * sizeof(k)) = (k+1) = &k[i] since i = 3
    //why not we did this int* k3_address = k + (i * sizeof(k));? because of double-scaling
    int* k3_address_DS = k + (i * sizeof(k));
    /*
        When you write k + i in C++, the compiler automatically multiplies i by 
        the size of the data type for you. This means:
        For us it looks like address = k+i, but compiler does;
        address = k + (i * sizeof(int)) because it reapplies the formula twice!
        If k is address 1000 and sizeof(int) is 4:k + 3 becomes 1000 + (3 * 4) = 1012. (Correct!)
        k + (3 * 4) becomes k + 12. Because of pointer arithmetic, 
        the compiler multiplies that 12 by 4, resulting in 1000 + (12 * 4) = 1048. 
        (Way out of bounds!)
        also k is a pointer; hence sizeof(k) is always 8 bytes since all pointers, no matter the
        datatype are 8 bytes whereas sizeof(*k) is the size of datatype the ptr is pointing to
    */


    return 0;
}