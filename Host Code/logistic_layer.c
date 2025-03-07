#include "logistic_layer.h"
#include "activations.h"
#include "blas.h"

#include <float.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

layer make_logistic_layer(int batch, int inputs)
{
    fprintf(stderr, "logistic x entropy                             %4d\n",  inputs);
    layer l;
    l.type = LOGXENT;
    l.batch = batch;
    l.inputs = inputs;
    l.outputs = inputs;
    l.loss = (float *) calloc(inputs*batch, sizeof(float));
    l.output = (float *) calloc(inputs*batch, sizeof(float));
    l.delta = (float *) calloc(inputs*batch, sizeof(float));
    l.cost = (float *) calloc(1, sizeof(float));

    l.forward = forward_logistic_layer;
    l.backward = backward_logistic_layer;

    return l;
}

void forward_logistic_layer(const layer l, network net)
{
    copy_cpu(l.outputs*l.batch, net.input, 1, l.output, 1);
    activate_array(l.output, l.outputs*l.batch, LOGISTIC);
    if(net.truth){
        logistic_x_ent_cpu(l.batch*l.inputs, l.output, net.truth, l.delta, l.loss);
        l.cost[0] = sum_array(l.loss, l.batch*l.inputs);
    }
}

void backward_logistic_layer(const layer l, network net)
{
    axpy_cpu(l.inputs*l.batch, 1, l.delta, 1, net.delta, 1);
}


