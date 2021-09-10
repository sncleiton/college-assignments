module gcd( inA, inB, out);

    input [15:0] inA;
    input [15:0] inB;
    output [15:0] out;

    integer aux;
    integer A=0;
    integer B=-1;

    always @((inA|inB)) begin

        A = inA;
        B = inB;

        if(A>B)
        begin
            aux = A;
            A = B;
            B = aux;
        end

        while(B != 0)
        begin
            aux = B;
            B = A%B;
            A = aux;
        end
    end
    assign out = A;
endmodule
