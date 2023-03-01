// classification.hpp
// A library that contains tools for classification.
// Authors:
// Date: 27 February 2023

#ifndef _CLASSIFICATION_H_
#define _CLASSIFICATION_H_

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <math.h>
#include <Eigen/Dense>
#include <Eigen/Core>

// Classifier.cpp

int bayesCaseOne(Eigen::Matrix<float, 2, 1> muOne, Eigen::Matrix<float, 2, 1> muTwo, float varianceOne, float varianceTwo, float priorOne, float priorTwo, const std::string& sourceFile, const std::string& destFile) {
    std::ifstream inFile;
    inFile.open(sourceFile.c_str());

    // Open file for writing classifications to
    std::ofstream outFile;
    outFile.open(destFile.c_str());

    float xf, yf, _f;
    while (inFile >> xf >> yf >> _f) {
        Eigen::Matrix<float, 2, 1> x;
        x << xf, yf;

        float discrimOne = (((1.0 / varianceOne) * muOne).transpose() * x) - (1.0 / (2 * varianceOne)) * pow(muOne.norm(), 2);
        float discrimTwo = (((1.0 / varianceTwo) * muTwo).transpose() * x) - (1.0 / (2 * varianceTwo)) * pow(muTwo.norm(), 2);

        if (priorOne != priorTwo) {
            discrimOne += log(priorOne);
            discrimTwo += log(priorTwo);
        }

        // Save choice
        outFile << xf << " " << yf << " ";
        if (discrimOne < discrimTwo) {
            outFile << "1";
        } else {
            outFile << "2";
        }
        outFile << std::endl;
    }

    inFile.close();
    outFile.close();

    return 0;
}


int bayesCaseTwo(const Eigen::Matrix<float, 2, 1>& muOne, const Eigen::Matrix<float, 2, 1>& muTwo, const Eigen::Matrix2f& sigmaOne, const Eigen::Matrix2f& sigmaTwo, float priorOne, float priorTwo, const std::string& sourceFile, const std::string& destFile) {
    std::ifstream inFile;
    inFile.open(sourceFile);

    // Open file for writing classifications to
    std::ofstream outFile;
    outFile.open(destFile);

    float xf, yf, _f;
    while(inFile >> xf >> yf >> _f) {
        Eigen::Vector2f x(xf, yf);
        float discrimOne = ((sigmaOne.inverse() * muOne).transpose() * x)(0) - (0.5 * muOne.transpose() * sigmaOne.inverse() * muOne);
        float discrimTwo = ((sigmaTwo.inverse() * muTwo).transpose() * x )(0) - (0.5 * muTwo.transpose() * sigmaTwo.inverse() * muTwo);

        if (priorOne != priorTwo) {
            discrimOne += log(priorOne);
            discrimTwo += log(priorTwo);
        }

        // Save choice
        outFile << xf << " " << yf << " ";
        if(discrimOne < discrimTwo) {
            outFile << "1";
        }
        else {
            outFile << "2";
        }
        outFile << std::endl;
    }

    // Close files
    inFile.close();
    outFile.close();

}


int bayesCaseThree(const Eigen::Matrix<float, 2, 1>& muOne, const Eigen::Matrix<float, 2, 1>& muTwo, 
    const Eigen::Matrix2f& sigmaOne, const Eigen::Matrix2f& sigmaTwo, float priorOne, float priorTwo,
    const std::string& sourceFile, const std::string& destFile) {

    std::ifstream inFile;
    inFile.open(sourceFile);

    // Open file for writing classifications to
    std::ofstream outFile;
    outFile.open(destFile);

    float xf, yf, _f;
    while (inFile >> xf >> yf >> _f) {
        Eigen::Vector2f x(xf, yf);
        float discrimOne = (x.transpose() * (-0.5 * sigmaOne.inverse()) * x) + (sigmaOne.inverse() * muOne).transpose() * x(0) +(-0.5 * muOne.transpose() * sigmaOne.inverse() * muOne) + (-0.5 * log(sigmaOne.determinant()));
        float discrimTwo = (x.transpose() * (-0.5 * sigmaTwo.inverse()) * x) + (sigmaTwo.inverse() * muTwo).transpose() * x(0) +(-0.5 * muTwo.transpose() * sigmaTwo.inverse() * muTwo) + (-0.5 * log(sigmaTwo.determinant()));

        if (priorOne != priorTwo) {
            discrimOne += log(priorOne);
            discrimTwo += log(priorTwo);
        }

        // Save choice
        outFile << xf << " " << yf << " ";
        if (discrimOne < discrimTwo) {
            outFile << "1";
        }
        else {
            outFile << "2";
        }
        outFile << std::endl;
    }

    // Close files
    inFile.close();
    outFile.close();
}


void classifyEuclidean(Eigen::Matrix<float, 2, 1> means1,
		Eigen::Matrix<float, 2, 1> means2,
		std::string sourceFile,
		std::string destFile) {
	// Open file for reading feature sets
	std::ifstream inFile;
	inFile.open(sourceFile);

	// Open file for writing classifications to
	std::ofstream outFile;
	outFile.open(destFile);

	// Read features from source file
	float xf, yf, _f;
	while(inFile >> xf >> yf >> _f) {
		// Compute distance from first mean
		float dist1 = std::pow((xf - means1(0, 0)), 2)
			+ std::pow((yf - means1(1, 0)), 2);

		// Compute distance from second mean
		float dist2 = std::pow((xf - means2(0, 0)), 2)
			+ std::pow((yf - means2(1, 0)), 2);

		// Save choice
		outFile << xf << " " << yf << " ";
		if(dist1 < dist2) {
			outFile << "1";
		}
		else {
			outFile << "2";
		}
		outFile << std::endl;
	}

	// Close files
	inFile.close();
	outFile.close();
}


#endif
