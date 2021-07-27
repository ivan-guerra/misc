#!/usr/bin/python

"""Lesion map neural network generator.

usage: layer_model_generator.py TRAININGPATH LAYER [-h]

layer_model_generator.py takes as input a training data CSV file produced by
the lesion_data_preprocessor.py script and a layer label (i.e., A, D, or G).
The output is a trained neural network (saved as <LAYER>_model.h5) and an
encoder file (saved as <LAYER>_encoder.npy). These files are used by the
predict_lmap.py script to output predictions using the pre-trained NN.
"""

import pandas
import argparse
import numpy as np
from keras.models import Sequential
from keras.layers import Dense
from sklearn.preprocessing import LabelEncoder
from keras.layers import Dropout
from keras.constraints import maxnorm
from keras.optimizers import Adam
from keras.utils import np_utils

# Import these objects if you are retuning the lesion map NN.
# from sklearn.model_selection import GridSearchCV
# from keras.wrappers.scikit_learn import KerasClassifier

# The baseline_model() function can be used in conjunction with the
# run_grid_search() function to perform hyperparameter tuning on a set of
# lesion data. See
# https://towardsdatascience.com/simple-guide-to-hyperparameter-tuning-in-neural-networks-3fe03dad8594
# to learn more.
# def baseline_model(neurons=1, optimizer='adam', init_mode='uniform',
#                    dropout_rate=0.0, weight_constraint=0,
#                    learning_rate=0.01):
#     model = Sequential()
#     model.add(Dropout(dropout_rate, input_shape=(3, )))
#     model.add(Dense(neurons, input_dim=3, activation='relu',
#                     kernel_constraint=maxnorm(weight_constraint),
#                     kernel_initializer=init_mode))
#     model.add(Dropout(dropout_rate))
#     model.add(Dense(3, activation='softmax', kernel_initializer=init_mode))
#
#     opt = Adam(learning_rate=learning_rate)
#     model.compile(loss='categorical_crossentropy', optimizer=opt,
#                   metrics=['accuracy'])
#     return model


# def run_grid_search():
#     X, Y = load_lesion_data()
#     encoder, dummy_y = encode_labels(Y)
#
#     estimator = KerasClassifier(build_fn=baseline_model, verbose=False)
#     batch_size = [8, 16, 32]
#     epochs = [2, 5, 10]
#     neurons = [3, 5]
#     learning_rate = [1e-02, 1e-03, 1e-04, 1e-05]
#     init_mode = ['he_normal', 'he_uniform']
#     weight_constraint = [1, 3, 5]
#     dropout_rate = [0.1, 0.5, 0.9]
#     param_grid = dict(batch_size=batch_size, epochs=epochs, neurons=neurons,
#                       learning_rate=learning_rate, init_mode=init_mode,
#                       weight_constraint=weight_constraint,
#                       dropout_rate=dropout_rate)
#     grid = GridSearchCV(estimator=estimator, param_grid=param_grid, n_jobs=3,
#                         cv=5)
#     grid_result = grid.fit(X, dummy_y)
#
#     print("Best: %f using %s" %
#           (grid_result.best_score_, grid_result.best_params_))
#     means = grid_result.cv_results_['mean_test_score']
#     stds = grid_result.cv_results_['std_test_score']
#     params = grid_result.cv_results_['params']
#     for mean, stdev, param in zip(means, stds, params):
#         print("%f (%f) with: %r" % (mean, stdev, param))


def load_lesion_data(filename):
    """Extract features and labels from the parameter CSV file.

    The expected format of the input CSV file should be produced using the
    lesion_data_preprocessor.py script included with this project.

    Parameters
    ----------
    filename : str
        Path to the CSV file produced by lesion_data_preprocessor.py.

    Returns
    -------
    X : pandas.DataFrame
        Data set features (i.e., behavioral_score, row_index, col_index).
    Y : pandas.DataFrame
        Data set labels (i.e., lesion label [NL, HL, FL]).
    """

    dataframe = pandas.read_csv(filename, header=None)
    dataset = dataframe.values
    X = dataset[:, 0:3].astype(float)
    Y = dataset[:, 3].astype(str)

    return X, Y


def encode_labels(labels):
    """Encode the parameter labels as integers.

    Parameters
    ----------
    labels : pandas.DataFrame
        A Pandas DataFrame containing unique labels.

    Returns
    -------
    encoder : sklearn.preprocessing.LabelEncoder
        A LabelEncoder object fit on on the parameter labels.
    encoded_Y
        Encoded labels.
    """

    encoder = LabelEncoder()
    encoder.fit(labels)
    encoded_Y = encoder.transform(labels)

    # convert integers to dummy variables (i.e. one hot encoded)
    return encoder, np_utils.to_categorical(encoded_Y)


def lesion_map_model():
    """Returns a neural network model optimized for lesion map data.

    lesion_map_model() returns a model containing 'optimal' parameters found
    via grid search. The metric used to measure performance is accuracy which
    may not be the best options for this dataset. Additional tuning can
    be performed when more data is available using the baseline_model() and
    run_grid_search() functions.

    Returns
    -------
    A neural network model tuned for the lesion map prediction problem.
    """

    model = Sequential()
    model.add(Dropout(0.9, input_shape=(3, )))
    model.add(Dense(5, input_dim=3, activation='relu',
                    kernel_constraint=maxnorm(1),
                    kernel_initializer='he_normal'))
    model.add(Dropout(0.9))
    model.add(Dense(3, activation='softmax', kernel_initializer='he_normal'))
    opt = Adam(learning_rate=0.0001)
    model.compile(loss='categorical_crossentropy', optimizer=opt,
                  metrics=['accuracy'])
    return model


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Lesion Map NN Generator.')
    parser.add_argument('trainingpath', type=str,
                        help='path to lesion map training CSV file')
    parser.add_argument('layer', type=str.lower,
                        help='target layer label (i.e., A, G, or D)')
    args = parser.parse_args()

    # Load the lesion map training data and one-hot encode the output labels.
    X, Y = load_lesion_data(args.trainingpath)
    encoder, dummy_y = encode_labels(Y)

    model = lesion_map_model()
    # The parameters epochs and batch_size were determined via a grid search
    # and are meant to produce optimal results with the model returned by
    # lesion_map_model(). **Do not change epochs or batch_size unless you
    # retune the model.**
    model.fit(X, dummy_y, epochs=10, batch_size=32)

    # Save the NN model.
    model.save(args.layer.lower() + '_model.h5')

    # Save the LabelEncoder object.
    np.save(args.layer.lower() + '_encoder.npy', encoder.classes_)
