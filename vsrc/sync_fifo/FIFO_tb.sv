module FIFO_tb();
    // 参数定义
    parameter W = 3;
    parameter D = 8;
    parameter CLK_PERIOD = 10;

    // 信号声明
    logic clk;
    logic rst_n;
    logic wen;
    logic ren;
    logic wfirst;
    logic [W-1:0] din;
    logic [W-1:0] dout;
    logic full;
    logic empty;
    logic [$clog2(D)-1:0] wCnt;  // 添加wcnt调试信号

    // 测试数据存储
    logic [W-1:0] write_data [$];
    logic [W-1:0] read_data [$];

    // DUT实例化
    FIFO #(
        .W(W),
        .D(D)
    ) dut (
        .clk     (clk),
        .rst_n   (rst_n),
        .wen     (wen),
        .ren     (ren),
        .wfirst  (wfirst),
        .din     (din),
        .dout    (dout),
        .full    (full),
        .empty   (empty),
        .wCnt    (wCnt)    // 连接wcnt信号
    );

    // 时钟生成
    initial begin
        clk = 0;
        forever #(CLK_PERIOD/2) clk = ~clk;
    end

    // 基本任务定义
    task reset();
        rst_n = 1'b0;
        wen = 1'b0;
        ren = 1'b0;
        wfirst = 1'b0;
        din = '0;
        repeat(3) @(posedge clk);
        rst_n = 1'b1;
        repeat(2) @(posedge clk);
        $display("Reset completed at time %0t", $time);
    endtask

	task read_word;
	    begin
		    @(negedge clk);
		    ren = 1'b1;
		    @(posedge clk) #5;
		    ren = 1'b0;
        end
	endtask

    task write_word;
        input [W-1:0] data;
        begin
            @(negedge clk);
            wen = 1'b1;
            din = data;
            @(posedge clk) #5;
            wen = 1'b0;
        end
    endtask

    task test1;
    	begin
		din = 32'b0;
		ren = 1'b0;
		wen = 1'b0;
		rst_n = 1'b1;
		#50 rst_n = 1'b0;
		#50 rst_n = 1'b1;
		write_word(32'd100);
		write_word(32'd99);
		write_word(32'd98);
		write_word(32'd97);
		read_word;
		read_word;
		write_word(32'd1);
		write_word(32'd2);
		write_word(32'd3);
		write_word(32'd4);
		write_word(32'd5);
		write_word(32'd6);
		write_word(32'd7);
		write_word(32'd8);
		write_word(32'd9);
		write_word(32'd10);
		
		repeat(9) begin 
		    read_word; 
		end
	end
	endtask

    // 测试场景
    initial begin
        // 波形配置
        $dumpfile("fifo_wave.vcd");
        $dumpvars(0, FIFO_tb);
        $timeformat(-9, 2, " ns", 20);

        $display("\nStarting FIFO testbench...");
        reset();

        // read empty fifo
        repeat(10) @(posedge clk);
        assert(empty == 1) else $display("Empty signal error!");
        assert(full == 0) else $display("Full signal error!");
        assert(dout == 0) else $display("Read data error!");
        assert(wCnt == 0) else $display("Write count error!");

        test1();

        // 测试完成
        #100;
        $display("\nTestbench completed successfully!");
        $finish;
    end

    // 超时保护
    initial begin
        #10000;
        $display("Timeout Error!");
        $finish;
    end

endmodule