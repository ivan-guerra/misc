#!/usr/bin/python

"""Lesion map data preprocessor.

usage: lesion_data_preprocessor.py FILENAME ROWS COLS [-h]

lesion_data_preprocessor.py is a script which takes as input a CSV file
(FILENAME) containing the raw lesion map data. The expected format of each
line in the CSV file is

    behavioral_score,layer_label,[0|0.5|1],[0|0.5|1],...,[0|0.5|1]

where 0 implies no lesion, 0.5 implies half lesion, and 1 implies full lesion.
ROWS and COLS are the number of rows and columns in the flattened lesion map
matrix respectively. The output of this script is a CSV file that can be
input directly to the layer_model_generator.py script to produce a fully
trained neural net.
"""

import pandas
import argparse
import datetime
import numpy as np


def generate_lesion_training_csv(filename, rows, cols, verbose=False):
    """Generate a lesion map training CSV from raw behavioral data.

    generate_lesion_training_csv() expects each sample in the input CSV file
    to have the format

    behavioral_score,layer_label,[0|0.5|1],[0|0.5|1],...,[0|0.5|1]

    Each sample is seperated by a newline. Each float value has the following
    number to label mapping:

    0   -> NL (No Lesion)
    0.5 -> HL (Half Lesion)
    1   -> FL (Full Lesion)

    Parameters
    ----------
    filename : str
        Path to the raw behavioral data CSV file.
    rows : int
        Number of rows in the lesion map matrix.
    cols : int
        Number of cols in the lesion map matrix.
    verbose : bool
        Flag enabling function verbosity.
    """

    dataframe = pandas.read_csv(filename, header=None)
    dataset = dataframe.values
    X = np.asarray(dataset[:, 0]).astype(np.float32)
    labels = np.asarray(dataset[:, 2:])

    samples = []
    label_map = {0.0: 'NL', 0.5: 'HL', 1.0: 'FL'}
    for i in range(len(X)):
        matrix = np.reshape(labels[i], (rows, cols))
        for x in range(0, matrix.shape[0]):
            for y in range(0, matrix.shape[1]):
                label = label_map[matrix[x, y]]
                samples.append([X[i], x, y, label])

    output = pandas.DataFrame(np.array(samples))

    date = datetime.datetime.now().strftime("%Y_%m_%d-%I:%M:%S_%p")
    layer = dataframe.values[0][1].lower()
    output_filename = layer + '_layer_training_data_' + str(date) + '.csv'
    output.to_csv(output_filename, index=False, header=None)

    if verbose:
        print('Results have been output to', output_filename)


if __name__ == '__main__':
    parser = argparse.ArgumentParser(
        description='Lesion Map Data Preprocessor.')
    parser.add_argument('filename', type=str,
                        help='path to lesion data CSV file')
    parser.add_argument('rows', type=int,
                        help='number of rows in the lesion map matrix')
    parser.add_argument('cols', type=int,
                        help='number of columns in the lesion map matrix')
    args = parser.parse_args()

    generate_lesion_training_csv(args.filename, args.rows, args.cols, True)
