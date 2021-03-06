/* =================================================================================================

(c - GPLv3) T.W.J. de Geus (Tom) | tom@geus.me | www.geus.me | github.com/tdegeus/GooseFEM

================================================================================================= */

#ifndef XGOOSEFEM_ELEMENTQUAD4_H
#define XGOOSEFEM_ELEMENTQUAD4_H

// -------------------------------------------------------------------------------------------------

#include "GooseFEM.h"

// =================================== xGooseFEM::Element::Quad4 ====================================

namespace xGooseFEM {
namespace Element {
namespace Quad4 {

// ======================================== tensor algebra =========================================

using T2 = xt::xtensor_fixed<double, xt::xshape<2,2>>;

inline double inv(const T2 &A, T2 &Ainv);

// ================================ xGooseFEM::Element::Quad4::Gauss ================================

namespace Gauss {
inline size_t                nip(); // number of integration points
inline xt::xtensor<double,2> xi();  // integration point coordinates (local coordinates)
inline xt::xtensor<double,1> w();   // integration point weights
}

// ================================ xGooseFEM::Element::Quad4::Nodal ================================

namespace Nodal {
inline size_t                nip(); // number of integration points
inline xt::xtensor<double,2> xi();  // integration point coordinates (local coordinates)
inline xt::xtensor<double,1> w();   // integration point weights
}

// =================================================================================================

// ------------------------------------------ quadrature -------------------------------------------

class Quadrature
{
private:

  // dimensions (flexible)
  size_t m_nelem; // number of elements
  size_t m_nip;   // number of integration points

  // dimensions (fixed for this element type)
  static const size_t m_nne=4;  // number of nodes per element
  static const size_t m_ndim=2; // number of dimensions

  // data arrays
  xt::xtensor<double,3> m_x;    // nodal positions stored per element [nelem, nne, ndim]
  xt::xtensor<double,1> m_w;    // weight of each integration point [nip]
  xt::xtensor<double,2> m_xi;   // local coordinate of each integration point [nip, ndim]
  xt::xtensor<double,2> m_N;    // shape functions [nip, nne]
  xt::xtensor<double,3> m_dNxi; // shape function gradients w.r.t. local  coordinate [nip, nne, ndim]
  xt::xtensor<double,4> m_dNx;  // shape function gradients w.r.t. global coordinate [nelem, nip, nne, ndim]
  xt::xtensor<double,2> m_vol;  // integration point volume [nelem, nip]

private:

  // compute "vol" and "dNdx" based on current "x"
  void compute_dN();

public:

  // convention:
  //    "elemmat"  -  matrices stored per element       -  [nelem, nne*ndim, nne*ndim]
  //    "elemvec"  -  nodal vectors stored per element  -  [nelem, nne, ndim]
  //    "qtensor"  -  integration point tensor          -  [nelem, nip, ndim, ndim]
  //    "qscalar"  -  integration point scalar          -  [nelem, nip]

  // constructor: integration point coordinates and weights are optional (default: Gauss)
  Quadrature() = default;
  Quadrature(const xt::xtensor<double,3> &x);
  Quadrature(const xt::xtensor<double,3> &x, const xt::xtensor<double,2> &xi, const xt::xtensor<double,1> &w);

  // update the nodal positions (shape of "x" should match the earlier definition)
  void update_x(const xt::xtensor<double,3> &x);

  // return dimensions
  size_t nelem() const; // number of elements
  size_t nne()   const; // number of nodes per element
  size_t ndim()  const; // number of dimension
  size_t nip()   const; // number of integration points

  // return integration volume
  // - in-place
  void dV(xt::xtensor<double,2> &qscalar) const;
  void dV(xt::xtensor<double,4> &qtensor) const; // same volume for all tensor components
  // - return qscalar/qtensor
  xt::xtensor<double,2> dV() const;
  xt::xtensor<double,4> dVtensor() const;

  // dyadic product "qtensor(i,j) += dNdx(m,i) * elemvec(m,j)", its transpose and its symmetric part
  // - in-place
  void gradN_vector   (const xt::xtensor<double,3> &elemvec, xt::xtensor<double,4> &qtensor) const;
  void gradN_vector_T (const xt::xtensor<double,3> &elemvec, xt::xtensor<double,4> &qtensor) const;
  void symGradN_vector(const xt::xtensor<double,3> &elemvec, xt::xtensor<double,4> &qtensor) const;
  // - return qtensor
  xt::xtensor<double,4> gradN_vector   (const xt::xtensor<double,3> &elemvec) const;
  xt::xtensor<double,4> gradN_vector_T (const xt::xtensor<double,3> &elemvec) const;
  xt::xtensor<double,4> symGradN_vector(const xt::xtensor<double,3> &elemvec) const;

  // integral of the scalar product "elemmat(m*ndim+i,n*ndim+i) += N(m) * qscalar * N(n) * dV"
  // - in-place
  void int_N_scalar_NT_dV(const xt::xtensor<double,2> &qscalar, xt::xtensor<double,3> &elemmat) const;
  // - return elemmat
  xt::xtensor<double,3> int_N_scalar_NT_dV(const xt::xtensor<double,2> &qscalar) const;

  // integral of the dot product "elemvec(m,j) += dNdx(m,i) * qtensor(i,j) * dV"
  // - in-place
  void int_gradN_dot_tensor2_dV(const xt::xtensor<double,4> &qtensor, xt::xtensor<double,3> &elemvec) const;
  // - return elemvec
  xt::xtensor<double,3> int_gradN_dot_tensor2_dV(const xt::xtensor<double,4> &qtensor) const;

};

// -------------------------------------------------------------------------------------------------

}}} // namespace ...

// =================================================================================================

#endif
