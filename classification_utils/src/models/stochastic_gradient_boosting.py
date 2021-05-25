"""Wrap the sklearn.ensemble Gradient Boosting Classifier."""

from model_base import ClassificationModelBase
from sklearn.ensemble import GradientBoostingClassifier


class StochasticGradientBoostingModel(ClassificationModelBase):
    def __init__(self, model_conf):
        model = GradientBoostingClassifier()
        super().__init__(model_conf, model)

    def get_params(self):
        parameters = {}
        parameters['learning_rate'] = self.fetch_parameter('learning_rate',
                                                           float,
                                                           True)
        parameters['n_estimators'] = self.fetch_parameter('n_estimators', int,
                                                          True)
        parameters['subsample'] = self.fetch_parameter('subsample', float,
                                                       True)
        parameters['max_depth'] = self.fetch_parameter('max_depth', int, True)

        return parameters
