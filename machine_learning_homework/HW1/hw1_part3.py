import numpy as np
import pandas as pd
from sklearn.metrics import mean_squared_error
from sklearn.linear_model import ElasticNetCV, ElasticNet
from sklearn.metrics import r2_score
from sklearn.preprocessing import StandardScaler
import matplotlib.pyplot as plt
from sklearn.linear_model import Ridge, RidgeCV
from hw1_part2 import seperate_data
from sklearn.linear_model import LassoCV, Lasso
from sklearn.preprocessing import PolynomialFeatures
from sklearn.linear_model import LinearRegression


df = pd.read_csv("HW1_cleaned_house_data.csv")


def evaluate_model(Y_train, Y_test, y_train_pred, y_test_pred):  # function 3-1
    print(
        "MSE(training): %.3f, MSE(testing): %.3f"
        % (
            mean_squared_error(Y_train, y_train_pred),
            mean_squared_error(Y_test, y_test_pred),
        )
    )
    print(
        "R^2(training): %.3f, R^2(testing): %.3f"
        % (r2_score(Y_train, y_train_pred), r2_score(Y_test, y_test_pred))
    )


def polynomial_regression(df, degree):  # function 3-2
    X_train, X_test, Y_train, Y_test = seperate_data(df)
    poly = PolynomialFeatures(degree)

    X_train_poly = poly.fit_transform(X_train)
    X_test_poly = poly.transform(X_test)

    model = LinearRegression()
    model.fit(X_train_poly, Y_train)

    y_train_pred = model.predict(X_train_poly)
    y_test_pred = model.predict(X_test_poly)

    print(f"polynomial.coef_ = {model.coef_}")
    print(f"polynomial.intercept_ = {model.intercept_}")

    return model, y_train_pred, y_test_pred


# modle, y_train_pred, y_test_pred = polynomial_regression(df, 3)
# evaluate_model(Y_train, Y_test, y_train_pred, y_test_pred)


def ridge_regression(X_train, X_test, Y_train, Y_test):  # function 3-3
    scaler = StandardScaler()
    X_train = scaler.fit_transform(X_train)
    Y_train = scaler.fit_transform(Y_train.values.reshape(-1, 1)).flatten()
    X_test = scaler.fit_transform(X_test)
    Y_test = scaler.fit_transform(Y_test.values.reshape(-1, 1)).flatten()

    # 找 alphas
    alphas = np.logspace(-3, 3, 50)
    reg_cv = RidgeCV(alphas, store_cv_values=True)
    reg_cv.fit(X_train, Y_train)

    print("Best alpha: %.3f" % reg_cv.alpha_)
    scores = reg_cv.cv_values_[0]
    scores_std = np.std(reg_cv.cv_values_, axis=0)[0]

    plt.semilogx(alphas, scores, color="red")

    std_error = scores_std / np.sqrt(len(np.mean(reg_cv.cv_values_, axis=0)))

    plt.semilogx(alphas, scores + std_error, "b--")
    plt.semilogx(alphas, scores - std_error, "b--")
    plt.fill_between(alphas, scores + std_error, scores - std_error, alpha=0.2)
    plt.ylabel("CV MSE +/- std error")
    plt.xlabel(r"$\alpha$")
    plt.xlim([alphas[0], alphas[-1]])
    plt.show()
    ridgeModel = Ridge(alpha=reg_cv.alpha_)
    Y_RidgePred = ridgeModel.fit(X_train, Y_train).predict(X_test)
    Y_RidgeTrainPred = ridgeModel.predict(X_train)

    evaluate_model(Y_train, Y_test, Y_RidgeTrainPred, Y_RidgePred)


def lasso_regression(X_train, X_test, Y_train, Y_test):  # function 3-4
    scaler = StandardScaler()
    X_train = scaler.fit_transform(X_train)
    Y_train = scaler.fit_transform(Y_train.values.reshape(-1, 1)).flatten()
    X_test = scaler.fit_transform(X_test)
    Y_test = scaler.fit_transform(Y_test.values.reshape(-1, 1)).flatten()

    alphas = np.logspace(-5, 3, 50)
    regLasso = LassoCV(alphas=alphas, cv=10, n_jobs=-1)
    reg_y = Y_train
    regLasso.fit(X_train, reg_y.reshape(-1))

    scores = np.mean(regLasso.mse_path_, axis=1)
    scores_std = np.std(regLasso.mse_path_, axis=1)

    plt.figure(figsize=(10, 8))
    plt.semilogx(alphas, scores, color="purple")
    std_error = scores_std / np.sqrt(len(scores))
    plt.semilogx(alphas, scores + std_error, "b--")
    plt.semilogx(alphas, scores - std_error, "b--")
    plt.title("Lasso Regression", fontsize=20, fontweight="bold")
    plt.fill_between(alphas, scores + std_error, scores - std_error, alpha=0.2)
    plt.show()
    lassoModel = Lasso(alpha=regLasso.alpha_, fit_intercept=False)
    Y_LassoPred = lassoModel.fit(X_train, Y_train).predict(X_test)
    Y_LassoTrainPred = lassoModel.predict(X_train)
    print("Best alpha: %.3f" % regLasso.alpha_)
    evaluate_model(Y_train, Y_test, Y_LassoTrainPred, Y_LassoPred)


def elastic_net(X_train, X_test, Y_train, Y_test):  # function 3-5
    scaler = StandardScaler()
    rho = [0.1, 0.5, 0.7, 0.9, 0.95, 0.99, 1]
    reg_cv = ElasticNetCV(cv=10, l1_ratio=rho)
    # reg_y = scalar.fit_transform(Y_train.loc[:, ["price"]])
    # X_train = scaler.fit_transform(X_train)
    Y_train = scaler.fit_transform(Y_train.values.reshape(-1, 1)).flatten()
    # X_test = scaler.fit_transform(X_test)
    Y_test = scaler.fit_transform(Y_test.values.reshape(-1, 1)).flatten()

    reg_cv.fit(X_train, Y_train.reshape(-1))

    df_coef = pd.DataFrame(data=reg_cv.coef_.reshape(1, -1), columns=X_train.columns[:])
    coef = np.array(df_coef)[0]
    coef_abs = np.apply_along_axis(abs, 0, coef)
    idx = np.argsort(-coef_abs)

    plt.bar(range(len(coef)), coef[idx])
    plt.xticks(range(len(coef)), df_coef.columns[idx], rotation=60)
    plt.ylabel("weights")
    plt.show()
    elasticModel = Lasso(alpha=reg_cv.alpha_)
    Y_ElasticPred = elasticModel.fit(X_train, Y_train).predict(X_test)
    Y_ElasticTrainPred = elasticModel.predict(X_train)
    evaluate_model(Y_train, Y_test, Y_ElasticTrainPred, Y_ElasticPred)


# X_train, X_test, Y_train, Y_test = seperate_data(df)
# elastic_net(X_train, X_test, Y_train, Y_test)
