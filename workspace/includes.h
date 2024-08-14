#pragma once

#include <Windows.h>
#include <iostream>
#include <stdexcept>
#include <cstring>
#include <cstdint>
#include <cstddef>
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include <functional>

#include "Luau/lua.h"
#include "Luau/lualib.h"
#include "Luau/lauxlib.h"

#include "engine/opcode_definitions.h"
#include "engine/types.h"

#include "engine/memory/memory_manager.h"
#include "engine/stack/stack_manager.h"
#include "engine/instructions/instruction_dispatcher.h"
#include "engine/hooks/custom_hooks.h"

#include "engine/bytecode/bytecode_encoder.h"
#include "engine/bytecode/bytecode_loader.h"

#include "security.h"

#include "engine/clvm_errors.h"
#include "engine/clvm/clvm.h"

class start
{
public:
	static auto main( ) -> int;
};