#include <stack>
#include <iostream>
#include <stack>

// memory layout is 16 bits wide , 'cause the execs are 16 bits long
namespace chipmem { 
    using chipstack = std::stack<uint16_t>;
    class chip8c { 
        private: 
            uint8_t memory[4096];
            //16x8 grid where every row is a register V0 - VE 
            uint8_t gpr[16];
            uint16_t ind_reg;
            uint16_t pc ; 
            chipstack cstack ;
            bool poweron = 0;
            //
            void decode();
            void fetch_dec_exec() ;

        public: 
            chip8c ( bool boot ) 
             : poweron ( boot ) { 
            //
                uint8_t sprites [80] = { 
                0xF0, 0x90, 0x90, 0x90, 0xF0,  // 0
                0x20, 0x60, 0x20, 0x20, 0x70,  // 1
                0xF0, 0x10, 0xF0, 0x80, 0xF0,  // 2
                0xF0, 0x10, 0xF0, 0x10, 0xF0,  // 3
                0x90, 0x90, 0xF0, 0x10, 0x10,  // 4
                0xF0, 0x80, 0xF0, 0x10, 0xF0,  // 5
                0xF0, 0x80, 0xF0, 0x90, 0xF0,  // 6
                0xF0, 0x10, 0x20, 0x40, 0x40,  // 7
                0xF0, 0x90, 0xF0, 0x90, 0xF0,  // 8
                0xF0, 0x90, 0xF0, 0x10, 0xF0,  // 9
                0xF0, 0x90, 0xF0, 0x90, 0x90,  // A
                0xE0, 0x90, 0xE0, 0x90, 0xE0,  // B
                0xF0, 0x80, 0x80, 0x80, 0xF0,  // C
                0xE0, 0x90, 0x90, 0x90, 0xE0,  // D
                0xF0, 0x80, 0xF0, 0x80, 0xF0,  // E
                0xF0, 0x80, 0xF0, 0x80, 0x80  // F
            };
            //
                memset(memory , 0 , sizeof(memory));
                pc = 0x200;
                ind_reg = 0x0;
                memset(gpr , 0x0 ,sizeof(gpr)) ;
                memcpy(&memory[0x0040] , sprites , sizeof(sprites)) ;
                if ( poweron ) { 
                    fetch_dec_exec();
                }
            }
            // flow control
            void op_1NNN_jump(uint16_t nnn);
            void op_2NNN_call(uint16_t nnn);
            void op_00EE_return();
            void op_BNNN_jump_v0(uint16_t nnn);
            // display
            void op_00E0_clear();
            void op_DXYN_draw(uint8_t x, uint8_t y, uint8_t n);      
            //conditionals 
            void op_3XNN_skip_eq(uint8_t x, uint8_t nn);
            void op_4XNN_skip_neq(uint8_t x, uint8_t nn);
            void op_5XY0_skip_reg_eq(uint8_t x, uint8_t y);
            void op_9XY0_skip_reg_neq(uint8_t x, uint8_t y);
            //math&logic
            void op_7XNN_add(uint8_t x, uint8_t nn);
            void op_8XY0_assign(uint8_t x, uint8_t y);
            void op_8XY1_or(uint8_t x, uint8_t y);
            void op_8XY2_and(uint8_t x, uint8_t y);
            void op_8XY3_xor(uint8_t x, uint8_t y);
            void op_8XY4_add_carry(uint8_t x, uint8_t y);
            void op_8XY5_sub(uint8_t x, uint8_t y);
            void op_8XY6_shr(uint8_t x);
            void op_8XY7_sub_inv(uint8_t x, uint8_t y);
            void op_8XYE_shl(uint8_t x);
            // constants 
            void op_6XNN_set(uint8_t x, uint8_t nn);
            void op_CXNN_rand(uint8_t x, uint8_t nn);
            // memory 
            void op_ANNN_set_index(uint16_t nnn);
            void op_FX1E_add_index(uint8_t x);
            void op_FX29_set_sprite(uint8_t x);
            void op_FX33_bcd(uint8_t x);
            void op_FX55_reg_dump(uint8_t x);
            void op_FX65_reg_load(uint8_t x);
            // keypad 
            void op_EX9E_skip_key_pressed(uint8_t x);
            void op_EXA1_skip_key_notpressed(uint8_t x);
            void op_FX0A_await_key(uint8_t x);
            // timers 
            void op_FX07_get_delay(uint8_t x);
            void op_FX15_set_delay(uint8_t x);
            void op_FX18_set_sound(uint8_t x);
            // 
            bool checkbounds(uint16_t addr ) { 
                return !(addr < 200 || addr > 4096);
            }
    };
}