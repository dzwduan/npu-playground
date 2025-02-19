module FIFO #(
    parameter W = 3,
    parameter D = 8
) (
    input clk,
    input rst_n,
    input wen,
    input ren,
    output full,
    output empty,
    input wfirst,
    input [W-1:0] din,
    output [W-1:0] dout,
    output [$clog2(D):0] wCnt
);

// add extra bit, to check full or empty
reg [$clog2(D):0] rptr;
reg [$clog2(D):0] wptr;
// when choose reg and when choose sram? by area and power
reg [W-1:0] fifo_queue [D]; // based on reg, so get data at the same time
reg [W-1:0] rdata;
// check write fist or read first
wire canWrite ;
wire canRead ;

assign canWrite = wen & !full;
assign canRead =  ren & !empty & !(wfirst & wen & rptr[$clog2(D)-1:0] == wptr[$clog2(D)-1:0]);

always_ff @(posedge clk) begin
    if (!rst_n) begin
        wptr <= 0;
    end
    else if (canWrite) begin
        fifo_queue[wptr[$clog2(D)-1:0]] <= din;
        wptr <= wptr + 1'b1;
    end
end

always_ff @(posedge clk) begin
    if (!rst_n) begin
        rptr <= 0;
        rdata <= 0;
    end
    else if (canRead) begin
        rdata <= fifo_queue[rptr[$clog2(D)-1:0]];
        rptr <= rptr + 1'b1;
    end
end

assign full  = (wptr[$clog2(D)-1:0] == rptr[$clog2(D)-1:0]) &&
               (wptr[$clog2(D)]     != rptr[$clog2(D)]);
assign empty = wptr == rptr;
assign dout  = rdata;
// wcnt for debug
assign wCnt = wptr;

endmodule