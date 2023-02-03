#include "DarcyPressure.h"

registerMooseObject("BabblerApp", DarcyPressure); // the registerMooseObject() method is called for BabblerApp and the DarcyPressure object

InputParameters
DarcyPressure::validParams() // this is the object of the next step
{
  InputParameters params = ADKernelGrad::validParams();
  params.addClassDescription("Compute the diffusion term for Darcy pressure ($p$) equation: "
                             "$-\\nabla \\cdot \\frac{\\mathbf{K}}{\\mu} \\nabla p = 0$");
  
  return params;
}

DarcyPressure::DarcyPressure(const InputParameters & parameters)
  : ADKernelGrad(parameters),
  
  // Set the coefficients for the pressure kernel
  _permeability(0.8451e-09),
  _viscosity(7.98e-04)
{
}

ADRealVectorValue
DarcyPressure::precomputeQpResidual() // the precomputeQpResidual() method is programmed to return the left-hand side of Eq.(2), 
{                                     // except that the nabla psi (_grad_test) term is automatically handled by the base class.
  return (_permeability / _viscosity) * _grad_u[_qp];
}

