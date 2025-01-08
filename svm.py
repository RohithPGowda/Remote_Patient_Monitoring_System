import pandas as pd
from sklearn.svm import SVR
from sklearn.model_selection import train_test_split
from sklearn.metrics import mean_squared_error

# Load the data from CSV file
df = pd.read_csv('sensor_data.csv')

# Features (input variables): BPM, SpO2
X = df[['BPM', 'SpO2']]

# Target variables (output): SystolicBP, DiastolicBP
y_systolic_bp = df['SystolicBP']
y_diastolic_bp = df['DiastolicBP']

# Split data into training and testing sets (80% training, 20% testing)
X_train, X_test, y_train_systolic_bp, y_test_systolic_bp = train_test_split(X, y_systolic_bp, test_size=0.2, random_state=42)
X_train, X_test, y_train_diastolic_bp, y_test_diastolic_bp = train_test_split(X, y_diastolic_bp, test_size=0.2, random_state=42)

# Train SVM models for Systolic BP and Diastolic BP
svm_systolic_bp = SVR(kernel='rbf')
svm_systolic_bp.fit(X_train, y_train_systolic_bp)

svm_diastolic_bp = SVR(kernel='rbf')
svm_diastolic_bp.fit(X_train, y_train_diastolic_bp)

# Predict on the test set
y_pred_systolic_bp = svm_systolic_bp.predict(X_test)
y_pred_diastolic_bp = svm_diastolic_bp.predict(X_test)

# Print the predictions
print("Predicted Systolic BP: ", y_pred_systolic_bp)
print("Predicted Diastolic BP: ", y_pred_diastolic_bp)

# Evaluate the model performance (Mean Squared Error)
mse_systolic_bp = mean_squared_error(y_test_systolic_bp, y_pred_systolic_bp)
mse_diastolic_bp = mean_squared_error(y_test_diastolic_bp, y_pred_diastolic_bp)

print(f"MSE for Systolic BP: {mse_systolic_bp}")
print(f"MSE for Diastolic BP: {mse_diastolic_bp}")