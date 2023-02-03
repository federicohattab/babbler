# The geometry of the pipe shall be defined using the MOOSE standard rectilinear mesh generator object, GeneratedMesh.
# This creates a planar mesh with a heigh equal to the pipe radius.
[Mesh]
  type = GeneratedMesh # Can generate simple lines, rectangles and rectangular prisms
  dim = 2 # Dimension of the mesh
  nx = 100 # Number of elements in the  direction
  ny = 10 # Number of elements in the y direction
  xmax = 0.304 # Length in (m) of test chamber
  ymax = 0.0257 # Test chamber radius in (m)
[] 

# Thus, this problem shall be solved using cylindrical coordinates. To do this, a [Problem] block shall be included in addition to the basic six blocks.
# The purpose of this block is to indicate that the planar mesh respresents an axisymmetric body defined with respect to a cylindrical coordinate system
[Problem]
  type = FEProblem # This is the "normal" type of Finite Element Problem in MOOSE
  coord_type = RZ # Axisymmetric RZ
  rz_coord_axis = X # Which axis the symmetry is around
[]

# The pressure variable u shall be added to the [Variables] bloch with an unambiguous name, i.e., pressure. The variables listed here are the variables
# to be solved using the Finite Element Method (FEM).
[Variables]
  [pressure]
    # Adds a Linear Lagrange variable by default
  []
[]

# The ADDiffusion class will be used to solve the Laplace equation and the pressure variable will be operated on
[Kernels]
  [diffusion]
    type = DarcyPressure # Zero-gravity, divergence-free form of Darcy's law
    variable = pressure # Operate on the "pressure" variable from above
  []
[]

# Now the BVP must be enforced. The ADDirichletBC class enforces a Dirichlet (essential) BC, e.g., the pressure described at the pipe inlet and outlet.
# For this problem, two separate ADDirichletBC objects are setup inder the [BCs] block - one for each end of the pipe.
# It is not necessary to enforce the Neumann (natural) BC = gradient of pressure at the faces normal to the inlet/outlet, since they are zero-valued fluxes
[BCs]
  [inlet]
    type = ADDirichletBC # Simple u=value BC
    variable = pressure # Variable to be set
    boundary = left # Name of a sideset in the mesh
    value = 4000 # (Pa) First data point fo 1mm spheres
  []
  [outlet]
    type = ADDirichletBC
    variable = pressure
    boundary = right
    value = 0 # (Pa) Gives the correct pressure drop for 1mm spheres    
  []
[]

# The problem being solved does not have a time component, so a steady-state executioner object, Steady, is invoked to solve the resulting equation:
[Executioner]
  type = Steady # Steady state problem
  solve_type = NEWTON # Perform a Newton solve
  
  # Set PETSc parameters to ptimize solver efficiency
  petsc_options_iname = '-pc_type -pc_hypre_type' # PETSc option pairs with value below
  petsc_options_value = 'hypre boomeramg'
[]

# The computed FE solution shall be output in ExodusII format
[Outputs]
  exodus = true # Output Exodus format
[]
