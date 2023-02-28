// classification.hpp
// A library that contains tools for classification.
// Authors:
// Date: 27 February 2023

#ifndef _CLASSIFICATION_H_
#define _CLASSIFICATION_H_

#include <iostream>
#include "Matrix.hpp"
#include <vector>
#include <math.h>
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;

class Classifier {
public:
    // Classifiers
    int classify(Matrix x, Matrix muOne, Matrix muTwo, Matrix2f sigmaOne, Matrix2f sigmaTwo, float priorOne, float priorTwo);
    int bayesCaseOne(Matrix x, Matrix muOne, Matrix muTwo, float varianceOne, float varianceTwo, float priorOne, float priorTwo);
    int bayesCaseTwo(Matrix x, Matrix muOne, Matrix muTwo, Matrix2f sigmaOne, Matrix2f sigmaTwo, float priorOne, float priorTwo);
    int bayesCaseThree(Matrix x, Matrix muOne, Matrix muTwo, Matrix2f sigmaOne, Matrix2f sigmaTwo, float priorOne, float priorTwo);
    
    
private:
    // Helper functions
    float squared(Matrix vec);
    float error(float p, Matrix muOne, Matrix muTwo, Matrix2f sigmaOne, Matrix2f sigmaTwo);
};

// Classifier.cpp

int Classifier::bayesCaseOne(Matrix x, Matrix muOne, Matrix muTwo, float varianceOne, float varianceTwo, float priorOne, float priorTwo) {
    float discrimOne = (((1.0 / varianceOne) * muOne).transpose() * x) - (1.0 / (2 * varianceOne)) * squared(muOne);
    float discrimTwo = (((1.0 / varianceTwo) * muTwo).transpose() * x) - (1.0 / (2 * varianceTwo)) * squared(muTwo);
    
    if (priorOne != priorTwo) {
        discrimOne += log(priorOne);
        discrimTwo += log(priorTwo);
    }
    
    if (discrimOne > discrimTwo) {
        return 1;
    } else {
        return 2;
    }
}

int Classifier::bayesCaseTwo(Matrix x, Matrix muOne, Matrix muTwo, Matrix2f sigmaOne, Matrix2f sigmaTwo, float priorOne, float priorTwo) {
    float discrimOne = (sigmaOne.inverse() * muOne).transpose() * x)(0) - (0.5 * muOne.transpose() *sigmaOne.inverse() * muOne);
    float discrimTwo = (sigmaTwo.inverse() * muTwo).transpose() * x)(0) - (0.5 * muTwo.transpose() *sigmaTwo.inverse() * muTwo);
    
    if (priorOne != priorTwo) {
        discrimOne += log(priorOne);
        discrimTwo += log(priorTwo);
    }
    
    if (discrimOne > discrimTwo) {
        return 1;
    } else {
        return 2;
    }
}

int Classifier::bayesCaseThree(Matrix x, Matrix muOne, Matrix muTwo, Matrix2f sigmaOne, Matrix2f sigmaTwo, float priorOne, float priorTwo) {
    float discrimOne = (x.transpose() * (-0.5 * sigmaOne.inverse()) * x) + (sigmaOne.inverse() * muOne).transpose() * x)(0) + (-0.5 * muOne.transpose() *2f sigmaOne.inverse() * muOne) + (-0.5 * log sigmaOne.determinant()));
    float discrimTwo = (x.transpose() * (-0.5 * sigmaTwo.inverse()) * x) + ( sigmaTwo.inverse() * muTwo).transpose() * x)(0) + (-0.5 * muTwo.transpose

}
int Classifier::classify(Matrix x, Matrix muOne, Matrix muTwo, vector<Matrix> vars, float priorOne, float priorTwo) {
    int discriminantCase = 3;
    if (std::equal(vars.cbegin() + 1, vars.cend(), vars.cbegin())) {
        discriminantCase = 2;
        if (vars[0].isDiagonal() && (vars[0].diagonal().array() == vars[0](0, 0)).all()) {
            discriminantCase = 1;
        }
    }
    
    switch (discriminantCase) {
        case 1:
            float varianceOne = vars[0](0, 0);
            float varianceTwo = vars[0](0, 0);
            return bayesCaseOne(x, muOne, muTwo, varianceOne, varianceTwo, priorOne, priorTwo);
        case 2:
            Matrix2f sigmaOne = vars[0];
            Matrix2f sigmaTwo = vars[0];
            return bayesCaseTwo(x, muOne, muTwo,sigmaOne, sigmaTwo, priorOne, priorTwo);
        default:
            Matrix2f sigmaOne = vars[0];
            Matrix2f sigmaTwo = vars[1];
            return bayesCaseThree(x, muOne, muTwo,sigmaOne,sigmaTwo, priorOne, priorTwo);
    }
}



#endif
