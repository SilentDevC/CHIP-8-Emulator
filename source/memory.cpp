#include "../header/memory.hpp"
#include "SDL2/SDL.h"
namespace chipmem   {
    /// @brief these op codes are responisble for the flow control
    /// @param addr 
    void chip8c::op_1NNN_jump(uint16_t addr) { 
        if ( checkbounds(addr) ) this->pc = addr;
    }
    void chip8c::op_2NNN_call(uint16_t addr) { 
        if ( checkbounds(addr) ) { 
            this->cstack.push(this->pc);
            this->pc = addr;
        } 
    }
    void chip8c::op_00EE_return() { 
        this->pc = this->cstack.top();
        this->cstack.pop();
    }
    void chip8c::op_BNNN_jump_v0(uint16_t size) {
        this->pc = pc + size;
    } 
    ///
    void chip8c::op_00E0_clear() { 
        
    }

} // namespace chipmem 
