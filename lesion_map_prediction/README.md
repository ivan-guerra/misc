# Lesion Map Prediction

### Overview

The Lesion Map Prediction (LMP) project is a collection of Python scripts that
allows Users to train neural nets targeting different layers of the brain. The
trained NNs take as input a behavioral score and output a lesion map matrix
showing which sections have no lesion, half lesion, and full lesion.

Due to limited data, the predictions produced by the NNs are relatively
inaccurate. This project provides a framework for further development once
additional training data is available.

### Installation and Dependencies

To use the tools in this project, you will need
[Python3](https://www.python.org/downloads/) and the following packages:

* [scikit-learn](https://scikit-learn.org/stable/)
* [NumPy](https://numpy.org/)
* [Pandas](https://pandas.pydata.org/)
* [Keras](https://keras.io/)
* [TensorFlow](https://www.tensorflow.org/learn)

### Making Lesion Map Predictions

To make lesion map predictions using the pre-trained NNs included in this
project, follow these steps:

1. Open a terminal.
2. Change directory to the LMP `src` directory: `cd /path/to/LMP/src/`
3. Run `predict_lmap.py` supplying both a lesion label (i.e., A, D, or G) and
   floating point behavioral score: `python predict_lmap.py G 91.5`
4. When the run completes, you will see the message:
   `Results have been output to...`. It may take a few minutes for the run to
   complete.
5. Open the output CSV to view the predicted lesion map matrix. For this
   example, a file labeled `g_pred_<DATE>.csv` will be output.

The labels in the output matrix can be interpreted as follows:

* NL: No Lesion
* HL: Half Lesion
* FL: Full Lesion

### Generating Additional Training Data and Training New NNs

LMP provides scripts for both generating lesion map training data from raw
lesion map data as well as training NNs using newly available training data.

`lesion_data_preprocessor.py` takes as input raw lesion data (see
[LMP/data/raw](https://github.com/ivan-guerra/lesion_map_prediction/tree/master/data/raw))
for examples). The output is a CSV file that can be given to the
`layer_model_generator.py` to produce new NNs trained on the dataset. Examples
of training data produced by `lesion_data_preprocessor.py` can be found under
[LMP/data/training](https://github.com/ivan-guerra/lesion_map_prediction/tree/master/data/raw)

`layer_model_generator.py` takes as input preprocessed training data and
outputs a NN `*.h5` file trained on that dataset as well an associated label
encoder `*.npy` file. These files are used by the `predict_lmap.py` script
when making predictions

All scripts in the `src` directory support the `-h` and `--help` commandline
arguments. Use these arguments to get more script usage details.

### License
This software is licensed under an MIT license (see [LICENSE](https://github.com/ivan-guerra/lesion_map_prediction/blob/master/LICENSE) file).
