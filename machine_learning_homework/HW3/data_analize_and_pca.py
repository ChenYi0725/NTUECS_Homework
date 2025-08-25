import pandas as pd
from sklearn.decomposition import PCA
import matplotlib.pyplot as plt
import seaborn as sns

df = pd.read_csv("random_3000_credit_card_data.csv")


def descriptive_statistics(df):  # function 2-1
    numeric_df = df.select_dtypes(include=["int", "float"]).columns
    numeric_df = df.describe()
    numeric_df.to_csv("descriptive_statistics.csv", index=False)


# descriptive_statistics(df)

df = pd.read_csv("standardized_credit_card_data.csv")


def generate_correlation_coefficient(df):  # function 2-2-1
    X = df.loc[:, :]
    corr_matrix_person = X.corr()
    corr_matrix_person["source"] = "person"
    merged_df = pd.concat([corr_matrix_person], axis=0)
    merged_df.to_csv("correlation_coefficient.csv", index=False)


def plot_heatmap():  # function 2-2-2
    merged_df = pd.read_csv("correlation_coefficient.csv")
    numerical_corr = merged_df.drop(columns=["source"])
    plt.figure(figsize=(8, 6))
    sns.heatmap(numerical_corr, annot=True, cmap="coolwarm", fmt=".2f")
    plt.title("Heatmap")
    plt.xlabel("")
    plt.ylabel("")
    plt.show()


# generate_correlation_coefficient(df)
# plot_heatmap()


def draw_explained_variance(df):  # function 2-3-1
    pca = PCA()
    pca.fit_transform(df)
    explained_variance_ratio = pca.explained_variance_ratio_
    plt.figure(figsize=(10, 6))
    plt.plot(
        range(1, len(explained_variance_ratio) + 1),
        explained_variance_ratio,
        marker="o",
    )
    plt.xlabel("Principal Component")
    plt.ylabel("Explained Variance Ratio")
    plt.title("Explained Variance Ratio by Principal Component")
    plt.grid(True)
    plt.show()


def draw_cumulative_explained_variance(df):  # function 2-3-2
    pca = PCA()
    pca.fit_transform(df)
    explained_variance_ratio = pca.explained_variance_ratio_
    cumulative_explained_variance = explained_variance_ratio.cumsum()
    plt.figure(figsize=(10, 6))
    plt.plot(
        range(1, len(cumulative_explained_variance) + 1),
        cumulative_explained_variance,
        marker="o",
    )
    plt.xlabel("Number of Principal Components")
    plt.ylabel("Cumulative Explained Variance")
    plt.title("Cumulative Explained Variance by Principal Component")
    plt.grid(True)
    plt.show()


draw_explained_variance(df)
draw_cumulative_explained_variance(df)


def apply_pca(df):  # function 2-3-1
    pca = PCA()
    pca.fit_transform(df)
    explained_variance_ratio = pca.explained_variance_ratio_
    cumulative_explained_variance = explained_variance_ratio.cumsum()
    num_components = (
        next(
            i
            for i, total_var in enumerate(cumulative_explained_variance)
            if total_var >= 0.90
        )
        + 1
    )
    print(f"{num_components}")
    pca = PCA(n_components=num_components)  # 進行PCA，保留選定的主成分數量
    X_reduced = pca.fit_transform(df)
    pca_columns = [f"PC{i+1}" for i in range(num_components)]
    pca_df = pd.DataFrame(data=X_reduced, columns=pca_columns)
    pca_df.to_csv("pca_data.csv", index=False)


def apply_2pc(df):
    pca = PCA(n_components=2)  # 進行PCA，保留選定的主成分數量
    X_reduced = pca.fit_transform(df)
    pca_columns = [f"PC{i+1}" for i in range(2)]
    pca_df = pd.DataFrame(data=X_reduced, columns=pca_columns)
    pca_df.to_csv("pca_data_2PC.csv", index=False)


apply_pca(df)
apply_2pc(df)

# apply_pca(df)
