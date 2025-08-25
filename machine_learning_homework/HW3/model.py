import pandas as pd
from sklearn.metrics import silhouette_samples, silhouette_score
from sklearn.decomposition import PCA
from sklearn.cluster import KMeans
import matplotlib.pylab as plt
import numpy as np
from sklearn.cluster import AgglomerativeClustering
from sklearn.metrics import silhouette_score, adjusted_rand_score
import scipy.cluster.hierarchy as sch
from sklearn.cluster import DBSCAN
from sklearn.metrics import adjusted_rand_score


# df = pd.read_csv("pca_data.csv")
df2 = pd.read_csv("pca_data_2PC.csv")
pca = PCA(n_components=2)
df_pca = pca.fit_transform(df2)


def draw_inertia(df):  # function 3-1-1
    sse = []
    k_values = range(2, 11)
    for k in k_values:
        kmeans = KMeans(n_clusters=k, random_state=42)
        kmeans.fit(df)
        sse.append(kmeans.inertia_)

    plt.figure(figsize=(10, 6))
    plt.plot(k_values, sse, marker="o")
    plt.xlabel("Number of clusters")
    plt.ylabel("SSE")
    plt.title("inerti")
    plt.show()


def draw_silhouette_score(df):  # function 3-1-2
    silhouette_scores = []
    k_values = range(2, 11)

    for k in k_values:
        kmeans = KMeans(n_clusters=k, random_state=42)
        cluster_labels = kmeans.fit_predict(df)

        silhouette_avg = silhouette_score(df, cluster_labels)
        silhouette_scores.append(silhouette_avg)

    # 繪圖
    plt.figure(figsize=(10, 6))
    plt.plot(k_values, silhouette_scores, marker="o")
    plt.xlabel("Number of clusters")
    plt.ylabel("Silhouette Score")
    plt.title("Silhouette_score")
    plt.show()


def kmean_scatter(df, num_clusters):  # 3-1-3
    kmeans = KMeans(n_clusters=num_clusters, random_state=42)
    cluster_labels = kmeans.fit_predict(df_pca)

    # 計算輪廓係數
    silhouette_avg = silhouette_score(df_pca, cluster_labels)
    print(f"Highest average silhouette score: {silhouette_avg:.2f}")

    # 計算每個分群的數量
    cluster_counts = np.bincount(cluster_labels)

    # 定義顏色列表，可以根據需要修改
    colors = ["red", "blue", "green"]

    # 繪圖
    plt.figure(figsize=(8, 6))
    scatter = plt.scatter(
        df_pca[:, 0],
        df_pca[:, 1],
        c=[colors[label] for label in cluster_labels],
        edgecolors="none",
    )
    plt.title(f"Scatter Plot after PCA and KMeans Clustering")
    plt.xlabel("PC1")
    plt.ylabel("PC2")

    legend_elements = [
        plt.Line2D(
            [0],
            [0],
            marker="o",
            color="w",
            label=f"Cluster {i}",
            markerfacecolor=colors[i],
            markersize=10,
        )
        for i in range(num_clusters)
    ]
    plt.legend(handles=legend_elements)

    plt.show()

    # 繪製長條圖
    plt.figure(figsize=(8, 6))
    plt.bar(
        np.arange(num_clusters),
        cluster_counts,
        align="center",
        color=colors[:num_clusters],
    )
    plt.xlabel("Cluster")
    plt.ylabel("Number of samples")
    plt.title("Cluster Sizes")
    plt.show()
    find_ARI(find_and_define_label(), cluster_labels)


def draw_silhouette(df, k):  # function 3-1-4
    silhouette_scores = []
    kmeans = KMeans(n_clusters=k, random_state=42)
    cluster_labels = kmeans.fit_predict(df)

    silhouette_avg = silhouette_score(df, cluster_labels)
    silhouette_scores.append(silhouette_avg)
    sample_silhouette_values = silhouette_samples(df, cluster_labels)
    fig, ax = plt.subplots()
    fig.set_size_inches(10, 6)
    y_lower = 10
    for i in range(k):
        # 收集每個集群中的輪廓分數
        ith_cluster_silhouette_values = sample_silhouette_values[cluster_labels == i]

        ith_cluster_silhouette_values.sort()

        size_cluster_i = ith_cluster_silhouette_values.shape[0]
        y_upper = y_lower + size_cluster_i

        color = plt.cm.get_cmap("Spectral")(float(i) / k)
        ax.fill_betweenx(
            np.arange(y_lower, y_upper),
            0,
            ith_cluster_silhouette_values,
            facecolor=color,
            edgecolor=color,
            alpha=0.7,
        )

        ax.text(-0.05, y_lower + 0.5 * size_cluster_i, str(i))

        y_lower = y_upper + 10

    ax.set_title("Silhouette plot for {} clusters".format(k))
    ax.set_xlabel("Silhouette coefficient values")
    ax.set_ylabel("Cluster label")
    ax.axvline(x=silhouette_avg, color="red", linestyle="--")
    ax.set_yticks([])
    ax.set_xticks([-0.1, 0, 0.2, 0.4, 0.6, 0.8, 1])
    plt.show()


