#include "DarcyPressure.h"

registerMooseObject("BabblerApp", DarcyPressure); // the registerMooseObject() method is called for BabblerApp and the DarcyPressure object

InputParameters
DarcyPressure::validParams()
{
  InputParameters params = ADKernelGrad::validParams();
  params.addClassDescription("Compute the diffusion term for Darcy pressure ($p$) equation: "
                             "$-\\nabla \\cdot \\frac{\\mathbf{K}}{\\mu} \\nabla p = 0$");
  return params;
}

DarcyPressure::DarcyPressure(const InputParameters & parameters)
  : ADKernelGrad(parameters),
  _permeability(getADMaterialProperty<Real>("permeability")),
  _viscosity(getADMaterialProperty<Real>("viscosity"))
{
}

ADRealVectorValue
DarcyPressure::precomputeQpResidual() // the precomputeQpResidual() method is programmed to return the left-hand side of Eq.(2), 
{                                     // except that the nabla psi (_grad_test) term is automatically handled by the base class.
  return (_permeability[_qp] / _viscosity[_qp]) * _grad_u[_qp];
}

