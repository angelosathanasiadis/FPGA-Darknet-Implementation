// Oh boy, why am I about to do this....
#ifndef NETWORK_H
#define NETWORK_H
#include "darknet.h"

#include "image.h"
#include "layer.h"
#include "data.h"





char *get_layer_string(LAYER_TYPE a);

network *make_network(int n);


int get_predicted_class_network(network *net);
void print_network(network *net);
int resize_network(network *net, int w, int h);
void calc_network_cost(network *net);

#endif

