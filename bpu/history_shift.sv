module history_shift(
    input clk,
    input areset,

    input predict_valid,
    input predict_taken,
    output logic [31:0] predict_history,

    input train_mispredicted,
    input train_taken,          // 实际的分支结果
    input [31:0] train_history  // 预测之前的历史
);

// 设计一个分支历史寄存器，里面的每一位T/N都代表是否跳转
// predict_valid=1, 从predict_history[0]处开始移位
// train_mispredicted=1， 说明预测错误，要回滚到错误之前的状态丢弃错误发生之后的预测，并使用正确的结果填充
// 同时发生预测和误预测，误预测优先

always_ff @(posedge clk or posedge areset) begin
    if (areset) begin
        predict_history <= 32'b0;
    end
    else if (train_mispredicted) begin
        predict_history <= {train_history[30:0], train_taken};
    end
    else begin
        if (predict_valid) begin
            predict_history <= {predict_history[30:0], predict_taken};
        end
        else begin
            predict_history <= predict_history;
        end
    end

end

endmodule