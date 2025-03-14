#include "common.h"
#include "Tensor.h"

class Model {
    private:
    std::string onnx_model_path;
    std::string name;
    

    public:
    Model();
    void init_model(std::vector<std::unique_ptr<Tensor>>& weight_table);
    void init_weight();
};
