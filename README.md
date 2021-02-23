# VLSI-KMNIST-Recognition-FPGA
Machine Learning Section from Very Large Scale Integration final project on Institut Teknologi Bandung that will be implemented on FPGA.


## Background

Convolutional Neural Network (CNN) has the advantage in its ability to learn features or characteristics from the model through many layers, such as convolution layer, pooling layer, and classification layer (fully connected layer). Each layer will do unique task, thus it can be implemented separately in hardware or software. Along with this advantages, CNN will recognize object more accurately compared to other neural network techniques. In this project, we proposed the design of CNN to recognize ancient Japanese handwritten characters (Kuzushiji). 

Kuzushiji is written in a script which differs substantially from modern Japanese, making even basic recognition difficult for contemporary Japanese. However, once Kuzushiji has been converted to the modern script, it is readable by most people fluent in Japanese. Even so, some difficulties remain due to changes in grammar and vocabulary. Kuzushiji recognition is very challenging, because it is capturing both local and global context which is important, the total number of characters in the vocabulary is very large, many characters can be written in multiple ways, and kuzushiji texts are often written together with illustrations and elaborate backgrounds, which are hard to separate from text. Hence, we are about to implementing CNN to perform detection of written Kuzushiji.

This project uses about 10 classes to make the dataset as look as MNIST dataset. Here are some images of Kuzushiji that are used in this projects.

## Architecture
Convolutional Neural Network is one of neural network in deep learning algorithm which able to differentiate one image from other with its various aspects/objects in the image. CNN has an ability to learn these filters/characteristics through many layers and steps, such as convolution layer, pooling layer, and classification layer (fully connected layer). We utilize FIR (finite impulse response) architecture in this task.

### Convolution Layer
In CNN, convolution is the first layer to extract features from an input image. In this layer, it performs dot products operation between image and a set of filters (kernels) to get convolved feature with fewer parameters. To implement such operation to do convolution, we are using FIR architecture. The figure above shows the implementation of FIR architecture to do convolution with Kernel 3x3. 

### Pooling Layer
Pooling layer is responsible for reducing the size of the convolved feature. It is used to decrease the parameter of input image before entering the classification (fully connected) layer by extracting dominant feature of the model. In this CNN architecture, we are using max pooling which returns  the maximum value from the portion of the image covered by the Kernel. 

### Classification Layer - Fully Connected Layer
The objective of a fully connected layer is to take the results of the convolution/pooling process and use them to classify the image into a label (in a simple classification example). The output of convolution/pooling is flattened into a single vector of values, each representing a probability that a certain feature belongs to a label.The fully connected part of the CNN network goes through its own backpropagation process to determine the most accurate weights. Each neuron receives weights that prioritize the most appropriate label. Finally, the neurons “vote” on each of the labels, and the winner of that vote is the classification decision.

## Design Process
To be able to conduct the training process, we need to load subsets that will be used. KMNIST Datasets are available in .npz format and are able to be loaded with numpy.load command. Here are the results of the loaded dataset and it shows the size of the array. 

From the results, we know that we have 60000 datasets of training image and 10000 datasets of test image. After the datasets are successfully put into the system, a CNN model that will be implemented in this system are created. Here are the models.

- Convolutional Layer 1 (Layer 1)
   - Number of kernel 		: 6 Kernel, 
   - Kernel size			: 3x3, 
   - Activation function 	: ReLU 
   - Bias			: No
- Maxpooling Layer
   - Kernel size 		: 2x2
- Convolutional Layer 2 (Layer 2)
   - Number of kernel 		: 6 Kernel, 
   - Kernel size			: 3x3, 
   - Activation function 	: ReLU 
   - Bias			: No
- Maxpooling Layer
   - Kernel size 		: 2x2
- Flattening
- Dense Layer 1 (Layer 3)
   - Number of kernel  	: 64 kernel, 
   - Activation function	: ReLU
- Dense Layer 2 (Layer Output)
   - Number of kernel  	: 10 kernel, 
   - Activation function	: Softmax
   
This is the summary of training systems that will be made.

The input value which initially is 28 x 28, becomes 26 x 26 x 6 after being operated with layer 1 convolution. After that, the data will enter layer 1 max pooling thus becoming 13 x 13 x 6. And then, the data will enter layer 2 convolution and max pooling. In this process, the dimension will change to 5 x 5 x 6 and will be flattened to 1 x 150. This flattened array will be densed from size of 64 to size of 10. The total of used parameters is 10.618 and most of them are located in hidden layers.

We will implement the model in system which has not been trained in tensorflow. This is the result of training for 2 epoch with adam compiler and model loss: sparse categorical crossentropy.

From training process, the accuracy level is 85.58 %. The input images and weight parameters are quantized to 7 bit and will be trained again with 7 bit precision so the accuracy level is still in 85.58%.


The 85.58% accuracy level is high enough to be implemented as hardware design in FPGA. All of the model weights will be extracted to size of 7 bit which then will be the weight of parameters if FPGA. 
