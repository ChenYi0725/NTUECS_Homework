import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
from sklearn.model_selection import train_test_split
from sklearn.linear_model import LogisticRegression
from sklearn.svm import SVC
from sklearn.ensemble import RandomForestClassifier
from sklearn.neighbors import KNeighborsClassifier
from sklearn.metrics import (
    accuracy_score,
    precision_score,
    recall_score,
    f1_score,
    classification_report,
    confusion_matrix,
)

0

from sklearn.metrics import confusion_matrix
from sklearn.metrics import ConfusionMatrixDisplay
from sklearn.metrics import roc_curve, auc


df = pd.read_csv("HW2_modified_heart.csv")


def seperate_data(df):  # function 2-1
    y = df["HeartDisease"]
    X = df.drop(
        ["HeartDisease"],
        axis=1,
    )

    X_train, X_test, Y_train, Y_test = train_test_split(
        X, y, train_size=0.8, test_size=0.2, random_state=10
    )
    # print(X_test.shape)
    # print(X_train.shape)
    # print(Y_train.shape)
    # print(Y_test.shape)
    return X_train, X_test, Y_train, Y_test


X_train, X_test, Y_train, Y_test = seperate_data(df)


def model_evaluate(
    train_predict_y, test_predict_y, Y_train, Y_test, model
):  # function 2-2-1
    print(
        "訓練集準確率: ", round(accuracy_score(Y_train, train_predict_y) * 100, 2), " %"
    )
    print(
        "準確率(Accuracy): ",
        round(accuracy_score(Y_test, test_predict_y) * 100, 2),
        " %",
    )
    print(
        "精確率(Precision): ",
        round(precision_score(Y_test, test_predict_y) * 100, 2),
        " %",
    )
    print(
        "召回率(Recall): ", round(recall_score(Y_test, test_predict_y) * 100, 2), " %"
    )
    print("F1-Score: ", round(f1_score(Y_test, test_predict_y), 2))
    print("分類報告: \n", classification_report(Y_test, test_predict_y))
    plot_confusion_matrix(model, X_test, Y_test)


def plot_confusion_matrix(model, X_test, Y_test):  # function 2-2-2
    class_names = ["True", "False"]
    y_true = np.argmax(Y_test, axis=1) if len(Y_test.shape) > 1 else Y_test
    cm = confusion_matrix(y_true, model.predict(X_test))
    disp = ConfusionMatrixDisplay(confusion_matrix=cm, display_labels=class_names)
    fig, ax = plt.subplots()
    disp.plot(ax=ax, cmap=plt.cm.Blues)
    plt.show()


def logistic_regression_ovr(X_train, X_test, Y_train, Y_test):  # function 2-3-1
    OvR_model = LogisticRegression(multi_class="ovr")
    OvR_model.fit(X_train, Y_train)
    train_predict_y = OvR_model.predict(X_train)
    test_predict_y = OvR_model.predict(X_test)
    model_evaluate(train_predict_y, test_predict_y, Y_train, Y_test, OvR_model)


def logistic_regression_ovo(X_train, X_test, Y_train, Y_test):  # function 2-3-2
    OvO_model = LogisticRegression(multi_class="multinomial", solver="newton-cg")
    OvO_model.fit(X_train, Y_train)
    train_predict_y = OvO_model.predict(X_train)
    test_predict_y = OvO_model.predict(X_test)
    model_evaluate(train_predict_y, test_predict_y, Y_train, Y_test, OvO_model)


def SVM_ovr(X_train, X_test, Y_train, Y_test):  # function 2-4-1
    svm_model_ovr = SVC(kernel="linear", decision_function_shape="ovr")
    svm_model_ovr.fit(X_train, Y_train)
    train_predict_y = svm_model_ovr.predict(X_train)
    test_predict_y = svm_model_ovr.predict(X_test)
    model_evaluate(train_predict_y, test_predict_y, Y_train, Y_test, svm_model_ovr)


