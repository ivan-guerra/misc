"""Wrap the sklearn.ensemble Bagging Classifier."""

from model_base import ClassificationModelBase
from sklearn.ensemble import BaggingClassifier


class BaggedDecisionTreesModel(ClassificationModelBase):
    def __init__(self, model_conf):
        model = BaggingClassifier()
        super().__init__(model_conf, model)

    def get_params(self):
        parameters = {}
        parameters['n_estimators'] = self.fetch_parameter('n_estimators', int,
                                                          True)
        parameters['max_features'] = self.fetch_parameter('max_features',
                                                          float,
                                                          True)
        parameters['bootstrap'] = self.fetch_parameter('bootstrap', bool, True)
        parameters['bootstrap_features'] = self.fetch_parameter(
                                            'bootstrap_features', bool, True)
        parameters['oob_score'] = self.fetch_parameter('oob_score', bool, True)

        return parameters
