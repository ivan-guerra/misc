#!/usr/bin/python

"""A classification model grid search utility.

This application is meant to help with hyperparameter tuning on a subset
of the classification models supported by sklearn. The User can define the
dataset, features, and labels via an input INI. Similarly, the classification
model and parameters to be used in the subsequent grid search can be
configured via an INI file. The output is a summary of the best parameter
set and mean cross-validated accuracy score for each data/model pairing.
"""

import argparse
import collections
import configparser
from model_data import ClassificationData
from model_factory import ClassificationModelFactory

if '__main__' == __name__:
    # Parse commandline options.
    parser = argparse.ArgumentParser(
        description='Classification model grid search utility.')
    parser.add_argument('-d', '--data-config',
                        default='../config/ClassificationDataConfig.ini',
                        help='path to data ini file')
    parser.add_argument('-m', '--model-config',
                        default='../config/ClassificationModelConfig.ini',
                        help='path to model ini file')
    args = parser.parse_args()

    # Read both the data and the model INI files.
    data_config = configparser.ConfigParser()
    data_config.read(args.data_config)
    model_config = configparser.ConfigParser()
    model_config.read(args.model_config)

    # Collect grid search results for each (data,model) pairing.
    results = collections.defaultdict(dict)
    for data_section in data_config.sections():
        data = ClassificationData(data_config[data_section])
        X_train, X_test, y_train, y_test = data.train_test_split(
                                                random_state=0)

        model_factory = ClassificationModelFactory()
        for model_section in model_config.sections():
            model = model_factory.get_model(model_section,
                                            model_config[model_section])
            results[data_section][model_section] = model.grid_search(X_train,
                                                                     y_train)

    # Display results to STDOUT.
    for data in results.keys():
        print(data + ' Results:')
        for model, output in results[data].items():
            print('\t' + model + ':')
            print(f'\t\tBest Parameters {output.best_params_}')
            print(
                '\t\tMean cross-validates accuracy score of the ' +
                f'best_estimator: {output.best_score_:.3f}'
            )
