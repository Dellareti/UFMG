// Code your testbench here
// or browse Examples
// Code your testbench here
// or browse Examples
module test;
  reg _X0,_X1,_reset,_clk;
  wire _led;
  
  Main test (.X0(_X0), .X1(_X1),.reset(_reset),.clk(_clk), .led(_led));
  
  always begin 
    _clk = 1;
    #30;
    _clk = 0;
    #30;
  end 
  initial begin 
    $dumpfile ("dump.vcd");
    $dumpvars (1);
  end
  
  initial 
    begin
    _reset = 0;
    _X1 = 0;
    _X0	= 0;
    #60 _reset = 1;
    #60 _reset = 0;
      //C
    #60 _X1 = 1; _X0 = 1;
      //B
    #60 _X1 = 1; _X0 = 0;
      //B
    #60 _X1 = 1; _X0 = 0;
      //A
    #60 _X1 = 0; _X0 = 1;
    
      // Nao vai chegar no estado final 
     #60 _X1 = 1; _X0 = 0;
	 #60 _X1 = 1; _X0 = 1;
     #60 _X1 = 0; _X0 = 1;
	 #60 _X1 = 1; _X0 = 1;
	 #60 _X1 = 1; _X0 = 0;
    #100 _X1 = 0 ; _X0 = 0;
    #100 _X1 = 0; _X0 = 0;
	$finish;


  end
  
endmodule