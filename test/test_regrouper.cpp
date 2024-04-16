#include "PlockY/BlockMatrix.hpp"
#include "PlockY/BlockMatrixLoader.hpp"
#include "PlockY/VectorRHSLoader.hpp"
#include "PlockY/VectorRHS.hpp"
#include "PlockY/Step.hpp"

int main() {
    std::cout<<"Starting"<<std::endl;
    PlockY::BlockMatrixLoader<double> loader;
    std::cout<<"Loading Matrix"<<std::endl;
    PlockY::BlockMatrix<double> mat = loader.load("blk_files/test5.blk");
    std::cout<<"Matrix Loaded"<<std::endl;

    PlockY::VectorRHSLoader<double> loader_vec;
    std::cout<<"Loading Matrix"<<std::endl;
    PlockY::VectorRHS<double> vec_RHS = loader_vec.load("blk_files/test5.vblk");
    std::cout<<"Vector Loaded"<<std::endl;

    std::vector<PlockY::Step> steps = {PlockY::Step({2,3}, 1.0),PlockY::Step({0,1,4}, 1.0)};

    std::cout<<"Regrouping Mat"<<std::endl;
    mat.regroup(steps);


    std::cout<<"Regrouping Vec"<<std::endl;
    vec_RHS.regroup(steps);

    std::cout<<"Complement Vec 23"<<std::endl;
    std::cout<<vec_RHS.get_rhs_compl(PlockY::Step({2,3}, 1.0))<<std::endl;

    std::cout<<"Complement Vec 14"<<std::endl;
    std::cout<<vec_RHS.get_rhs_compl(PlockY::Step({1,4}, 1.0))<<std::endl;

    std::cout<<"Complement Vec 2"<<std::endl;
    std::cout<<vec_RHS.get_rhs_compl(PlockY::Step({2}, 1.0))<<std::endl;


    return 0;
}