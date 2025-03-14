module saturate(
    input clk,
    input areset,
    input train_valid,
    input train_taken,
    output [1:0] state
);

parameter SNT = 2'b00; // Strongly Not Taken
parameter WNT = 2'b01; // Weakly Not Taken
parameter WT = 2'b10; // Weakly Taken
parameter ST = 2'b11; // Strongly Takenr


always_ff @(posedge clk or posedge areset) begin
    if (areset) state <= WNT;
    else if (train_valid) begin
        if (train_taken) begin
            state <= state == ST ? ST : state + 1;
        end
        else begin
            state <= state == SNT ? SNT : state - 1;
        end
    end
    else begin
        state <= state;
    end
end

endmodule
