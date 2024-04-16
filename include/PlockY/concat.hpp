#include <iostream>
#include <Eigen/Core>


namespace EigenCustom
{
using namespace Eigen;

template<typename Arg1, typename Arg2>
struct horizcat_helper {
  typedef Matrix<typename Arg1::Scalar,
    Arg1::RowsAtCompileTime,
    Arg1::ColsAtCompileTime==Dynamic || Arg2::ColsAtCompileTime==Dynamic
    ? Dynamic : Arg1::ColsAtCompileTime+Arg2::ColsAtCompileTime,
    ColMajor,
    Arg1::MaxRowsAtCompileTime,
    Arg1::MaxColsAtCompileTime==Dynamic || Arg2::MaxColsAtCompileTime==Dynamic
    ? Dynamic : Arg1::MaxColsAtCompileTime+Arg2::MaxColsAtCompileTime> MatrixType;
};

template<typename Arg1, typename Arg2>
class horizcat_functor
{
  const typename Arg1::Nested m_mat1;
  const typename Arg2::Nested m_mat2;

public:
  horizcat_functor(const Arg1& arg1, const Arg2& arg2)
    : m_mat1(arg1), m_mat2(arg2)
  {}

  const typename Arg1::Scalar operator() (Index row, Index col) const {
    if (col < m_mat1.cols())
      return m_mat1(row,col);
    return m_mat2(row, col - m_mat1.cols());
  }
};

template <typename Arg1, typename Arg2>
CwiseNullaryOp<horizcat_functor<Arg1,Arg2>, typename horizcat_helper<Arg1,Arg2>::MatrixType>
horizcat(const Eigen::MatrixBase<Arg1>& arg1, const Eigen::MatrixBase<Arg2>& arg2)
{
  typedef typename horizcat_helper<Arg1,Arg2>::MatrixType MatrixType;
  return MatrixType::NullaryExpr(arg1.rows(), arg1.cols()+arg2.cols(),
                                horizcat_functor<Arg1,Arg2>(arg1.derived(),arg2.derived()));
}


} // namespace EigenCustom