"""Wrap the sklearn.linear_model ridge classification model."""

from model_base import ClassificationModelBase
from sklearn.linear_model import RidgeClassifier


class RidgeClassifierModel(ClassificationModelBase):
    def __init__(self, model_conf):
        model = RidgeClassifier()
        super().__init__(model_conf, model)

    def get_params(self):
        parameters = {}
        parameters['alpha'] = self.fetch_parameter('alpha', float, True)
        parameters['tol'] = self.fetch_parameter('tol', float, True)
        parameters['solver'] = self.fetch_parameter('solver', str, True)
        parameters['max_iter'] = self.fetch_parameter('max_iter', int, True)

        return parameters
