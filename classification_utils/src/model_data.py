"""Define data ingestion utilities."""

import pandas
from sklearn.model_selection import train_test_split


class ClassificationData:
    """Classification data configuration handler."""

    def __init__(self, data_conf):
        """Read configuration data from the parameter dictionary.

        Parameters
        ----------
        data_conf : Dictionary of configuration data. See
                    config/ClassificationDataConfig.ini for further details.
        """

        self._conf = data_conf
        self._data = pandas.read_csv(self._conf['csv_file'])

        self._features = [str(f) for f in self._conf['features'].split(',')]
        self._labels = self._conf['labels']

    def train_test_split(self, test_size=None, train_size=None,
                         random_state=None, shuffle=True, stratify=None):
        """Wrapper for the sklearn.model_selection.train_test_split method."""

        X = self._data[self._features]
        y = self._data[self._labels]

        return train_test_split(X,
                                y,
                                test_size=test_size,
                                train_size=train_size,
                                random_state=random_state,
                                shuffle=shuffle,
                                stratify=stratify)
