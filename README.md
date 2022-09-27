# Optical Character Recognition


This program employes the Histogram of Oriented Gradients for feature detection and the K-nearest neighbors algorithm for classification on handwritten digits 0-9.

The data used for training and testing is from the MNIST dataset. Which can be found at http://yann.lecun.com/exdb/mnist/. 

Currently working at a 96% correct digit identification rate. These results were obtained with k set to 3, and 2000 HOGs per digit for the KNN algorithm to reference for classification. 
