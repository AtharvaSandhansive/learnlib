//arrays.cpp
#include <iostream>

int arrays(){

    //Arrays
    //declaring a arr; telling os to  create an array with the elements inside it
    int scores[5] = {1, 2, 3, 4, 5};
    /*ASM:
        mov     DWORD PTR [rbp-32], 1
        mov     DWORD PTR [rbp-28], 2
        mov     DWORD PTR [rbp-24], 3
        mov     DWORD PTR [rbp-20], 4
        mov     DWORD PTR [rbp-16], 5
    */
    //creating a contigious block of memeory

    
    int* k = new int[5]; 
    /*ASM:
        mov     edi, 20
        call    "operator new[](unsigned long)"
        mov     QWORD PTR [rbp-8], rax
    
    */
    /*
        Requests dynamic storage sufficient for 5 int objects.
        If int is 4 bytes: 5 × 4 = 20 bytes
        The C++ dynamic allocation machinery obtains suitable storage
        and returns the address of the first element.

        k stores that address. iT only stores the memory address of the first block/ index 0
    */

    //acessing the first element of the array since k is mem address of 1st element
    int k0 = *k; 
    /*ASM:
        mov     rax, QWORD PTR [rbp-8]
        mov     eax, DWORD PTR [rax]
        mov     DWORD PTR [rbp-12], eax
    */

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