def SVM_ovo(X_train, X_test, Y_train, Y_test):  # function 2-4-2
    svm_model_ovo = SVC(kernel="linear", decision_function_shape="ovo")
    svm_model_ovo.fit(X_train, Y_train)
    train_predict_y = svm_model_ovo.predict(X_train)
    test_predict_y = svm_model_ovo.predict(X_test)
    model_evaluate(train_predict_y, test_predict_y, Y_train, Y_test, svm_model_ovo)


def SVM_ovr_rbf(X_train, X_test, Y_train, Y_test):  # function 2-5-1
    svm_model_ovo = SVC(kernel="rbf", decision_function_shape="ovr")
    svm_model_ovo.fit(X_train, Y_train)
    train_predict_y = svm_model_ovo.predict(X_train)
    test_predict_y = svm_model_ovo.predict(X_test)
    model_evaluate(train_predict_y, test_predict_y, Y_train, Y_test, svm_model_ovo)


def SVM_ovo_rbf(X_train, X_test, Y_train, Y_test):  # function 2-5-2
    svm_model_ovo = SVC(kernel="rbf", decision_function_shape="ovo")
    svm_model_ovo.fit(X_train, Y_train)
    train_predict_y = svm_model_ovo.predict(X_train)
    test_predict_y = svm_model_ovo.predict(X_test)
    model_evaluate(train_predict_y, test_predict_y, Y_train, Y_test, svm_model_ovo)


def random_forest_find_best_estimators(
    X_train, X_test, Y_train, Y_test
):  # function 2-6-1
    accuracy_list = []
    for i in range(1, 200):
        rf_model = RandomForestClassifier(n_estimators=i, random_state=10)
        rf_model.fit(X_train, Y_train)
        test_predict_y = rf_model.predict(X_test)
        accuracy_list.append(accuracy_score(Y_test, test_predict_y))

    max_i = accuracy_list.index(max(accuracy_list)) + 1
    print(f"best estimators:{max_i}")
    return max_i


def random_forest(X_train, X_test, Y_train, Y_test):  # function 2-6-2
    best_estimators = random_forest_find_best_estimators(
        X_train, X_test, Y_train, Y_test
    )
    rf_model = RandomForestClassifier(n_estimators=best_estimators, random_state=10)
    rf_model.fit(X_train, Y_train)
    train_predict_y = rf_model.predict(X_train)
    test_predict_y = rf_model.predict(X_test)
    model_evaluate(train_predict_y, test_predict_y, Y_train, Y_test, rf_model)


def knn_find_best_neighbors(X_train, X_test, Y_train, Y_test):  # function 2-7-1
    accuracy_list = []
    for i in range(1, 200, 2):
        knn_model = KNeighborsClassifier(n_neighbors=i)
        knn_model.fit(X_train, Y_train)
        test_predict_y = knn_model.predict(X_test)
        accuracy_list.append(accuracy_score(Y_test, test_predict_y))

    max_i = accuracy_list.index(max(accuracy_list)) + 1
    print(f"best neighbors:{max_i}")
    return max_i


def knn(X_train, X_test, Y_train, Y_test):  # function 2-7-2
    best_neighbors = knn_find_best_neighbors(X_train, X_test, Y_train, Y_test)
    knn_model = KNeighborsClassifier(n_neighbors=best_neighbors)
    knn_model.fit(X_train, Y_train)
    train_predict_y = knn_model.predict(X_train)
    test_predict_y = knn_model.predict(X_test)
    model_evaluate(train_predict_y, test_predict_y, Y_train, Y_test, knn_model)


# logistic_regression_ovr(X_train, X_test, Y_train, Y_test)
# logistic_regression_ovo(X_train, X_test, Y_train, Y_test)
# SVM_ovr(X_train, X_test, Y_train, Y_test)
# SVM_ovo(X_train, X_test, Y_train, Y_test)
# SVM_ovr_rbf(X_train, X_test, Y_train, Y_test)
# SVM_ovo_rbf(X_train, X_test, Y_train, Y_test)
# random_forest(X_train, X_test, Y_train, Y_test)
knn(X_train, X_test, Y_train, Y_test)
