#ifndef DILATED_CONVOLUTIONAL_LAYER_H
#define DILATED_CONVOLUTIONAL_LAYER_H

#include "image.h"
#include "activations.h"
#include "layer.h"
#include "network.h"
#include "im2col_dilated.h"

#include "col2im.h"
#include "col2im_dilated.h"
#include "im2col.h"

#include "darknet.h"

typedef layer dilated_convolutional_layer;


dilated_convolutional_layer make_dilated_conv_layer(int batch, int h, int w, int c, int n, int groups, int size, int stride, int padding, ACTIVATION activation, int batch_normalize, int binary, int xnor, int adam, int dilate_rate);
void resize_dilated_conv_layer(dilated_convolutional_layer *layer, int w, int h);
void forward_dilated_conv_layer(const dilated_convolutional_layer layer, network net, cl::Buffer a_buf, cl::Buffer b_buf, cl::Buffer c_buf, cl::Buffer d_buf);
void update_dilated_conv_layer(dilated_convolutional_layer layer, update_args a);
image *visualize_dilated_conv_layer(dilated_convolutional_layer layer, char *window, image *prev_weights);



void add_bias_dilated(float *output, float *biases, int batch, int n, int size);
void backward_bias_dilated(float *bias_updates, float *delta, int batch, int n, int size);
void scale_bias_dilated(float *output, float *scales, int batch, int n, int size);
image *get_weights_dilated(dilated_convolutional_layer l);
void rescale_weights_dilated(dilated_convolutional_layer l, float scale, float trans);
void rgbgr_weights_dilated(dilated_convolutional_layer l);


void backward_dilated_conv_layer(dilated_convolutional_layer layer, network net);


image get_dilated_conv_image(dilated_convolutional_layer layer);
image get_dilated_conv_delta(dilated_convolutional_layer layer);
image get_dilated_conv_weight(dilated_convolutional_layer layer, int i);

int dilated_conv_out_height(dilated_convolutional_layer layer);
int dilated_conv_out_width(dilated_convolutional_layer layer);

void test_dconv_backprop_gpu();
void test_dconv_backprop_cpu();
void test_dconv_forward_gpu();
void test_dconv_forward_cpu();

#endif

