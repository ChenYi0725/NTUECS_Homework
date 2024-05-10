import numpy as np
import pandas as pd
from sklearn.ensemble import IsolationForest
import matplotlib.pyplot as plt
import seaborn as sns
from random import choice as randChoice
from statsmodels.graphics.gofplots import qqplot


# 1.	資料清理與視覺化圖表 ======================================
df = pd.read_csv("HW1_house_data.csv")


def find_missing_value(df):  # function 1
    df.info()


def outlier_dection(df):  # function 2
    X = df.loc[:, "price":"sqft_lot15"]
    clf = IsolationForest(max_samples=df.shape[0], contamination=0.01)
    clf.fit(X)
    y_pred_train = clf.predict(X)
    outlier_indices = np.where(y_pred_train == -1)[0]
    print(f"abnormal indices number:{len(outlier_indices)}")
    print(outlier_indices)
    return outlier_indices


def clean_outlier_and_save(df, outlier_indices):  # function 3
    cleaned_df = df.drop(outlier_indices)
    cleaned_df.to_csv("HW1_cleaned_house_data.csv", index=False)


# find_missing_value(df)        #function 1
# outlier_dection(df)           #function 2
# df = clean_outlier_and_save(df, outlier_dection(df))  # function 3

df = pd.read_csv("HW1_cleaned_house_data.csv")  # load new data


def draw_plot(df):  # function 4
    price = df["price"]

    plt.scatter(price, df["date"], label="date")
    plt.ylabel("date")
    plt.xlabel("Price")
    plt.title(f"Price vs date")
    plt.legend()
    plt.gca().yaxis.set_major_locator(plt.MaxNLocator(10))  # 設置 x 軸主要刻度為 5 個
    plt.tight_layout()
    plt.show()

    features = df.drop(["price", "id", "date"], axis=1)
    for feature in features.columns:
        plt.scatter(price, features[feature], label=feature)
        plt.ylabel(str(feature))
        plt.xlabel("Price")
        plt.title(f"Price vs {feature}")
        plt.legend()
        plt.show()


# draw_plot(df)     # function 4

# 2.	敘述性統計分析 =======================================


def descriptive_statistics(df):  # function 5
    df = df.drop(["id"], axis=1)
    df = df.describe()
    df.to_csv("HW1_data_descriptive_statistics.csv", index=False)


def draw_box_plot(df):  # function 6
    df = df.drop(["id"], axis=1)
    data_property_numerical_value = df.select_dtypes(include=["float64", "int"])
    countSubplot = 1
    plt.figure(figsize=(40, 14), dpi=40)

    for title in data_property_numerical_value:
        plt.subplot(3, 7, countSubplot)
        hexColor = ["#" + "".join([randChoice("ABCDEF0123456789") for i in range(6)])]
        sns.boxplot(
            data=df[[title]],
            orient="v",
            palette=hexColor,
            whis=1.5,
            saturation=1,
            width=0.2,
        )
        countSubplot += 1

    plt.suptitle("Property Box Plot", fontsize=40, fontweight="bold")
    plt.show()


# descriptive_statistics(df)        # function 5
# draw_box_plot(df)         # function 6

# 3.	特徵相關性分析 ===============================


def generate_correlation_coefficient(df):  # function 7
    X = df.loc[:, "price":"sqft_lot15"]
    corr_matrix_person = X.corr()
    corr_matrix_spearman = X.corr(method="spearman")
    corr_matrix_kendall = X.corr(method="kendall")
    corr_matrix_person["source"] = "person"
    corr_matrix_spearman["source"] = "spearman"
    corr_matrix_kendall["source"] = "kendall"
    merged_df = pd.concat(
        [corr_matrix_person, corr_matrix_spearman, corr_matrix_kendall], axis=0
    )
    merged_df.to_csv("HW1_correlation_coefficient2.csv", index=False)


def draw_heatmap():  # function 8
    merged_df = pd.read_csv("HW1_correlation_coefficient.csv")
    numerical_corr = merged_df.drop(columns=["source"])
    plt.figure(figsize=(10, 8))
    sns.heatmap(numerical_corr, annot=True, cmap="coolwarm", fmt=".2f")
    plt.title("Correlation Heatmap")
    plt.show()


def corr_price(df):  # function 9
    X = df.loc[:, "bedrooms":"sqft_lot15"]
    y = df["price"]

    corr_price_person = X.corrwith(y)
    abs_corr_with_price = corr_price_person.abs()  # 取相關係數的絕對值
    corr_price_person = corr_price_person.iloc[abs_corr_with_price.argsort()[::-1]]
    print("Person:")
    print(corr_price_person)

    corr_price_spearman = X.corrwith(y, method="spearman")
    abs_corr_price_spearman = corr_price_spearman.abs()
    corr_price_spearman = corr_price_spearman.iloc[
        abs_corr_price_spearman.argsort()[::-1]
    ]
    print("Spearman:")
    print(corr_price_spearman)

    corr_price_kendall = X.corrwith(y, method="kendall")
    abs_corr_price_kendall = corr_price_kendall.abs()
    corr_price_kendall = corr_price_kendall.iloc[abs_corr_price_kendall.argsort()[::-1]]
    print("Kendall:")
    print(corr_price_kendall)


# generate_correlation_coefficient(df)  # function 7
# draw_heatmap()    #function 8
# corr_price(df)  # function 9
