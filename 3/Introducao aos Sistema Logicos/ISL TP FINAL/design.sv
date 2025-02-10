// Code your design here
module Main(X1, X0,reset,clk,led);
	// Componentes exigidos
  	output led;
  	input clk,reset;
  	input X0,X1;
  	wire Q2M,Q1M,Q0M; 
  	wire Q2,Q1,Q0;
  
  always @ (posedge clk or posedge reset)
  begin
    // referentes aos valores da tabela
    // Q2M = Q2+
    // Q1M = Q1+
    // Q0M = Q0+

    $display("Estado Atual do circuito: %b %b %b",Q2M,Q1M,Q0M);
    $display("Saída do circuito: %b",led);
  end
  
  DflipFlop D2 (Q2, clk,Q2M, reset);
  DflipFlop D1 (Q1, clk,Q1M, reset);
  DflipFlop D0 (Q0, clk,Q0M, reset);
  
  // Saídas dos mapas de karnaugh
  assign Q2M = (Q1 & Q0 & ~X1 & X0) | (Q2 & ~X1) | (Q2 & Q0);
  assign Q1M = (~Q2 & ~Q1 & Q0 & X1 & ~X0) | (Q1 & ~Q0 & ~X0) | (Q1 & ~X1 & ~X0);
  assign Q0M = (X1 & X0) | (Q0 & ~X1 & ~X0) | (Q1 & ~Q0 & X1) | (Q2 & X0) | (Q2 & Q0);
  assign led = (Q2 & ~Q1 & Q0); 
  
endmodule
    
module DflipFlop(q, clk, d, reset);
  
    output reg q;
    input clk, reset;
    input d;
  always @ (posedge clk or posedge reset)
    if (reset) begin
        q <= 'b0;
    end 
    else begin
        q<= d;
    end
endmodule