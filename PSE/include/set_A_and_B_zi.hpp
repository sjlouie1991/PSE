#ifndef SET_A_AND_B_ZI_H
#define SET_A_AND_B_ZI_H
#include <petscksp.h>
namespace PSE
{
    /** 
     * 
     * \brief set A and B matrix for PSE equations for zi plane
     * \return 0 if successful
     */
    PetscInt set_A_and_B_zi(
            const PetscScalar y[],  ///< y array
            const PetscInt &ny,     ///< size of y array
            const PetscScalar z[],  ///< z array
            const PetscInt &nz,     ///< size of z array
            Mat &A,                 ///< A matrix (uninitialized)
            Mat &B,                 ///< B matrix (uninitialized)
            const PetscScalar &Re,  ///< Reynolds number
            const PetscScalar &rho,  ///< rho density
            const PetscScalar &alpha,///< alpha
            const PetscScalar &m,   ///< m for omega
            const PetscScalar &omega,///< omega value
            const PetscInt &zi=0,     ///< zi plane of matrix
            const PetscInt &order=4,  ///< order of accuracy of derivatives in finite difference
            const PetscBool &reduce_wall_order=PETSC_TRUE ///< reduce order of derivatives at the wall if true
            );
}

#endif
