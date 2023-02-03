#pragma once

// Including the "ADKernel" base class here so we can extend it
#include "ADKernelGrad.h"

/**
 * Computes the residual contribution: K/mu * grad_test * grad_u
 */
class DarcyPressure : public ADKernelGrad // create the class DarcyPressure as a type of ADKernelGrad object
{
public: // a MooseObject must have a validParams() method and a constructor
  static InputParameters validParams();
  
  DarcyPressure(const InputParameters & parameters);
   
protected:
  /// ADKernel objects must override precomputeQpResidual
  virtual ADRealVectorValue precomputeQpResidual() override; // the method is overriden because the term computed in the PED is only multiplied by the gradient of the test function
     
  //The variables which hold the value for K and mu
  const Real _permeability;
  const Real _viscosity;
};
