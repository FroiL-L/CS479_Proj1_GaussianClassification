import numpy as np
import matplotlib.pyplot as plt
from scipy.stats import multivariate_normal

# read input data from file
X = np.loadtxt("B_BC.txt",dtype=float)

# Bayes classifier parameters
mu1 = np.array([1, 1])
mu2 = np.array([4, 4])
cov1 = np.array([[1, 0], [0, 1]])
cov2 = np.array([[4, 0], [0, 8]])
p1 = 0.5
p2 = 0.5

# define a mesh grid of points to evaluate the decision boundary
h = 0.02
x_min, x_max = X[:, 0].min() - 0.5, X[:, 0].max() + 0.5
y_min, y_max = X[:, 1].min() - 0.5, X[:, 1].max() + 0.5
xx, yy = np.meshgrid(np.arange(x_min, x_max, h), np.arange(y_min, y_max, h))

# evaluate the probability densities on the mesh grid
Z1 = multivariate_normal.pdf(np.c_[xx.ravel(), yy.ravel()], mean=mu1, cov=cov1)
Z1 = Z1.reshape(xx.shape)

Z2 = multivariate_normal.pdf(np.c_[xx.ravel(), yy.ravel()], mean=mu2, cov=cov2)
Z2 = Z2.reshape(xx.shape)

# calculate the decision boundary
Z = Z1 - Z2

# plot the decision boundary
plt.contourf(xx, yy, Z, levels=[-1, 0, 1], colors=('blue', 'red'), alpha=0.2)

# create a color map for the data points
colors = ['blue'] * int(len(X)/2) + ['red'] * int(len(X)/2)

# plot the data points
plt.scatter(X[:, 0], X[:, 1], c=colors, cmap=plt.cm.coolwarm, edgecolors='black')

plt.title('Bayes Classifier Decision Boundary')
plt.xlabel('Feature 1')
plt.ylabel('Feature 2')
plt.show()
