# fulcrum-analytical-tool
This is a very short tool that predicts the number of cycles and execution time in Fulcrum when the operands and operations are known.
For ex. 
How many number of cycles and what would be the execution time to perform an addition of two 1024-length vectors in Fulcrum? 
Tool would output Execution Time and Number of Cycles in the output.

Usage - 
1. Make a build directory (ex. "mkdir build")
2. cd build
3. cmake ..
4. make
5. You will get an executable called "analytical_tool.out
6. This is your executable tool that predicts the number of cycles that Fulcrum architecture would take to execute an operation

Command Line Usage - 
The analytical tool take inputs and parameters in the form of a JSON file. Hence, please edit the JSON file to change the parameters and then, input the same to the analytical tool using the command. 
./analytical_tool.out  <input_json_file> 

The JSON file contains information about two elements - 
1. Operands - Length of the operands specifically. Usually most of Fulcrum operations are represented in the form of vectors. Hence, vector sizes need to be mentioned in this field inside the the JSON file. 
2. Operations - This field conveys what operation the Fulcrum architecture needs to perform. Ex. Add, Multiply, AXPY (kernel), Average etc. 

A sample input file has been presented in this code repo. One could edit the same and use it. 

Currently supported operations - 
  ADD OPERATIONS          --> "add" (in JSON file)  -- a[] + b[] = c[]
  SUBTRACT OPERATIONS     --> "sub"                 -- a[] - b[] = c[]
  MULTIPLY OPERATIONS     --> "multiply"            -- a[] * b[] = c[]
  AXPY KERNEL             --> "axpy"                -- a*x[] + y[] = y[]
  AVERAGE OPERATIONS      --> "average"             -- average(a[])
  
More will be added in later versions ... 
  
