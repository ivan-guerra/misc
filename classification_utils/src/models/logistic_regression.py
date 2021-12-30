"""Wrap the sklearn.linear_model logistic regression model."""

from model_base import ClassificationModelBase
from sklearn.linear_model import LogisticRegression


class LogisticRegressionModel(ClassificationModelBase):
    def __init__(self, model_conf):
        model = LogisticRegression(random_state=0,
                                   class_weight='balanced',
                                   solver='liblinear')
        super().__init__(model_conf, model)

    def get_params(self):
        parameters = {}
        parameters['penalty'] = self.fetch_parameter('penalty', str, True)
        parameters['C'] = self.fetch_parameter('C', float, True)
        parameters['tol'] = self.fetch_parameter('tol', float, True)
        parameters['solver'] = self.fetch_parameter('solver', str, True)
        parameters['max_iter'] = self.fetch_parameter('max_iter', int, True)

        return parameters
