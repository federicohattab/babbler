[Mesh]
  type = GeneratedMesh
  dim = 1
[]

[Problem] # Since no actual FE prolem is going to be solved, the "solve" parameter was set to false
  solve = false # his will increase performance by not processing tasks that are unnecessary for this particular test
[]

[Variables]
  [u]
  []
[]

[Kernels]
  [zero_viscosity]
    type = DarcyPressure
    variable = u
    permeability = 0.8451e-09
    viscosity = 0 # The viscosity must be a non-zero number, so this input should invoke an error
  []
[]

[Executioner]
  type = Steady
[]

