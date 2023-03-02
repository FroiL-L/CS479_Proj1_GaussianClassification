import numpy as np
import matplotlib.pyplot as plt
from scipy.stats import multivariate_normal

# read input data from file
X = np.loadtxt("B_BC.txt", dtype=float)

# select 500 rows with ID 1 and 500 rows with ID 2 from X
X_id1 = X[X[:, 2] == 1][:500]
X_id2 = X[X[:, 2] == 2][:500]
X = np.concatenate([X_id1, X_id2], axis=0)
Y = X[:, 1]

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

# evaluate the probability densities at (5, 5)
Z1 = multivariate_normal.pdf([5, 5], mean=mu1, cov=cov1)
Z2 = multivariate_normal.pdf([5, 5], mean=mu2, cov=cov2)

# calculate the decision boundary
Z = Z1 - Z2

# plot the decision boundary
x = np.linspace(-10, 10, 100)
y = x + 5  # slope = 1, y-intercept = 5

plt.plot(x, y, '-r', label='y=x+5')
plt.plot(5, 5, 'bo', label='(5,5)')

#for plot B
##plt.contourf(xx, yy, Z, levels=[-1, 0, 1], colors=('blue', 'red'), alpha=0.2)

# create a color map for the data points
colors = np.concatenate([np.array(['blue'] * 500), np.array(['red'] * 500)])

# plot the data points
plt.scatter(X[:, 0], X[:, 1], c=colors, cmap=plt.cm.coolwarm, edgecolors='black')

plt.title('Bayes Classifier Decision Boundary')
plt.xlabel('Feature 1')
plt.ylabel('Feature 2')
plt.show()
