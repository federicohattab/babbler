[Tests]
  [test] # creates an Exodiff object that will attempt to match the output from darcy_pressure_test.i to the gold file
    type = Exodiff
    input = darcy_pressure_test.i
    exodiff = darcy_pressure_test_out.e
  []
  [zero_viscosity_error] # creates a RunException object that attempts to match the error message incurred by zero_viscosity_error.i to the string specified for the expect_err parameter
    type = RunException
    input = zero_viscosity_error.i
    expect_err = "The viscosity must be a non-zero real number."
  []
[]
