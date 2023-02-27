/* dataGen.hpp:
 * 	Library with tools for generating normally
 * 	distributed data.
 * authors:
 * 	Froilan Luna-Lopez
 * 		University of Nevada, Reno
 * 		CS 479 - Pattern Recognition
 * date:
 * 	27 February 2023
 */

#ifndef _DATAGEN_HPP_
#define _DATAGEN_HPP_

// Libraries
#include "boxmuller.c"
#include <vector>
#include <fstream>
#include <string>

// Methods

/* genGauss():
 * 	Generates random values that are normally distributed
 * 	with a given set of mean and standard deviation.
 * args:
 * 	@count: Number of elements to generate.
 * 	@mean: The mean of the distribution.
 * 	@sd: The standard deviation of the distribution.
 * 	@dest: The location to save the generated values.
 * return:
 * 	@dest
 */
void genGauss(int count, float mean, float sd, std::vector<float>& dest) {
	for(int i = 0; i < count; i++) {
		dest.push_back(box_muller(mean, sd));
	}
}

/* save2D():
 * 	Saves two sets of vectors in a file.
 * args:
 * 	@source1: A vector with values to grab from.
 * 	@source2: A vector with values to grab from.
 * 	@fname: The name of the file to save to.
 * return:
 * 	void
 */
void save2D(std::vector<float>& source1, std::vector<float>& source2, std::string fname) {
	// Open output file
	std::ofstream outFile;
	outFile.open(fname);

	// Save the first set of data
	for(int i = 0; i < source1.size(); i++) {
		outFile << std::to_string(source1[i]) 
			<< std::endl;
	}

	// Save the second set of data
	for(int i = 0; i < source2.size(); i++) {
		outFile << std::to_string(source2[i])
			<< std::endl;
	}

	// Close the opened file
	outFile.close();
}

#endif
