#pragma once

class CustomHooks 
{
public:
    using HookCallback = std::function<void( )>;

    CustomHooks( ) = default;

    auto set_before_instruction_hook( HookCallback callback ) -> void;
    auto set_after_instruction_hook( HookCallback callback ) -> void;
    auto set_on_error_hook( HookCallback callback ) -> void;

    auto call_before_instruction( ) -> void;
    auto call_after_instruction( ) -> void;
    auto call_on_error( ) -> void;

private:
    HookCallback before_instruction_hook;
    HookCallback after_instruction_hook;
    HookCallback on_error_hook;
};