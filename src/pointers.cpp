//pointers.cpp

//NOTE: This code is not for exectuting but only reading, do not dare compile it!
int pointers(){

    //Variables
    /*
        int a = 42;

        |--------a---------|
        ____________________
        |  0x10001         | <-- Memory address (MemBlock)
        |__________________| 
        |  0101010         | <--  Actual data (42) (DataBlock)
        |__________________|
        |-----4 bytes------|
        
        This is not how the actual memory looks, one should note. 
        This is rather a simplified abstraction made by me to understand concepts better
        and hence should not be cemented as actual memory.
        Actual memory looks like this;

        Address             Memory
        ────────────────────────────
        0x10000             ??
        0x10001             ??
        0x10002             ??
        0x10003             ??
        0x10004             ??
        ...
        
        And an int occupies some consecutive bytes somewhere in that address space
        So int a = 42 doesnt look like the earlier block but like;

        Address      Byte
        ────────────────────
        ...
        0x0FFFF      xx
        0x10000      xx  ←┐
        0x10001      xx   │
        0x10002      xx   │  one int object
        0x10003      xx  ←┘
        0x10004      xx
        ...
        
        The address of a conventionally refers to the starting address of the object, 
        0x10000 in this example.
        SO the correct mental pic is this;

        a
        │
        │ refers to
        ↓
        Memory
        ─────────────────────────────
        0x10000 │ xx │ (Byte 1)
        0x10001 │ xx │ (Byte 2)
        0x10002 │ xx │ (Byte 3)
        0x10003 │ xx │ (Byte 4)
        ─────────────────────────────
        ↑
        &a

        Where address of a (&a) will always refer to first address in this case Byte 1
        But this is shit to remember, atleast for me, so I would be using the abstract memory
        blocks i made than this.
        Then how does the compiler knows where the variable in the memory is ended?
        Because we know where the integer a in memory starts because &a is the memory address
        of first byte but there is no diffrentiation between the last byte of a and the next
        byte ;

        Address      Byte
        ────────────────────
        ...
        0x0FFFF      xx
        0x10000      xx <-- &a (a starts here)
        0x10001      xx   
        0x10002      xx   
        0x10003      xx  <-- var a ends here conceptually
        0x10004      xx  <-- some bullshit value, but how to differ a from this now?!
        ...        

        SInce memory is just a giant ocean of bullshit values when percieved as all
        but senseful when diffrentiated, the compiler keeps ledger table like;

        The Compiler's Secret Ledger (Symbol Table):
        ┌───────┬───────────┬───────────┐
        │ Name  │ Data Type │  Address  │
        ├───────┼───────────┼───────────┤
        │   a   │    int    │  0x10000  │
        │   b   │   float   │  0x10004  │
        └───────┴───────────┴───────────┘

        The compiler looks at this ledger and generates entirely different machine code 
        instructions based on the data type, even though the sizes match:
        1. For a (int): The compiler tells the CPU, "Go to 0x10000, grab 4 bytes, 
        and decode them using integer math circuitry."
        2. For b (float): The compiler tells the CPU, "Go to 0x10004, grab 4 bytes, 
        and decode them using floating-point math circuitry."
        The data type dictates the lens through which the bytes are viewed.

        This is exactly why you cannot just declare a generic pointer like pointer p;. 
        You must specify the type: int* p; or float* p;.
        When you type *p1, the compiler reads the instruction manual, grabs 4 bytes, 
        and treats them as a whole number.
        C++ actually lets you strip away the instruction manual completely 
        using a void* (a void pointer). A void* is a purely blind pointer. 
        It stores a memory address, but because it has no type, 
        the compiler has no idea where the variable ends or what the fuck it is
        We'll see this in the void pointer section
    */

    //assigning a variable
    int a = 42;

    //sizeof() returns the memory size of the variable or in profesional lingo
    //gives the size in bytes of the type of its operand, or of the type itself.
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

    //Pointers
    int* p = &a;
    /*
        Pointer is a variable that stores memory address of another variable.
        Its a object whose stored value is a pointer value.
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
        |  0x10005         | <-- &p (memory address of p)
        |__________________| 
        |  0x10001         | <--  Memory address of a
        |__________________|
        |-----8 bytes------|

        Pointers can store values like
        1. the address of an object
        2. the address of a function in appropriate contexts
        3. a null pointer
        4. a past-the-end pointer
        etc.

        SUMMARY:
        p   → "What value does the pointer contain?"
        &p  → "Where is the pointer object itself?"
        *p  → "What object does that pointer point at?"
    */

    /*
        Why create a pointer at all?
        If I have var a and I can get its memory address by simply &a,
        Why do i waste space creating another variable for storing that address 
        when i can simply do '&a'? Seems counter-intuitive.

        The same reason we use variables at the first place.
        Technically you can hard code the int value 67 everywhere, 
        then why did you created a variable 'a for storing at all?
        Because a variable is something that can be changed, passed around, and redirected.
        Similarly a pointer can too.

        &a is not a permanant handle, because the address of a changes every instance of the
        program. When I run a program compiler just finds an empty place in the heap
        and allocates it to this variable, and every instance it changes.
        On instance 1, &a = 0x01110, on another instance &a = 0x11101 and so on...
        It is hence impossible to keep the address with hardcoding. 
        
        ALso in heap memory, when you create memory dynamically using new 
        there is no named variable like a to begin with. 
        The memory is allocated anonymously out in the heap. 
        The only way to know where it is, use it, or delete it later is to capture its 
        address in a pointer variable.
        Also a pointer isn't a fixed value, since its a variable, its value,
        i.e. the thing it is pointing can be changed whereas &a is readonly and 
        permanant for that instance.
        It is like a GPS device, of which you can change its target.

        This allows us to access the same data in memory rather than copying it again and
        again, which for massive data like databases or 3d objects is not feasible.

        Pointers aren't only about accessing an existing variable.
        They allow you to work with things whose addresses you don't know beforehand.
        To summarize
        &a says "Where is a?"
        ptr says "I remember where a is"

        The extra storage buys you persistant reference of that variaable or function,
        indirection, ability to change target, to store relationships, to represent
        dynamic objects, to pass around addresses etc.
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
        It stores '0x0' in their pointing value

        |--------n---------|
        ____________________
        |  0x10006         | <-- memory address of n
        |__________________|  
        |  0x0             | <-- stores virtually nothing i.e. points to nothing
        |__________________|
        |-----8 bytes------|

        Uses of Null Pointer:
        1. Pointer Initialization: You can assign a null value to a pointer when you declare 
        it if you do not have a valid memory address to give it yet
        2. Error Signaling: Functions return a null pointer to show that an operation failed, 
        such as when malloc fails to allocate memory or fopen fails to open a file or
        the system failed to find a person id in a database
        3. Sentinel Values: Data structures like linked lists use a null pointer in the 
        final node to mark the end of the sequence.
        4. Safety and Error Prevention: Programmers use conditional statements to check 
        if a pointer is null before trying to read or write to the memory address it references
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
    int* val_ptr = new int (67);
    delete val_ptr;
    val_ptr = nullptr; //reset it
    /*
        Here we created an int val and assign value 67 to it.
        We then create a pointer val_ptr and point it to val.
        delete val_ptr does not delete val_ptr but the variable it is pointing to!!
        delete val_ptr in C++ or free(val_ptr) in C says;
        "Go to the memory address stored inside val_ptr, and free up that block 
        of heap memory so I can use it for something else in future"
        So delete val_ptr deleted val, that is memory of val was freed, but
        val_ptr still exists, now pointing to nothing, this is a dangling pointer
        This may cause problems and crashes, hence we always reset it to point nothing 

        NOTE: When we call delete, the binary data for 67 is still sitting in the same
        memory location as before, untouched because cleaning or freeing up space
        consumes cpu cycles. Instead the compiler simply marks in its ledger table that
        this memory address is "available". This is called "garbage data".
        So val remains untouched and so does val_ptr, it is still pointing to val,
        but since the compiler already market it "available" in its ledger, this causes
        the danger of dangling pointer.
    */

    //Difference between this
    int value = 69;
    int* value_ptr1 = &value;
    //and this
    int* value_ptr2 = new int (69);
    /*
        While both result in a pointer (val_ptr) pointing to a value,
        they handle memory management, lifetime, and locations completely differently.
        THe primary diffrentation is *where* this are stored.

        1. Heap Approach (dynamic)
        This int* val_ptr = new int(67); uses the new keyword which bypasses the local scope 
        entirely. It goes out the to the system heap, allocates a fresh 4-byte and drops 
        value 67 inside it. It then hands back back this anonymous address and saves it 
        inside the val_ptr. If the function ends, val_ptr disappears, 
        but the box containing 67 stays on the heap forever (a memory leak) 
        unless you explicitly wrote delete val_ptr; beforehand.

        2. Stack approach 
        The runtime automatically allocates a 4-byte box named val on the stack 
        frame of the current function. Then, val_ptr is created and simply takes a 
        peek at val's address. You do not own this memory’s lifecycle. 
        The millisecond the execution path exits the curly braces {} enclosing this code, 
        val is instantly destroyed. If you try to use val_ptr after that, it becomes a 
        dangling pointer pointing to dead stack memory.        

    */

    return 0;
}