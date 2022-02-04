#ifndef     PREDICT_CYCLES_HPP_
#define     PREDICT_CYCLES_HPP_

#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <ctype.h>
#include <bits/stdc++.h>
#include "nlohmann/json.hpp"
#include "FulrcumArchParameters.hpp"
#include "debug.hpp"

using namespace std;
using json = nlohmann::json;

uint32_t    countNumOfRowActivations(
    uint32_t    sizeOfInputArrays,
    uint32_t    operation)
{
    uint32_t        numOfRowActivations = 0;

    switch(operation) {
        case    ADD_OPERATION           :
        case    SUBTRACT_OPERATION      :
        case    MULTIPLY_OPERATION      :
        case    AXPY_OPERATION          :   numOfRowActivations = sizeOfInputArrays / NUMBER_OF_COLUMNS_PER_SUBARRAY;
                                            
                                            // 2 input vectors and 1 output vector, thus 3 row activations are considered
                                            numOfRowActivations = numOfRowActivations * 3;
                                            break;
        
        case    AVERAGE_OPERATION       :   numOfRowActivations = sizeOfInputArrays / NUMBER_OF_COLUMNS_PER_SUBARRAY;
                                            
                                            // 1 input vector and 1 output element (not a vector), thus only 1 row activation considered
                                            break;
        
        default                         :   numOfRowActivations = 0;
    }

    uint32_t    numOfRowActivationWaitCycles = numOfRowActivations * NUMBER_OF_WAIT_CYCLES_FOR_ROW_ACTIVATIONS;
    debug_printf("Number of Row Activation Wait Cycles = %d \n", numOfRowActivationWaitCycles);
    return numOfRowActivationWaitCycles;
}

uint32_t    countNumOfCyclesForShifting(
    uint32_t    sizeOfInputArrays,
    uint32_t    operation) 
{
    /* Generally 1 subcycle is used for shifting the walkers. And 8 subcycles form 1 cycle. */
    uint32_t    numOfSubcyclesConsumedForShiftingWalkers;

    switch(operation) {
        case    ADD_OPERATION           :
        case    SUBTRACT_OPERATION      :
        case    MULTIPLY_OPERATION      :
        case    AXPY_OPERATION          :   numOfSubcyclesConsumedForShiftingWalkers = sizeOfInputArrays;
                                            break;
        
        case    AVERAGE_OPERATION       :   numOfSubcyclesConsumedForShiftingWalkers = sizeOfInputArrays;
                                            break;
        
        default                         :   numOfSubcyclesConsumedForShiftingWalkers = 0;
    }

    uint32_t    numOfCycles = numOfSubcyclesConsumedForShiftingWalkers / NUMBER_OF_SUBCYCLES_FORMING_A_CYCLE;
    debug_printf("Number of Cycles Required for Column Shifting = %d \n", numOfCycles);
    return numOfCycles;
}

uint32_t    countNumOfCyclesForComputation(
    uint32_t    sizeOfInputArrays,
    uint32_t    operation) 
{
    /* Generally Fulcrum executes 1 instruction per clock cycle */
    uint32_t    numOfCyclesForComputation;

    switch(operation) {
        case    ADD_OPERATION           :   numOfCyclesForComputation = sizeOfInputArrays * NUM_OF_INSTR_ADD_OP;
                                            break;
        
        case    SUBTRACT_OPERATION      :   numOfCyclesForComputation = sizeOfInputArrays * NUM_OF_INSTR_SUB_OP;
                                            break;
        
        case    MULTIPLY_OPERATION      :   numOfCyclesForComputation = sizeOfInputArrays * NUM_OF_INSTR_MULT_OP;
                                            break;
        
        case    AXPY_OPERATION          :   numOfCyclesForComputation = sizeOfInputArrays * NUM_OF_INSTR_AXPY_OP;
                                            break;
        
        case    AVERAGE_OPERATION       :   numOfCyclesForComputation = sizeOfInputArrays * NUM_OF_INSTR_AVG_OP;
                                            break;
        
        default                         :   numOfCyclesForComputation = 0;
    }

    debug_printf("Number of Cycles Consumed for ALPU Computaiton = %d \n", numOfCyclesForComputation);
    return numOfCyclesForComputation;
}


