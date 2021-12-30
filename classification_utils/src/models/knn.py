"""Wrap the sklearn.neighbors K Nearest Neighbors model."""

from model_base import ClassificationModelBase
from sklearn.neighbors import KNeighborsClassifier


class KNNModel(ClassificationModelBase):
    def __init__(self, model_conf):
        model = KNeighborsClassifier()
        super().__init__(model_conf, model)

    def get_params(self):
        parameters = {}
        parameters['n_neighbors'] = self.fetch_parameter('n_neighbors', int,
                                                         True)
        parameters['metric'] = self.fetch_parameter('metric', str, True)
        parameters['weights'] = self.fetch_parameter('weights', str, True)
        parameters['algorithm'] = self.fetch_parameter('algorithm', str, True)
        parameters['p'] = self.fetch_parameter('p', int, True)

        return parameters
