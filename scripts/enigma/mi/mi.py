#!/usr/bin/python3
import pandas as pd
import numpy as np
import sklearn.feature_selection
from scipy.stats import entropy
from statistics import mean

if __name__ == "__main__":
   dfc = pd.read_csv('./sybil.log', index_col=False, header=None)
   # dfc = pd.read_csv('./actual.log', index_col=False, header=None)
   dfv = pd.read_csv('./actual.log', index_col=False, header=None)
   dfcd = pd.read_csv('./padding.log', index_col=False, header=None)

   # dfc = pd.read_csv('./fiocompact_lat.1.log', index_col=False, header=None)
   # dfv = pd.read_csv('./fiovanilla_lat.1.log', index_col=False, header=None)
   # dfcd = pd.read_csv('./fiocompactdelay_lat.1.log', index_col=False, header=None)

   # print("mean of actual: ", mean(dfv.iloc[:, 1]))
   # print("mean of sybil: ", mean(dfc.iloc[:, 1]))
   # print("mean of padded: ", mean(dfcd.iloc[:, 1]))
   # entropy = entropy(dfv.iloc[:, 1], base=2)
   # print("entropy of actual = ", entropy)
   feature1 = np.append(dfv.iloc[:, 1], dfc.iloc[:, 1])
   feature1 = feature1.reshape(-1, 1)
   target1 = np.append(np.full((len(dfv),), 'V'), np.full((len(dfc)), 'C'))
   mi1 = sklearn.feature_selection.mutual_info_classif(feature1, target1, discrete_features=False, n_neighbors=50)
   # print('Mutual Information of timing and type (vanilla or compact):', mi1, '(natural log),', 'or',
         # mi1 * (1 / np.log(2)), '(log 2)')
   feature2 = np.append(dfv.iloc[:, 1], dfcd.iloc[:, 1])
   feature2 = feature2.reshape(-1, 1)
   target2 = np.append(np.full((len(dfv),), 'V'), np.full((len(dfcd)), 'D'))
   mi2 = sklearn.feature_selection.mutual_info_classif(feature2, target2, discrete_features=False, n_neighbors=50)
   # print('Mutual Information of timing and type (vanilla or compact-delayed):', mi2, '(natural log),', 'or',
         # mi2 * (1 / np.log(2)), '(log 2)')
   print(mi2[0] * (1 / np.log(2)))


