#include <cstdint>
#include <vector>
#include <string>

enum class Opcode {
    MOVIN, MOVOUT, GEMM_PRELOAD, GEMM, GEMM_WRITE, COMP, BAR
};


using addr_type = uint64_t;
constexpr addr_type SPAD_BASE = 0x10000000;
// accumulator 
constexpr addr_type ASPAD_BASE = 0x20000000;
using cycle_type = uint64_t;


class Instr {
    public:
     Instr();
     std::string toString();

     private:
     enum class Type {
        LD_INST, ST_INST, EXE_INST
      };
     uint32_t id; 
     Opcode opcode;
     Type type;
     size_t tile_size;
     //TODO: 为什么要在isa里面考虑？
     cycle_type start_cycle;
     cycle_type finish_cycle;
     std::vector<std::string> dependent_ids;
     std::string dest_id;
     addr_type spad_addr;
     uint32_t spad_size;
     std::vector<addr_type> dram_addrs;
};