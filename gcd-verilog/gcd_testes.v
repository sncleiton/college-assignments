module gcd_t();

    reg [15:0] a;
    reg [15:0] b;
    wire [15:0] saida;
    
    gcd m(.inA(a), .inB(b), .out(saida));
    
    initial begin

        $dumpfile("mydump.vcd");
        $dumpvars(0,m);

        a <=16'd24;
        b <=16'd9;
        #2 $display("a=%d b=%d o=%d", a, b, saida);
        
        a <=9;
        b <=24;
        #2 $display("a=%d b=%d o=%d", a, b, saida);

        a <=0;
        b <=0;
        #2 $display("a=%d b=%d o=%d", a, b, saida);
        
        a <=0;
        b <=7;
        #2 $display("a=%d b=%d o=%d", a, b, saida);
        
        a <=7;
        b <=0;
        #2 $display("a=%d b=%d o=%d", a, b, saida);
        
        a <=65535;
        b <=1125;
        #2 $display("a=%d b=%d o=%d", a, b, saida);

        $finish;
    end

endmodule
