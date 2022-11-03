#include "Vcounter.h"
#include "verilated.h"
#include "verilated_vcd_c.h"

int main(int argc, char **argv, char **env) {
    int i;
    int clk;


    Verilated::commandArgs(argc, argv);
    Vcounter* top = new Vcounter;

    Verilated::traceEverOn(true);
    VerilatedVcdC* tfp = new VerilatedVcdC;
    top->trace (tfp, 99);
    tfp->open ("counter.vcd");
    top->clk =1;
    top->rst = 1;
    top->en = 0;
    int pause_counter = 1;
    bool pause = false;

    for (i = 0; i < 300; i++) {
        for (clk = 0; clk<2; clk++) {
            tfp->dump (2*i+clk);
            top->clk = !top->clk;
            top->eval ();
        }
        top->rst = (i<2);
        top->en = (i>4) && !pause;
        if (pause == true) {
            pause_counter++;
            if (pause_counter == 3) {
                pause = false;
            }
        }
        else if (top->count == 8) {
            pause = true;
        }
        if (Verilated::gotFinish()) exit(0);
    }
    tfp->close();
    exit(0);
}