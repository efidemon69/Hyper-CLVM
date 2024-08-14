#pragma once

class InstructionDispatcher 
{
public:
    explicit InstructionDispatcher( void* bytecode );

    auto run( ) -> void;
    auto push_value( int value ) -> void;
    auto pop_value( ) -> void;
    auto add( ) -> void;
    auto subtract( ) -> void;
    auto multiply( ) -> void;
    auto divide( ) -> void;

    auto load( int address ) -> void;
    auto store( int address, int value ) -> void;

    auto call( int address ) -> void;
    auto ret( ) -> void;
    auto jump( int address ) -> void;
    auto jump_if( bool condition, int address ) -> void;

    auto fetch_opcode( ) -> int;
    auto fetch_value( ) -> int;
    auto fetch_address( ) -> int;
    auto fetch_condition( ) -> bool;

private:
    void* bytecode;
};