#include "predictCycles.hpp"

int main(int argc, char const *argv[]) 
{
    string inputJsonFilename = argv[1];
    ifstream    inputJsonFile(inputJsonFilename);
    json inputParameters;
    uint32_t    totalNumberOfCycles = 0;

    inputJsonFile >> inputParameters;
    inputJsonFile.close();


    string FulcrumOperation = inputParameters["operation"];
    transform(FulcrumOperation.begin(), FulcrumOperation.end(), FulcrumOperation.begin(), ::tolower);

    if(FulcrumOperation == "add")
        totalNumberOfCycles = predictForAddArrayOperation(inputParameters);
    
    else if (FulcrumOperation == "sub")     // Very similar to add operation, hence calling the same function
        totalNumberOfCycles = predictForAddArrayOperation(inputParameters);

    else if(FulcrumOperation == "multiply")
        totalNumberOfCycles = predictForMultiplyArrayOperation(inputParameters);
    
    else if(FulcrumOperation == "axpy")
        totalNumberOfCycles = predictForAXPYOperation(inputParameters);
    
    else if(FulcrumOperation == "average")
        totalNumberOfCycles = predictForAverageOperation(inputParameters);
    
    else
        debug_printf("Incorrect operation detected in JSON file \n");

    debug_printf("Operating Frequency = %.2f MHz \n", FULCRUM_OPERATING_FREQUENCY_IN_MHZ);
    float   totalExecutionTime = totalNumberOfCycles * (1 / FULCRUM_OPERATING_FREQUENCY_IN_MHZ);
    debug_printf("Total Execution Time = %.2f ns\n", totalExecutionTime);

    return totalNumberOfCycles;
}