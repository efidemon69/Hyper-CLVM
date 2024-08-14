#pragma once

class CLVM 
{
public:
    CLVM( size_t memoryPoolSize, size_t stackSize );
    ~CLVM( ) = default;

    auto load_bytecode( const std::string& lua_code ) -> void;
    auto execute( ) -> void;

private:
    unsigned char* bytecode;
    size_t bytecode_size;

    MemoryManager memoryManager;
    StackManager stackManager;

    std::unique_ptr<InstructionDispatcher> dispatcher;
};