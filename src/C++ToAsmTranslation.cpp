//C++ToAsmTranslation

int main(){

    /*
        SIZES 
        1. BYTE: 8 bits: char, uint8_t
        2. WORD: 16 bits: short, uint16_t
        3. DWORD (Double WORD): 32 bits: int, float, uint32_t
        4. QWORD (Quad WORD): 64 bits: long long, dounle, uint_64_t
    */

    //assigning a variable
    int a = 42;
    /*
        The instruction means:

            1. Take the value 42.
            2. Calculate the memory address RBP - 4.
            3. Treat that memory operand as 4 bytes wide.
            4. Store the 4-byte representation of 42 at that address.

        In pseudocode: memory[rbp - 4] = 42

        Here:

            mov → copy a value from source to destination

            42 → immediate value

            rbp - 4 → effective memory address

            [rbp-4] → memory located at that address

            DWORD PTR → the memory operand is 32 bits / 4 bytes wide
    */


    return 0;
}