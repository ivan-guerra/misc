"""Define a classification model object factory.

ClassificationModelFactory is a classification model object factory that
can be used to spawn any model supported by this application (see, src/models/
to find out what models are supported or check
config/ClassificationModelConfig.ini for details).
"""

from models.logistic_regression import LogisticRegressionModel
from models.ridge_classifier import RidgeClassifierModel
from models.knn import KNNModel
from models.support_vector_machine import SupportVectorMachineModel
from models.bagged_decision_trees import BaggedDecisionTreesModel
from models.random_forest import RandomForestModel
from models.stochastic_gradient_boosting import StochasticGradientBoostingModel


class ClassificationModelFactory:
    """Classification model object factory.

    For details regarding what models have been implemented, see
    config/ClassificationModelConfig.ini.
    """

    def __init__(self):
        self.LOGISTIC_REGRESSION = 'LogisticRegression'
        self.RIDGE_CLASSIFIER = 'RidgeClassifier'
        self.KNN = 'KNN'
        self.SUPPORT_VECTOR_MACHINE = 'SupportVectorMachine'
        self.BAGGED_DECISION_TREES = 'BaggedDecisionTrees'
        self.RANDOM_FOREST = 'RandomForest'
        self.SGB = 'StochasticGradientBoosting'

    def get_model(self, model_name, model_conf):
        """Return the model object  associated with model_name."""

        if model_name == self.LOGISTIC_REGRESSION:
            return LogisticRegressionModel(model_conf)
        elif model_name == self.RIDGE_CLASSIFIER:
            return RidgeClassifierModel(model_conf)
        elif model_name == self.KNN:
            return KNNModel(model_conf)
        elif model_name == self.SUPPORT_VECTOR_MACHINE:
            return SupportVectorMachineModel(model_conf)
        elif model_name == self.BAGGED_DECISION_TREES:
            return BaggedDecisionTreesModel(model_conf)
        elif model_name == self.RANDOM_FOREST:
            return RandomForestModel(model_conf)
        elif model_name == self.SGB:
            return StochasticGradientBoostingModel(model_conf)
        else:
            raise ValueError(model_name)
