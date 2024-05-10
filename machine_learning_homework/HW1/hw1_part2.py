import numpy as np
import pandas as pd
from random import choice as randChoice
from sklearn.linear_model import LinearRegression
from sklearn.model_selection import train_test_split
import statsmodels.api as sm
import matplotlib.pyplot as plt
from sklearn.metrics import mean_squared_error
from sklearn.metrics import mean_absolute_error
from sklearn.metrics import r2_score
from sklearn.preprocessing import StandardScaler
import seaborn as sns

df = pd.read_csv("HW1_cleaned_house_data.csv")


# 資料分割
def seperate_data(df):  # function 2-1
    X, y = df.loc[:, "bedrooms":"sqft_lot15"], df["price"]

    X_train, X_test, Y_train, Y_test = train_test_split(
        X, y, train_size=0.8, test_size=0.2, random_state=10
    )
    # print(X_train.shape[0])
    # print(X_test.shape[0])
    # print(Y_train.shape[0])
    # print(Y_test.shape[0])
    return X_train, X_test, Y_train, Y_test


def build_linear_regression_model(df):  # function 2-2
    X_train, X_test, Y_train, Y_test = seperate_data(df)
    lr = LinearRegression()
    lr.fit(X_train, Y_train)
    Y_pred_train = lr.predict(X_train)
    resid_train = Y_train - Y_pred_train
    print(f"linearModel.coef_ = {lr.coef_}")
    print(f"linearModel.intercept_ = {lr.intercept_}")
    return lr


# build_linear_regression_model(df)  # function 2-2


def evaluate_model(df):  # function 2-3
    X_train, X_test, Y_train, Y_test = seperate_data(df)
    lr = LinearRegression()
    lr.fit(X_train, Y_train)
    y_train_pred = lr.predict(X_train)
    y_test_pred = lr.predict(X_test)
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


# evaluate_model(df)  # function 2-3


def draw_qq_plot(df):  # function 2-4
    X_train, X_test, Y_train, Y_test = seperate_data(df)
    lr = LinearRegression()
    lr.fit(X_train, Y_train)
    resid = Y_train - lr.predict(X_train)
    plt.figure(figsize=(15, 10), dpi=40)
    sm.qqplot(resid, line="r")
    plt.title("QQ plot", fontsize=20, fontweight="bold")
    plt.show()


# def draw_residual_plot(df):
#     X_train, X_test, Y_train, Y_test = seperate_data(df)
#     model = LinearRegression()
#     model.fit(X_train, Y_train)
#     df_resid = pd.DataFrame()
#     df_resid["y_pred"] = model.predict(X_train)
#     df_resid["resid"] = model.resid
#     df_resid = StandardScaler().fit_transform(df_resid)

#     kws = {"color": "red", "lw": 3}
#     sns.residplot(x=df_resid[:, 0], y=df_resid[:, 1], lowess=True, line_kws=kws)
#     plt.xlabel("Predicted Values (standardization)", fontsize=14)
#     plt.ylabel("Residual (standardization)", fontsize=14)


# draw_residual_plot(df)
# draw_qq_plot(df)
