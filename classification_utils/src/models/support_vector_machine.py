"""Wrap the sklearn.svm Suppport Vector Machine model."""

from model_base import ClassificationModelBase
from sklearn.svm import SVC


class SupportVectorMachineModel(ClassificationModelBase):
    def __init__(self, model_conf):
        model = SVC()
        super().__init__(model_conf, model)

    def get_params(self):
        parameters = {}
        parameters['C'] = self.fetch_parameter('C', float, True)
        parameters['kernel'] = self.fetch_parameter('kernel', str, True)
        parameters['degree'] = self.fetch_parameter('degree', int, True)
        parameters['gamma'] = self.fetch_parameter('gamma', str, True)
        parameters['coef0'] = self.fetch_parameter('coef0', float, True)
        parameters['shrinking'] = self.fetch_parameter('shrinking', bool, True)
        parameters['probability'] = self.fetch_parameter('probability', bool,
                                                         True)
        parameters['max_iter'] = self.fetch_parameter('max_iter', int, True)
        parameters['break_ties'] = self.fetch_parameter('break_ties', bool,
                                                        True)

        return parameters
