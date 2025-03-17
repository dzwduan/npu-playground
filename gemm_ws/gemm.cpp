#include "gemm.h"



Gemm::Gemm(SimulationConfig config, MappingTable mapping_table,
    std::vector<uint32_t> input_shape,
    std::vector<uint32_t> weight_shape,
    std::vector<uint32_t> output_shape)
: Operation(config) {

_input_shape = input_shape;
_weight_shape = weight_shape;
_output_shape = output_shape;

 // input dim0 = IH dim1 = IC
 // weight dim0 = IC_w, dim1 = OC
 IHdim = 0;
 ICdim = 1;
 ICdim_w = 0;
 OCdim = 1;
}