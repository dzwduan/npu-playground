module gshare(
    input clk,
    input areset,

    input  predict_valid,
    input  [6:0] predict_pc,
    output predict_taken,
    output logic [6:0] predict_history,

    input train_valid,
    input train_taken,
    input train_mispredicted,
    input [6:0] train_history,
    input [6:0] train_pc
);

logic [1:0] PHT[128]; 
// 128 entry的 2bit饱和计数器表项，每一项都初始化为2'b01 , 该表名为PHT
// pc ^ history 作为索引
// train 优先于 predict
// predict_valid = 1, 更新predict_history，这里和前面的history_shift设计一样
// train_valid = 1 && train_mispredicted = 0, 根据train_taken更新PHT，注意索引
// train_valid = 1 && train_mispredicted = 1, 需要更新predict_history
integer i;
always_ff @(posedge clk or posedge areset) begin
    if (areset) begin
        predict_history <= 7'b0;
        for (int i = 0; i < 128; i = i + 1) begin
            PHT[i] <= 1;
        end
    end
    else begin
        if (train_valid & train_mispredicted) begin
            // 训练模式下，发现预测错误，需要恢复分支历史寄存器
            predict_history <= {train_history[5:0], train_taken};
        end
        else if (predict_valid) begin
            predict_history <= {predict_history[5:0], predict_taken};
        end
        // PHT 和 predict_history 可以同时更新，因此这里不是else if
        if(train_valid) begin
            if (train_taken)
                PHT[train_pc ^ train_history] <= (PHT[train_pc ^ train_history] == 2'b11) ? 2'b11 : (PHT[train_pc ^ train_history] + 1);
            else
                PHT[train_pc ^ train_history] <= (PHT[train_pc ^ train_history] == 2'b00) ? 2'b00 : (PHT[train_pc ^ train_history] - 1);
        end
    end
end

// 使用 predict_history ^ predict_pc 作为索引，从PHT中取出预测结果的第一位
assign predict_taken = PHT[predict_history ^ predict_pc][1];

endmodule