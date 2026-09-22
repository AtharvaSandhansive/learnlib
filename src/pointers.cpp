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
    //
    /*
        ASM: mov DWORD PTR [rbp-4], 42
        rbp: This a 
    */

    //sizeof() returns the memory size of the variable or in profesional lingo
    //gives the size in bytes of the type of its operand, or of the type itself.
    int size_of_a = sizeof(a);
    //ASM: mov DWORD PTR [rbp-8], 4
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
    /*ASM:
        lea rax, [rbp-20]
        mov QWORD PTR [rbp-16], rax
    */
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
    /*ASM:
        mov rax, QWORD PTR [rbp-16]
        mov eax, DWORD PTR [rax]
        mov DWORD PTR [rbp-20], eax
    */
    //now b = whatever p is pointing to and p is pointing to a, so b = a

    //Multiple pointers; u can create pointers for pointers, pointers for everyone!
    int** q = &p; //double pointer
    /*ASM:
        lea rax, [rbp-32]
        mov QWORD PTR [rbp-16], rax 
    */

    int*** r = &q; //triple pointer
    /*ASM
        lea rax, [rbp-40]
        mov QWORD PTR [rbp-16], rax
    */
    //Null pointers
    int* n = nullptr;
    //ASM: mov QWORD PTR [rbp-24], 0
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
    /*ASM:
        lea rax, [rbp-36]
        mov QWORD PTR [rbp-32], rax
    */
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
    /*ASM:
        "main"
                mov     edi, 4
                call    "operator new(unsigned long)"
                mov     DWORD PTR [rax], 67
                mov     edx, 0
                mov     QWORD PTR [rbp-8], rax
                test    dl, dl
                je      .L2
                mov     esi, 4
                mov     rdi, rax
                call    "operator delete(void*, unsigned long)"
        .L2:
                mov     rax, QWORD PTR [rbp-8]
                test    rax, rax
                je      .L3
                mov     esi, 4
                mov     rdi, rax
                call    "operator delete(void*, unsigned long)"
        .L3:
                mov     QWORD PTR [rbp-8], 0
    */
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
    /*ASM
        For;
        int value = 69;
        int* value_ptr1 = &value; ->

        mov     DWORD PTR [rbp-20], 69
        lea     rax, [rbp-20]
        mov     QWORD PTR [rbp-8], rax

        For;
        int* value_ptr2 = new int (69); ->

        mov     edi, 4
        call    "operator new(unsigned long)"
        mov     DWORD PTR [rax], 69
        mov     edx, 0
        mov     QWORD PTR [rbp-16], rax
        test    dl, dl
        je      .L2
        mov     esi, 4
        mov     rdi, rax
        call    "operator delete(void*, unsigned long)"
    */
    /*
        While both result in a pointer (val_ptr) pointing to a value,
        they handle memory management, lifetime, and locations completely differently.
        THe primary diffrentation is *where* this are stored.

        1. Heap Approach (dynamic)
        This int* val_ptr = new int(67); uses the new keyword which bypasses the local scope 
        entirely. It goes out the to the system heap (by invokinh the operator new call), 
        allocates a fresh 4-byte and drops value 67 inside it. 
        It then hands back back this anonymous address and saves it 
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

/*
    DIFFERENCE BETWEEN STACK and HEAP

    Both are areas in memory for storage associated with a running program, but they have
    different alloc. mechanics, lifetime and purposes

    1. STACK:
     The stack is used for automatic storage associated with function
    execution.

    When a function is called, it gets a stack frame (activation record)
    Local variables can be stored within this frame.

        int value = 69;
    
        Stack
        ┌─────────────────────┐
        │ function frame      │
        │                     │
        │ value = 69          │
        │                     │
        └─────────────────────┘
                  ↑
             stack pointer /
             frame pointer

    When the function's execution ends, its stack frame is removed.
    Therefore, objects with automatic storage duration normally cease
    to exist when their scope/lifetime ends.

    Example:
        void function(){

            int value = 69;
            int* ptr = &value;

        } // value's lifetime ends here

    ptr must not be used to access value after value's lifetime ends.
    The pointer would be dangling.

    2. HEAP

    Dynamic storage is used when we need an object's lifetime to be
    controlled independently of the current scope.

        int* ptr = new int(69);


        Stack                         Dynamic Storage

        ┌───────────────┐             ┌───────────────┐
        │ ptr           │────────────→│      69       │
        │ 0x...         │             │               │
        └───────────────┘             └───────────────┘

        ptr itself is a local variable.
        The int object it points to has dynamic storage duration.

    The pointer variable and the object it points to are therefore
    TWO DIFFERENT objects with potentially different lifetimes.

    The pointer can disappear while the dynamically allocated object
    remains alive.

    {
        int* ptr = new int(69);
    }

    Here ptr disappears at the end of the scope, but the dynamically
    allocated int has not been released.

    The allocation has therefore become unreachable, producing a memory leak.

    To release the dynamically allocated object:delete ptr;

    3. IMPORTANT DIFFERENCES:
    Stack: Storage lifetime is tied to automatic execution/scope.

    Dynamic storage: Storage lifetime is explicitly managed through the dynamic allocation 
    mechanism.

    Therefore:

        int value = 69;

        value -> object with automatic storage duration
        

        int* ptr = new int(69);

        ptr -> pointer object with automatic storage duration

        *ptr -> dynamically allocated int
        
    4. POINTER != HEAP
    "A pointer is stored on the heap."
    No it isnt.
    A pointer is simply an object that stores a pointer value.

    Where the pointer itself is stored depends on how the pointer
    object was created. int* ptr = new int(69);

    ptr may be stored in the current function's stack frame while
    the int it points to exists in dynamic storage.

    Therefore:POINTER LOCATION!=LOCATION OF OBJECT IT POINTS TO

    5. STACK DOESNT MEAN VARIABLE and HEAP DOESNT MEAN PTR
    These are storage/lifetime concepts, not data types.

    int value = 69;

    creates an int with automatic storage duration.

    int* ptr = &value;

    creates a pointer object with automatic storage duration.

    int* ptr = new int(69);

    creates:
        1. a pointer object with automatic storage duration
        2. an int object with dynamic storage duration

    SIMPLIFIED MODEL:

    PROCESS MEMORY

        ┌─────────────────────────────────────┐
        │              STACK                  │
        │                                     │
        │      function frames                │
        │      local objects                  │
        │      pointer variables              │
        │                                     │
        ├─────────────────────────────────────┤
        │                                     │
        │              ...                    │
        │                                     │
        ├─────────────────────────────────────┤
        │              HEAP                   │
        │                                     │
        │      dynamically allocated          │
        │      storage                        │
        │                                     │
        └─────────────────────────────────────┘


*/

