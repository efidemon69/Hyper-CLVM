#include "../../includes.h"

std::vector<int> stack;
std::vector<int> memory;

std::vector<int> call_stack;
unsigned char* program_counter = nullptr; // wow sir

InstructionDispatcher::InstructionDispatcher( void* bytecode ) : bytecode( bytecode ) {}
auto InstructionDispatcher::run( ) -> void 
{
    while ( true ) 
    {
        auto opcode = static_cast< Opcode >( fetch_opcode( ) );
        if ( opcode == Opcode::HALT ) break;

        switch ( opcode ) {
        case Opcode::NOP:
            break;

        case Opcode::PUSH:
            push_value( fetch_value( ) );
            break;

        case Opcode::POP:
            pop_value( );
            break;

        case Opcode::ADD:
            add( );
            break;

        case Opcode::SUB:
            subtract( );
            break;

        case Opcode::MUL:
            multiply( );
            break;

        case Opcode::DIV:
            divide( );
            break;

        case Opcode::LOAD:
            load( fetch_address( ) );
            break;

        case Opcode::STORE:
            store( fetch_address( ), fetch_value( ) );
            break;

        case Opcode::CALL:
            call( fetch_address( ) );
            break;

        case Opcode::RET:
            ret( );
            break;

        case Opcode::JUMP:
            jump( fetch_address( ) );
            break;

        case Opcode::JUMP_IF:
            jump_if( fetch_condition( ), fetch_address( ) );
            break;

        default:
            std::cout << "Unknown opcode: " << static_cast< int >( opcode ) << std::endl;
            throw std::runtime_error( "Unknown opcode" );
        }
    }
}

auto InstructionDispatcher::push_value( int value ) -> void 
{
    stack.push_back( value );
}

auto InstructionDispatcher::pop_value( ) -> void
{
    if ( stack.empty( ) )
    {
        throw std::runtime_error( "Stack underflow" );
    }

    stack.pop_back( );
}

auto InstructionDispatcher::add( ) -> void 
{
    if ( stack.size( ) < 2 )
    {
        throw std::runtime_error( "Not enough values on stack for ADD" );
    }

    auto b = stack.back( ); stack.pop_back( );
    auto a = stack.back( ); stack.pop_back( );
    stack.push_back( a + b );
}

auto InstructionDispatcher::subtract( ) -> void 
{
    if ( stack.size( ) < 2 ) 
    {
        throw std::runtime_error( "Not enough values on stack for SUB" );
    }

    auto b = stack.back( ); stack.pop_back( );
    auto a = stack.back( ); stack.pop_back( );
    stack.push_back( a - b );
}

auto InstructionDispatcher::multiply( ) -> void
{
    if ( stack.size( ) < 2 )
    {
        throw std::runtime_error( "Not enough values on stack for MUL" );
    }

    auto b = stack.back( ); stack.pop_back( );
    auto a = stack.back( ); stack.pop_back( );
    stack.push_back( a * b );
}

auto InstructionDispatcher::divide( ) -> void 
{
    if ( stack.size( ) < 2 ) throw std::runtime_error( "Not enough values on stack for DIV" );

    auto b = stack.back( ); stack.pop_back( );
    auto a = stack.back( ); stack.pop_back( );

    if ( b == 0 ) throw std::runtime_error( "Division by zero" );

    stack.push_back( a / b );
}

auto InstructionDispatcher::load( int address ) -> void
{
    if ( address < 0 || address >= memory.size( ) ) 
    {
        throw std::runtime_error( "Memory address out of range" );
    }

    stack.push_back( memory[ address ] );
}

auto InstructionDispatcher::store( int address, int value ) -> void
{
    if ( address < 0 || address >= memory.size( ) ) 
    {
        throw std::runtime_error( "Memory address out of range" );
    }

    memory[ address ] = value;
}

auto InstructionDispatcher::call( int address ) -> void 
{
    if ( address < 0 || address >= memory.size( ) ) 
    {
        throw std::runtime_error( "Memory address out of range" );
    }

    call_stack.push_back( reinterpret_cast< int >( program_counter ) );
    jump( address );
}

auto InstructionDispatcher::ret( ) -> void
{
    if ( call_stack.empty( ) )
    {
        throw std::runtime_error( "Call stack is empty" );
    }

    auto return_address = call_stack.back( );
    call_stack.pop_back( );
    program_counter = reinterpret_cast< unsigned char* >( return_address );
}

auto InstructionDispatcher::jump( int address ) -> void 
{
    if ( address < 0 || address >= memory.size( ) ) 
    {
        throw std::runtime_error( "Memory address out of range" );
    }

    program_counter = reinterpret_cast< unsigned char* >( address );
}

auto InstructionDispatcher::jump_if( bool condition, int address ) -> void
{
    if ( address < 0 || address >= memory.size( ) )
    {
        throw std::runtime_error( "Memory address out of range" );
    }

    if ( condition ) jump( address );
}

auto InstructionDispatcher::fetch_opcode( ) -> int 
{
    if ( program_counter == nullptr ) 
    {
        throw std::runtime_error( "Program counter is null" );
    }

    auto opcode = *reinterpret_cast< int* >( program_counter );
    program_counter += sizeof( int );
    return opcode;
}

auto InstructionDispatcher::fetch_value( ) -> int 
{
    if ( program_counter == nullptr ) 
    {
        throw std::runtime_error( "Program counter is null" );
    }

    auto value = *reinterpret_cast< int* >( program_counter );
    program_counter += sizeof( int );
    return value;
}

auto InstructionDispatcher::fetch_address( ) -> int
{
    if ( program_counter == nullptr ) 
    {
        throw std::runtime_error( "Program counter is null" );
    }

    auto address = *reinterpret_cast< int* >( program_counter );
    program_counter += sizeof( int );
    return address;
}

auto InstructionDispatcher::fetch_condition( ) -> bool 
{
    if ( program_counter == nullptr )
    {
        throw std::runtime_error( "Program counter is null" );
    }

    auto condition = *reinterpret_cast< bool* >( program_counter );
    program_counter += sizeof( bool );
    return condition;
}