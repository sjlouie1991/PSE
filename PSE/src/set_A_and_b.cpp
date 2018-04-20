#include <stdexcept>
#include <string>
#include <cmath>
#include "set_A_and_B_zi.hpp"
#include "set_A_and_b.hpp"
#include "set_D.hpp"
#include "get_D_Coeffs.hpp"
#include "Init_Vec.hpp"
#include "Init_Mat.hpp"
#include "print.hpp"
#include "set_Mat.hpp"
#include "set_Vec.hpp"
#include "base_flow.hpp"
#include <iostream>

namespace PSE
{
    PetscInt set_A_and_b(
            const PetscScalar &hx,
            const PetscScalar y[],
            const PetscInt &ny,
            const PetscScalar z[],
            const PetscInt &nz,
            const Vec &qn,
            Mat &A,         
            Vec &b,         
            const PetscScalar &Re,
            const PetscScalar &rho,
            const PetscScalar &alpha,
            const PetscScalar &m,
            const PetscScalar &omega,
            const PetscInt &order,
            const PetscBool &reduce_wall_order
            ){

        Mat B;
        PetscErrorCode ierr;
        PetscInt dim=ny*nz*4;

        Init_Mat(A,dim);
        Init_Mat(B,dim);
        Init_Vec(b,dim);
        for (PetscInt i=0; i<nz; i++){
            set_A_and_B_zi(y,ny,z,nz,A,B,Re,rho,alpha,m,omega,i,order,reduce_wall_order);
        }

        // set A and b for output
        //MatAXPY(1./hx,B,A); // A<- 1./hx * B + A
        MatAXPY(A,1./hx,B,SAME_NONZERO_PATTERN); // A+= 1./hx * B
        MatScale(B,1./hx);  // B+=1./hx
        MatMult(B,qn,b);    // b=B*qn

        ierr = MatDestroy(&B);CHKERRQ(ierr);

        return 0;
    }
}