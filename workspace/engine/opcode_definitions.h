#pragma once

// thanks to fucking google i aint writing allat
enum class Opcode : uint8_t
{
    NOP,         // No operation
    PUSH,        // Push value onto the stack
    POP,         // Pop value from the stack
    ADD,         // Add top two values on the stack
    SUB,         // Subtract top two values on the stack
    MUL,         // Multiply top two values on the stack
    DIV,         // Divide top two values on the stack
    LOAD,        // Load value from memory
    STORE,       // Store value to memory
    CALL,        // Call function
    RET,         // Return from function
    JUMP,        // Unconditional jump
    JUMP_IF,     // Conditional jump
    HALT,        // Halt execution
    OP_MAX       // Maximum value for opcode range checks
};

inline auto opcode_to_string( Opcode opcode ) -> const char*
{
    switch ( opcode ) 
    {
        case Opcode::NOP:       return "NOP";
        case Opcode::PUSH:      return "PUSH";
        case Opcode::POP:       return "POP";
        case Opcode::ADD:       return "ADD";
        case Opcode::SUB:       return "SUB";
        case Opcode::MUL:       return "MUL";
        case Opcode::DIV:       return "DIV";
        case Opcode::LOAD:      return "LOAD";
        case Opcode::STORE:     return "STORE";
        case Opcode::CALL:      return "CALL";
        case Opcode::RET:       return "RET";
        case Opcode::JUMP:      return "JUMP";
        case Opcode::JUMP_IF:   return "JUMP_IF";
        case Opcode::HALT:      return "HALT";
        case Opcode::OP_MAX:    return "OP_MAX";
        default:                return "UNKNOWN_OPCODE";
    }
}

// owwmagad is opcode rlly valiiid??!!
inline auto is_valid_opcode( Opcode opcode ) -> bool
{
    return opcode < Opcode::OP_MAX;
}