/* =================================================================================================

(c - GPLv3) T.W.J. de Geus (Tom) | tom@geus.me | www.geus.me | github.com/tdegeus/GooseFEM

================================================================================================= */

#ifndef GOOSEFEM_VECTOR_H
#define GOOSEFEM_VECTOR_H

// -------------------------------------------------------------------------------------------------

#include "GooseFEM.h"

// =========================================== GooseFEM ============================================

namespace GooseFEM {

// -------------------------------------------------------------------------------------------------

class Vector
{
private:

  // information
  MatS m_conn; // connectivity                               [nelem, nne ]
  MatS m_dofs; // DOF-numbers per node                       [nnode, ndim]
  MatS m_part; // DOF-numbers per node, after partitioning   [nnode, ndim]
  ColS m_iiu;  // DOF-numbers that are unknown               [nnu]
  ColS m_iip;  // DOF-numbers that are prescribed            [nnp]

  // dimensions
  size_t m_nelem; // number of elements
  size_t m_nne;   // number of nodes per element
  size_t m_nnode; // number of nodes
  size_t m_ndim;  // number of dimensions
  size_t m_ndof;  // number of DOFs
  size_t m_nnu;   // number of unknown DOFs
  size_t m_nnp;   // number of prescribed DOFs

public:

  // notation:
  //    "nodevec"   -  nodal vectors                     -  [nnode, ndim]
  //    "elemvec"   -  nodal vectors stored per element  -  [nelem, nne, ndim]
  //    "dofval"    -  DOF values                        -  [ndof]
  //    "dofval_u"  -  DOF values (Unknown)              -  [nnu]
  //    "dofval_p"  -  DOF values (Prescribed)           -  [nnp]

  // constructor
  Vector(){};
  Vector(const MatS &conn, const MatS &dofs);
  Vector(const MatS &conn, const MatS &dofs, const ColS &iip);

  // dimensions
  size_t nelem() const; // number of elements
  size_t nne()   const; // number of nodes per element
  size_t nnode() const; // number of nodes
  size_t ndim()  const; // number of dimensions
  size_t ndof()  const; // number of DOFs
  size_t nnu()   const; // number of unknown DOFs
  size_t nnp()   const; // number of prescribed DOFs

  // DOF lists
  MatS dofs() const; // DOFs
  ColS iiu()  const; // unknown    DOFs
  ColS iip()  const; // prescribed DOFs

  // convert vectors (overwrite entries that occur more that once) -- no allocation
  void asDofs   (const ColD &dofval_u, const ColD &dofval_p, ColD &dofval ) const;
  void asDofs   (const MatD &nodevec                       , ColD &dofval ) const;
  void asDofs   (const ArrD &elemvec                       , ColD &dofval ) const;
  void asDofs_u (const MatD &nodevec                       , ColD &dofval ) const;
  void asDofs_u (const ArrD &elemvec                       , ColD &dofval ) const;
  void asDofs_p (const MatD &nodevec                       , ColD &dofval ) const;
  void asDofs_p (const ArrD &elemvec                       , ColD &dofval ) const;
  void asNode   (const ColD &dofval                        , MatD &nodevec) const;
  void asNode   (const ColD &dofval_u, const ColD &dofval_p, MatD &nodevec) const;
  void asNode   (const ArrD &elemvec                       , MatD &nodevec) const;
  void asElement(const ColD &dofval                        , ArrD &elemvec) const;
  void asElement(const ColD &dofval_u, const ColD &dofval_p, ArrD &elemvec) const;
  void asElement(const MatD &nodevec                       , ArrD &elemvec) const;

  // assemble vectors (adds entries that occur more that once) -- no allocation
  void assembleDofs  (const MatD &nodevec, ColD &dofval ) const;
  void assembleDofs  (const ArrD &elemvec, ColD &dofval ) const;
  void assembleDofs_u(const MatD &nodevec, ColD &dofval ) const;
  void assembleDofs_u(const ArrD &elemvec, ColD &dofval ) const;
  void assembleDofs_p(const MatD &nodevec, ColD &dofval ) const;
  void assembleDofs_p(const ArrD &elemvec, ColD &dofval ) const;
  void assembleNode  (const ArrD &elemvec, MatD &nodevec) const;

  // convert vectors (overwrite entries that occur more that once)
  ColD asDofs   (const ColD &dofval_u, const ColD &dofval_p) const;
  ColD asDofs   (const MatD &nodevec                       ) const;
  ColD asDofs   (const ArrD &elemvec                       ) const;
  ColD asDofs_u (const MatD &nodevec                       ) const;
  ColD asDofs_u (const ArrD &elemvec                       ) const;
  ColD asDofs_p (const MatD &nodevec                       ) const;
  ColD asDofs_p (const ArrD &elemvec                       ) const;
  MatD asNode   (const ColD &dofval                        ) const;
  MatD asNode   (const ColD &dofval_u, const ColD &dofval_p) const;
  MatD asNode   (const ArrD &elemvec                       ) const;
  ArrD asElement(const ColD &dofval                        ) const;
  ArrD asElement(const ColD &dofval_u, const ColD &dofval_p) const;
  ArrD asElement(const MatD &nodevec                       ) const;

  // assemble vectors (adds entries that occur more that once)
  ColD assembleDofs  (const MatD &nodevec) const;
  ColD assembleDofs  (const ArrD &elemvec) const;
  ColD assembleDofs_u(const MatD &nodevec) const;
  ColD assembleDofs_u(const ArrD &elemvec) const;
  ColD assembleDofs_p(const MatD &nodevec) const;
  ColD assembleDofs_p(const ArrD &elemvec) const;
  MatD assembleNode  (const ArrD &elemvec) const;

};

// -------------------------------------------------------------------------------------------------

} // namespace ...

// =================================================================================================

#endif