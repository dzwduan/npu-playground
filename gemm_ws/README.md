# implement a gemm flow

1. get_ws_config
2. op_factory init
3. SystolocWs init
4. Op init (make gemmWs)
  1. Read mapping_table
  2. Set output_shape , weight_shape
  3. Op get config
  4. Op initialize tiles by mapping_table
5. Do simulation (cal cycle) 先不细看