# import onnx
# from onnx import helper
# from onnx import AttributeProto, TensorProto, GraphProto


# # Create one input (ValueInfoProto)
# X = helper.make_tensor_value_info('X', TensorProto.FLOAT, [3, 2])
# pads = helper.make_tensor_value_info('pads', TensorProto.FLOAT, [1, 4])
# value = helper.make_tensor_value_info('value', AttributeProto.FLOAT, [1])

# # Create one output (ValueInfoProto)
# Y = helper.make_tensor_value_info('Y', TensorProto.FLOAT, [3, 4])

# # Create a node (NodeProto) - This is based on Pad-11
# node_def = helper.make_node(
#     'Pad', # node name
#     ['X', 'pads', 'value'], # inputs
#     ['Y'], # outputs
#     mode='constant', # attributes
# )

# # Create the graph (GraphProto)
# graph_def = helper.make_graph(
#     [node_def],
#     'test-model',
#     [X, pads, value],
#     [Y],
# )

# # Create the model (ModelProto)
# model_def = helper.make_model(graph_def, producer_name='onnx-example')

# print('The model is:\n{}'.format(model_def))
# onnx.checker.check_model(model_def)
# print('The model is checked!')

import torch


class JustReshape(torch.nn.Module):
    def __init__(self):
        super(JustReshape, self).__init__()

    def forward(self, x):
        return x.view((x.shape[0], x.shape[1], x.shape[3], x.shape[2]))


net = JustReshape()
model_name = 'just_reshape.onnx'
dummy_input = torch.randn(2, 3, 4, 5)
torch.onnx.export(net, dummy_input, model_name, input_names=['input'], output_names=['output'])