/*
    <higher address>

1. Setup 
[main's base] 0x1000 <- rbp
[MAIN'S local data] 0x99C-0x968 (local data used)
[Top of main() stack] 0x960 <- rsp (lowest element in stack as of now) 

2. call "caller()"
[main's base] 0x1000 <- rbp
...
[MAIN'S local data] 0x960 
[ADDR_MAIN_NEXT] 0x958 <- rsp 

Apparantly this ADDR_MAIN_NEXT is some kind of instruction that tells cpu to load the instruction in RIP register, because giving CPU only the address of main function (0x1000) to return isnt enough, the cpu needs to know what to do with this address, correct me if im wrong but thats dementia on another level

3. The execution pointer jumps to caller() now, and now we store the actual return address for main(). SO rsp moves down again by 8 bytes
[main's base] 0x1000 <- rbp
...
[MAIN'S local data] 0x960 
[ADDR_MAIN_NEXT] 0x958
[0x1000 (return address of main)] 0x950 <- rsp (moved down by 8 bytes)

4. mov rbp, rsp : This instruction makes rbp copies the current address held in rsp (0x950), this anchors the base pointer for caller()
[main's base] 0x1000
...
[MAIN'S local data] 0x960 
[ADDR_MAIN_NEXT] 0x958
[0x1000 (return address of main)] 0x950 <- rsp, rbp (rbp moved to rsp pos)

5. sub rsp, 16
This subtracts 16 bytes from rsp memory address 
[main's base] 0x1000
...
[MAIN'S local data] 0x960 
[ADDR_MAIN_NEXT] 0x958
[0x1000 (return address of main)] 0x950 <- rbp (acts as a frozen anchor)
[empty] 0x94C
[empty] 0x948
[empty] 0x944 <- rsp

6. mov DWORD PTR [rbp-4], 6 and mov DWORD PTR [rbp-8], 7: This is saying move 6 at memory positionm rbp-4 and 7 at rbp - 8
[main's base] 0x1000
...
[MAIN'S local data] 0x960 
[ADDR_MAIN_NEXT] 0x958
[0x1000 (return address of main)] 0x950 <- rbp (acts as a frozen anchor)
[6] 0x94C
[7] 0x94C ([rbp-4] = 0x950 - 4 = 0x94C)
[empty space for c (return of add())] 0x944 <- rsp ([rbp-8] = 0x950 - 4 = 0x944)

7. Now we prepare arguments for add() function since add() taks two arguments as add(int a, int b)
If it didnt took any parameters this step would be skipped)
mov edx, DWORD PTR [rbp-8] Copies data inside from [rbp-8] (6) to edx (lower half of rdx) register
mov eax, DWORD PTR [rbp-4] Copies data inside from [rbp-4] (7) to eax (lower half of rax) register

SInce this exist in register not stack, there wont be a stakc representation here

8. call    "add(int, int)"
This calls the add function now, so the execution pointer jumps here.
The cpu drops rsp by 8 bytes and put the instruction for returning back to caller, ADDR_CALLER_NEXT

[main's base] 0x1000
...
[MAIN'S local data] 0x960 
[ADDR_MAIN_NEXT] 0x958
[0x1000 (return address of main)] 0x950 <- rbp 
[6] 0x94C
[7] 0x948 
[empty space for c (return of add())] 0x944
[ADDR_CALLER_NEXT] 0x938 <- rsp

9. push rbp
Now we are inside add(int, int). now we push the address of caller() base back so we can go back to caller() after executing add(), since we added the instruction for it (ADDR_CALLER_NEXT) we now give it the address to go back where i.e. address of base of caller() i.e. where we left rbp anchoered i.e. address of rbp. THATS The whole game... 
SO push rsp by 8 bytes again to store the address of rbp

[main's base] 0x1000
...
[MAIN'S local data] 0x960 
[ADDR_MAIN_NEXT] 0x958
[0x1000 (return address of main)] 0x950 <- rbp 
[6] 0x94C
[7] 0x948 
[empty space for c (return of add())] 0x944
[ADDR_CALLER_NEXT] 0x938
[0x950 (*[rpb])] 0x930 <- rsp 

10. mov rbp, rsp
Second line inside add(). SImilar to caller() back we make rbp copies rsp (0x930) to set up add's temporary base i.e. move rbp to where rsp is now...

[main's base] 0x1000
...
[MAIN'S local data] 0x960 
[ADDR_MAIN_NEXT] 0x958
[0x1000 (return address of main)] 0x950 (rbp previous position)
[6] 0x94C
[7] 0x948 
[empty space for c (return of add())] 0x944
[ADDR_CALLER_NEXT] 0x938
[0x950 (*[rpb])] 0x930 <- rsp, rbp

11. add eax, edx
This is where the actual operatiojn happen. back in point 7, we put the values from stack in  the register which are still there
This literally means eax = eax + edx = 6 + 7 = 13

12. pop rbp
THis does two things
a. It looks at where rsp is pointing right now (0x930), reads the value stored there (0x950), and forces that value back into the rbp register
SO it says Hey rbp where you are check the address inside and jump to it (i.e. 0x950)

[main's base] 0x1000
...
[MAIN'S local data] 0x960 
[ADDR_MAIN_NEXT] 0x958
[0x1000 (return address of main)] 0x950 <- rbp
[6] 0x94C
[7] 0x948 
[empty space for c (return of add())] 0x944
[ADDR_CALLER_NEXT] 0x938
[0x950 (*[rpb])] 0x930 <- rsp

b. it increments rsp by 8 bytes i.e. moves up rsp

[main's base] 0x1000
...
[MAIN'S local data] 0x960 
[ADDR_MAIN_NEXT] 0x958
[0x1000 (return address of main)] 0x950 <- rbp
[6] 0x94C
[7] 0x948 
[empty space for c (return of add())] 0x944
[ADDR_CALLER_NEXT] 0x938 <- rsp
[0x950 (*[rpb])] 0x930 

13. ret
The ret instruction does two things automatically:
a. It pops the value at the current rsp (0x938), which is ADDR_CALLER_NEXT, and throws it directly into the RIP (Instruction Pointer) register. This cures the CPU's dementia; the execution pointer instantly flashes back to caller()
so RIP = *[rsp] = *[0x938] 
b. It increments rsp by 8 bytes (0x938 -> 0x944)

[main's base] 0x1000
...
[MAIN'S local data] 0x960 
[ADDR_MAIN_NEXT] 0x958
[0x1000 (return address of main)] 0x950 <- rbp
[6] 0x94C
[7] 0x948 
[empty space for c (return of add())] 0x944 <- rsp (back at caller's top element baby!)
[ADDR_CALLER_NEXT] 0x938
[0x950 (*[rpb])] 0x930 

14.  mov DWORD PTR [rbp-12], eax
This basically gets back the calculated result by the add() function at the rbp-12 position i.e. 0x950-12 = 0x944, the space reserved for C i.e. rsp is currently now

[main's base] 0x1000
...
[MAIN'S local data] 0x960 
[ADDR_MAIN_NEXT] 0x958
[0x1000 (return address of main)] 0x950 <- rbp
[6] 0x94C
[7] 0x948 
[13] 0x944 <- rsp

15. nop (no operation)
This tells cpu to do absolutely nothing for one cpu cycle.
If a function ends a little too early and leaves an uneven gap in memory, the compiler will pad the empty space with nop instructions. This ensures that the next function starts at a perfectly aligned, clean memory address so the CPU can read it at maximum speed. THis is unopt code o0 so thats why maybe it have added that

16. leave
leave does two operations at once mov rsp, rbp and pop rbp
a. mov rsp, rbp

[main's base] 0x1000
...
[MAIN'S local data] 0x960 
[ADDR_MAIN_NEXT] 0x958
[0x1000 (return address of main)] 0x950 <- rbp, rsp 
[6] 0x94C
[7] 0x948 
[13] 0x944

b. pop rbp

Tells rbp to read the address inside i.e. 0x1000 and jump there and also increments rsp by one address

[main's base] 0x1000 <- rbp (restored to main)
...
[MAIN'S local data] 0x960 
[ADDR_MAIN_NEXT] 0x958 <- rsp
[0x1000 (return address of main)] 0x950
[6] 0x94C
[7] 0x948 
[13] 0x944

17. ret
Just like before, The CPU pops ADDR_MAIN_NEXT from 0x958 into the RIP register and rsp moves up 8 bytes (0x958 -> 0x960)
[main's base]                        0x1000 <- rbp
...
[MAIN'S local data]                  0x960  <- rsp
[ADDR_MAIN_NEXT] 0x958 

We are now fully back to main. Loop at the starting and ending state of the stack
[main's base] 0x1000 <- rbp
[MAIN'S local data] 0x99C-0x968 (local data used)
[Top of main() stack] 0x960 <- rsp (lowest element in stack as of now) 

Perfect end.

<lower address>
*/