def hierarchical_clustering(df, k): #function 3-2
    cluster = AgglomerativeClustering(n_clusters=k, linkage="ward")
    cluster_labels = cluster.fit_predict(df)

    # 集群大小
    unique_labels, counts = np.unique(cluster_labels, return_counts=True)
    cluster_sizes = dict(zip(unique_labels, counts))
    colors = ["red", "blue", "green"]
    # 繪製散佈圖
    plt.figure(figsize=(10, 6))
    scatter = plt.scatter(
        df_pca[:, 0],
        df_pca[:, 1],
        c=[colors[label] for label in cluster_labels],
        edgecolors="none",
    )
    legend_elements = [
        plt.Line2D(
            [0],
            [0],
            marker="o",
            color="w",
            label=f"Cluster {i}",
            markerfacecolor=colors[i],
            markersize=10,
        )
        for i in range(k)
    ]
    plt.legend(handles=legend_elements)
    plt.title("Scatter Plot of Hierarchical Clustering")
    plt.xlabel("PC1")
    plt.ylabel("PC2")
    plt.show()

    # 長條圖
    plt.figure(figsize=(8, 5))
    plt.bar(
        cluster_sizes.keys(),
        cluster_sizes.values(),
        color=colors[:k],
    )
    plt.title("Cluster Sizes")
    plt.xlabel("Cluster")
    plt.ylabel("Number of Samples")
    plt.xticks(list(cluster_sizes.keys()))
    plt.show()

    # 樹狀圖
    plt.figure(figsize=(14, 7))
    dendrogram = sch.dendrogram(sch.linkage(df, method="ward"))
    plt.title("Dendrogram")
    plt.xlabel("Samples")
    plt.ylabel("Distance")
    plt.show()

    # 輪廓係數
    silhouette_avg = silhouette_score(df, cluster_labels)
    print(f"Silhouette score: {silhouette_avg:.2f}")
    find_ARI(find_and_define_label(), cluster_labels)


def dbscan_clustering(df, eps, min_samples):    #function 3-3
    dbscan = DBSCAN(eps=eps, min_samples=min_samples)
    cluster_labels = dbscan.fit_predict(df)

    # 檢查並過濾離群值
    if np.sum(cluster_labels == -1) > 0:
        print(f"Number of outliers: {np.sum(cluster_labels == -1)}")

    # 計算集群數量（不包括離群值）
    num_clusters = len(set(cluster_labels)) - (1 if -1 in cluster_labels else 0)
    print(f"Number of clusters: {num_clusters}")

    if num_clusters > 0:
        silhouette_avg = silhouette_score(df, cluster_labels)
        print(f"Silhouette score: {silhouette_avg:.2f}")

        # 散佈圖
        plt.figure(figsize=(10, 6))
        scatter = plt.scatter(
            df[:, 0], df[:, 1], c=cluster_labels, cmap="viridis", edgecolors="none"
        )
        plt.title("Scatter Plot of DBSCAN Clustering")
        plt.xlabel("PC1")
        plt.ylabel("PC2")
        plt.colorbar(scatter, label="Cluster")
        plt.show()

        # 繪製各群數量的長條圖
        unique_labels, counts = np.unique(cluster_labels, return_counts=True)
        plt.figure(figsize=(10, 6))
        colors = [
            plt.cm.viridis(label / num_clusters) if label != -1 else "k"
            for label in unique_labels
        ]
        plt.bar(unique_labels, counts, color=colors)
        plt.title("Cluster Sizes")
        plt.xlabel("Cluster Label")
        plt.ylabel("Number of Points")
        plt.xticks(unique_labels)
        plt.show()
        find_ARI(find_and_define_label(), cluster_labels)


def find_and_define_label():    #function 3-4-1
    df = pd.read_csv("random_3000_credit_card_data.csv")
    df_sorted = df.sort_values(by="BALANCE")
    count = len(df) // 3
    df_sorted["BALANCE_GROUP"] = np.repeat(
        ["1", "0", "-1"], [count, count, len(df) - 2 * count]
    )
    df_sorted = df_sorted.sort_index()
    return df_sorted["BALANCE_GROUP"].tolist()


def find_ARI(true_labels, cluster_labels):#function 3-4-2
    ari = adjusted_rand_score(true_labels, cluster_labels)
    print(f"Adjusted Rand Index: {ari:.2f}")


dbscan_clustering(df_pca, 0.36, 10)
hierarchical_clustering(df_pca, 3)
kmean_scatter(df_pca, 3)
