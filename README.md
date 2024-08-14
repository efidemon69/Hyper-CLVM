# Hyper-CLVM
Hyper CLVM is a base for a Custom Lua Virtual Machine. This project is not complete at all and it is just a base.

## Features

- **Lua Bytecode Execution**: Executes Lua bytecode generated from Lua source code. (NOT DONE)
- **Custom Memory Management**: Includes a memory manager with garbage collection. (NOT COMPLETE)
- **Instruction Dispatching**: Handles various Lua instructions with an extensible dispatcher. (NOT COMPLETE)
- **Stack Management**: Supports stack operations for function calls and arithmetic operations. (NOT COMPLETE)
- **Error Handling**: Provides robust error handling during bytecode execution.

### Running the VM

1. Enter a script defined as a string.
2. Load and execute the bytecode in the CLVM:

    ```cpp
    const std::string lua_code = R"( print("clvm in 2034 is real?!!!") )";
    BytecodeEncoder encoder;
    std::vector<unsigned char> bytecode;

    bytecode = encoder.encode( lua_code );
    std::string bytecode_str( bytecode.begin( ), bytecode.end( ) );
    vm.load_bytecode( bytecode_str );
    vm.execute( );
    ```

