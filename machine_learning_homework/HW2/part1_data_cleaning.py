import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

# 1.	資料清理與視覺化圖表 ======================================
df = pd.read_csv("HW2_heart.csv")
age_interval = [
    "25-30",
    "31-35",
    "36-40",
    "41-45",
    "46-50",
    "51-55",
    "56-60",
    "61-65",
    "66-70",
    "71-75",
    "76-80",
]


def find_missing_value(df):  # function 1-1
    df.info()


def find_outlier(x):  # function 1-2-1
    q1, q3 = np.percentile(x, [25, 75])
    IQR = q3 - q1
    lower_bound = q1 - 2 * IQR
    upper_bound = q3 + 2 * IQR
    return np.where((x < lower_bound) | (x > upper_bound))


def check_numeric_data(df):  # function 1-2-2
    numeric_df = df.select_dtypes(include=["int64", "float64"])
    for i in numeric_df.columns:
        print(i)
        print(f"max: {max(numeric_df['%s' % (i)])}")
        print(f"min: {min(numeric_df['%s' % (i)])}")
        print(find_outlier(numeric_df["%s" % (i)]))


def show_abnormal_scatter(df):  # function 1-3-1
    plt.scatter(df["Age"], df["RestingBP"])
    plt.title("age and RestingBP")
    plt.show()
    plt.scatter(df["Age"], df["Cholesterol"])
    plt.title("age and Cholesterol")
    plt.show()


def delete_abnormal_data_and_save(df):  # function 1-4
    df = df[df["RestingBP"] != 0]
    df = df[df["Cholesterol"] != 0]
    df.to_csv("HW2_cleaned_heart.csv", index=False)


df = pd.read_csv("HW2_cleaned_heart.csv")


def check_object_data(df):  # function 1-5
    object_df = df.select_dtypes(include=["object"])
    for classificationIndex in object_df.columns:
        print(
            object_df["%s" % (classificationIndex)]
            .astype("category")
            .value_counts()
            .reset_index(),
        )


def modify_data_and_save(df):  # function 1-6
    df.loc[df["ExerciseAngina"] == "N", "ExerciseAngina"] = 0
    df.loc[df["ExerciseAngina"] == "Y", "ExerciseAngina"] = 1
    df["ExerciseAngina"] = df["ExerciseAngina"].astype(int)
    df.loc[df["Sex"] == "F", "Sex"] = 0
    df.loc[df["Sex"] == "M", "Sex"] = 1
    df["Sex"] = df["Sex"].astype(int)
    df_dummies = pd.get_dummies(df, columns=["ChestPainType", "RestingECG", "ST_Slope"])
    df_dummies.to_csv("HW2_modified_heart.csv", index=False)
    df_dummies.info()


df = pd.read_csv("HW2_modified_heart.csv")


def age_number_plot(df):  # function 1-7-1
    df["Age Interval"] = df["Age"].apply(assign_age_interval)
    diseace_data = df.loc[(df["HeartDisease"] == 1)]
    diseace_data.loc[df["Sex"] == "M", "Sex"] = "Male with Heart Disease"
    diseace_data.loc[df["Sex"] == "F", "Sex"] = "Female with Heart Disease"

    sns.countplot(
        x="Age Interval",
        hue="Sex",
        hue_order=["M", "F"],
        data=df,
        order=age_interval,
        palette=["cyan", "pink"],
    ).set_ylim(0, 175)
    sns.countplot(
        x="Age Interval",
        hue="Sex",
        hue_order=["Male with Heart Disease", "Female with Heart Disease"],
        data=diseace_data,
        order=age_interval,
        palette=["blue", "red"],
    ).set_ylim(0, 175)
    plt.title("Age Interval and Heart Disease", fontsize=20, fontweight="bold")
    plt.xlabel("Age Interval")
    plt.ylabel("Number")
    plt.show()


def assign_age_interval(age):  # function 1-7-2
    if age >= 25 and age < 31:
        return age_interval[0]
    elif age >= 31 and age < 36:
        return age_interval[1]
    elif age >= 36 and age < 41:
        return age_interval[2]
    elif age >= 41 and age < 46:
        return age_interval[3]
    elif age >= 46 and age < 51:
        return age_interval[4]
    elif age >= 51 and age < 56:
        return age_interval[5]
    elif age >= 56 and age < 61:
        return age_interval[6]
    elif age >= 61 and age < 66:
        return age_interval[7]
    elif age >= 66 and age < 71:
        return age_interval[8]
    elif age >= 71 and age < 76:
        return age_interval[9]
    elif age >= 76 and age < 81:
        return age_interval[10]
    else:
        return "error"


# age_number_plot(df)
def heart_disease_plot(df, x, y):  # function 1-8
    heart_disease = df[df["HeartDisease"] == 1]
    no_heart_disease = df[df["HeartDisease"] == 0]
    plt.scatter(
        heart_disease[x],
        heart_disease[y],
        c="red",
        label="Heart Disease",
    )
    plt.scatter(
        no_heart_disease[x],
        no_heart_disease[y],
        c="blue",
        label="No Heart Disease",
    )
    plt.title(f"{x} and {y}")
    plt.xlabel(x)
    plt.ylabel(y)
    plt.legend()
    plt.show()


# heart_disease_plot(df, "RestingBP", "Cholesterol")
# heart_disease_plot(df, "MaxHR", "Oldpeak")
# heart_disease_plot(df, "RestingBP", "MaxHR")
# heart_disease_plot(df, "RestingBP", "Oldpeak")
# heart_disease_plot(df, "Cholesterol", "MaxHR")
# heart_disease_plot(df, "Cholesterol", "Oldpeak")


def descriptive_statistics(df):  # function 1-9
    numeric_df = df.select_dtypes(include=["int", "float"]).columns
    numeric_df = df.describe()
    numeric_df.to_csv("HW2_heart_descriptive_statistics.csv", index=False)


df = pd.read_csv("HW2_modified_heart.csv")


def generate_correlation_coefficient(df):  # function 1-10-1
    X = df.loc[:, :]
    corr_matrix_person = X.corr()
    corr_matrix_person["source"] = "person"
    merged_df = pd.concat([corr_matrix_person], axis=0)
    merged_df.to_csv("HW2_correlation_coefficient.csv", index=False)


def plot_heatmap2():  # function 1-10-2
    merged_df = pd.read_csv("HW2_correlation_coefficient.csv")
    numerical_corr = merged_df.drop(columns=["source"])
    plt.figure(figsize=(10, 8))
    sns.heatmap(numerical_corr, annot=True, cmap="coolwarm", fmt=".2f")
    plt.title("Correlation Heatmap")
    plt.show()


# generate_correlation_coefficient(df)
# plot_heatmap2()
