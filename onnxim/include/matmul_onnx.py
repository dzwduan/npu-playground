import torch.nn
import torch.nn.init as init
from pathlib import Path
import json
import os

# set save path
save_path = Path(__file__).parent / '../model'
if not os.path.exists(save_path):
    os.makedirs(save_path, exist_ok=True)

TYPE = torch.int8
M0 = 3
K0 = 4
N0 = 5

# generate random input
in1 = torch.randn(M0, K0)
in2 = torch.randn(K0, N0)

# dump matmul.onnx
class Matmul(torch.nn.Module):
    def __init__(self):
        super(Matmul, self).__init__()

    def forward(self, x, y):
        return torch.matmul(x, y)

model = Matmul()
onnx_path = save_path / 'matmul.onnx'
torch.onnx.export(model, (in1, in2), onnx_path, export_params=True, input_names=['input1', 'input2'], output_names=['output'])
# dump config
config = {
    "models": [
        {
            "name": f"matmul_{M0}x{K0} @ {K0}x{N0}",
            "path": str(onnx_path)
        }
    ]
}

with open(save_path / 'config.json', 'w') as f:
    json.dump(config, f)