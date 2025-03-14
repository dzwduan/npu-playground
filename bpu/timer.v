module timer(
	input clk, 
	input load, 
	input [9:0] data, 
	output tc
);

reg [9:0] count ;
reg stop ;

always @(posedge clk) begin
    if (load) begin
        count <= data;
        if (data == 10'b0) stop <= 1'b1;
        else               stop <= 1'b0;
    end
    else begin
        if (count != 10'b0) begin
            count <= count - 1'b1;
            if (count == 10'b1) begin
                stop <= 1'b1;
            end
        end
    end
end

assign tc = stop;

endmodule
