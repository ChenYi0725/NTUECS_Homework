import random
import pandas as pd
from sklearn.preprocessing import StandardScaler
from sklearn.decomposition import PCA

df = pd.read_csv("HW3_Credit Card Dataset.csv")


def find_missing_value(df):  # function 1-1-1
    df.info()


def delet_missing_value(df):  # function 1-1-2
    new_df = df.dropna()
    return new_df


df = delet_missing_value(df)


def select_3000_random_data_and_save(df):  # function 1-1-3
    df_3000 = df.sample(n=3000)
    df_3000.to_csv("random_3000_credit_card_data.csv", index=False)


# select_3000_random_data_and_save(df)
df = pd.read_csv("random_3000_credit_card_data.csv")


def standardized_dataframe(df):  # function 1-2
    cust_id = df["CUST_ID"]
    scaler = StandardScaler()
    standardized_df = pd.DataFrame(
        scaler.fit_transform(df.iloc[:, 1:]), columns=df.columns[1:]
    )
    # df_final = pd.concat([cust_id, standardized_df], axis=1)
    standardized_df.to_csv("standardized_credit_card_data.csv", index=False)


# standardized_dataframe(df)
df = pd.read_csv("standardized_credit_card_data.csv")