int predictForAddArrayOperation(json    inputConfigParameters)
{

    uint32_t    sizeOfInputArrays = inputConfigParameters["size of array"];

    // Calculate the number of row activations
    uint32_t    numOfRowActivations = countNumOfRowActivations(sizeOfInputArrays, ADD_OPERATION);

    // Calculate the number of cycles required for shifting walkers i.e. feeding data into the ALU sequentially
    uint32_t    numOfCyclesForShifting = countNumOfCyclesForShifting(sizeOfInputArrays, ADD_OPERATION);

    // Calculate the number of cycles required for the computation in Fulcrum ALU/Fulcrum ALPU
    uint32_t    numOfCyclesForComputation = countNumOfCyclesForComputation(sizeOfInputArrays, ADD_OPERATION);

    uint32_t    totalNumberOfCycles = numOfRowActivations + numOfCyclesForShifting + numOfCyclesForComputation;

    debug_printf("Total Number of Cycles for ADD Operation of two %d-length arrays = %d \n", sizeOfInputArrays, totalNumberOfCycles);

    return      totalNumberOfCycles;    
}

int predictForMultiplyArrayOperation(json    inputConfigParameters)
{
    uint32_t    sizeOfInputArrays = inputConfigParameters["size of array"];

    // Calculate the number of row activations
    uint32_t    numOfRowActivations = countNumOfRowActivations(sizeOfInputArrays, MULTIPLY_OPERATION);

    // Calculate the number of cycles required for shifting walkers i.e. feeding data into the ALU sequentially
    uint32_t    numOfCyclesForShifting = countNumOfCyclesForShifting(sizeOfInputArrays, MULTIPLY_OPERATION);

    // Calculate the number of cycles required for the computation in Fulcrum ALU/Fulcrum ALPU
    uint32_t    numOfCyclesForComputation = countNumOfCyclesForComputation(sizeOfInputArrays, MULTIPLY_OPERATION);

    uint32_t    totalNumberOfCycles = numOfRowActivations + numOfCyclesForShifting + numOfCyclesForComputation;

    debug_printf("Total Number of Cycles for Multiply Operation of two %d-length arrays = %d \n", sizeOfInputArrays, totalNumberOfCycles);

    return      totalNumberOfCycles;    
}

/* a*x[] + y[] = y[] */
int predictForAXPYOperation(json    inputConfigParameters)
{
    uint32_t    sizeOfInputArrays = inputConfigParameters["size of array"];

    // Calculate the number of row activations
    uint32_t    numOfRowActivations = countNumOfRowActivations(sizeOfInputArrays, AXPY_OPERATION);

    // Calculate the number of cycles required for shifting walkers i.e. feeding data into the ALU sequentially
    uint32_t    numOfCyclesForShifting = countNumOfCyclesForShifting(sizeOfInputArrays, AXPY_OPERATION);

    // Calculate the number of cycles required for the computation in Fulcrum ALU/Fulcrum ALPU
    uint32_t    numOfCyclesForComputation = countNumOfCyclesForComputation(sizeOfInputArrays, AXPY_OPERATION);

    uint32_t    totalNumberOfCycles = numOfRowActivations + numOfCyclesForShifting + numOfCyclesForComputation;

    debug_printf("Total Number of Cycles for AXPY Operation of two %d-length arrays = %d \n", sizeOfInputArrays, totalNumberOfCycles);

    return      totalNumberOfCycles;    
}

int predictForAverageOperation(json    inputConfigParameters)
{
    uint32_t    sizeOfInputArrays = inputConfigParameters["size of array"];

    // Calculate the number of row activations
    uint32_t    numOfRowActivations = countNumOfRowActivations(sizeOfInputArrays, AVERAGE_OPERATION);

    // Calculate the number of cycles required for shifting walkers i.e. feeding data into the ALU sequentially
    uint32_t    numOfCyclesForShifting = countNumOfCyclesForShifting(sizeOfInputArrays, AVERAGE_OPERATION);

    // Calculate the number of cycles required for the computation in Fulcrum ALU/Fulcrum ALPU
    uint32_t    numOfCyclesForComputation = countNumOfCyclesForComputation(sizeOfInputArrays, AVERAGE_OPERATION);

    uint32_t    totalNumberOfCycles = numOfRowActivations + numOfCyclesForShifting + numOfCyclesForComputation;

    debug_printf("Total Number of Cycles for Average Operation of %d-length array = %d \n", sizeOfInputArrays, totalNumberOfCycles);

    return      totalNumberOfCycles;    
}

#endif      /*  PREDICT_CYCLES_HPP_ */