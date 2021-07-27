#!/usr/bin/python

"""Lesion map prediction tool.

usage: predict_lmap.py LAYER BSCORE [-e] [-m] [-h]

predict_lmap.py takes as input a layer label (i.e., A, D, or G) and BSCORE
(behavioral score). The output of the script is a CSV file displaying a lesion
map matrix prediction with no lesion (NL), half lesion (HL), and full lesion
(FL) labels.
"""

import os
import pandas
import argparse
import datetime
import numpy as np
from keras.models import load_model
from sklearn.preprocessing import LabelEncoder


def predict_lesion_map(behavioral_score, encoder, model, rows, cols):
    """Predict a lesion map matrix.

    Parameters
    ----------
    behavioral_score : float
        Target behavioral score.
    encoder : sklearn.preprocessing.LabelEncoder
        Label encoder.
    model : keras.models.Sequential
        A pre-trained lesion map neural network.
    rows : int
        Number of rows in the lesion map matrix.
    cols : int
        Number of cols in the lesion map matrix.

    Returns
    -------
    An numpy.array containing rows x cols lesion map labels.
    """

    # Each model in the models ensemble is used to make a predicition for each
    # individual cell in the lesion map matrix. The collection of results
    # for each cell is averaged to get the final prediction for that cell.
    predictions = []
    for i in range(rows):
        preds = []
        for j in range(cols):
            prediction = model.predict([[behavioral_score, i, j]])
            preds.append(encoder.inverse_transform(np.argmax(prediction,
                                                             axis=1))[0])
        predictions.append(preds)

    return np.array(predictions)


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Lesion Map Prediction Tool.')
    parser.add_argument('layer', type=str.upper,
                        help='target layer label (i.e., A, G, or D)')
    parser.add_argument('bscore', type=float,
                        help='the behavioral score used in the prediction')
    parser.add_argument('-e', '--encoder', type=str, default=None,
                        help='path to the one-shot lesion map label encoder')
    parser.add_argument('-m', '--model', type=str, default=None,
                        help='path to the NN model\'s h5 file')
    args = parser.parse_args()

    # Define layer A, D, and G row/col constants.
    A_ROWS, A_COLS = 900, 3
    D_ROWS, D_COLS = 530, 3
    G_ROWS, G_COLS = 530, 3

    # Load the LabelEncoder object used during model training.
    encoder = LabelEncoder()
    if args.encoder:
        encoder.classes_ = np.load(args.encoder)
    else:
        encoder.classes_ = np.load(os.path.join('..', 'models',
                                                args.layer.lower() +
                                                '_encoder.npy'))

    # Load the pre-trained NN model.
    model = None
    if args.model:
        model = load_model(args.model)
    else:
        model = load_model(os.path.join('..', 'models', args.layer.lower() +
                                        '_model.h5'))

    # Make the map prediction using the appropriate layer NN model.
    prediction_matrix = None
    if 'A' == args.layer:
        prediction_matrix = predict_lesion_map(args.bscore,
                                               encoder,
                                               model,
                                               A_ROWS,
                                               A_COLS)
    elif 'D' == args.layer:
        prediction_matrix = predict_lesion_map(args.bscore,
                                               encoder,
                                               model,
                                               D_ROWS,
                                               D_COLS)
    elif 'G' == args.layer:
        prediction_matrix = predict_lesion_map(args.bscore,
                                               encoder,
                                               model,
                                               G_ROWS,
                                               G_COLS)
    else:
        raise ValueError('unknown layer type specified: ' + repr(args.layer))

    # Output the predicted lesion map matrix to a CSV file.
    date = datetime.datetime.now().strftime("%Y_%m_%d-%I:%M:%S_%p")
    output = pandas.DataFrame(prediction_matrix)
    output_filename = args.layer.lower() + '_pred_' + str(date) + '.csv'
    output.to_csv(output_filename, index=False, header=None)
    print('Results have been output to', output_filename)
