# Classification Utilities

### Overview
Classification Utilities is a collection of Python scripts that allows Users to
experiment with hyperparameter tuning on various classification models. The
objective is to identify the best hyperparameter combination for each
selected model on a User defined dataset(s). The metric used to measure
performance is prediction accuracy though future updates will introduce support
for additional metrics.

To view all supported models and their configurable hyperparameters, checkout
the [ClassificationModelConfig.ini](https://github.com/ivan-guerra/classification_utils/blob/master/config/ClassificationModelConfig.ini).
included with this project. For more details regarding each hyperparameter,
visit the model's corresponding doc page on
[scikit-learn](https://scikit-learn.org/stable/).

### Installation and Dependencies

To use the tools in this project, you will need
[Python3](https://www.python.org/downloads/) and the following packages:

* [scikit-learn](https://scikit-learn.org/stable/)
* [NumPy](https://numpy.org/)
* [Pandas](https://pandas.pydata.org/)

### Configuration

The core `classifier.py` script requires a dataset configuration file and a
model parameter configuration file. Examples of each file can be found under
`classification_utils/config`.

`classifier.py` supports commandline arguments. To view all options, use the
`--help` option:

```
python classifier.py --help
```

You can tell the script where your configuration files are by using the
`--data-conf` and `--model-conf` options:

```
python classifier.py --data-conf /path/to/data.ini --model-conf /path/to/model.ini
```

When tuning model parameters in the model configuration file, *be sure to
consult the scikit-learn docs for the model that you are configuring*! Some
combinations of parameters are unsupported or simply do not make sense for
certain datasets. If you see errors or warnings in the output, consult the
docs!

### Sample Run

To run `classifier.py` using the sample datasets under `sample_data/` and
the default configurations under `configs/`, follow these steps:

1. Open a terminal.
2. Navigate to the `src` directory: `cd /path/to/classification_utils/src/`
3. Run `classifier.py`: `python classifier.py -d /path/to/classifcation_utils/config/ClassificationDataConfig.ini -m /path/to/classifcation_utils/config/ClassificationModelConfig.ini`

You should see output similar to that below:

```
IrisData Results:
	LogisticRegression:
		Best Parameters {'C': 1.0, 'max_iter': 10000, 'penalty': 'l2', 'solver': 'liblinear', 'tol': 0.0001}
		Mean cross-validates accuracy score of the best_estimator: 0.928
...
```

For each dataset specified, the script will show the parameters that give
the best predictions as well as the prediction accuracy associated with those
parameters.

### License
This software is licensed under GPLv3 license (see LICENSE file).
