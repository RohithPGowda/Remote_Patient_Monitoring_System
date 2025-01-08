# Remote_Patient_Monitoring_System
Project Description
This project integrates a Pulse Oximeter (MAX30100) sensor, an LM35 temperature sensor, and a Machine Learning (ML) model to monitor and predict vital health metrics such as heart rate (BPM), blood oxygen saturation (SpO2), blood pressure (BP), and body temperature. It combines hardware-based data acquisition with software-driven prediction and anomaly detection.

Hardware Implementation
Pulse Oximeter (MAX30100):

Measures heart rate (BPM) and blood oxygen saturation (SpO2).
Normalizes BPM values towards a typical range (e.g., 70-80 bpm) for enhanced reliability.
LM35 Temperature Sensor:

Captures ambient temperature data and converts it to body temperature readings with calibrated adjustments.
Outputs temperature in degrees Celsius.
Alert Mechanism:

An LED and buzzer are triggered if:
BPM is outside the normal range (e.g., <60 or >120 bpm).
SpO2 drops below a critical threshold (e.g., <80%).
Ensures real-time feedback on abnormal conditions.
Software Implementation
Arduino Code:

The Arduino script processes sensor readings and calculates derived metrics such as:
Systolic BP (SBP) and Diastolic BP (DBP) using an estimation formula based on BPM and SpO2.
Constrains BP values within realistic physiological ranges (e.g., SBP: 90-180 mmHg, DBP: 60-120 mmHg).
Provides continuous data monitoring and anomaly detection.
Machine Learning Model:

Trained a Support Vector Regressor (SVR) model to predict Systolic and Diastolic BP using real sensor data.
Steps involved:
Dataset Preparation:
Features: BPM and SpO2.
Targets: Systolic BP (SBP) and Diastolic BP (DBP).
Data Splitting:
Split into 80% training and 20% testing datasets.
Model Training:
Separate SVR models trained for SBP and DBP with an RBF kernel.
Evaluation:
Used Mean Squared Error (MSE) to evaluate model performance.
Predictions improve the reliability of BP measurements beyond formulaic calculations.
