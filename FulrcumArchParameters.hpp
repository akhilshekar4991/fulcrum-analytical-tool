#ifndef FULCRUM_ARCH_PARAMETERS_HPP_
#define FULCRUM_ARCH_PARAMETERS_HPP_

#define     NUMBER_OF_COLUMNS_PER_SUBARRAY      64
#define     NUMBER_OF_ROWS_PER_SUBARRAY         2048
#define     LENGTH_OF_EACH_SUBARRAY_ELEMENT_IN_BITS     32
#define     NUMBER_OF_SUBCYCLES_FORMING_A_CYCLE         8
#define     NUMBER_OF_WAIT_CYCLES_FOR_ROW_ACTIVATIONS   9

#define     FULCRUM_OPERATING_FREQUENCY_IN_MHZ     164.00

// Operations
#define     ADD_OPERATION       1
#define     MULTIPLY_OPERATION  2
#define     AXPY_OPERATION      3
#define     AVERAGE_OPERATION   4
#define     SUBTRACT_OPERATION  5

// Number of instructions required for each Operation
#define     NUM_OF_INSTR_ADD_OP     1
#define     NUM_OF_INSTR_MULT_OP    1
#define     NUM_OF_INSTR_SUB_OP     1
#define     NUM_OF_INSTR_AVG_OP     3
#define     NUM_OF_INSTR_AXPY_OP    1

#endif  /* FULCRUM_ARCH_PARAMETERS_HPP_ */