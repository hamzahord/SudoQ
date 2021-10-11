#include <stdio.h>
#include "sigmoid.h"
#include "neuron.h"


int main(){
 double inputs[4][2] = {{0,0},{1,0},{0,1},{1,1}};
 int epoc = 0;
 double result[4] = {0,1,1,0};
 struct Neuron hiddenNeuron1;
 struct Neuron hiddenNeuron2;
 struct Neuron outputNeuron;
 hiddenNeuron1 = randomizeWeights(hiddenNeuron1);
 hiddenNeuron2 = randomizeWeights(hiddenNeuron2);
 outputNeuron = randomizeWeights(outputNeuron);
 while(epoc < 2000){
  for (int i = 0; i < 4; i++){
   hiddenNeuron1.input[0] = inputs[i][0];
   hiddenNeuron1.input[1] = inputs[i][1];
   hiddenNeuron2.input[0] = inputs[i][0];
   hiddenNeuron2.input[1] = inputs[i][1];
   outputNeuron.input[0] = output(hiddenNeuron1);
   outputNeuron.input[1] = output(hiddenNeuron2);
   printf("%lf xor %lf = %lf\n",inputs[i][0],inputs[i][1]
    ,output(outputNeuron));
   outputNeuron.error = deriv_sigmoid(output(outputNeuron))
    *(result[i]-output(outputNeuron));
   outputNeuron = adjustWeights(outputNeuron);
   hiddenNeuron1.error = deriv_sigmoid(output(hiddenNeuron1))
    *outputNeuron.error*outputNeuron.weight[0];
   hiddenNeuron2.error = deriv_sigmoid(output(hiddenNeuron2))
    *outputNeuron.error*outputNeuron.weight[1];
   hiddenNeuron1 = adjustWeights(hiddenNeuron1);
   hiddenNeuron2 = adjustWeights(hiddenNeuron2);
  }
  epoc++;
 }
}
