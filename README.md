# Optical Character Recognition


This program employes the Histogram of Oriented Gradients for feature detection and the K-nearest neighbors algorithm for classification on handwritten digits 0-9.

The data used for training and testing is from the MNIST dataset. Which can be found at http://yann.lecun.com/exdb/mnist/. 

Current version has been found to be 96% correct when identifying handwritten digits. These results were obtained with k set to 3, and 2,000 HOGs per digit for the KNN algorithm to reference for classification. 

Examples of digits classified wrong:

guessed: 1, actual: 2
![Alt text](/images/img00004.png?raw=true "Title")

guessed: 7, actual: 2
![Alt text](/images/img00010.png?raw=true "Title")

guessed: 8, actual: 9
![Alt text](/images/img00008.png?raw=true "Title")

