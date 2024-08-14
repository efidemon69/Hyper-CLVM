#pragma once

using Byte = uint8_t;
using Word = uint32_t;
using Address = uint32_t;
using Value = int32_t;

using BytecodeFunction = void( * )( Byte* );
using OpcodeHandler = void( * )( void* );

struct StackFrame 
{
    Address return_address;
};

struct Function
{
    Address entry_point;
    size_t num_locals;
    // .....
};

struct VMState 
{
    std::vector<Value> stack;        
    std::vector<Byte> memory;        
    std::unordered_map<Address, Function> functions;
    std::vector<StackFrame> call_stack;
};

struct Bytecode 
{
    Byte* data;      // ptr -> bytecode data
    size_t size;     // whats this??
};

constexpr size_t MAX_STACK_SIZE = 1024;
constexpr size_t MAX_MEMORY_SIZE = 65536;
constexpr size_t MAX_FUNCTIONS = 256;

inline auto is_address_valid( Address address, size_t memory_size ) -> bool
{
    return address < memory_size;
}

inline auto is_value_valid( Value value ) -> bool
{
    return value >= INT32_MIN && value <= INT32_MAX;
}