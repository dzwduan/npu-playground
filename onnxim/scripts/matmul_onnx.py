import torch.nn
import torch.nn.init as init
from pathlib import Path
import json
import os

# set save path
save_path = Path(__file__).parent / 'model'
if not os.path.exists(save_path):
    os.makedirs(save_path, exist_ok=True)

# generate random input
in1 = torch.randn(3, 4)
in2 = torch.randn(4, 5)

# dump matmul.onnx
class Matmul(torch.nn.Module):
    def __init__(self):
        super(Matmul, self).__init__()

    def forward(self, x, y):
        return torch.matmul(x, y)


model = Matmul()
onnx_path = save_path / 'matmul.onnx'
input1 = torch.zeros((in1.shape[0], in1.shape[1]))
input2 = torch.zeros((in2.shape[0], in2.shape[1]))
torch.onnx.export(model, (input1, input2), onnx_path, export_params=True, input_names=['input1', 'input2'], output_names=['output'])
# dump config
config = {
    "models": [
        {
            "name": "matmul",
            "path": str(onnx_path),
            "input_shapes": [
                [3, 4],
                [4, 5]
            ],
            "output_shapes": [
                [3, 5]
            ]
        }
    ]
}
with open(save_path / 'config.json', 'w') as f:
    json.dump(config, f)