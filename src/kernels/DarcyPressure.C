#include "DarcyPressure.h"

registerMooseObject("BabblerApp", DarcyPressure); // the registerMooseObject() method is called for BabblerApp and the DarcyPressure object

InputParameters
DarcyPressure::validParams()
{
  InputParameters params = ADKernelGrad::validParams();
  params.addClassDescription("Compute the diffusion term for Darcy pressure ($p$) equation: "
                             "$-\\nabla \\cdot \\frac{\\mathbf{K}}{\\mu} \\nabla p = 0$");
  
  // Add a required parameter. If this isn't provided in the iput file MOOSE will error.
  params.addRequiredParam<Real>("permeability", "The isotropic permeability ($K$) of the medium.");
  
  // Add an optional parameter and set its default value.
  params.addParam<Real>(
      "viscosity",
      7.98e-04,
      "The dynamic viscosity ($\\mu$) of the fluid, the default value is that of water at 30 "
      "degrees Celcius (7.98e-04 Pa-s).");
      
  return params;
}

DarcyPressure::DarcyPressure(const InputParameters & parameters)
  : ADKernelGrad(parameters),
  
  // Get the parameters from the input file
  _permeability(getParam<Real>("permeability")),
  _viscosity(getParam<Real>("viscosity"))
{
}

ADRealVectorValue
DarcyPressure::precomputeQpResidual() // the precomputeQpResidual() method is programmed to return the left-hand side of Eq.(2), 
{                                     // except that the nabla psi (_grad_test) term is automatically handled by the base class.
  return (_permeability / _viscosity) * _grad_u[_qp];
}

