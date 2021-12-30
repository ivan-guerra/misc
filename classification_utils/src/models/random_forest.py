"""Wrap the sklearn.ensemble Random Forest Classifier."""

from model_base import ClassificationModelBase
from sklearn.ensemble import RandomForestClassifier


class RandomForestModel(ClassificationModelBase):
    def __init__(self, model_conf):
        model = RandomForestClassifier()
        super().__init__(model_conf, model)

    def get_params(self):
        parameters = {}
        parameters['max_features'] = self.fetch_parameter('max_features',
                                                          str,
                                                          True)
        parameters['n_estimators'] = self.fetch_parameter('n_estimators', int,
                                                          True)

        return parameters
