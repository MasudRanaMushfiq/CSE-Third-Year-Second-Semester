# Digital Signal Processing (DSP) LAB

A structured collection of Jupyter Notebooks covering core Digital Signal Processing concepts from scratch — organized into foundational practice, comprehensive lab exercises, lab test solutions, and previous year exam question solves.

---

## 📋 Table of Contents

- [Overview](#overview)
- [Project Structure](#project-structure)
- [Files Overview](#files-overview)
- [Prerequisites](#prerequisites)
- [Installation & Local Run](#installation--local-run)
- [Topics Covered](#topics-covered)
- [References](#references)

---

## Overview

This repository contains lab practice work for Our Rajshahi University Level DSP course. It is divided into four major sections:

- **DSP First Time Lab Practice** — introductory notebooks on core DSP building blocks
- **DSP All Topics Practices** — 12 comprehensive lab notebooks covering all major DSP topics
- **Lab Test Exam Solve** — solved scripts from 1st and 2nd lab test exams
- **Previous Year Lab Questions Solve** — previous year lab question solutions (1st & 2nd shift)

All implementations include manual (from-scratch) approaches alongside standard library verification, with Matplotlib visualizations throughout.

---

## Project Structure

```
DSP_First_Time_Lab_Practise/
│
├── DSP First Time Lab Practise/
│   ├── Continuous_Discrete_Signal.ipynb
│   ├── Convolution.ipynb
│   ├── Correlation.ipynb
│   ├── DFT_IDFT.ipynb
│   ├── Filter (Question Solve).ipynb
│   ├── Signa Sampling.ipynb
│   └── UnitStep UnitSample Ramp Signal.ipynb
│
├── DSP All Topics Practises/
│   ├── Lab01_Sampling_and_DFT.ipynb
│   ├── Lab02_Linear_Combination_and_FFT.ipynb
│   ├── Lab03_Convolution_and_Correlation.ipynb
│   ├── Lab04_Cross_Correlation_and_Delay.ipynb
│   ├── Lab05_DFT_Magnitude_and_Phase.ipynb
│   ├── Lab06_Convolution_Theorem_IDFT.ipynb
│   ├── Lab07_FIR_Filter_Design.ipynb
│   ├── Lab08_Noise_Filtering_Moving_Average.ipynb
│   ├── Lab09_FIR_Lowpass_Filter_Noisy_Signal.ipynb
│   ├── Lab10_Auto_and_Cross_Correlation.ipynb
│   ├── Lab11_FFT_Spectrum_Analysis.ipynb
│   ├── Lab12_Aliasing_and_Sampling_Theorem.ipynb
│   └── Practice_DSP_Fundamentals.ipynb
│
├── Lab Test Exam Solve/
│   ├── 1st LabTest Solve.ipynb
│   └── 2nd Lab Test Solve.ipynb
│
├── Previous Year Lab Questions Solve/
│   ├── 1st Shift Solve/
│   │   ├── 1No.ipynb
│   │   ├── 2No.ipynb
│   │   └── 3No.ipynb
│   └── 2nd Shift Solve/
│       ├── 1No.ipynb
│       ├── 2No.ipynb
│       └── 3No.ipynb
│
└── README.md
```

---

## Files Overview

### 🔰 DSP First Time Lab Practise

Introductory notebooks — the first hands-on implementations of core DSP concepts.

| File | Topic | Key Concepts |
|------|-------|--------------|
| `Continuous_Discrete_Signal.ipynb` | Continuous & Discrete Signals | Signal generation, continuous-to-discrete conversion, visualization |
| `Convolution.ipynb` | Convolution | Manual convolution, linear convolution of discrete sequences |
| `Correlation.ipynb` | Correlation | Signal similarity, correlation computation |
| `DFT_IDFT.ipynb` | DFT & IDFT | Discrete Fourier Transform, Inverse DFT, frequency domain representation |
| `Filter (Question Solve).ipynb` | Filter Design (Problem Set) | FIR filter design, frequency response, question-based problem solving |
| `Signa Sampling.ipynb` | Signal Sampling | Nyquist theorem, sampling rate, sampled signal reconstruction |
| `UnitStep UnitSample Ramp Signal.ipynb` | Elementary Signals | Unit step, unit sample (impulse), ramp signal generation |

---

### 📚 DSP All Topics Practises

Comprehensive lab notebooks covering all major DSP topics in depth.

| File | Topic | Key Concepts |
|------|-------|--------------|
| `Lab01_Sampling_and_DFT.ipynb` | Sampling & DFT | Continuous vs discrete signals, aliasing, DFT, IDFT, N-point DFT |
| `Lab02_Linear_Combination_and_FFT.ipynb` | Linear Combination & FFT | Linear superposition of signals, FFT-based computation, IFFT verification |
| `Lab03_Convolution_and_Correlation.ipynb` | Convolution & Correlation | Manual convolution, unit impulse, auto-correlation, cross-correlation |
| `Lab04_Cross_Correlation_and_Delay.ipynb` | Cross-Correlation & Signal Delay | Time delay detection, cross-correlation, manual convolution |
| `Lab05_DFT_Magnitude_and_Phase.ipynb` | DFT Magnitude & Phase Spectrum | Manual DFT, magnitude spectrum, phase spectrum, FFT comparison |
| `Lab06_Convolution_Theorem_IDFT.ipynb` | Convolution Theorem & IDFT | Convolution theorem, frequency-domain multiplication, IDFT reconstruction |
| `Lab07_FIR_Filter_Design.ipynb` | FIR Filter Design | Windowed-sinc FIR design, Hamming/Hanning window, frequency response |
| `Lab08_Noise_Filtering_Moving_Average.ipynb` | Noise Filtering | Moving average filter, differencing filter, noisy signal smoothing |
| `Lab09_FIR_Lowpass_Filter_Noisy_Signal.ipynb` | FIR Lowpass Filtering | Sinc-based FIR filter, noise removal, windowed design |
| `Lab10_Auto_and_Cross_Correlation.ipynb` | Correlation Analysis | Auto-correlation, cross-correlation between sine and square waves |
| `Lab11_FFT_Spectrum_Analysis.ipynb` | FFT Spectrum Analysis | FFT magnitude spectrum, multi-frequency signal analysis |
| `Lab12_Aliasing_and_Sampling_Theorem.ipynb` | Aliasing & Nyquist Theorem | Nyquist-Shannon theorem, aliasing demonstration, FFT analysis |
| `Practice_DSP_Fundamentals.ipynb` | Practice Notebook | Sine waves, convolution, correlation, DFT — all fundamentals |

---

### 🧪 Lab Test Exam Solve

Solved exam scripts from university lab tests.

| File | Description |
|------|-------------|
| `1st LabTest Solve.ipynb` | Complete solution to the 1st lab test exam questions |
| `2nd Lab Test Solve.ipynb` | Complete solution to the 2nd lab test exam questions |

---

### 📝 Previous Year Lab Questions Solve

Solutions to previous year lab examination questions, organized by shift.

| Folder | File | Description |
|--------|------|-------------|
| `1st Shift Solve/` | `1No.ipynb` | 1st Shift — Question 1 solution |
| `1st Shift Solve/` | `2No.ipynb` | 1st Shift — Question 2 solution |
| `1st Shift Solve/` | `3No.ipynb` | 1st Shift — Question 3 solution |
| `2nd Shift Solve/` | `1No.ipynb` | 2nd Shift — Question 1 solution |
| `2nd Shift Solve/` | `2No.ipynb` | 2nd Shift — Question 2 solution |
| `2nd Shift Solve/` | `3No.ipynb` | 2nd Shift — Question 3 solution |

---

## Prerequisites

- Python 3.8 or higher
- Jupyter Notebook or JupyterLab

### Required Python Packages

| Package | Purpose |
|---------|---------|
| `numpy` | Numerical computation, FFT, array operations |
| `matplotlib` | Signal and spectrum visualization |
| `scipy` | Signal processing utilities (filters, convolution) |

---

## Installation & Local Run

### 1. Clone the Repository

```bash
git clone https://github.com/your-username/DSP_First_Time_Lab_Practise.git
cd DSP_First_Time_Lab_Practise
```

### 2. (Recommended) Create a Virtual Environment

```bash
python -m venv venv

# On Windows
venv\Scripts\activate

# On macOS/Linux
source venv/bin/activate
```

### 3. Install Dependencies

```bash
pip install numpy matplotlib scipy jupyter
```

---

## Topics Covered

- **Signals & Systems** — Continuous vs discrete signals, unit impulse, unit step, ramp, signal generation
- **Sampling Theory** — Nyquist-Shannon theorem, aliasing, signal reconstruction
- **Fourier Analysis** — DFT, IDFT, FFT, magnitude and phase spectrum
- **Convolution** — Manual implementation, convolution theorem, frequency-domain multiplication
- **Correlation** — Auto-correlation, cross-correlation, time delay detection
- **FIR Filter Design** — Windowed-sinc method, Hamming/Hanning windows, lowpass filter
- **Noise Filtering** — Moving average, differencing filter, noisy signal smoothing
- **Exam Practice** — Lab test solutions, previous year question solves (1st & 2nd shift)

---

## References

1. **Proakis, J. G. & Manolakis, D. G.** — *Digital Signal Processing: Principles, Algorithms, and Applications*, 4th Edition. Pearson, 2006.
2. **NumPy FFT Documentation** — https://numpy.org/doc/stable/reference/routines.fft.html
3. **SciPy Signal Processing** — https://docs.scipy.org/doc/scipy/reference/signal.html
4. **Matplotlib Documentation** — https://matplotlib.org/stable/contents.html

---

## Author

> This lab work was completed as part of the DSP course, where concepts were first learned and then implemented from scratch.
> Special emphasis was given to manual implementations before verifying results using built-in functions.
> All work was carried out by **Masud Rana Mushfiq**.
---

## License

This project is for educational purposes. Feel free to reference or build upon it with attribution.
