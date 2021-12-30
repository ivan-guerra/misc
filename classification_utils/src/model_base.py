"""Define a classification model base class.

Classification models in this application inherit ClassificationModelBase.
Examples of models that derive from ClassificationModelBase can be found
under src/models/.
"""

from sklearn.model_selection import GridSearchCV


class ClassificationModelBase:
    """Classification model base class."""

    def __init__(self, model_conf, model):
        self._conf = model_conf
        self._model = model
        self._parameters = self.get_params()

    def fetch_parameter(self, key, data_type, is_list=False):
        """Return the configuration data corresponding to key.

        Parameters
        ----------
        key       : String corresponding to the parameter data to be fetched.
        data_type : Type of the data being extracted (e.g., int, float, str).
        is_list   : Flag indicating whether the parameter is a list of elements
                    (True) or a single value (False).
        """

        if key not in self._conf:
            return None

        if is_list:
            return [data_type(val) for val in self._conf[key].split(',')]
        else:
            return data_type(self._conf[key])

    def get_params(self):
        """Fetch model parameters from the INI file."""

        return None

    def grid_search(self, X_train, y_train, cv=5, scoring='accuracy'):
        """Wrap the sklearn.model_selection.GridSearchCV function."""

        gs_model = GridSearchCV(
          self._model,
          self._parameters,
          cv=cv,
          scoring=scoring)
        gs_model.fit(X_train, y_train)

        return gs_model
