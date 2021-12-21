# arduino_csv_encoder

This code is to demonstrate how to encode two 15 different chars (8 bits) into one uint8_t. 
For example this code encode two of the following chars: 0 1 2 3 4 5 6 7 8 9 , . " - : into one uint8_t to reduce in half the size of a data string to transmit over a Lora module RFH95.

An example payload string is:

3,"19:41:38","12-18-2021",33.023270,-89.373413,2.13,217.70,5,2319,4.11,97.89,0,990.260,192.19,24.12,9.39,-0.67,-0.27,229.35,-36.95,72.08,0.00,0.01,-0.00,23.12,73.62,29.62,85.32,3759,27,43,40,29,99,26.66,988.58,207.26,27.22,32.00,359.94,0.31,93.19,-0.00,-0.00,0.00,0.01,0.04,0.07,-41.06,109.38,25.38,0.07,-9.74,-0.48,0.05,-9.79,-0.55
